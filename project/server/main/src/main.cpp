#include <Poco/Net/TCPServer.h>
#include <Poco/Net/TCPServerParams.h>
#include <Poco/Net/TCPServerConnectionFactory.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Thread.h>
#include <iostream>
#include <string>
#include <vector>
#include <server/room/room.h>
#include <server/connection/connection.h>

class ConnectionFactory : public Poco::Net::TCPServerConnectionFactory
{
public:
     ConnectionFactory(std::shared_ptr<Room> room) :
          room_(room)
     {
          
     }

     Poco::Net::TCPServerConnection* createConnection(const Poco::Net::StreamSocket& socket)
     {
          std::cout << "client connected:" << socket.address() << std::endl;   
          return new Connection(socket, room_);
     }
private:
     std::shared_ptr<Room> room_;
};

class Server
{
public:
     Server(const std::string& address, Poco::UInt16 port) : 
          address_(address), 
          port_(port)
     {
          params_ = new Poco::Net::TCPServerParams();
          params_->setMaxThreads(4);
          params_->setMaxQueued(16);
     }

     void start()
     {
          try
          {
               Poco::Net::ServerSocket socket(Poco::Net::SocketAddress(address_, port_));
               Poco::Net::TCPServer server(new ConnectionFactory(std::make_shared<Room>()), socket, params_);
               
               server.start();
               std::cout << "Server started on port: " << port_ << std::endl;

               Poco::Thread::sleep(1000); // Даем время серверу запуститься

               // Ожидаем нажатия клавиши 'q' для остановки сервера
               char ch;
               std::cout << "Press 'q' to quit." << std::endl;
               std::cin >> ch;

               server.stop();
          }
          catch(const Poco::Exception& exc)
          {
               std::cerr << "Failed to send message: " << exc.displayText() << std::endl;
          }
          

     }

private:
     std::string address_;
     Poco::UInt16 port_;
     Poco::Net::TCPServerParams::Ptr params_;
};

int main()
{
    // Создаем сервер с указанным адресом и портом
    Server server("127.0.0.1", 8080);

    // Запускаем сервер
    server.start();

    return 0;
}