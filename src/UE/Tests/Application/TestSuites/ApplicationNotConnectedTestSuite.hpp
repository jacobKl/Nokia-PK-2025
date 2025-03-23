#ifndef APPLICATION_NOT_CONNECTED_TEST_SUITE_HPP
#define APPLICATION_NOT_CONNECTED_TEST_SUITE_HPP

#include "ApplicationTestSuite.hpp"

namespace ue
{

struct ApplicationNotConnectedTestSuite : ApplicationTestSuite
{
    void sendAttachReqOnSibRecieve();
};

}

#endif
