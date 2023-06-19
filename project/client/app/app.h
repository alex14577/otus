#pragma once

#include <Poco/Types.h>

#include <string>
#include <thread>
#include <chrono>

#include <client/client/network.h>
#include <client/client/ui.h>
#include <cmn/message/message.h>

using namespace std::chrono_literals;

class ClientApp {
public:
     bool Run(const std::string& address, Poco::UInt16 port, const std::string& clientName);
};