#include <iostream>

#include <client/app/app.h>


int main(int argc, char** argv) 
{
     std::string name;
     if(argc > 1)
     {
          name = argv[1];
     }
     else
     {
          std::cout << "Invalid arg" << std::endl;
          std::cout << "Usage:" << argv[0] << " name" << std::endl;
          return -1;
          // name = "bob";
     }

     std::string address = "localhost";
     Poco::UInt16 port = 8080;

     ClientApp client;
     client.Run(address, port, name);

     return 0;
}