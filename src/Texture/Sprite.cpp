#include "Sprite.h"

namespace doengine
{

Sprite::Sprite(Texture* texture, std::vector<Rect>& frames, Point& offset,
               Renderer& renderer, Point& dst_size, const ClipType type)
    : renderer(renderer), texture(texture), frames(frames), offset(offset),
      dst_size(dst_size), clipType(type)
{
    frame_it = frames.begin();
}

Sprite::~Sprite()
{
    texture = nullptr;
}

void Sprite::Draw(const Point& pos)
{
    switch (clipType)
    {
    case ClipType::Contiguous: {
        int x = (*frame_it).x;
        int y = (*frame_it).y;
        Rect srcRect{x, y, (*frame_it).w, (*frame_it).h};
        Rect dstRect{pos.x, pos.y, dst_size.x, dst_size.y};
        texture->Draw(dstRect, srcRect);
        x = (*frame_it).x + offset.x;
        y = (*frame_it).y + offset.y;
    }
    break;

    case ClipType::Free: {
        Rect srcRect{(*frame_it).x, (*frame_it).y, (*frame_it).w,
                     (*frame_it).h};
        Rect dstRect{pos.x, pos.y, dst_size.x, dst_size.y};
        texture->Draw(dstRect, srcRect);
    }
    break;
    default:
        break;
    }
}
void Sprite::Update(const long deltaTime)
{
    frame_it++;
}

void Sprite::SetClipType(const ClipType type)
{
    clipType = type;
}

ClipType Sprite::GetClipType() const
{
    return clipType;
}

Texture* Sprite::GetTexture() const
{
    return texture;
}

} // namespace doengine
