#include "Sprite.h"

namespace doengine
{

Sprite::Sprite(std::shared_ptr<Texture> texture, const std::vector<Rect>& frames,
               const Point& offset, const ClipType type,
               const size_t spritesCount, const Direction direction)
    : texture(texture), frames(frames), offset(offset), duration(0.0f),
      startTime(0.0f), clipType(type), animId(0U), spriteCount(spritesCount),
      direction(direction)
{
    if (clipType == ClipType::Free)
    {
        spriteCount = frames.size();
    }
}

Sprite::Sprite(int textureId, const std::vector<Rect>& frames,
               const Point& offset, const ClipType type,
               const size_t spritesCount, const Direction direction)
    : texture(texture), frames(frames), offset(offset), duration(0.0f),
      startTime(0.0f), clipType(type), animId(0U), spriteCount(spritesCount),
      direction(direction)
{
    texture = TextureManager::getTextureManager()->getTexture(textureId);
}

Sprite::~Sprite()
{
}

void Sprite::Draw(const Rect& dstRect)
{
    Rect clipRect(0, 0, frames.front().w, frames.front().h);
    switch (direction)
    {
    case Direction::Horizontal:
        clipRect.x = frames.front().x +
                     ((offset.x + frames.front().w) * static_cast<int>(animId));
        clipRect.y = offset.y + frames.front().y;
        break;
    case Direction::Vertical:
        clipRect.x = offset.x + frames.front().x;
        clipRect.y = frames.front().y +
                     ((offset.y + frames.front().h) * static_cast<int>(animId));
        break;
    case Direction::Diagonal:
        clipRect.x = offset.x + frames.front().x +
                     (frames.front().w * static_cast<int>(animId));
        clipRect.y = offset.y + frames.front().y +
                     (frames.front().h * static_cast<int>(animId));
        break;
    case Direction::None:
    default:
        break;
    }

    switch (clipType)
    {
    case ClipType::Contiguous: {
        texture->Draw({dstRect.x - (frames.front().w * dstRect.w) / 2,
                       dstRect.y - (frames.front().h * dstRect.h) / 2,
                       frames.front().w * dstRect.w,
                       frames.front().h * dstRect.h},
                      clipRect);
    }
    break;

    case ClipType::Free:
        texture->Draw({dstRect.x - (frames.at(animId).w * dstRect.w) / 2,
                       dstRect.y - (frames.at(animId).h * dstRect.h) / 2,
                       frames.at(animId).w * dstRect.w,
                       frames.at(animId).h * dstRect.h},
                      frames.at(animId));
    default:
        break;
    }
}
void Sprite::Update(const float deltaTime)
{
    const float timeslot = duration / spriteCount;
    if ((startTime > timeslot) && (spriteCount > 1))
    {
        animId = ++animId % spriteCount;
        startTime = 0.0f;
    }

    startTime += deltaTime;
}

void Sprite::setClipType(const ClipType type)
{
    clipType = type;
}

void Sprite::setDuration(const float duration)
{
    this->duration = duration;
}

void Sprite::setSpriteCount(const size_t spriteCount)
{
    this->spriteCount = spriteCount;
}

void Sprite::setFrameId(const size_t frameId)
{
    this->animId = frameId;
}

void Sprite::setDirection(const Direction direction)
{
    this->direction = direction;
}

ClipType Sprite::getClipType() const
{
    return clipType;
}

std::shared_ptr<Texture> Sprite::getTexture() const
{
    return texture;
}

size_t Sprite::getSpriteCount() const
{
    return spriteCount;
}

size_t Sprite::getFrameId() const
{
    return animId;
}

Direction Sprite::getDirection() const
{
    return direction;
}

} // namespace doengine
