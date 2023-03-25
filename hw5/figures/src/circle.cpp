#include <figures/circle.h>

#include <vector>
#include <algorithm>

using namespace std;

Circle::Circle(Point p, uint64_t r)
    : pos_(p),
      radius_(r)
{}

std::string Circle::GetData() const
{
    string metaData = "name = " + name_ + 
        " pos = " + to_string(pos_.GetX()) + " : " + to_string(pos_.GetY()) +
        " radius = " + to_string(radius_);

    return metaData;
}