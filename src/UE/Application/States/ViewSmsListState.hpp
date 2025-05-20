#pragma once

#include "ConnectedState.hpp"

namespace ue {

class ViewSmsListState : public ConnectedState {
public:
    ViewSmsListState(Context& context);
    ~ViewSmsListState() override = default;

    std::string getName() const override { return "ViewSmsListState"; }

private:
    void handleSmsSelected(std::size_t index);
    void closeView();
};

}
