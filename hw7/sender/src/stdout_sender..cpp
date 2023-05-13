#include <sender/stdout_sender.h>
#include <bulk/bulk.h>

#include <iostream>

using namespace std;

StdOutSender::StdOutSender(const std::shared_ptr<Bulk>& bulk)
    : bulk_(bulk)
{
}

void StdOutSender::Update()
{
    auto data = bulk_->GetData();
    cout << "bulk: ";
    for(const auto& d : data)
    {
        cout << d << " ";
    }
    cout << endl;
}