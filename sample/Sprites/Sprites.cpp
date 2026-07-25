#include "Application.h"
#include "Event.h"
#include "GameObject.h"
#include "GameState.h"

#include "Geometric.h"
#include "Keyboard.h"
#include "SelectionRect.h"
#include "Sprite.h"
#include "Texture.h"
#include "Tilemap.h"
#include <memory>
#include <unordered_map>
#include <vector>

using doengine::ClipType;
using doengine::Direction;
using doengine::GameObject;
using doengine::GameState;
using doengine::KeyboardInputhandlingEvent;
using doengine::Point;
using doengine::Rect;
using doengine::SelectionRect;
using doengine::Sprite;
using doengine::Texture;

struct Player : public GameObject
{
    Player(std::shared_ptr<Texture> texture, std::vector<Rect>& frames,
           const Point& offset = Point(0, 0),
           const ClipType clipType = ClipType::Free,
           const size_t spriteCount = 0,
           const Direction direction = Direction::None,
           const float duration = 0.500)
        : texture(texture)
    {
        sprite = std::make_shared<Sprite>(texture, frames, offset, clipType,
                                          spriteCount, direction);
        sprite->setDuration(duration);
    }
    ~Player()
    {
    }

    virtual void Update(float timer = 0);
    virtual void Render();
    void Move(const Rect& dstRect);

    Rect position;
    std::shared_ptr<Texture> texture;
    std::shared_ptr<Sprite> sprite;
};

void Player::Update(float timer)
{
    if (sprite != nullptr)
        sprite->Update(timer);
}

void Player::Render()
{
    if (sprite != nullptr)
        sprite->Draw(position);
}

void Player::Move(const Rect& dstRect)
{
    position = dstRect;
}

struct PlayState : public GameState, public KeyboardInputhandlingEvent
{
    PlayState() = default;
    ~PlayState();

    std::shared_ptr<Texture> battleCityTexture;
    std::shared_ptr<Texture> spriteRpgTexture;

    std::vector<Rect> explosionSpriteframes;
    std::vector<Rect> spawningSpriteframes;
    std::vector<Rect> shieldSpriteframes;
    std::vector<Rect> playerSpriteframes;
    std::vector<Rect> player2Spriteframes;
    std::vector<Rect> player3Spriteframes;
    std::vector<Rect> eagleSpriteframes;
    std::vector<std::shared_ptr<Player>> players;

 
    void loadDebugResource();
 

    virtual void OnEnter();
    virtual void OnExit();
    virtual void Update(float elapsed);
    virtual void Render();
    virtual void OnKeydown(const Keyboard&);
    virtual void OnKeyup(const Keyboard&);
};

PlayState::~PlayState()
{
 
}

void PlayState::loadDebugResource()
{

    explosionSpriteframes = {Rect(256, 128, 16, 16), Rect(272, 128, 16, 16),
                             Rect(289, 128, 16, 16), Rect(256, 128, 16, 16),
                             Rect(272, 128, 16, 16), Rect(289, 128, 16, 16),
                             Rect(304, 128, 30, 29), Rect(334, 128, 34, 32),
                             Rect(304, 128, 30, 29), Rect(334, 128, 34, 32)};

    playerSpriteframes.push_back(Rect(0, 3, 30, 43));
    player2Spriteframes.push_back(Rect(0, 51, 30, 43));
    player3Spriteframes.push_back(Rect(0, 146, 30, 43));
    spawningSpriteframes.push_back(Rect(256, 95, 15, 15));
    shieldSpriteframes.push_back(Rect(256, 144, 16, 16));

    eagleSpriteframes.push_back(Rect(304, 32, 16, 16));
}

void PlayState::OnEnter()
{
    loadDebugResource();

    battleCityTexture =
        std::make_shared<Texture>("./assets/gfx/sprites/battle_city.jpg");
    spriteRpgTexture =
        std::make_shared<Texture>("./assets/gfx/sprites/spriterpg.png");

    auto explosion = std::make_shared<Player>(
        battleCityTexture, explosionSpriteframes, Point(0, 0), ClipType::Free,
        0, Direction::None, 0.450);

    auto spawning = std::make_shared<Player>(
        battleCityTexture, spawningSpriteframes, Point(1, 0),
        ClipType::Contiguous, 4U, Direction::Horizontal, 0.2);

    auto shield = std::make_shared<Player>(
        battleCityTexture, shieldSpriteframes, Point(0, 0),
        ClipType::Contiguous, 2U, Direction::Horizontal, 0.1);

    auto eagle = std::make_shared<Player>(battleCityTexture, eagleSpriteframes,
                                          Point(0, 0), ClipType::Contiguous, 1U,
                                          Direction::Horizontal, 0.1);

    auto player = std::make_shared<Player>(spriteRpgTexture, playerSpriteframes,
                                           Point(3, 0), ClipType::Contiguous,
                                           4U, Direction::Horizontal, 0.8);

    auto player2 = std::make_shared<Player>(
        spriteRpgTexture, playerSpriteframes, Point(0, 5), ClipType::Contiguous,
        4U, Direction::Vertical, 0.8);

    auto player3 = std::make_shared<Player>(
        spriteRpgTexture, player2Spriteframes, Point(3, 0),
        ClipType::Contiguous, 4U, Direction::Horizontal, 0.8);

    auto player4 = std::make_shared<Player>(
        spriteRpgTexture, player3Spriteframes, Point(3, 0),
        ClipType::Contiguous, 4U, Direction::Horizontal, 0.8);

    auto player5 = std::make_shared<Player>(
        spriteRpgTexture, player3Spriteframes, Point(3, 0),
        ClipType::Contiguous, 1U, Direction::Horizontal, 0.8);
    player5->sprite->setFrameId(1U);

    explosion->Move(Rect(100, 150, 5, 5));
    player->Move(Rect(100, 350, 5, 5));
    player2->Move(Rect(250, 350, 5, 5));
    player3->Move(Rect(400, 350, 5, 5));
    player4->Move(Rect(550, 350, 5, 5));

    player5->Move(Rect(700, 350, 5, 5));

    spawning->Move(Rect(250, 150, 5, 5));
    shield->Move(Rect(350, 150, 5, 5));
    eagle->Move(Rect(450, 150, 5, 5));

    players.push_back(explosion);
    players.push_back(player);
    players.push_back(player2);
    players.push_back(player3);
    players.push_back(player4);
    players.push_back(player5);
    players.push_back(spawning);
    players.push_back(shield);
    players.push_back(eagle);
}
void PlayState::OnExit()
{
   
}
void PlayState::Update(float elapsed)
{
    for (size_t i = 0; i < players.size(); i++)
    {
        players.at(i)->Update(elapsed);
    }
}
void PlayState::Render()
{
    for (size_t i = 0; i < players.size(); i++)
    {
        players.at(i)->Render();
    }
}
void PlayState::OnKeydown(const Keyboard& keyboard)
{
    auto keys = keyboard.getKeysBitset();

    if (keys[doengine::SCANCODE_ESCAPE])
    {
        doengine::Application::getApplication()->Quit();
    }
}
void PlayState::OnKeyup(const Keyboard&)
{
}

int main(int argc, char* argv[])
{
    auto app = doengine::Application::getApplication();
    auto resolution =
        doengine::Application::getApplication()->getDisplayMode(0);
    doengine::Rect rect{resolution.w / 2, resolution.h};
    app->createWindow(rect);
    auto playstate = std::make_shared<PlayState>();
    app->addState(playstate, 1);
    app->setState(1);

    while (app->IsRunning())
    {
        app->PollEvent();
        app->Update();
        app->clearScreen(doengine::Colors::black);
        app->Render();
    }
    app->Quit();
    return 0;
    return 0;
}
