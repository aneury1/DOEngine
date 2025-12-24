#ifndef SCROLLABLE_LIST_H_DEFINED
#define SCROLLABLE_LIST_H_DEFINED
#include <vector>
#include <algorithm>

#include "Event.h"
#include "Geometric.h"
#include "Renderer.h"

/// Todo remove
#include <SDL2/SDL.h>

namespace doengine
{

class ScrollableContainer : public MouseEvent
{
  private:

    Renderer* renderer = nullptr;
    Rect containerRect;      // The visible container area
    std::vector<Rect> items; // List of items to display

    int scrollOffset;     // Current scroll position
    int maxScrollOffset;  // Maximum scroll value
    int itemSpacing;      // Padding between items
    int containerPadding; // Padding inside container

    // Scrollbar properties
    Rect scrollbarTrack;
    Rect scrollbarThumb;
    bool isScrollbarDragging;
    int dragStartY;
    int dragStartOffset;

    // Mouse/touch state
    bool isDragging;
    int lastMouseY;
    int dragVelocity;

    void calculateScrollbar()
    {
        int contentHeight = getContentHeight();
        int visibleHeight = containerRect.h - (2 * containerPadding);

        if (contentHeight <= visibleHeight)
        {
            scrollbarThumb.h = 0; // No scrollbar needed
            return;
        }

        // Scrollbar track
        scrollbarTrack.x = containerRect.x + containerRect.w - 10;
        scrollbarTrack.y = containerRect.y;
        scrollbarTrack.w = 10;
        scrollbarTrack.h = containerRect.h;

        // Scrollbar thumb
        float thumbRatio = (float)visibleHeight / contentHeight;
        scrollbarThumb.w = 8;
        scrollbarThumb.h = std::max(20, (int)(scrollbarTrack.h * thumbRatio));
        scrollbarThumb.x = scrollbarTrack.x + 1;

        // Calculate thumb position based on scroll offset
        float scrollRatio = (float)scrollOffset / maxScrollOffset;
        int maxThumbY = scrollbarTrack.h - scrollbarThumb.h;
        scrollbarThumb.y = containerRect.y + (int)(scrollRatio * maxThumbY);
    }

    int getContentHeight() const
    {
        if (items.empty())
            return 0;
        return items.size() * (items[0].h + itemSpacing) - itemSpacing;
    }

  public:
    ScrollableContainer(int x, int y, int width, int height, int padding = 5,
                        int spacing = 5)
        : scrollOffset(0), maxScrollOffset(0), itemSpacing(spacing),
          containerPadding(padding), isScrollbarDragging(false),
          isDragging(false), lastMouseY(0), dragVelocity(0)
    {

        containerRect = {x, y, width, height};
        renderer = Application::getApplication()->getRender();
    }

    void setItems(const std::vector<Rect>& itemList)
    {
        items = itemList;

        // Position items vertically
        int currentY = containerPadding;
        for (auto& item : items)
        {
            item.y = currentY;
            currentY += item.h + itemSpacing;
        }

        // Calculate max scroll offset
        int contentHeight = getContentHeight();
        int visibleHeight = containerRect.h - (2 * containerPadding);
        maxScrollOffset = std::max(0, contentHeight - visibleHeight);
        scrollOffset = std::min(scrollOffset, maxScrollOffset);

        calculateScrollbar();
    }

    virtual void MouseWheel(const Mouse& mouse)
    {
        scroll(-mouse.getWheelScroll().y *
               15); // Scroll 15 pixels per wheel tick
    }
    virtual void MouseMove(const Mouse& mouse)
    {
        Point motion; 
        motion.x = mouse.getMotionPosition().x;
        motion.y = mouse.getMotionPosition().y;
        if (isScrollbarDragging)
        {
                int deltaY = motion.y - dragStartY;
                int contentHeight = getContentHeight();
                int visibleHeight = containerRect.h - (2 * containerPadding);
                int maxThumbY = scrollbarTrack.h - scrollbarThumb.h;

                if (maxThumbY > 0)
                {
                    float scrollRatio = (float)deltaY / maxThumbY;
                    int newOffset =
                        dragStartOffset + (int)(scrollRatio * maxScrollOffset);
                    scrollOffset = std::clamp(newOffset, 0, maxScrollOffset);
                    calculateScrollbar();
                }
        }
        else if (isDragging)
        {
                int deltaY = motion.y - lastMouseY;
                dragVelocity = deltaY;
                scroll(-deltaY); // Invert for natural scrolling
                lastMouseY = motion.y;
        }
    }
    virtual void MouseButtonDown(const Mouse& mouse)
    {
        if (mouse.getButtonPressed() == Mouse::MouseButtonDown::Left)
        {

            Rect mousePosition = mouse.getMousePosition();
            int mx = mousePosition.x; /// event.button.x;
            int my = mousePosition.y; /// event.button.y;
            Point of{mx, my};
            // Check if clicking on scrollbar thumb
            if (checkPointOnRect(of, scrollbarThumb))
            {
                isScrollbarDragging = true;
                dragStartY = my;
                dragStartOffset = scrollOffset;
            }
            // Check if clicking in container
            else if (checkPointOnRect(of, containerRect))
            {
                isDragging = true;
                lastMouseY = my;
                dragVelocity = 0;
            }
        }
    }
    virtual void MouseButtonUp(const Mouse& mouse)
    {
        if (mouse.getButtonPressed() == Mouse::MouseButtonDown::Left)
        {
            isScrollbarDragging = false;
            isDragging = false;
        }
    }
#if 0
    void handleEvent(const SDL_Event& event)
    {
        switch (event.type)
        {
        case SDL_MOUSEWHEEL:
            scroll(-event.wheel.y * 15); // Scroll 15 pixels per wheel tick
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                int mx = event.button.x;
                int my = event.button.y;
                SDL_Point of{mx, my};
                // Check if clicking on scrollbar thumb
                if (SDL_PointInRect(&of, &scrollbarThumb))
                {
                    isScrollbarDragging = true;
                    dragStartY = my;
                    dragStartOffset = scrollOffset;
                }
                // Check if clicking in container
                else if (SDL_PointInRect(&of, &containerRect))
                {
                    isDragging = true;
                    lastMouseY = my;
                    dragVelocity = 0;
                }
            }
            break;

        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                isScrollbarDragging = false;
                isDragging = false;
            }
            break;

        case SDL_MOUSEMOTION:
            if (isScrollbarDragging)
            {
                int deltaY = event.motion.y - dragStartY;
                int contentHeight = getContentHeight();
                int visibleHeight = containerRect.h - (2 * containerPadding);
                int maxThumbY = scrollbarTrack.h - scrollbarThumb.h;

                if (maxThumbY > 0)
                {
                    float scrollRatio = (float)deltaY / maxThumbY;
                    int newOffset =
                        dragStartOffset + (int)(scrollRatio * maxScrollOffset);
                    scrollOffset = std::clamp(newOffset, 0, maxScrollOffset);
                    calculateScrollbar();
                }
            }
            else if (isDragging)
            {
                int deltaY = event.motion.y - lastMouseY;
                dragVelocity = deltaY;
                scroll(-deltaY); // Invert for natural scrolling
                lastMouseY = event.motion.y;
            }
            break;

        case SDL_FINGERDOWN:
            isDragging = true;
            lastMouseY = (int)(event.tfinger.y * containerRect.h);
            dragVelocity = 0;
            break;

        case SDL_FINGERUP:
            isDragging = false;
            break;

        case SDL_FINGERMOTION:
            if (isDragging)
            {
                int currentY = (int)(event.tfinger.y * containerRect.h);
                int deltaY = currentY - lastMouseY;
                dragVelocity = deltaY;
                scroll(-deltaY * 2); // Touch is often more sensitive
                lastMouseY = currentY;
            }
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                scroll(-20);
                break;
            case SDLK_DOWN:
                scroll(20);
                break;
            case SDLK_PAGEUP:
                scroll(-containerRect.h);
                break;
            case SDLK_PAGEDOWN:
                scroll(containerRect.h);
                break;
            case SDLK_HOME:
                scrollOffset = 0;
                calculateScrollbar();
                break;
            case SDLK_END:
                scrollOffset = maxScrollOffset;
                calculateScrollbar();
                break;
            }
            break;
        }
    }
 #endif
    void scroll(int delta)
    {
        scrollOffset = std::clamp(scrollOffset + delta, 0, maxScrollOffset);
        calculateScrollbar();
    }

    void Render()
    {
        if(!renderer)return ;
        // Draw container background
        ////SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
        ////SDL_RenderFillRect(renderer, &containerRect);
        renderer->DrawFillRect(containerRect,{40,40,40,255});
        // Set up clipping rectangle for scrollable area
        Rect clipRect = {containerRect.x + containerPadding,
                         containerRect.y + containerPadding,
                         containerRect.w - (2 * containerPadding) -
                             12, // Leave room for scrollbar
                         containerRect.h - (2 * containerPadding)};
        
        renderer->RenderSetClipRect(clipRect);

        // Draw items
        ////SDL_SetRenderDrawColor(renderer, 80, 120, 200, 255);
        for (const auto& item : items)
        {
            Rect renderRect = item;
            renderRect.x = containerRect.x + containerPadding + 5;
            renderRect.y =
                containerRect.y + containerPadding + item.y - scrollOffset;

            // Only render if visible
            if (renderRect.y + renderRect.h >= clipRect.y &&
                renderRect.y <= clipRect.y + clipRect.h)
            {
                ///SDL_RenderFillRect(renderer, &renderRect);
                renderer->DrawFillRect(renderRect, {80,120,220,255});
                // Draw border
                ////SDL_SetRenderDrawColor(renderer, 120, 160, 240, 255);
                ////SDL_RenderDrawRect(renderer, &renderRect);
                renderer->DrawRect(renderRect, {120,160,240,255});
                ////SDL_SetRenderDrawColor(renderer, 80, 120, 200, 255);
            }
        }

        // Clear clipping
        renderer->ResetRenderSetClipRect();

        // Draw scrollbar track
        if (scrollbarThumb.h > 0)
        {
            ///SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
            ///SDL_RenderFillRect(renderer, &scrollbarTrack);
            renderer->DrawFillRect(scrollbarTrack, {60,60,60,255});
            // Draw scrollbar thumb
            ///SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
            ///SDL_RenderFillRect(renderer, &scrollbarThumb);
            renderer->DrawFillRect(scrollbarThumb, {120,120,120,255});

        }

        // Draw container border
        ////SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        ///SDL_RenderDrawRect(renderer, &containerRect);
        renderer->DrawRect(containerRect, {100,100,100,255});
    }
};
} // namespace doengine
#endif