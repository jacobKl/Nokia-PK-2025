#ifndef APPLICATION_SMS_RECEIVING_TEST_SUITE_HPP
#define APPLICATION_SMS_RECEIVING_TEST_SUITE_HPP

#include "ApplicationTestSuite.hpp"

namespace ue
{

class ApplicationSmsReceivingTestSuite : public ApplicationTestSuite
{
protected:
    void expectShowNewSms();
    void setupConnectedState();
};

}

#endif
