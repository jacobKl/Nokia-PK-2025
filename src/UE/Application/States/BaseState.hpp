#pragma once

#include "IEventsHandler.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "Context.hpp"
#include "Messages/IncomingMessage.hpp"

namespace ue
{

class BaseState : public IEventsHandler
{
public:
    BaseState(Context& context, const std::string& name);
    ~BaseState() override;

    virtual std::string getName() const = 0;

    // ITimerEventsHandler interface
    void handleTimeout() override;

    // IBtsEventsHandler interface
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleDisconnect() override;
    void handleCallMessage(common::MessageId msgId, common::PhoneNumber from) override;
    void handleCallReceive(common::MessageId msgId, common::PhoneNumber from) override;
    void handleCallTalk(common::PhoneNumber from, const std::string& text) override;
    void handleSmsReceived(common::PhoneNumber from, const std::string& text) override;

protected:
    Context& context;
    common::PrefixedLogger logger;
};

}
