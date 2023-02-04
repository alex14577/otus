#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

constexpr int AddrfieldsNum = 4;
constexpr int maxLineElements = 4;
using IpAddress = array<int, AddrfieldsNum>;

vector<string> split(const string &str, const char d)
{
    vector<string> ret;

    string::size_type start = 0;
    string::size_type stop = str.find_first_of(d);
    while(stop != string::npos)
    {
        ret.emplace_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    ret.emplace_back(str.substr(start));

    return ret;
}

vector<IpAddress> Init()
{
        vector<IpAddress> ipPool;
        for(string line; getline(cin, line);)
        {
            auto v = split(line, '\t');
            auto ipAddr = split(v.at(0), '.');

            if(ipAddr.size() == AddrfieldsNum)
            {
                IpAddress addr;
                size_t fieldNum = 0;
                for(const auto& field : ipAddr)
                {
                    addr[fieldNum] = stoi(field);
                    fieldNum++;
                }
                ipPool.emplace_back(addr);
            }
        }    
        return ipPool;
}

void SortIpPool(vector<IpAddress>& ipPool)
{
    std::sort(ipPool.begin(), ipPool.end(), [](IpAddress l, IpAddress r)
                                        {            
                                            for(IpAddress::size_type filedNum = 0;
                                                filedNum < AddrfieldsNum; 
                                                ++filedNum
                                            )
                                            {
                                                if(l[filedNum] < r[filedNum])
                                                {
                                                    return false;
                                                }
                                                if(l[filedNum] > r[filedNum])
                                                {
                                                    return true;
                                                }
                                            }
                                            return true;
                                        }
        );
}

void Print(const vector<IpAddress>& ipPool, bool toPrint(const IpAddress &addr))
{
        for(const auto& ip : ipPool)
        {
            if(toPrint(ip))
            {
                bool needDot = false;
                for(const auto& ipPart : ip)
                {
                    if (needDot)
                    {
                        cout << ".";
                    }
                    needDot = true;
                    cout << ipPart;
                }
                cout << endl;
            }
        }
}

constexpr bool PrintAll(const IpAddress&)
{
    return true;
}

constexpr bool PrintFirstIs1(const IpAddress& addr)
{
    return addr[0] == 1;
}

constexpr bool Print46_70(const IpAddress& addr)
{
    return addr[0] == 46 && addr[1] == 70;
}

bool Print46Any(const IpAddress& addr)
{
    return find(addr.begin(), addr.end(), 46) != addr.end();
}

int main(int , char const *[])
{
    try
    {
        auto ipPool{ Init() };
        SortIpPool(ipPool);

        for(auto& toPrint : {&PrintAll, &PrintFirstIs1, &Print46_70, &Print46Any})
        {
            Print(ipPool, toPrint);
        }
    }
    catch(const exception &e)
    {
        cerr << e.what() << endl;
    }

    return 0;

}
