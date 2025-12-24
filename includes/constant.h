#ifndef CONSTANT_H_DEFINED
#define CONSTANT_H_DEFINED

namespace doengine
{

enum class LayerId : int{
    BeginnerLayer=-1,
    Background1=0,
    Background2=1,
    Background3=2,
    Background4=3,
    Background5=4,
    BackgroundEffect1=5,
    Tile1,
    Tile2,
    Tile3,
    Tile4,
    
    Event1,
    Event2,
    Event3,

    UiContainer,
    UiChild,
    UiSubChild,
    DebugScreen,
    UltrHighEvent,
    LastEvent
};

}

#endif
