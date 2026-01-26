#pragma once
#include <algorithm>
#include "Camera.h"
#include "Geometric.h"

namespace doengine
{


class Camera
{
public:
    enum class CameraMovement
    {
        CameraUp,
        CameraDown,
        CameraLeft,
        CameraRight
    };

private:
    Point position;          // Camera position (usually negative for scrolling)
    Point targetPosition;    // Target position for smooth following
    int viewportWidth;       // Screen width
    int viewportHeight;      // Screen height
    int tileSize;            // Size of each tile
    
    // Bounds
    bool boundsEnabled;
    int minX, minY;          // Minimum camera position (usually negative)
    int maxX, maxY;          // Maximum camera position (usually 0)
    
    // Smoothing
    float smoothingFactor;   // Interpolation factor (0.0 - 1.0)
    bool smoothingEnabled;
    
    // Cached values for optimization
    int rowOffset;
    int colOffset;
    int rowsToRender;
    int colsToRender;
    
public:
    Camera(int viewportW, int viewportH, int tileSize, float smoothing = 0.1f)
        : position(0, 0),
          targetPosition(0, 0),
          viewportWidth(viewportW),
          viewportHeight(viewportH),
          tileSize(tileSize),
          boundsEnabled(false),
          minX(0), minY(0),
          maxX(0), maxY(0),
          smoothingFactor(smoothing),
          smoothingEnabled(true),
          rowOffset(0),
          colOffset(0),
          rowsToRender(0),
          colsToRender(0)
    {
        updateCachedValues();
    }

    void update(float deltaTime)
    {
        if (smoothingEnabled)
        {
            // Smooth interpolation towards target
            float factor = std::min(1.0f, smoothingFactor * deltaTime * 60.0f); // Normalize for 60 FPS
            position.x += (int)((targetPosition.x - position.x) * factor);
            position.y += (int)((targetPosition.y - position.y) * factor);
        }
        else
        {
            // Instant movement
            position = targetPosition;
        }
        
        // Apply bounds
        if (boundsEnabled)
        {
            applyBounds();
        }
        
        // Update cached values
        updateCachedValues();
    }

    void centerOn(const Point& worldPos)
    {
        // Center camera on a world position
        targetPosition.x = -(worldPos.x - viewportWidth / 2);
        targetPosition.y = -(worldPos.y - viewportHeight / 2);
        
        if (boundsEnabled)
        {
            targetPosition.x = std::max(minX, std::min(maxX, targetPosition.x));
            targetPosition.y = std::max(minY, std::min(maxY, targetPosition.y));
        }
    }

    void centerOn(int worldX, int worldY)
    {
        centerOn(Point(worldX, worldY));
    }

    void moveCamera(CameraMovement direction, int speed)
    {
        switch (direction)
        {
            case CameraMovement::CameraUp:
                targetPosition.y += speed;
                break;
            case CameraMovement::CameraDown:
                targetPosition.y -= speed;
                break;
            case CameraMovement::CameraLeft:
                targetPosition.x += speed;
                break;
            case CameraMovement::CameraRight:
                targetPosition.x -= speed;
                break;
        }
        
        if (boundsEnabled)
        {
            targetPosition.x = std::max(minX, std::min(maxX, targetPosition.x));
            targetPosition.y = std::max(minY, std::min(maxY, targetPosition.y));
        }
    }

    void setPosition(const Point& pos)
    {
        position = pos;
        targetPosition = pos;
        
        if (boundsEnabled)
        {
            applyBounds();
        }
        
        updateCachedValues();
    }

    void setPosition(int x, int y)
    {
        setPosition(Point(x, y));
    }

    Point getPosition() const
    {
        return position;
    }

    void setBounds(int minX, int minY, int maxX, int maxY)
    {
        this->minX = minX;
        this->minY = minY;
        this->maxX = maxX;
        this->maxY = maxY;
    }

    void enableBounds(bool enabled)
    {
        boundsEnabled = enabled;
    }

    void setSmoothing(float factor)
    {
        smoothingFactor = std::max(0.0f, std::min(1.0f, factor));
    }

    void enableSmoothing(bool enabled)
    {
        smoothingEnabled = enabled;
    }

    // Get visible tile range
    int getRowOffset() const { return rowOffset; }
    int getColOffset() const { return colOffset; }
    int getRowsToRender() const { return rowsToRender; }
    int getColsToRender() const { return colsToRender; }

    // Viewport dimensions
    int getViewportWidth() const { return viewportWidth; }
    int getViewportHeight() const { return viewportHeight; }

    // Coordinate conversions
    Point worldToScreen(int worldX, int worldY) const
    {
        return Point(worldX + position.x, worldY + position.y);
    }

    Point screenToWorld(int screenX, int screenY) const
    {
        return Point(screenX - position.x, screenY - position.y);
    }

    // Check if a world rectangle is visible
    bool isVisible(int worldX, int worldY, int width, int height) const
    {
        Point screenPos = worldToScreen(worldX, worldY);
        return !(screenPos.x + width < 0 || 
                 screenPos.x > viewportWidth ||
                 screenPos.y + height < 0 || 
                 screenPos.y > viewportHeight);
    }

    // Check if a tile is visible
    bool isTileVisible(int tileRow, int tileCol) const
    {
        return tileCol >= colOffset && 
               tileCol < colOffset + colsToRender &&
               tileRow >= rowOffset && 
               tileRow < rowOffset + rowsToRender;
    }

private:
    void applyBounds()
    {
        position.x = std::max(minX, std::min(maxX, position.x));
        position.y = std::max(minY, std::min(maxY, position.y));
        targetPosition.x = std::max(minX, std::min(maxX, targetPosition.x));
        targetPosition.y = std::max(minY, std::min(maxY, targetPosition.y));
    }

    void updateCachedValues()
    {
        // Calculate which tiles are visible
        colOffset = std::max(0, -position.x / tileSize);
        rowOffset = std::max(0, -position.y / tileSize);
        
        // Add 2 extra tiles for safety (partial tiles at edges)
        colsToRender = (viewportWidth / tileSize) + 2;
        rowsToRender = (viewportHeight / tileSize) + 2;
    }
};

 

} // namespace doengine
