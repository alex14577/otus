#include <receiver/console_receiver.h>

#include <string>
#include <iostream>

using namespace std;

ConsoleReceiver::ConsoleReceiver()
{

}

ConsoleReceiver::~ConsoleReceiver()
{

}

string ConsoleReceiver::GetData()
{
    string res;
    getline(cin, res);
    return res;
}