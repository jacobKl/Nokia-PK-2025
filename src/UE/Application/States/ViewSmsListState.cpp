#include "ViewSmsListState.hpp"
#include "ViewSmsState.hpp"
#include "Sms/SmsFormatter.hpp"

namespace ue {

    ViewSmsListState::ViewSmsListState(Context& context)
        : ConnectedState(context)
    {
        refreshList();
        context.user.smsSelectedCallback([this](std::size_t idx){ handleSmsSelected(idx); });
        context.user.rejectCallback([this](){ closeView(); });
    }

    void ViewSmsListState::handleSmsReceived(common::PhoneNumber /*from*/, const std::string& /*text*/)
    {
        refreshList();
    }

    void ViewSmsListState::refreshList()
    {
        if (context.messages.empty()) {
            context.user.showEmptySmsListView();
        } else {
            std::vector<std::string> items;
            items.reserve(context.messages.size());

            for (const Sms& sms : context.messages) {
                items.push_back(formatSmsLabel(sms, context.phoneNumber));
            }

            context.user.showSmsListView(items);
        }
    }

    void ViewSmsListState::handleSmsSelected(std::size_t index)
    {
        if (index < context.messages.size()) {
            context.setState<ViewSmsState>(index);
        } else {
            logger.logError("Invalid SMS index: ", index);
        }
    }

    void ViewSmsListState::closeView()
    {
        context.setState<ConnectedState>();
    }

}
