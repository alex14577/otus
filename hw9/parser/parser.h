#pragma once

#include <types/types.h>

#include <string>

/// @brief Определяет тип входной строки.
/// @details команда для выполнения или управляющие символы.
LineType ParseLine(const std::string& cmd);