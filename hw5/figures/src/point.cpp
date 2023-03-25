#include <figures/point.h>

#include <vector>
#include <algorithm>

using namespace std;

std::string Point::GetData() const
{
    string metaData = "name = " + name_ + " x = " + to_string(x_) + " y = " + to_string(y_);
    return metaData;
}
Point::Type Point::GetX() const
{
    return x_;
}
Point::Type Point::GetY() const
{
    return y_;
}