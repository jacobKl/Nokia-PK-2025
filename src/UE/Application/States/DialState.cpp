#include "DialState.hpp"

using namespace std::chrono_literals;

namespace ue {

    DialState::DialState(Context &context) : ConnectedState(context), iDialMode(context.user.activateDialMode())
    {
        context.user.homeCallback([this]{ this->context.user.showConnected(); });
        context.user.acceptCallback([this]{ sendCallRequest(); });
    }

    void DialState::sendCallRequest() {
        logger.logDebug("[DialState] Sending call request to: ", iDialMode.getPhoneNumber());

        context.bts.sendCallRequest(iDialMode.getPhoneNumber());
        
        context.timer.startTimer(1000ms);
    }

    void DialState::handleUnknownRecipient() {
        context.timer.stopTimer();
        context.setState<ConnectedState>();
        context.user.showPeerUserNotAvailable(iDialMode.getPhoneNumber());
    }

    void DialState::handleTimeout() {
        printf("[DialState] handle timeout.\n");
    }
}