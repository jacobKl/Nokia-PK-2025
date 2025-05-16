#ifndef APPLICATION_SENDING_CALL_REQUEST_TEST_SUITE_HPP
#define APPLICATION_SENDING_CALL_REQUEST_TEST_SUITE_HPP

#include "ApplicationTestSuite.hpp"
#include "UeGui/IDialMode.hpp"


namespace ue
{

class MockIDialMode : public IUeGui::IDialMode {
    public:
        MOCK_METHOD(PhoneNumber, getPhoneNumber, (), (const, override));
};

struct ApplicationSendingCallRequestTestSuite : ApplicationTestSuite
{
    protected: 
        void setup();
        MockIDialMode mockDialMode;
        void sendSetup(common::PhoneNumber testNumber);
};

}

#endif
