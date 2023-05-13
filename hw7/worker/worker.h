#pragma once

#include <iostream>
#include <parser/parser.h>
#include <manager/manager.h>
#include <bulk/bulk.h>

#include <memory>

class BulkImpl;

class Worker
{
public:
    Worker(Worker&&) = default;
    Worker
    (
        std::istream& rec,
        std::ostream& sender,
        std::shared_ptr<Manager>& mgr,
        std::unique_ptr<Parser> parser,
        std::shared_ptr<BulkImpl>& bulk
    );

    void Run();

private:
    std::istream& receiver_;
    std::ostream& sender_;
    std::shared_ptr<Manager> mgr_;
    std::unique_ptr<Parser> parser_;
    std::shared_ptr<BulkImpl> bulk_;
};