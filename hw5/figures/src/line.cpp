#include <figures/line.h>

#include <vector>
#include <algorithm>
#include <string>

using namespace std;

Line::Line(Point start, Point end)
    : start_(start),
      end_(end)
{}

std::string Line::GetData() const
{
    string metaData = "name = " + name_ 
        + " start = " + to_string(start_.GetX()) + " : " + to_string(start_.GetY())
        + " end = " + to_string(end_.GetX()) + " : " + to_string(end_.GetY());
    return metaData;
}