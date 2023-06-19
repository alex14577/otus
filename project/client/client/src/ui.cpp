#include <client/client/ui.h>

std::string ClientUI::GetUserInput() 
{
     char buf[64]{};
     std::cin.getline(buf, sizeof(buf));
     std::string in = buf;
     return in;
}

void ClientUI::DisplayMessage(const std::string& sender, const std::string& message) 
{
     std::cout << sender << ": " << message << std::endl;
}