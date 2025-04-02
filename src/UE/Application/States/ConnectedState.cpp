#include "ConnectedState.hpp"
#include "../Enums/ScreenType.hpp"
#include "ComposeSmsState.hpp"
namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    context.user.acceptCallback([this] { showSmsButton();});
    context.user.showConnected();
}

    void ConnectedState::showSmsButton() {
    logger.logInfo("Wywołuje sie");
        switch (context.user.getScreenId()) {
            case COMPOSE_SMS_SCREEN:
                context.setState<ComposeSmsState>();
                break;
            case VIEW_SMS_SCREEN:
                break;
        }
}
}
