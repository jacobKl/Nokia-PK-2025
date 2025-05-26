#include "ApplicationCallDropTestSuite.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <chrono>
using namespace std::chrono_literals;

class MockCallManager {
public:
    MOCK_METHOD(void, dropCall, (int callId), ());
    MOCK_METHOD(bool, isCallActive, (int callId), ());
};

TEST(ApplicationCallDropTestSuite, DropCallSuccessfully) {
    MockCallManager mockCallManager;
    int callId = 1;

    EXPECT_CALL(mockCallManager, isCallActive(callId))
        .WillOnce(::testing::Return(true));
    EXPECT_CALL(mockCallManager, dropCall(callId))
        .Times(1);

    if (mockCallManager.isCallActive(callId)) {
        mockCallManager.dropCall(callId);
    }
}

TEST(ApplicationCallDropTestSuite, DropCallWhenNotActive) {
    MockCallManager mockCallManager;
    int callId = 2;

    EXPECT_CALL(mockCallManager, isCallActive(callId))
        .WillOnce(::testing::Return(false));
    EXPECT_CALL(mockCallManager, dropCall(callId))
        .Times(0);

    if (mockCallManager.isCallActive(callId)) {
        mockCallManager.dropCall(callId);
    }
}

namespace ue
{
    void ApplicationCallDropTestSuite::setupConnectedAndInCallMode(const common::PhoneNumber& phoneNumber)
    {
        EXPECT_CALL(userPortMock, showNotConnected());
        EXPECT_CALL(btsPortMock, sendAttachRequest(BTS_ID));
        EXPECT_CALL(timerPortMock, startTimer(500ms));
        EXPECT_CALL(userPortMock, showConnecting());
        objectUnderTest.handleSib(BTS_ID);
        
        EXPECT_CALL(timerPortMock, stopTimer());
        EXPECT_CALL(userPortMock, showConnected());
        objectUnderTest.handleAttachAccept();
        
        EXPECT_CALL(userPortMock, showCallRequest(phoneNumber));
        objectUnderTest.handleCallReceive(common::MessageId::CallTalk, phoneNumber);
    }

    TEST_F(ApplicationCallDropTestSuite, shallSendCallDroppedWhenUserHangsUp)
    {
        common::PhoneNumber phoneNumber{123};
        setupConnectedAndInCallMode(phoneNumber);
        
        std::function<void()> acceptCallback;
        std::function<void()> rejectCallback;
        
        EXPECT_CALL(userPortMock, showCallRequest(phoneNumber));
        EXPECT_CALL(userPortMock, acceptCallback(_))
            .WillOnce(::testing::SaveArg<0>(&acceptCallback));
        EXPECT_CALL(userPortMock, rejectCallback(_))
            .WillOnce(::testing::SaveArg<0>(&rejectCallback));
            
        EXPECT_CALL(btsPortMock, sendCallAccept(phoneNumber));
        EXPECT_CALL(btsPortMock, sendCallDropped(phoneNumber));
        EXPECT_CALL(userPortMock, showConnected());
        
        if (acceptCallback) acceptCallback();
        if (rejectCallback) rejectCallback();
    }
    
    TEST_F(ApplicationCallDropTestSuite, shallShowConnectedWhenPeerDropsCall)
    {
        common::PhoneNumber phoneNumber{123};
        setupConnectedAndInCallMode(phoneNumber);
        
        std::function<void()> acceptCallback;
        
        EXPECT_CALL(userPortMock, showCallRequest(phoneNumber));
        EXPECT_CALL(userPortMock, acceptCallback(_))
            .WillOnce(::testing::SaveArg<0>(&acceptCallback));
            
        EXPECT_CALL(btsPortMock, sendCallAccept(phoneNumber));
        EXPECT_CALL(userPortMock, showConnected());
        
        if (acceptCallback) acceptCallback();
        objectUnderTest.handleCallMessage(common::MessageId::CallDropped, phoneNumber);
    }
}