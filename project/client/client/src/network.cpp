#include <client/client/network.h>

#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/StreamCopier.h>

#include <iostream>

Network::Network(const std::string& serverAddress, int port) 
     : serverAddress_(serverAddress), port_(port) 
{
     ciph_.Init();
}

bool Network::ConnectToServer(const std::string& clientName) 
{
     try 
     {
          Poco::Net::SocketAddress serverSocketAddress(serverAddress_, port_);
          socket_.connect(serverSocketAddress);
          return KeyExchange(clientName);
     } 
     catch (const Poco::Exception& exc) 
     {
          std::cerr << "Failed to connect to server: " << exc.displayText() << std::endl;
          return -1;
     }
}

void Network::SendMessage(const Message& message) 
{
     try 
     {
          auto out = ciph_.EncryptMessage(message.ToString());
          Poco::Net::SocketStream socketStream(socket_);
          socketStream << out;
     } 
     catch (const Poco::Exception& exc) 
     {
          std::cerr << "Failed to send message: " << exc.displayText() << std::endl;
     }
}

bool Network::ReceiveMessage(std::string& msg) 
{
     try 
     {
          socket_.setBlocking(true);
          char buffer[1024]{};
          auto c = socket_.receiveBytes(buffer, sizeof(buffer));
          if(c)
          {
               msg = ciph_.DecryptMessage(std::string(buffer, c));
               return true;
          }
     } 
     catch (const Poco::Exception& exc) 
     {
          std::cerr << "Failed to receive message: " << exc.displayText() << std::endl;
     }
     return false;
}

bool Network::KeyExchange(const std::string& clientName) noexcept
{
     auto key = ciph_.GetPubKey();
     auto msgRawWithKey = Message(clientName, key).ToString();
     socket_.sendBytes(msgRawWithKey.data(), msgRawWithKey.size());

     char buf[1024]{};
     auto c = socket_.receiveBytes(buf, sizeof(buf));
     if(c)
     {
          Message msg(buf);
          ciph_.AddOtherPubKey(msg.GetText());
          return true;
     }
     return false;
}