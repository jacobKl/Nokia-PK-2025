#include "../Enums/ScreenType.hpp"

#include "TalkingState.hpp"
#include "ConnectedState.hpp"
#include "ComposeSmsState.hpp"
#include "DialState.hpp"
#include "TalkingState.hpp"

namespace ue
{

    std::string ConnectedState::getName() const { return "ConnectedState"; }

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    context.user.doubleClickCallback([this] { changeScreen();});
    context.user.showConnected();
}

    void ConnectedState::changeScreen() {
        switch (context.user.getScreenId()) {
            case COMPOSE_SMS_SCREEN:
                context.setState<ComposeSmsState>();
                break;
            case VIEW_SMS_SCREEN:
                logger.logInfo("Screen not implemented.");
                break;
            case MAKE_CALL_SCREEN:
                context.setState<DialState>();
                break;

            case NO_SCREEN:
                logger.logInfo("No screen selected");
                break;
        }
}

void ConnectedState::handleCallMessage(common::MessageId msgId, common::PhoneNumber from)
{
    if (msgId == common::MessageId::CallRequest)
    {
        logger.logInfo("Incoming call from ", to_string(from));
        context.user.showCallRequest(from);
        context.peerPhoneNumber = from;

        context.user.acceptCallback([this, from] {
            logger.logDebug("Accepting call from ", to_string(from));
            context.bts.sendCallAccept(from);
            context.setState<TalkingState>();
        });

        context.user.rejectCallback([this, from] {
            logger.logDebug("Rejecting call from ", to_string(from));
            context.bts.sendCallDropped(from);
            context.setState<ConnectedState>();
        });
    }
}


}
