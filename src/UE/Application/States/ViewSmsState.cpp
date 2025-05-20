#include "ViewSmsState.hpp"
#include "ViewSmsListState.hpp"

namespace ue {

ViewSmsState::ViewSmsState(Context& context, std::size_t smsIndex)
    : ConnectedState(context), smsIndex(smsIndex)
{
    logger.logInfo("Entering ViewSmsState, SMS #", smsIndex+1);
    if (smsIndex < context.messages.size()) {
        auto& sms = context.messages[smsIndex];
        if (!sms.hasBeenRead()) {
            sms.markAsRead();

            bool anyNew = false;
            for (auto &m : context.messages) {
                if (!m.hasBeenRead()) { anyNew = true; break; }
            }
            context.hasUnreadMessages = anyNew;
        }
        context.user.showSmsView(std::to_string(sms.getFrom().value), sms.getText());
        context.user.rejectCallback([this](){ closeView(); });
    } else {
        logger.logError("Invalid SMS index: ", smsIndex);
        context.setState<ViewSmsListState>();
    }
}

void ViewSmsState::closeView() {
    context.setState<ViewSmsListState>();
}

}
