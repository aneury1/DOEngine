#pragma once

#include <vector>

#include "Renderer.h"
#include "Texture.h"

namespace doengine
{

enum class ClipType
{
    Contiguous,
    Free
};

class Sprite
{
  public:
    Sprite(Texture* texture, std::vector<Rect>& frames, Point& offset,
           Renderer& renderer, Point& dst_size,
           const ClipType = ClipType::Contiguous);

    ~Sprite();

    virtual void Draw(const Point& pos);
    virtual void Update(const long deltaTime);

    virtual void SetClipType(const ClipType type);
    virtual ClipType GetClipType() const;

    virtual Texture* GetTexture() const;

  protected:
    Renderer& renderer;
    std::vector<Rect>& frames;
    Texture* texture;
    Point& offset;
    ClipType clipType;
    Point dst_size;
    std::vector<Rect>::iterator frame_it;
};
} // namespace doengine
