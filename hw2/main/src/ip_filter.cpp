#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using IpAddress = vector<string>;

vector<string> split(const string &str, char d)
{
    vector<string> r;

    string::size_type start = 0;
    string::size_type stop = str.find_first_of(d);
    while(stop != string::npos)
    {
        r.emplace_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.emplace_back(str.substr(start));

    return r;
}

vector<IpAddress> Init()
{
        vector<IpAddress> ipPool;
        for(string line; getline(cin, line);)
        {
            auto v = split(line, '\t');
            ipPool.emplace_back(split(v.at(0), '.'));
        }    
        return ipPool;
}

int CmpStr(string& l, string& r)
{
    auto rSize = r.size();
    auto lSize = l.size();

    if(lSize < rSize)
    {
        return -1;
    }
    if(lSize > rSize)
    {
        return 1;
    }

    return l.compare(r);
};

void SortIpPool(vector<IpAddress>& ipPool)
{
    auto cmpAddr = [](IpAddress& l, IpAddress& r)
        {
            bool result{true};
            
            for(int part = 0;
                part < l.size(), part < r.size(); 
                part++
            )
            {
                auto cmpStr = [&]()
                {
                    auto rSize = r[part].size();
                    auto lSize = l[part].size();

                    if(lSize < rSize)
                    {
                        return -1;
                    }
                    if(lSize > rSize)
                    {
                        return 1;
                    }

                    return l[part].compare(r[part]);
                };
                int res = cmpStr();
                if(res != 0)
                {
                    result = res < 0 ? false : true;
                    break;
                }
            }

            return result;
        };

    sort(ipPool.begin(), ipPool.end(), cmpAddr);

}

bool PrintAll(const IpAddress& addr)
{
    return true;
}

bool PrintFirstIs1(const IpAddress& addr)
{
    return addr[0] == "1";
}

bool Print46_70(const IpAddress& addr)
{
    return addr[0] == "46" && addr[1] == "70";
}

bool Print46Any(const IpAddress& addr)
{
    return find(addr.begin(), addr.end(), "46") != addr.end();
}

template <typename F>
void Print(const vector<IpAddress>& ipPool, F toPrint)
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

int main(int , char const *[])
{
    try
    {
        auto ipPool{ Init() };
        SortIpPool(ipPool);
        Print(ipPool, &PrintAll);
        Print(ipPool, &PrintFirstIs1);
        Print(ipPool, &Print46_70);
        Print(ipPool, &Print46Any);

    }
    catch(const exception &e)
    {
        cerr << e.what() << endl;
    }

    return 0;

}
