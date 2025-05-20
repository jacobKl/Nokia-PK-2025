#pragma once

#include "ConnectedState.hpp"
#include <string>

namespace ue {

class ViewSmsListState : public ConnectedState {
public:
    ViewSmsListState(Context& context);
    ~ViewSmsListState() override = default;

    std::string getName() const override { return "ViewSmsListState"; }

    void handleSmsReceived(common::PhoneNumber from, const std::string& text) override;
private:
    void handleSmsSelected(std::size_t index);
    void closeView();
    void refreshList();
};

}
