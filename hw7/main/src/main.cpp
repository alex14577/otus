#include <iostream>
#include <fstream>
#include <memory>
#include <exception>
#include <worker/worker.h>
#include <manager/manager.h>

using namespace std;

ifstream OpenFile(const char* filePath)
{
    ifstream fs(filePath, std::fstream::in);
    if(!fs.is_open())
    {
        throw runtime_error("Can't open file");
    }
    return fs;
}

Worker MakeWorker
(
    istream& rec,
    shared_ptr<Manager> mgr
)
{
    return Worker(rec, std::cout, mgr, move(make_unique<Parser>()), make_unique<Bulk>());
}

int main(int argc, char** argv)
{
    ifstream rec;
    ifstream iStream;
    size_t cmdBlockNum{0};
    switch(argc)
    {
        case(2):
        {
            cmdBlockNum = atoi(argv[1]);
            break;
        }
        case(3):
        {
            cmdBlockNum = atoi(argv[1]);
            try
            {
                iStream = OpenFile(argv[2]);
            }
            catch(const std::exception& e)
            {
                cout << e.what() <<  endl;
                return -1;
            }
            rec = move(iStream);
            break;
        }
        default:
        {
            cout << "Invalid arg number." << endl;
            cout << "See man" << endl;
            return -1;
        }
    }

    istream& in = rec.is_open() ? rec : std::cin;

    shared_ptr<Manager> mgr = make_shared<Manager>(cmdBlockNum);
    Worker wrk = MakeWorker(in, mgr);

    wrk.Run();
    
}