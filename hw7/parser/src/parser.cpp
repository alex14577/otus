#include <parser/parser.h>
#include <types/types.h>

using namespace std;

LineType Parser::ParseLine(const string& line)
{
    switch (line[0])
    {
    case ('{'):
        {
            return LineType::StartBlock;
            break;
        }
    case ('}'):
        {
            return LineType::EndBlock;
            break;
        }    
    default:
        break;
    };

    if(line.find("cmd") != string::npos)
    {
        return LineType::Cmd;
    }
    if(line == to_string(EOF))
    {
        return LineType::Eof;
    }
    
    return LineType::None;
}
