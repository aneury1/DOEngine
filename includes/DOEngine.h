#ifndef DOENGINE_HPP_DEFINED
#define DOENGINE_HPP_DEFINED

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#ifdef NAMESPACE
#define DOENGINE_NAME_START                                                    \
    namespace doengine                                                         \
    {
#define DOENGINE_NAME_END }
#else
#define DOENGINE_NAME_START namespace doengine
#define DOENGINE_NAME_END
#endif

#ifdef OFF

#include "Application.h"
#include "Event.h"
#include "EventHandler.h"
#include "FPSManager.h"
#include "GameObject.h"
#include "GameStateManager.h"
#include "Geometric.h"
#include "Grids.h"
#include "LinkList.h"
#include "Sprite.h"
#include "TTFText.h"
#include "Tile.h"
#include "Tilemap.h"
#include "UDPPacket.h"
#include "Vector.h"
#include "defines.h"
#include "sort.h"

#endif

#endif