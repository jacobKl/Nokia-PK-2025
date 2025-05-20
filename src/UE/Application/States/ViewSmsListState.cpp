#include "ViewSmsListState.hpp"
#include "ViewSmsState.hpp"

namespace ue {

    ViewSmsListState::ViewSmsListState(Context& context)
        : ConnectedState(context)
    {
        logger.logInfo("Entering ViewSmsList state");
        if (context.messages.empty()) {
            context.user.showEmptySmsListView();
        } else {
            std::vector<std::string> items;
            for (size_t i = 0; i < context.messages.size(); ++i) {
                const auto& sms = context.messages[i];
                std::string status = sms.hasBeenRead() ? "read" : "NEW";
                items.push_back("[" + status + "] From: " + std::to_string(sms.getFrom().value));
            }
            context.user.showSmsListView(items);
        }
        context.user.smsSelectedCallback([this](size_t idx){ handleSmsSelected(idx); });
        context.user.rejectCallback([this](){ closeView(); });
    }

    void ViewSmsListState::handleSmsSelected(std::size_t index) {
        if (index < context.messages.size()) {
            context.setState<ViewSmsState>(index);
        } else {
            logger.logError("Invalid SMS index: ", index);
        }
    }

    void ViewSmsListState::closeView() {
        context.setState<ConnectedState>();
    }

}
