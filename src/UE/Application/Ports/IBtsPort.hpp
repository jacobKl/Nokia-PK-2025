#pragma once

#include "Messages/BtsId.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Messages/IncomingMessage.hpp"

namespace ue
{

class IBtsEventsHandler
{
public:
    virtual ~IBtsEventsHandler() = default;

    virtual void handleSib(common::BtsId) = 0;
    virtual void handleAttachAccept() = 0;
    virtual void handleAttachReject() = 0;
    virtual void handleDisconnect() = 0;
    virtual void handleCallMessage(common::MessageId msgId, common::PhoneNumber from) = 0;
    virtual void handleCallReceive(common::MessageId msgId, common::PhoneNumber from) = 0;
};

class IBtsPort
{
public:
    virtual ~IBtsPort() = default;

    virtual void sendAttachRequest(common::BtsId) = 0;
    virtual void sendSms(common::PhoneNumber, std::string) = 0;
    virtual void sendCallRequest(common::PhoneNumber) = 0;
    virtual void sendCallAccept(common::PhoneNumber) = 0;
    virtual void sendCallDropped(common::PhoneNumber to) = 0;
};

}
