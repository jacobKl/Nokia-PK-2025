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
        common::PhoneNumber recipient = iSmsComposeMode.getPhoneNumber();
        std::string text = iSmsComposeMode.getSmsText();
        
        context.bts.sendSms(recipient, text);
        
        Sms sentSms(text, context.phoneNumber, recipient);
        sentSms.markAsRead(); // since we are sending it
        context.messages.push_back(sentSms);
        
        // More advanced log for debug purposes
        logger.logInfo("Current SMS database contains ", context.messages.size(), " messages:");
        for (size_t i = 0; i < context.messages.size(); ++i) {
            const auto& sms = context.messages[i];
            std::string status = sms.hasBeenRead() ? "read" : "unread";
            logger.logInfo("  [", i+1, "] From: ", sms.getFrom(), " | Status: ", status, " | Text: ", sms.getText());
        }
        
        context.setState<ConnectedState>();
    }

}