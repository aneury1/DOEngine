#include "Logger.h"
#include <iostream>
#include <stdarg.h>
namespace doengine
{

namespace
{
const char* GetColorCode(const logger_type& type)
{
    switch (type)
    {
    case logger_type::Information:
        return "\033[32m"; // Green
    case logger_type::Warning:
        return "\033[33m"; // Yellow
    case logger_type::Error:
        return "\033[31m"; // Red
    default:
        return "\033[0m"; // Reset (no color)
    }
}
} // namespace

void LogOuput(const logger_type& type,const char* msg, ...)
{
    // Determine log level prefix
    const char* prefix;
    switch (type)
    {
    case logger_type::Information:
        prefix = "[INFO] ";
        break;
    case logger_type::Warning:
        prefix = "[WARNING] ";
        break;
    case logger_type::Error:
        prefix = "[ERROR] ";
        break;
    default:
        prefix = "[LOG] ";
        break;
    }

    // Start variable argument handling
    va_list args;
    va_start(args, msg);

    // Buffer for formatted message
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), msg, args);

    // End argument handling
    va_end(args);

    // Print to console (or you can log to a file)
    //std::cout << prefix << buffer << std::endl;
    const char* color_code = GetColorCode(type);
    std::cout << color_code << prefix << buffer << "\033[0m" << std::endl; 
}

}; // namespace doengine