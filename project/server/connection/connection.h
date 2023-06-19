#pragma once

#include <server/room/room.h>
#include <cmn/message/message.h>
#include <cmn/cipher_engine/cipher_engine.h>

#include <Poco/Net/TCPServerConnection.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketNotification.h>
#include <Poco/Observer.h>
#include <Poco/NotificationCenter.h>

#include <iostream>

class Connection : public Poco::Net::TCPServerConnection
{
public:
     Connection(const Poco::Net::StreamSocket& socket, std::shared_ptr<Room> room);

     void run();

private:
     std::shared_ptr<Client> AcceptConnection();

     std::shared_ptr<Room> room_;
     std::shared_ptr<CipherEngine> ciph_;
};