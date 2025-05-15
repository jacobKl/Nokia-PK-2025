#include "Sms.hpp"

namespace ue {

Sms::Sms(std::string text, const common::PhoneNumber &from, const common::PhoneNumber &to,
        const std::chrono::time_point<std::chrono::system_clock> &receiveTime)
    : text(std::move(text))
    , from(from)
    , to(to)
    , receiveTime(receiveTime)
    , isRead(false)
{
}

}
