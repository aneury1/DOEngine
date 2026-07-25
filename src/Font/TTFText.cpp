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

#include "TTFText.h"
#include "Logger.h"
#include "Renderer.h"
#include <stdarg.h>
namespace doengine
{
TTFText::TTFText()
{
    LogOuput(logger_type::Information, "--TTFText--");
    nativeRenderer =
        Application::getApplication()->getRender()->getTextRenderer();
}

void TTFText::setColor(Color color)
{
    nativeRenderer->setColor(color);
}

void TTFText::setFont(const std::string& path, int fntsize)
{
    LogOuput(logger_type::Information, "TTFText::setFont FontSRc=%s",
             path.c_str());
    nativeRenderer->setFont(path, fntsize);
}

void TTFText::setForegroundColor(const Color& color)
{
    nativeRenderer->setForegroundColor(color);
}

void TTFText::DrawText(int x, int y, const char* fmt, ...)
{
    // Start variable argument handling
    va_list args;
    va_start(args, fmt);

    // Buffer for formatted message
    char buffer[4096];
    vsnprintf(buffer, sizeof(buffer), fmt, args);

    // End argument handling
    va_end(args);
    this->DrawText(buffer, x, y);
}

void TTFText::DrawText(const char* text, int x, int y)
{
    if (nativeRenderer){
       //// LogOuput(logger_type::Information, "TTFText::DrawText calling native Renderer, to Draw [%s]", text);
        
        nativeRenderer->DrawText(text, x, y);
    }
    else{
        LogOuput(logger_type::Information, "TTFText::setFont Fontrneder nullptr");
    }
}

std::shared_ptr<Texture> TTFText::createText(const std::string& text)
{
    return nativeRenderer->createText(text);
}

void TTFText::wrapText(const char* text, int maxWidth, char* wrappedText)
{
    nativeRenderer->wrapText(text, maxWidth, wrappedText);
    return;
}

std::shared_ptr<Texture> TTFText::createBitmapFont(const std::string& font_path,
                                   const doengine::Color& bg,
                                   const doengine::Color& fg)
{

    if (nativeRenderer)
    {
        LogOuput(logger_type::Information, "Create Bitmap font");
        return nativeRenderer->createBitmapFont(font_path, bg, fg);
    }
    return nullptr;
}

int TTFText::getFontHeight()
{
    if (nativeRenderer)
    {
        LogOuput(logger_type::Information, "Create Bitmap font");
        return nativeRenderer->getFontHeight();
    }
    return 0;
}

} // namespace doengine