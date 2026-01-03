#ifndef SPRITE_OFFSET_H_DEFINED
#define SPRITE_OFFSET_H_DEFINED
#include <vector>
#include "Geometric.h"
#include "Logger.h"


namespace doengine
{

struct SpriteOffset
{
    int id;
    std::vector<doengine::Rect> spriteOffset;

    int current = 0;
    bool ended = false;
    bool rewind = true;

    double frameDuration = 0.1;   // seconds per frame
    double accumulator = 0.0;

    explicit SpriteOffset(int id, std::vector<doengine::Rect> offsets)
        : id{id},
          spriteOffset{std::move(offsets)}
    {
    }

    void update(double deltaTime)
    {
        doengine::LogOuput(doengine::logger_type::Information, "detal Time %lf", deltaTime);
        if ((ended && !rewind) || spriteOffset.empty())
            return;
        if(ended && rewind)
            reset();

        accumulator += deltaTime;

        while (accumulator >= frameDuration)
        {
            accumulator -= frameDuration;
            current++;

            if (current >= static_cast<int>(spriteOffset.size()))
            {
                current = static_cast<int>(spriteOffset.size()) - 1;
                ended = true;
                break;
            }
        }
    }

    doengine::Rect getCurrentOffset() const
    {
        return spriteOffset[current];
    }

    void reset()
    {
        current = 0;
        accumulator = 0.0;
        ended = false;
    }

    bool finish() const
    {
        return ended;
    }
};


}


#endif
