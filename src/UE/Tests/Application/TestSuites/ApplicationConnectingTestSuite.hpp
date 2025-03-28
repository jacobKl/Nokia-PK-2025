#ifndef APPLICATION_CONNECTING_TEST_SUITE_HPP
#define APPLICATION_CONNECTING_TEST_SUITE_HPP

#include "ApplicationNotConnectedTestSuite.hpp"

namespace ue
{

struct ApplicationConnectingTestSuite : ApplicationNotConnectedTestSuite
{
    ApplicationConnectingTestSuite()
    {
        sendAttachReqOnSibRecieve();
    }
};

}

#endif
