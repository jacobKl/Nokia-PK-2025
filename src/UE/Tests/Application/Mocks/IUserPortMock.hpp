#pragma once

#include <gmock/gmock.h>
#include "Ports/IUserPort.hpp"

namespace ue
{

class IUserEventsHandlerMock : public IUserEventsHandler
{
public:
    IUserEventsHandlerMock();
    ~IUserEventsHandlerMock() override;

};

class IUserPortMock : public IUserPort
{
public:
    IUserPortMock();
    ~IUserPortMock() override;

    MOCK_METHOD(void, showNotConnected, (), (final));
    MOCK_METHOD(void, showConnecting, (), (final));
    MOCK_METHOD(void, showConnected, (), (final));
    MOCK_METHOD(void, showPeerUserNotAvailable, (common::PhoneNumber), (override));

    MOCK_METHOD(void, acceptCallback, (IUeGui::Callback), (override));
    MOCK_METHOD(void, rejectCallback, (IUeGui::Callback), (override));
    MOCK_METHOD(void, doubleClickCallback, (IUeGui::Callback), (override));
    MOCK_METHOD(void, homeCallback, (IUeGui::Callback), (override));

    MOCK_METHOD(int, getScreenId, (), (override));
    MOCK_METHOD(IUeGui::ISmsComposeMode&, activateComposeMode, (), (override));
    MOCK_METHOD(IUeGui::IDialMode&, activateDialMode, (), (override));
};

}
