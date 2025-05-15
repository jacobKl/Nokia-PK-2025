#include "BtsPort.hpp"
#include "Messages/IncomingMessage.hpp"
#include "Messages/OutgoingMessage.hpp"

namespace ue
{

BtsPort::BtsPort(common::ILogger &logger, common::ITransport &transport, common::PhoneNumber phoneNumber)
    : logger(logger, "[BTS-PORT]"),
      transport(transport),
      phoneNumber(phoneNumber)
{}

void BtsPort::start(IBtsEventsHandler &handler)
{
    transport.registerMessageCallback([this](BinaryMessage msg) {handleMessage(msg);});
    transport.registerDisconnectedCallback(([this]() { handleDisconnect(); }));
    this->handler = &handler;
}

void BtsPort::stop()
{
    transport.registerMessageCallback(nullptr);
    transport.registerDisconnectedCallback(nullptr);
    handler = nullptr;
}

void BtsPort::handleMessage(BinaryMessage msg)
{
    try
    {
        common::IncomingMessage reader{msg};
        auto msgId = reader.readMessageId();
        auto from = reader.readPhoneNumber();
        auto to = reader.readPhoneNumber();

        switch (msgId)
        {
            case common::MessageId::Sib:
            {
                auto btsId = reader.readBtsId();
                handler->handleSib(btsId);
                break;
            }
            case common::MessageId::AttachResponse:
            {
                bool accept = reader.readNumber<std::uint8_t>() != 0u;
                if (accept)
                    handler->handleAttachAccept();
                else
                    handler->handleAttachReject();
                break;
            }
            case common::MessageId::UnknownRecipient:
            case common::MessageId::CallRequest:
            {
                handler->handleCallMessage(msgId, from);
                break;
            }
            case common::MessageId::Sms:
            {
                std::string text = reader.readRemainingText();
                logger.logInfo("Received SMS from ", from, ": ", text);
                handler->handleSmsReceived(from, text);
                break;
            }
            default:
                logger.logError("Unknown message: ", msgId, ", from: ", from);

        }
    }
    catch (std::exception const& ex)
    {
        logger.logError("handleMessage error: ", ex.what());
    }
}

void BtsPort::sendSms(common::PhoneNumber sendTo, std::string message) {
    common::OutgoingMessage outgoingMessage = common::OutgoingMessage(common::MessageId::Sms,phoneNumber,sendTo);
    outgoingMessage.writeText(message);
    transport.sendMessage(outgoingMessage.getMessage());
}

void BtsPort::sendAttachRequest(common::BtsId btsId)
{
    logger.logDebug("sendAttachRequest: ", btsId);
    common::OutgoingMessage msg{common::MessageId::AttachRequest,
                                phoneNumber,
                                common::PhoneNumber{}};
    msg.writeBtsId(btsId);
    transport.sendMessage(msg.getMessage());


}

void BtsPort::handleDisconnect()
{
    handler->handleDisconnect();
}

void BtsPort::sendCallRequest(common::PhoneNumber to) {
    common::OutgoingMessage outgoingMessage = common::OutgoingMessage(common::MessageId::CallRequest, phoneNumber, to);
    transport.sendMessage(outgoingMessage.getMessage());
}

void BtsPort::sendCallAccept(common::PhoneNumber to)
{
    common::OutgoingMessage outgoingMessage = common::OutgoingMessage(common::MessageId::CallAccepted, phoneNumber, to);
    transport.sendMessage(outgoingMessage.getMessage());
}

void BtsPort::sendCallDropped(common::PhoneNumber to)
{
    common::OutgoingMessage outgoingMessage(common::MessageId::CallDropped, phoneNumber, to);
    transport.sendMessage(outgoingMessage.getMessage());
}
}
