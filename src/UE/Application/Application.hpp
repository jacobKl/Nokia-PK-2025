#pragma once

#include "Logger/PrefixedLogger.hpp"
#include "Messages/PhoneNumber.hpp"
#include "IEventsHandler.hpp"
#include "Context.hpp"
#include "Messages/IncomingMessage.hpp"
#include "States/NotConnectedState.hpp"

namespace ue
{

using common::PhoneNumber;
using common::ILogger;

class Application : public IEventsHandler
{
public:
    Application(PhoneNumber phoneNumber,
                ILogger& iLogger,
                IBtsPort& bts,
                IUserPort& user,
                ITimerPort& timer);
    ~Application();

    // ITimerEventsHandler interface
    void handleTimeout() override;

    // IBtsEventsHandler interface
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleDisconnect() override;
    void handleCallMessage(common::MessageId msgId, common::PhoneNumber from) override;
    void handleCallReceive(common::MessageId msgId, common::PhoneNumber from) override;
    void handleSmsReceived(common::PhoneNumber from, const std::string& text) override;

    Context& getContext();
    std::string getStateName();

private:
    Context context;
    common::PrefixedLogger logger;

};

}
