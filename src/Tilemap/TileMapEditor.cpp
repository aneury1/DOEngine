#include "TileMapEditor.h"
#include "Texture.h"
namespace doengine
{

    TileMapEditor::TileMapEditor(const std::string& fontsrc)
    {
        renderer = doengine::Application::getApplication()->getRender();
        panelPosition.x = 0;
        panelPosition.y = 0;
        panelPosition.w = 600;
        panelPosition.h = 1000;
        font = new doengine::TTFText();
        font->setFont(fontsrc, 20);
        font->setColor(doengine::Colors::yellow1);
        /// font->(doengine::Colors::yellow1);
        visible = false;
        saveIcon = TextureManager::getTextureManager()->getTexture("save1");
    }

    TileCharTextureOffset TileMapEditor::getSelectedEditorTileTextureOffset()
    {
        return offset_of_drawing[selected_type];
    }

    bool TileMapEditor::isSelectect()
    {
        return selected;
    }

    void TileMapEditor::setup(const std::string& textId,
               std::unordered_map<char, TileCharTextureOffset> clipList)
    {
        constexpr const int ts = 48;
        mapTexture =
            doengine::TextureManager::getTextureManager()->getTexture(textId);
        doengine::Rect current_rect = {0, 0, ts, ts};
        for (auto clip : clipList)
        {
            offset_of_drawing[clip.first] = clip.second;
            InternalTileCharTextureOffset tileEntry;
            tileEntry.position_in_panel = current_rect;
            tileEntry.clipset = clip.second;
            tileset_display.emplace_back(tileEntry);
            current_rect.x += (ts + paddingLeft);

            if (current_rect.x > panelPosition.w - 10)
            {
                current_rect.x = 0;
                current_rect.y += (ts + paddingTop);
            }
        }
        selected_type = clipList.begin()->first;
    }

    void TileMapEditor::update(double elapsed)
    {
    }

    void TileMapEditor::render()
    {
        /////font->DrawText(200, 400, "Cursor[%d, %d]", 10, 100);
        if (visible && mapTexture && renderer)
        {

            renderer->DrawFillRect(this->panelPosition,
                                   (inEditorArea
                                        ? doengine::Color(0x43, 0x43, 0x43, 255)
                                        : doengine::Colors::white));
            for (auto it : tileset_display)
            {
                Rect adjusted_position_in_editor
                {
                    it.position_in_panel.x  + 24,
                    it.position_in_panel.y  + 32,
                    it.position_in_panel.w,
                    it.position_in_panel.h,
                };
                mapTexture->Draw(adjusted_position_in_editor, it.clipset.offset);
                //// mapTexture->Draw(it.position_in_panel, it.clipset.offset);
            }

            if (inEditorArea)
            {
                renderer->DrawRect(this->panelPosition, doengine::Colors::red,
                                   3);
                /// if(cursor.w > 0)
                {
                    renderer->DrawRect(this->cursor, doengine::Colors::green,
                                       3);
                }
            }
            else
            {
                renderer->DrawRect(this->cursor, doengine::Colors::black, 3);
            }

            if (selected)
            {
                doengine::LogOuput(doengine::logger_type::Error,
                                   "Drawing Selected %c", selected_type);
                font->DrawText(30, 96,"Selected Tile:");
                doengine::Rect offset_rect =
                    offset_of_drawing[selected_type].offset;
                mapTexture->Draw({30, 124, 100, 100}, offset_rect);

                saveIcon->Draw({168, 124, 100, 100});
            }
        }
    }

    void TileMapEditor::MouseMove(const Mouse& mouse)
    {
        this->inEditorArea = doengine::checkCollision(mouse.getMousePosition(),
                                                      this->panelPosition);

        this->cursor = mouse.getMousePosition();
    }

    void TileMapEditor::MouseButtonDown(const Mouse& mouse)
    {
        if (inEditorArea)
        {
            doengine::Rect _position = mouse.getMousePosition();

            for (auto tile_to_check : this->tileset_display)
            {
                 Rect adjusted_position_in_editor
                {
                    tile_to_check.position_in_panel.x  + 24,
                    tile_to_check.position_in_panel.y  + 32,
                    tile_to_check.position_in_panel.w,
                    tile_to_check.position_in_panel.h,
                };
                bool collide = doengine::checkCollision(
                    _position, adjusted_position_in_editor);


                if (collide && visible)
                {
                    doengine::LogOuput(doengine::logger_type::Error,
                                       "Selected Type %c",
                                       tile_to_check.clipset.type);
                    this->cursor = tile_to_check.position_in_panel;
                    this->cursor.x +=24;
                    this->cursor.y += 32;
                    this->selected_type = tile_to_check.clipset.type;
                    selected = true;
                    for(auto it : selected_type_for_char_type){
                        it(this->selected_type);
                    }   
                }
                else
                {

                    ////selected = false;
                }
            }
        }
    }
    void TileMapEditor::MouseButtonUp(const Mouse&)
    {
    }
    void TileMapEditor::OnKeydown(const Keyboard& keyboard)
    {
        auto keys = keyboard.getKeysBitset();
        if (keys[doengine::SCANCODE_E])
        {
            visible = !visible;
        }
        if (keys[doengine::SCANCODE_M])
        {
            mousePositionDebug = !mousePositionDebug;
        }
    }
     void TileMapEditor::OnKeyup(const Keyboard& keyboard)
    {
        (void)keyboard;
    }

    void TileMapEditor::registerSelectedTileByChar(std::function<void(char)> fn)
    {
        this->selected_type_for_char_type.emplace_back(fn);
    }
};