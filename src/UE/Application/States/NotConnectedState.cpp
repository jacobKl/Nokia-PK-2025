#include "NotConnectedState.hpp"
#include "ConnectingState.hpp"

using namespace std::chrono_literals;
namespace ue
{
    std::string NotConnectedState::getName() const { return "NotConnectedState"; }

    NotConnectedState::NotConnectedState(Context &context)
        : BaseState(context, "NotConnectedState")
    {
        context.user.showNotConnected();
    }

    void NotConnectedState::handleSib(common::BtsId btsId)
    {
        context.bts.sendAttachRequest(btsId);
        context.timer.startTimer(500ms);
        context.setState<ConnectingState>();
    }

}