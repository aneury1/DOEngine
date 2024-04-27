#ifndef DOENGINE_HPP_DEFINED
#define DOENGINE_HPP_DEFINED

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <string>

#ifdef NAMESPACE 
#define DOENGINE_NAME_START namespace doengine{
#define DOENGINE_NAME_END }
#else
#define DOENGINE_NAME_START namespace doengine
#define DOENGINE_NAME_END 
#endif

#ifdef OFF

#include "defines.h"
#include "Application.h"
#include "sort.h"
#include "LinkList.h"
#include "EventHandler.h"
#include "Event.h"
#include "FPSManager.h"
#include "Geometric.h"
#include "GameObject.h"
#include "GameStateManager.h"
#include "Grids.h"
#include "Sprite.h"
#include "LinkList.h"
#include "Tile.h"
#include "Tilemap.h"
#include "TTFText.h"
#include "UDPPacket.h"
#include "Vector.h"
#include "Application.h"


#endif

#endif