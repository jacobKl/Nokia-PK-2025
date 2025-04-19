#include "../Enums/ScreenType.hpp"
#include "ConnectedState.hpp"
#include "ComposeSmsState.hpp"
#include "DialState.hpp"

namespace ue
{

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
}
