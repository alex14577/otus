#pragma once 

// Интерфейс для получения команд.

#include <receiver/receiver.h>

class ConsoleReceiver : public Reciever
{
public:
    ConsoleReceiver();
    virtual ~ConsoleReceiver();

    virtual std::string GetData() override final;
};