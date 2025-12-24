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
    doengine::Texture* saveIcon = nullptr;
    doengine::Texture* mapTexture = nullptr;
    doengine::Renderer* renderer;
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
    doengine::TTFText* font;

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

    inline const bool isVisible()const {
        return visible;
    }
};

} // namespace doengine

#endif