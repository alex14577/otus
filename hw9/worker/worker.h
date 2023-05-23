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
        std::shared_ptr<Manager>& mgr,
        std::shared_ptr<BulkImpl>& bulk
    );

    void Run();

private:
    std::istream& receiver_;
    std::shared_ptr<Manager> mgr_;
    std::shared_ptr<BulkImpl> bulk_;
};