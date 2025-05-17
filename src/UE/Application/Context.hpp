#pragma once

#include "IEventsHandler.hpp"
#include "Logger/ILogger.hpp"
#include <memory>
#include <vector>
#include "Sms/Sms.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

struct Context
{
    common::ILogger& logger;
    IBtsPort& bts;
    IUserPort& user;
    ITimerPort& timer;
    std::unique_ptr<IEventsHandler> state{};

    common::PhoneNumber phoneNumber;
    common::PhoneNumber peerPhoneNumber;

    std::vector<Sms> messages;
    bool hasUnreadMessages = false;

    template <typename State, typename ...Arg>
    void setState(Arg&& ...arg)
    {
        state = std::make_unique<State>(*this, std::forward<Arg>(arg)...);
    }

    IEventsHandler* getState() const
    {
        return state.get();
    }
};

}
