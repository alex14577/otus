#include <server/room/room.h>

Room::Room(const std::string& name) : name_(name) {}

const std::string& Room::GetName() const
{
     return name_;
}

void Room::AddClient(std::shared_ptr<Client> client)
{
     clients_.push_back(client);
}

void Room::RemoveClient(std::shared_ptr<Client> client)
{
     clients_.erase(std::remove(clients_.begin(), clients_.end(), client), clients_.end());
}

void Room::BroadcastMessage(const std::shared_ptr<Client>& client, const Message& message)
{
     for (const auto& c : clients_)
     {
          if (c != client)
          {
               c->SendMessage(message);
          }
     }
}
