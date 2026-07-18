/*
 * ============================================================================
 * DOEngine
 * Copyright (c) 2026 Victor D. Montero, Aneury Perez
 * All Rights Reserved.
 *
 * Licensed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1. The above copyright notice, this license notice, and this disclaimer
 *    MUST be included in all copies or substantial portions of the Software.
 *
 * 2. This notice may not be removed from the original source files distributed
 *    as part of this project.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * ============================================================================
 */
#include <format>
#include <iostream>
#include <string_view>
#include "Logger.h"
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


template<typename... Args>
void LogOuputF(logger_type type,
              std::format_string<Args...> fmt,
              Args&&... args)
{
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

    const char* color = GetColorCode(type);

    std::cout
        << color
        << prefix
        << std::format(fmt, std::forward<Args>(args)...)
        << "\033[0m\n";
}


template<typename... Args>
void LogInfo(std::format_string<Args...> fmt, Args&&... args)
{
    LogOutput(logger_type::Information,
              fmt,
              std::forward<Args>(args)...);
}

template<typename... Args>
void LogWarning(std::format_string<Args...> fmt, Args&&... args)
{
    LogOutput(logger_type::Warning,
              fmt,
              std::forward<Args>(args)...);
}

template<typename... Args>
void LogError(std::format_string<Args...> fmt, Args&&... args)
{
    LogOutput(logger_type::Error,
              fmt,
              std::forward<Args>(args)...);
}

}; // namespace doengine