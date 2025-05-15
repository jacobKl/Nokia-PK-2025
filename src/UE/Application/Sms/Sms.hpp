#pragma once
#include <Messages/PhoneNumber.hpp>
#include <chrono>
#include <string>

namespace ue {

class Sms {
private:
    std::string text;
    common::PhoneNumber from;
    common::PhoneNumber to;
    std::chrono::time_point<std::chrono::system_clock> receiveTime;
    bool isRead{false};

public:
    Sms() = default;

    Sms(std::string text, const common::PhoneNumber &from, const common::PhoneNumber &to,
        const std::chrono::time_point<std::chrono::system_clock> &receiveTime = std::chrono::system_clock::now())
        : text(std::move(text))
        , from(from)
        , to(to)
        , receiveTime(receiveTime)
        , isRead(false)
    {
    }
    
    const std::string& getText() const { return text; }
    const common::PhoneNumber& getFrom() const { return from; }
    const common::PhoneNumber& getTo() const { return to; }
    const std::chrono::time_point<std::chrono::system_clock>& getReceiveTime() const { return receiveTime; }
    
    bool hasBeenRead() const { return isRead; }
    void markAsRead() { isRead = true; }
};

}


