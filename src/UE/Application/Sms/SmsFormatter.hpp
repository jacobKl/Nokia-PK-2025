#pragma once

#include "Sms/Sms.hpp"
#include "Messages/PhoneNumber.hpp"
#include <string>

namespace ue {

    /// Formats a single SMS for the list: “[status] To:/From: <number>”
    inline std::string formatSmsLabel(const Sms& sms, const common::PhoneNumber& me) {
        std::string status = sms.hasBeenRead() ? "read" : "NEW";
        bool outgoing = (sms.getFrom() == me);
        common::PhoneNumber other = outgoing ? sms.getTo() : sms.getFrom();
        std::string prefix = outgoing ? "To: " : "From: ";
        return "[" + status + "] " + prefix + std::to_string(other.value);
    }

}
