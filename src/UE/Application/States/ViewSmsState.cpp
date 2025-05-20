#include "ViewSmsState.hpp"
#include "ViewSmsListState.hpp"
#include "Sms/SmsFormatter.hpp"

namespace ue {

ViewSmsState::ViewSmsState(Context& context, std::size_t smsIndex)
    : ConnectedState(context), smsIndex(smsIndex)
{
    if (smsIndex < context.messages.size()) {
        Sms& sms = context.messages[smsIndex];

        if (!sms.hasBeenRead()) {
            sms.markAsRead();
            bool anyNew = false;
            for (const Sms& m : context.messages) {
                if (!m.hasBeenRead()) { anyNew = true; break; }
            }
            context.hasUnreadMessages = anyNew;
        }

        context.user.showSmsView(sms.getText());
        context.user.rejectCallback([this](){ closeView(); });
    } else {
        logger.logError("Invalid SMS index: ", smsIndex);
        context.setState<ViewSmsListState>();
    }
}

void ViewSmsState::closeView()
{
    context.setState<ViewSmsListState>();
}

}
