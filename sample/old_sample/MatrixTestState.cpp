#include "MatrixTestState.h"
#include "Canvas.h"
#include "TTFText.h"
#include "Utils.h"

const char* charset =
    "QWERTYUIOPASDFGHJKLZXCVBNM,./1234567890-=!@#$%^&*()_+*/.\"\'`";

class Symbol
{

    int canvas_h;
    SDL_Point point;
    int fnt_size;
    Canvas* canvas;

    SDL_Color color;

    int inty = 0;

  public:
    Symbol(int fontsize, int x, int y, int canvasHeight)
    {
        color = {0x0A, 0xFF, 0x0a, 255};
        canvas_h = canvasHeight;
        point.x = x;
        point.y = inty = y;
        fnt_size = fontsize;
    }

    void draw(Canvas* canvas)
    {
        std::string str;
        str += charset[getRandomInt(0, 59)];
        canvas->fillColor(color);
        canvas->FillText(str.c_str(), point.x * fnt_size, point.y * fnt_size);
        if (point.y * fnt_size > canvas_h)
            point.y = inty;
        else
            point.y += 1;

        if (point.y > 0)
        {
            color.g -= 1;
        }
        else
        {
            color.g = 0xff;
        }
    }
};

class Effect
{

    int width;
    int height;
    int fontsize;
    int columns;
    std::vector<Symbol*> symbols;
    Canvas* ctx;

  public:
    Effect(Canvas* canvas)
    {
        ctx = canvas;
        fontsize = 25;
        width = canvas->getCanvasSize().w;
        height = canvas->getCanvasSize().h;
        columns = width / fontsize;

        for (int i = 0; i < columns - 5; i++)
        {
            symbols.push_back(new Symbol(fontsize, i + 4, 10, height));
        }
    }

    void Draw()
    {
        for (auto it : symbols)
        {
            it->draw(ctx);
        }
    }
};

Effect* effect = nullptr;

void MatrixTestState::OnEnter()
{
    canvas = new Canvas(this->window);
    canvas->setCanvasBackgroundColor({0, 0, 0, 255});
    canvas->fillColor({0x0A, 0xFF, 0x0a, 255});
    effect = new Effect(canvas);
}
void MatrixTestState::OnExit()
{
}
void MatrixTestState::Update(float elapsed)
{
    canvas->clearCanvas();
}
void MatrixTestState::Render()
{
    //// canvas->clearCanvas();
    effect->Draw();
    canvas->update();
}