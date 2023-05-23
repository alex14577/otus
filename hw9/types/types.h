#pragma once

#include <cstdint>

enum LineType
{
     Cmd,
     StartBlock,
     EndBlock,
     Eof,
     None
};

// Возможность выбора, куда сообщение должно дойти.
enum Target : uint8_t
{
     NoTarget = 0,
     Log = (1 << 0),
     File = (1 << 1),
     All = Log | File,
};

