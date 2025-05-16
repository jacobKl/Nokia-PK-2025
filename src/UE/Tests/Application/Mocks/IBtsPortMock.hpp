#pragma once

#include <gmock/gmock.h>
#include "Ports/IBtsPort.hpp"

namespace ue
{

class IBtsEventsHandlerMock : public IBtsEventsHandler
{
public:
    IBtsEventsHandlerMock();
    ~IBtsEventsHandlerMock() override;

    MOCK_METHOD(void, handleSib, (common::BtsId), (final));
    MOCK_METHOD(void, handleAttachAccept, (), (final));
    MOCK_METHOD(void, handleAttachReject, (), (final));
    MOCK_METHOD(void, handleDisconnect, (), (final));
    MOCK_METHOD(void, handleCallMessage, (common::MessageId msgId, common::PhoneNumber from), (override));
    MOCK_METHOD(void, handleCallReceive, (common::MessageId msgId, common::PhoneNumber from), (override));
};

class IBtsPortMock : public IBtsPort
{
public:
    IBtsPortMock();
    ~IBtsPortMock() override;

    MOCK_METHOD(void, sendAttachRequest, (common::BtsId), (final));
    MOCK_METHOD(void, sendSms, (common::PhoneNumber, std::string), (override));
    MOCK_METHOD(void, sendCallRequest, (common::PhoneNumber), (override));
    MOCK_METHOD(void, sendCallAccept, (common::PhoneNumber), (override));
    MOCK_METHOD(void, sendCallDropped, (common::PhoneNumber), (override));  
};

}
