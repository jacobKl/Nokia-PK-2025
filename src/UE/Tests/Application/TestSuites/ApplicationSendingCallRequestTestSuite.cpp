#include "ApplicationSendingCallRequestTestSuite.hpp"
#include "States/DialState.hpp"
#include "Messages/IncomingMessage.hpp"

namespace ue {
    void ApplicationSendingCallRequestTestSuite::setup()
    {
        EXPECT_CALL(userPortMock, activateDialMode()).WillRepeatedly(ReturnRef(mockDialMode));
        EXPECT_CALL(userPortMock, showConnected()).WillRepeatedly(Return());
        EXPECT_CALL(userPortMock, doubleClickCallback(_)).WillRepeatedly(Return());
        EXPECT_CALL(userPortMock, homeCallback(_)).WillRepeatedly(Return());
        EXPECT_CALL(userPortMock, acceptCallback(_)).WillRepeatedly(Return());
        EXPECT_CALL(userPortMock, rejectCallback(_)).WillRepeatedly(Return());
    }

    void ApplicationSendingCallRequestTestSuite::sendSetup(common::PhoneNumber testNumber)
    {
        EXPECT_CALL(userPortMock, activateDialMode()).WillOnce(ReturnRef(mockDialMode));
        EXPECT_CALL(mockDialMode, getPhoneNumber()).WillRepeatedly(Return(testNumber));
        EXPECT_CALL(btsPortMock, sendCallRequest(testNumber)).Times(1);
        EXPECT_CALL(timerPortMock, startTimer(_)).Times(1);
        EXPECT_CALL(timerPortMock, stopTimer()).Times(1);
    } 

    // SUNNY DAY SCENARIO
    TEST_F(ApplicationSendingCallRequestTestSuite, shallHandleBtsCallAccepted)
    {   
        this->setup();

        common::PhoneNumber testNumber{211};
        sendSetup(testNumber);

        objectUnderTest.getContext().setState<DialState>();
        auto state = objectUnderTest.getContext().getState();
        auto dialState = dynamic_cast<DialState*>(state);

        dialState->sendCallRequest();
        dialState->handleCallMessage(common::MessageId::CallAccepted, testNumber);

        EXPECT_EQ(objectUnderTest.getStateName(), "TalkingState");
    }

    TEST_F(ApplicationSendingCallRequestTestSuite, shallHandleBtsCallDrop)
    {
        this->setup();

        common::PhoneNumber testNumber{211};
        sendSetup(testNumber);

        EXPECT_CALL(userPortMock, showCallDropped()).Times(1);

        objectUnderTest.getContext().setState<DialState>();
        auto state = objectUnderTest.getContext().getState();
        auto dialState = dynamic_cast<DialState*>(state);

        dialState->sendCallRequest();
        dialState->handleCallMessage(common::MessageId::CallDropped, testNumber);

        EXPECT_EQ(objectUnderTest.getStateName(), "ConnectedState");
    }

    TEST_F(ApplicationSendingCallRequestTestSuite, shallHandleBtsCallUnknownRecipient)
    {
        this->setup();

        common::PhoneNumber testNumber{211};
        sendSetup(testNumber);

        EXPECT_CALL(userPortMock, showPeerUserNotAvailable(testNumber)).Times(1);

        objectUnderTest.getContext().setState<DialState>();
        auto state = objectUnderTest.getContext().getState();
        auto dialState = dynamic_cast<DialState*>(state);

        dialState->sendCallRequest();
        dialState->handleCallMessage(common::MessageId::UnknownRecipient, testNumber);

        EXPECT_EQ(objectUnderTest.getStateName(), "ConnectedState");
    }

    TEST_F(ApplicationSendingCallRequestTestSuite, shallHandleBtsCallTimeout)
    {
        this->setup();

        common::PhoneNumber testNumber{211};
        sendSetup(testNumber);

        EXPECT_CALL(userPortMock, showCallTimeout()).Times(1);

        objectUnderTest.getContext().setState<DialState>();
        auto state = objectUnderTest.getContext().getState();
        auto dialState = dynamic_cast<DialState*>(state);

        dialState->sendCallRequest();

        dialState->handleTimeout();

        EXPECT_EQ(objectUnderTest.getStateName(), "ConnectedState");
    }


    TEST_F(ApplicationSendingCallRequestTestSuite, shallHandleBtsCallReject)
    {
        this->setup();

        common::PhoneNumber fromNumber{111};
        common::PhoneNumber testNumber{211};
        sendSetup(testNumber);

        EXPECT_CALL(btsPortMock, sendCallDropped(_)).Times(1);

        objectUnderTest.getContext().setState<DialState>();
        auto state = objectUnderTest.getContext().getState();
        auto dialState = dynamic_cast<DialState*>(state);

        dialState->sendCallRequest();

        dialState->handleReject(fromNumber);

        EXPECT_EQ(objectUnderTest.getStateName(), "ConnectedState");
    }
}
