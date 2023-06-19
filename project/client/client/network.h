#pragma once

#include <Poco/Net/SocketStream.h>

#include <cmn/message/message.h>
#include <cmn/cipher_engine/cipher_engine.h>

class Network {
public:
     Network(const std::string& serverAddress, int port);

     bool ConnectToServer(const std::string& clientName);

     void SendMessage(const Message& message);

     bool ReceiveMessage(std::string& msg);

private:
     bool KeyExchange(const std::string& clientName) noexcept;

     std::string serverAddress_;
     int port_;
     Poco::Net::StreamSocket socket_;
     CipherEngine ciph_;
};
