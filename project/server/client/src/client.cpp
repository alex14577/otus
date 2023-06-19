#include <server/client/client.h>

Client::Client(const std::string& name, Poco::Net::StreamSocket& socket, 
        std::shared_ptr<CipherEngine> ciph) : 
     name_(name),    
     socket_(socket),
     ciph_(ciph)
{
}


const std::string& Client::GetName() const
{
     return name_;
}

void Client::SendMessage(const Message& message)
{
     auto str = ciph_->EncryptMessage(message.ToString());
     socket_.sendBytes(str.data(), str.size());
}