#include <print_ip/print_ip.h>

#include <string>
#include <iostream>
#include <vector>
#include <list>

int main()
{
    int8_t ipInt8 = -1;
    int16_t ipInt16 = 0;
    int32_t ipInt32 = 2130706433;
    int64_t ipInt64 = 8875824491850138409;

    std::string ipString = "Hello World";
    std::vector<int> ipVec = {400, 300, 200, 100};
    std::list<short> ipList = {400, 300, 200, 100};

    PrintIp(ipInt8);
    std::cout << std::endl;
    PrintIp(ipInt16);
    std::cout << std::endl;
    PrintIp(ipInt32);
    std::cout << std::endl;
    PrintIp(ipInt64);
    std::cout << std::endl;
    PrintIp(ipString);
    std::cout << std::endl;
    PrintIp(ipVec);
    std::cout << std::endl;
    PrintIp(ipList);
    std::cout << std::endl;
}