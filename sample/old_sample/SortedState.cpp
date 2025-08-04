#include "SortedState.h"
#include "Utils.h"

void SortedState::OnEnter()
{

    this->ctx = new Canvas(window);
    this->ctx->setCanvasBackgroundColor(Canvas::black);

    this->height = window->getH() - 100;

    width = 48;

    int nTimes = (window->getW() / width) - 4;

    for (int i = 0; i < nTimes; i++)
    {
        ColumnEntry* entry = new ColumnEntry();
        entry->offset.x = i * width;
        entry->offset.y = 0;
        entry->offset.w = width;
        entry->value = getRandomInt(10, 1000);
        entry->offset.h = getPercentageFrom(entry->value, 1000);
        this->entries.push_back(entry);
        /// SDL_Log("value = %ld, height=%ld", entry->value, entry->offset.h);
    }

    ctx->fillColor(
        {200, 200, static_cast<unsigned char>(getRandomInt(0, 234)), 255});
}
void SortedState::OnExit()
{
}
void SortedState::Update(float elapsed)
{
}

void SortedState::Render()
{

    for (auto it : entries)
    {
        ctx->DrawRect(it->offset.x + 100, it->offset.y + 100, it->offset.w,
                      it->offset.h, false);

        ctx->DrawRect(it->offset.x + 108, it->offset.y + 104, it->offset.w - 12,
                      it->offset.h - 14, true);
    }
    ctx->update();
}
