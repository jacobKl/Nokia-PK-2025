#include "BaseState.hpp"
#include "NotConnectedState.hpp"

namespace ue
{

    std::string BaseState::getName() const { return "BaseState"; }

    BaseState::BaseState(Context &context, const std::string &name)
        : context(context),
        logger(context.logger, "[" + name + "]")
    {
        logger.logDebug("entry");
    }

    BaseState::~BaseState()
    {
        logger.logDebug("exit");
    }

    void BaseState::handleTimeout()
    {
        logger.logError("Uexpected: handleTimeout");
    }

    void BaseState::handleSib(common::BtsId btsId)
    {
        logger.logError("Uexpected: handleSib: ", btsId);
    }

    void BaseState::handleAttachAccept()
    {
        logger.logError("Uexpected: handleAttachAccept");
    }

    void BaseState::handleAttachReject()
    {
        logger.logError("Uexpected: handleAttachReject");
    }

    void BaseState::handleDisconnect() 
    {
        logger.logError("BaseState: handling BTS Disconnect.");
        context.setState<NotConnectedState>();
    }

    void BaseState::handleCallMessage(common::MessageId msgId, common::PhoneNumber from)
    {
        logger.logInfo("BaseState: call message incoming from ", to_string(from), ", msgId=", static_cast<int>(msgId));
    }

    void BaseState::handleCallReceive(common::MessageId msgId, common::PhoneNumber from)
    {
        logger.logError("BaseState: handling receving call.");
    }
}
