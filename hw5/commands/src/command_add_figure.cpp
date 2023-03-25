#include <commands/command_add_figure.h>

#include <figures/circle.h>
#include <figures/point.h>
#include <figures/line.h>

#include <memory>

using namespace std;

namespace
{
unique_ptr<Figure> ConvertArgToFigure(vector<string>& arg)
{
    unique_ptr<Figure> res;
    if(arg[0] == "point")
    {
        res = make_unique<Point>(stoi(arg[1]), stoi(arg[2]));
    }
    if(arg[0] == "circle")
    {
        res = make_unique<Circle>(Point(stoi(arg[1]), stoi(arg[2])), stoi(arg[3]));
    }
    if(arg[0] == "line")
    {
        res = make_unique<Line>(Point(stoi(arg[1]), stoi(arg[2])),
                                Point(stoi(arg[3]), stoi(arg[4])));
    }
    return res;
}
}

AddFigure::AddFigure(FileKeeper::Ptr fileKeeper)
    : fileKeeper_(fileKeeper)
{
    
}

void AddFigure::Execute(vector<string>& args)
{
    unique_ptr<Figure> figure;
    try
    {
        figure = ConvertArgToFigure(args);
    }
    catch(const exception& )
    {
        throw runtime_error("Unable to make this figure");
    }
    fileKeeper_->AddToFile(figure);
}