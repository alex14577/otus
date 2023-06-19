#pragma once

#include <string>
#include <vector>
#include <server/client/client.h>
#include <cmn/message/message.h>

class Room
{
public:
    Room() = default;
    Room(const std::string& name);

    const std::string& GetName() const;

    void AddClient(const std::shared_ptr<Client> client);

    void RemoveClient(const std::shared_ptr<Client> client);

    void BroadcastMessage(const std::shared_ptr<Client>& client, const Message& message);

private:
    std::string name_;
    std::vector<std::shared_ptr<Client>> clients_;
};