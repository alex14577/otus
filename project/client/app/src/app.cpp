#include <client/app/app.h>

using namespace std::chrono_literals;

bool ClientApp::Run(const std::string& address, Poco::UInt16 port, const std::string& clientName) {
     Network network(address, port); 
     ClientUI ui;

     if(!network.ConnectToServer(clientName))
     {
          return -1;
     }
     
     bool needExit = false;
     std::thread inputThread([&]() 
     {
          while (!needExit) {
               std::string in = ui.GetUserInput();
               if(!in.empty())
               {
                    Message message(clientName, in);
                    network.SendMessage(message);
               }
          }
     });

     while (!needExit) 
     {
          std::string buf;
          bool res = network.ReceiveMessage(buf);
          if(!res)
          {
               needExit = true;
          }
          Message msg(buf);
          if(!msg.GetErr().empty())
          {
               needExit = true;
          }
          else
          {
               ui.DisplayMessage(msg.GetSender(), msg.GetText());
          }
     }

     inputThread.join();

     std::cout << "Server closed connection" << std::endl;

     return 0;
}