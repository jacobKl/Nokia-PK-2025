#pragma once

#include "ConnectedState.hpp"

namespace ue {

    class ViewSmsState : public ConnectedState {
    public:
        ViewSmsState(Context& context, std::size_t smsIndex);
        ~ViewSmsState() override = default;

        std::string getName() const override { return "ViewSmsState"; }
    private:
        std::size_t smsIndex;
        void closeView();
    };

}
