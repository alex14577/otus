#pragma once

#include <cmn/message/message.h>
#include <cmn/cipher_engine/cipher_engine.h>

#include <string>
#include <Poco/Net/StreamSocket.h>

class Client
{
public:
    Client(const std::string& name, Poco::Net::StreamSocket& socket, 
        std::shared_ptr<CipherEngine> ciph);

    const std::string& GetName() const;

    void SendMessage(const Message& message);

private:
    std::string name_;
    Poco::Net::StreamSocket socket_;
    std::shared_ptr<CipherEngine> ciph_;
};