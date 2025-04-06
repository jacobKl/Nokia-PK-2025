#include "ComposeSmsState.hpp"

namespace ue {

    ComposeSmsState::ComposeSmsState(Context &context) :
            ConnectedState(context),
            iSmsComposeMode(context.user.activateComposeMode()) {
        context.user.rejectCallback([this]{ this->context.user.showConnected(); });
        context.user.homeCallback([this]{ this->context.user.showConnected(); });
        context.user.acceptCallback([this]{ sendSms(); });
    }

    void ComposeSmsState::sendSms() {
        context.bts.sendSms(iSmsComposeMode.getPhoneNumber(), iSmsComposeMode.getSmsText());
        context.setState<ConnectedState>();
    }

}