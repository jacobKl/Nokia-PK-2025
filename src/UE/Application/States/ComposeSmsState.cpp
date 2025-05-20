#include "ComposeSmsState.hpp"

namespace ue {

    std::string ComposeSmsState::getName() const { return "ComposeSmsState"; }

    ComposeSmsState::ComposeSmsState(Context &context) :
            ConnectedState(context),
            iSmsComposeMode(context.user.activateComposeMode()) {
        context.user.rejectCallback([this]{ this->context.user.showConnected(); });
        context.user.homeCallback([this]{ this->context.user.showConnected(); });
        context.user.acceptCallback([this]{ sendSms(); });
    }

    void ComposeSmsState::sendSms() {
        common::PhoneNumber recipient = iSmsComposeMode.getPhoneNumber();
        std::string text = iSmsComposeMode.getSmsText();
        
        context.bts.sendSms(recipient, text);
        
        Sms sentSms(text, context.phoneNumber, recipient);
        sentSms.markAsRead(); // since we are sending it
        context.messages.push_back(sentSms);
        
        context.setState<ConnectedState>();
    }

}