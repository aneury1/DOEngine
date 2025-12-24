#include "EventHandler.h"
#include "Event.h"
#include "Logger.h"

namespace doengine
{
   KeyboardInputhandlingEvent::KeyboardInputhandlingEvent()
   {
       doengine::Event::AddKeyboardEvent(this);
   }
    KeyboardInputhandlingEvent::~KeyboardInputhandlingEvent()
   {
       doengine::Event::RemoveKeyboardEvent(this);
   }

   MouseEvent::MouseEvent()
   {
      doengine::Event::AddMouseEvent(this);
   }
   MouseEvent::~MouseEvent()
   {
      doengine::Event::RemovedMouseEvent(this);
   }

   TextInputEvent::TextInputEvent()
   {
      doengine::Event::AddTextInputEvent(this);
   }
   TextInputEvent::~TextInputEvent()
   {
      doengine::Event::RemoveTextInputEvent(this);
   }
}