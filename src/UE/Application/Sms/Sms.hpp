#pragma once
#include <Messages/PhoneNumber.hpp>
#include <chrono>


class Sms {

private:
    std::string text;
    common::PhoneNumber from;
    common::PhoneNumber to;
    std::chrono::time_point <std::chrono::system_clock> receiveTime;
public:
    Sms();

    Sms(std::string text, const common::PhoneNumber &from, const common::PhoneNumber &to,
        const std::chrono::time_point<std::chrono::system_clock> &receiveTime = std::chrono::system_clock::now());
};


