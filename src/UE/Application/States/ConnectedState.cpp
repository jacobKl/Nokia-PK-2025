#include "ConnectedState.hpp"
#include "../Enums/ScreenType.hpp"
#include "ComposeSmsState.hpp"
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
            case NO_SCREEN:
                logger.logInfo("No screen selected");
                break;
        }
}
}
