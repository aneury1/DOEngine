#pragma once
#include <stdio.h>
#include <stdlib.h>

namespace doengine
{

enum TextColor
{
    TextColorBlack,
    TextColorRed,
    TextColorGreen,
    TextColorYellow,
    TextColorBlue,
    TextColorMagenta,
    TextColorCyan,
    TextColorWhite,
    TextColorCounter
};

template <typename... Args>
void LogConsole(const char* prefix, char* msg, TextColor color, Args... args)
{
    static const char* TextColorTable[TextColorCounter] = {
        "\x1b[30m", // TextColorBlack
        "\x1b[31m", // TextColorRed
        "\x1b[32m", // TextColorGreen
        "\x1b[33m", // TextColorYellow
        "\x1b[34m", // TextColorBlue
        "\x1b[35m", // TextColorMagenta
        "\x1b[36m", // TextColorCyan
        "\x1b[37m", // TextColorWhite
    };

    char formatBuffer[8192] = {};
    sprintf(formatBuffer, "%s %s %s \033[0m", TextColorTable[color], prefix,
            msg);

    char textBuffer[8912] = {};
    sprintf(textBuffer, formatBuffer, args...);

    puts(textBuffer);
}

#define DO_TRACE(msg, ...)                                                     \
    LogConsole("TRACE: ", msg, TextColorGreen, ##__VA_ARGS__);
#define DO_WARN(msg, ...)                                                      \
    LogConsole("WARN: ", msg, TextColorYellow, ##__VA_ARGS__);
#define DO_ERROR(msg, ...)                                                     \
    LogConsole("ERROR: ", msg, TextColorRed, ##__VA_ARGS__);

}; // namespace doengine