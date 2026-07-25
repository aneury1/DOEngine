#include "Mouse.h"
#include "constants.h"
#include <Application.h>
#include <Color.h>
#include <DS.h>
#include <Event.h>
#include <GameState.h>
#include <NothingNess.h>
#include <SelectionRect.h>
#include <Timer.h>
#include <vector>

#define SCALE_FACTOR 1
#define TILESET                                                                \
    "/home/phenom/Projects/DOEngine/assets/gfx/sprites/battle_city.jpg"

struct Player : public doengine::GameObject
{
    doengine::Rect rect;
    doengine::Rect clipset;
    doengine::Texture* texture;
    Player(const doengine::Rect& offset) : rect{offset}
    {
        clipset.x = PLAYER_TANK_A_CLIP_X;
        clipset.y = PLAYER_TANK_A_CLIP_X;
        clipset.w = ENEMY1_TANK_A_CLIP_W;
        clipset.h = ENEMY1_TANK_A_CLIP_H;
        texture = doengine::TextureManager::getTextureManager()->getTexture(1);
    }
    virtual void Update(float timer = 0)
    {
    }
    virtual void Render()
    {
        texture->Draw(rect, clipset);
    }
};

enum GameId
{
    /// Intro,
    /// Menu
    PlayGameState
};

struct PreviewObject : public doengine::GameObject
{

    doengine::Rect offset;
    doengine::Rect clipset;
    doengine::Texture* texture;
    doengine::TTFText* font;
    PreviewObject(int textureId)
    {
        texture = doengine::TextureManager::getTextureManager()->getTexture(
            textureId);
        offset.x = 39;
        offset.y = 543;
        offset.w = 92;
        offset.h = 92;
        clipset.x = 0;
        clipset.y = 0;
        clipset.w = 16;
        clipset.h = 16;
        font = new doengine::TTFText();
        font->setFont("/usr/share/fonts/TTF/OpenSans-Bold.ttf", 19);
        font->setColor(doengine::Colors::white);
    }

    void setClipset(const doengine::Rect& cl)
    {
        clipset = cl;
    }
    void Update(float elapsed)
    {
    }
    void Render()
    {
        texture->Draw(offset, clipset);
        font->DrawText(offset.x + offset.w + 20, offset.y, "[%d, %d, %d, %d]",
                       clipset.x, clipset.y, clipset.w, clipset.h);
    }
};

struct TilesetCropset : public doengine::GameObject
{
    doengine::Texture* texture;
    doengine::TTFText* ttffont;
    PreviewObject* previewObject;
    doengine::SelectionRect selectionRect;
    bool visible;
    TilesetCropset(int textureId);
    void setFont(const std::string& f)
    {
    }
    virtual void Update(float elapsed = 0)
    {
        selectionRect.Update(elapsed);
    }
    virtual void Render()
    {
        selectionRect.Render();
        previewObject->Render();
    }
};

TilesetCropset::TilesetCropset(int textureId)
{
    visible = false;
    texture =
        doengine::TextureManager::getTextureManager()->getTexture(texture_id);
    previewObject = new PreviewObject(1);
    selectionRect.setFont("/usr/share/fonts/TTF/Hack-Bold.ttf");
    selectionRect.setFontColor(doengine::Colors::green);
    selectionRect.registerSelectionRectFinished([this](doengine::Rect rect) {
        rect.x /= 2;
        rect.y /= 2;
        rect.w /= 2;
        rect.h /= 2;
        previewObject->setClipset(rect);
    });
}

struct PlayState : public doengine::GameState,
                   public doengine::KeyDownEvent,
                   public doengine::MouseEvent
{
    doengine::Texture* tileset;

    TilesetCropset* cropset;

    doengine::Rect current;

    PlayState()
    {
    }
    virtual void OnEnter() override
    {
        doengine::Event::AddKeyPressEventListener(this);
        doengine::Event::AddMouseEvent(this);
        doengine::TextureManager::getTextureManager()->loadTextureFromFile(
            1, TILESET, {0xFF, 0x00, 0xFF, 255});
        tileset = doengine::TextureManager::getTextureManager()->getTexture(1);
        cropset = new TilesetCropset(1);
    }
    virtual void OnExit() override
    {
    }
    virtual void Update(float elapsed) override
    {
        cropset->Update(elapsed);
    }
    virtual void Render() override
    {
        tileset->Draw(
            {0, 0, tileset->getWidth() * 2, tileset->getHeight() * 2});
        cropset->Render();

        doengine::Renderer* render =
            doengine::Application::getApplication()->getRender();

        const auto window =
            doengine::Application::getApplication()->getWindow();
        render->DrawLine(
            doengine::Point(0, current.y),
            doengine::Point(window->getWindowDisplayMode(0).w, current.y),
            doengine::Colors::green);

        render->DrawLine(
            doengine::Point(current.x, 0),
            doengine::Point(current.x, window->getWindowDisplayMode(0).h),
            doengine::Colors::green);
    }
    doengine::Color transparent;
    virtual void OnKeydown(const Keyboard& key)
    {
        if (key.getLastKeyPressed() == doengine::SCANCODE_X)
            doengine::Application::getApplication()->Quit();
    }

    virtual void MouseWheel(const Mouse&)
    {
    }
    virtual void MouseMove(const Mouse& mouse)
    {
        current.x = mouse.getMousePosition().x;
        current.y = mouse.getMousePosition().y;
    }
    virtual void MouseButtonDown(const Mouse&)
    {
    }
    virtual void MouseButtonUp(const Mouse&)
    {
    }
};

int main(int argc, char* argv[])
{
    auto app = doengine::Application::getApplication();
    doengine::Rect rect{840, 680};
    app->createWindow(rect);
    auto playstate = new PlayState();
    app->addState(playstate, PlayGameState);
    app->setState(PlayGameState);

    while (app->IsRunning())
    {
        app->PollEvent();
        app->Update();
        app->clearScreen(doengine::Color(0, 0, 0, 255));
        app->Render();
    }
    app->Quit();
    return 0;
}
