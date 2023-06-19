#include <server/connection/connection.h>

Connection::Connection(const Poco::Net::StreamSocket& socket, std::shared_ptr<Room> room) :
     Poco::Net::TCPServerConnection(socket),
     room_(room),
     ciph_(std::make_shared<CipherEngine>())
{
     ciph_->Init();
}

void Connection::run()
{
     auto client = AcceptConnection(); 
     if(!client)
     {
          return;
     }

     room_->AddClient(client);

     Poco::Net::StreamSocket& soc = socket();
     std::vector<char> buffer(1024, 0);
     bool isOpen = true;
     while(isOpen)
     {
          auto c = soc.receiveBytes(buffer.data(), buffer.size());
          if(c > 0)
          {    
               try
               {
                    auto decryptedMsg = ciph_->DecryptMessage(std::string(buffer.data(), c));
                    Message msg(decryptedMsg.data());
                    room_->BroadcastMessage(client, msg);
               }
               catch(const std::exception& e)
               {
                    std::cerr << e.what() << std::endl;
               }
               catch(...)
               {
                    
               }
          }
          else
          {
               isOpen = false;
          }
     }

     room_->RemoveClient(client);
}

std::shared_ptr<Client> Connection::AcceptConnection()
{
     Poco::Net::StreamSocket& soc = socket();
     std::shared_ptr<Client> client;
     if (soc.poll(Poco::Timespan(10, 0), Poco::Net::Socket::SELECT_READ) == true)
     {
          auto bytesAval = soc.available();
          std::vector<char> buffer(bytesAval + 1, 0);
          soc.receiveBytes(buffer.data(), bytesAval);
          if(bytesAval > 0)
          {
               Message msg(buffer.data());
               ciph_->AddOtherPubKey(msg.GetText());
               client = std::make_shared<Client>(msg.GetSender(), soc, ciph_);
               Message msgWithKey("server", ciph_->GetPubKey());
               if(!msgWithKey.GetErr().empty())
               {
                    return {};
               }
               auto msgRaw = msgWithKey.ToString();
               soc.sendBytes(msgRaw.data(), msgRaw.size());
          }
     }
     return client;
}