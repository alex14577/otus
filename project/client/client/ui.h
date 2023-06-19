#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

class ClientUI 
{
public:
     std::string GetUserInput();

     void DisplayMessage(const std::string& sender, const std::string& message);
};