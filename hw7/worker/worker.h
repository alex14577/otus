#pragma once

#include <iostream>
#include <parser/parser.h>
#include <manager/manager.h>
#include <bulk/bulk.h>


#include <memory>

class Worker
{
public:
    Worker(Worker&&) = default;
    Worker
    (
        std::istream& rec,
        std::ostream& sender,
        std::shared_ptr<Manager> mgr,
        std::unique_ptr<Parser> parser,
        std::unique_ptr<Bulk> bulk
    );

    void Run();

private:
    std::istream& receiver_;
    std::ostream& sender_;
    std::shared_ptr<Manager> mgr_;
    std::unique_ptr<Parser> parser_;
    std::unique_ptr<Bulk> bulk_;
};