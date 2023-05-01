#pragma once

#include <types/types.h>

#include <string>

// Класс парсера входного потока. Определяет тип входной строки: 
// команда для выполнения или управляющие символы.
class Parser
{
public:
    LineType ParseLine(const std::string& cmd);

};