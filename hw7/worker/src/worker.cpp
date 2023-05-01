#include <worker/worker.h>
#include <types/types.h>

#include <string>

using namespace std;

namespace
{
Manager::Event LineTypeToEvent(LineType lineType)
{
    switch (lineType)
    {
    case (LineType::Cmd):
        {
            return Manager::Event::CmdAdded;
        }
    case (LineType::StartBlock):
        {
            return Manager::Event::StartBlockReceived;
        }        
    case (LineType::EndBlock):
        {
            return Manager::Event::EndBlockReceived;
        }
    case (LineType::Eof):
        {
            return Manager::Event::EofReceived;
        }
    default:
        {
            return Manager::Event::None;
        }
    }
}
}

Worker::Worker
    (
        istream& rec,
        ostream& sender,
        std::shared_ptr<Manager> mgr,
        std::unique_ptr<Parser> parser,
        std::unique_ptr<Bulk> bulk
    )
    : receiver_ (rec),
      sender_(sender),
      mgr_(mgr),
      parser_(move(parser)),
      bulk_ (move(bulk))
{}

void Worker::Run()
{
    char buf[256];
    while(1)
    {
        auto& in = receiver_.getline(buf, sizeof(buf));

        string line;
        LineType lineType{LineType::Eof};
        if(in)
        {
            line.append(buf);
            lineType = parser_->ParseLine(line);
        }

        if(lineType == LineType::Cmd)
        {
            bulk_->AddCmd(line);
        }

        switch(mgr_->HandleEvent(LineTypeToEvent(lineType)))
        {
            case (Manager::State::NeedExitAndExecute):
            {
                bulk_->Execute(sender_);
                return;
            }
            case (Manager::State::NeedExecute):
            {
                bulk_->Execute(sender_);
                break;
            }
            case (Manager::State::NeedExit):
            {
                return;
            }
            default:
                {}
        }
    }
}