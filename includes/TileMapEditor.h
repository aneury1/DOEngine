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



#ifndef TILEMAP_EDITOR_H_DEFINED
#define TILEMAP_EDITOR_H_DEFINED

#include "Application.h"
#include "Event.h"
#include "Geometric.h"
#include "Logger.h"
#include "Renderer.h"
#include "TTFText.h"
#include <functional>
#include <vector>


namespace doengine
{
struct TileCharTextureOffset
{
    char type;
    doengine::Rect offset;
    TileCharTextureOffset()
    {
    }
    TileCharTextureOffset(char t, doengine::Rect rect) : type{t}, offset{rect}
    {
    }
};

struct InternalTileCharTextureOffset
{
    doengine::Rect position_in_panel;
    TileCharTextureOffset clipset;
};
struct TileMapEditor : public doengine::MouseEvent,
                       public doengine::KeyboardInputhandlingEvent
{

    std::vector<std::function<void(char)>> selected_type_for_char_type;

    bool visible = true;
    std::shared_ptr<doengine::Texture> saveIcon = nullptr;
    std::shared_ptr<doengine::Texture> mapTexture = nullptr;
    std::shared_ptr<doengine::Renderer> renderer;
    std::unordered_map<char, TileCharTextureOffset> offset_of_drawing;
    std::vector<doengine::Rect> tiles;
    doengine::Rect panelPosition;
    std::vector<InternalTileCharTextureOffset> tileset_display;

    /// Tile Layout
    int paddingTop = 10;
    int paddingLeft = 10;

    /// Editor Controls
    bool inEditorArea = false;
    doengine::Rect debug_area;
    doengine::Rect cursor;
    char selected_type;
    bool selected = false;

    /// Debug Options
    bool mousePositionDebug = false;
    doengine::Rect mouseDebugText;
    std::shared_ptr<doengine::TTFText> font;

    TileMapEditor(const std::string& fontsrc);
    TileCharTextureOffset getSelectedEditorTileTextureOffset();
    bool isSelectect();
    void setup(const std::string& textId,
               std::unordered_map<char, TileCharTextureOffset> clipList);
    void update(double elapsed);
    void render();
    void MouseMove(const Mouse& mouse);
    void MouseButtonDown(const Mouse& mouse);
    void MouseButtonUp(const Mouse&);
    virtual void OnKeydown(const Keyboard& keyboard);
    virtual void OnKeyup(const Keyboard& keyboard);
    void registerSelectedTileByChar( std::function<void(char)> fn);

    bool isVisible() const {
        return visible;
    }
};

} // namespace doengine

#endif