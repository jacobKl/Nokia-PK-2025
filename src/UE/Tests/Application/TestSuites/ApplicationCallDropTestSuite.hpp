#ifndef APPLICATION_CALL_DROP_TEST_SUITE_HPP
#define APPLICATION_CALL_DROP_TEST_SUITE_HPP

#include "ApplicationTestSuite.hpp"

namespace ue
{

struct ApplicationCallDropTestSuite : ApplicationTestSuite
{
    void setupConnectedAndInCallMode(const common::PhoneNumber& phoneNumber);
};

}

#endif