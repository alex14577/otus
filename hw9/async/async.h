#pragma once

#include <cstddef>

namespace async {

using Handle = void*;

Handle Connect(std::size_t bulk);
void Receive(Handle handle, const char *data, std::size_t size);
void Disconnect(Handle handle);

}
