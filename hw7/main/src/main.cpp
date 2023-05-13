#include <iostream>
#include <fstream>
#include <memory>
#include <exception>
#include <worker/worker.h>
#include <manager/manager.h>
#include <sender/file_sender.h>
#include <sender/stdout_sender.h>
#include <bulk/bulk_impl.h>

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
    shared_ptr<Manager>& mgr,
    shared_ptr<BulkImpl>& bulk
)
{
    return Worker(rec, std::cout, mgr, make_unique<Parser>(), bulk);
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
        case(4):
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

    shared_ptr<BulkImpl> bulk = make_shared<BulkImpl>();

    shared_ptr<Sender> fileSender = make_shared<FileSender>(bulk, argc > 3 ? argv[3] : nullptr); 
    shared_ptr<Sender> stdOutSender = make_shared<StdOutSender>(bulk);

    bulk->Attach(fileSender);
    bulk->Attach(stdOutSender);

    shared_ptr<Manager> mgr = make_shared<Manager>(cmdBlockNum);
    Worker wrk = MakeWorker(in, mgr, bulk);

    wrk.Run();
    
}