#pragma once

#include "gmock/gmock.h"

// TODO issue-27 Remove SDL code
typedef unsigned int Uint32;
typedef int Sint32;
typedef short Sint16;
typedef unsigned char Uint8;
typedef unsigned short Uint16;
typedef Sint32 SDL_Keycode;
typedef Uint32 SDL_JoystickID;

#define SDL_RELEASED 0
#define SDL_PRESSED 1

#define SDL_BUTTON(X) (1 << ((X)-1))
#define SDL_BUTTON_LEFT 1
#define SDL_BUTTON_MIDDLE 2
#define SDL_BUTTON_RIGHT 3
#define SDL_BUTTON_X1 4
#define SDL_BUTTON_X2 5
#define SDL_BUTTON_LMASK SDL_BUTTON(SDL_BUTTON_LEFT)
#define SDL_BUTTON_MMASK SDL_BUTTON(SDL_BUTTON_MIDDLE)
#define SDL_BUTTON_RMASK SDL_BUTTON(SDL_BUTTON_RIGHT)
#define SDL_BUTTON_X1MASK SDL_BUTTON(SDL_BUTTON_X1)
#define SDL_BUTTON_X2MASK SDL_BUTTON(SDL_BUTTON_X2)

typedef enum
{
    SDL_FALSE = 0u,
    SDL_TRUE = 1U
} SDL_bool;

typedef enum
{
    KMOD_NONE = 0x0000,
    KMOD_LSHIFT = 0x0001,
    KMOD_RSHIFT = 0x0002,
    KMOD_LCTRL = 0x0040,
    KMOD_RCTRL = 0x0080,
    KMOD_LALT = 0x0100,
    KMOD_RALT = 0x0200,
    KMOD_LGUI = 0x0400,
    KMOD_RGUI = 0x0800,
    KMOD_NUM = 0x1000,
    KMOD_CAPS = 0x2000,
    KMOD_MODE = 0x4000,
    KMOD_SCROLL = 0x8000,

    KMOD_CTRL = KMOD_LCTRL | KMOD_RCTRL,
    KMOD_SHIFT = KMOD_LSHIFT | KMOD_RSHIFT,
    KMOD_ALT = KMOD_LALT | KMOD_RALT,
    KMOD_GUI = KMOD_LGUI | KMOD_RGUI
} SDL_Keymod;

struct SDL_Point
{
    int x;
    int y;
};

// The following definitions were obtain from SDL repo.
// Specifically from this file:
// https://github.com/libsdl-org/SDL/blob/SDL2/include/SDL_events.h

typedef enum
{
    SDL_FIRSTEVENT = 0,
    SDL_QUIT = 0x100,
    SDL_APP_TERMINATING,
    SDL_APP_LOWMEMORY,
    SDL_APP_WILLENTERBACKGROUND,
    SDL_APP_DIDENTERBACKGROUND,
    SDL_APP_WILLENTERFOREGROUND,
    SDL_APP_DIDENTERFOREGROUND,
    SDL_LOCALECHANGED,
    SDL_DISPLAYEVENT = 0x150,
    SDL_WINDOWEVENT = 0x200,
    SDL_SYSWMEVENT,
    SDL_KEYDOWN = 0x300,
    SDL_KEYUP,
    SDL_TEXTEDITING,
    SDL_TEXTINPUT,
    SDL_KEYMAPCHANGED,
    SDL_TEXTEDITING_EXT,
    SDL_MOUSEMOTION = 0x400,   /**< Mouse moved */
    SDL_MOUSEBUTTONDOWN,       /**< Mouse button pressed */
    SDL_MOUSEBUTTONUP,         /**< Mouse button released */
    SDL_MOUSEWHEEL,            /**< Mouse wheel motion */
    SDL_JOYAXISMOTION = 0x600, /**< Joystick axis motion */
    SDL_JOYBALLMOTION,         /**< Joystick trackball motion */
    SDL_JOYHATMOTION,          /**< Joystick hat position change */
    SDL_JOYBUTTONDOWN,         /**< Joystick button pressed */
    SDL_JOYBUTTONUP,           /**< Joystick button released */
    SDL_JOYDEVICEADDED, /**< A new joystick has been inserted into the system */
    SDL_JOYDEVICEREMOVED,  /**< An opened joystick has been removed */
    SDL_JOYBATTERYUPDATED, /**< Joystick battery level change */
    SDL_CONTROLLERAXISMOTION = 0x650, /**< Game controller axis motion */
    SDL_CONTROLLERBUTTONDOWN,         /**< Game controller button pressed */
    SDL_CONTROLLERBUTTONUP,           /**< Game controller button released */
    SDL_CONTROLLERDEVICEADDED,
    SDL_CONTROLLERDEVICEREMOVED,
    SDL_CONTROLLERDEVICEREMAPPED, /**< The controller mapping was updated */
    SDL_CONTROLLERTOUCHPADDOWN,   /**< Game controller touchpad was touched */
    SDL_CONTROLLERTOUCHPADMOTION,
    SDL_CONTROLLERTOUCHPADUP, /**< Game controller touchpad finger was lifted */
    SDL_CONTROLLERSENSORUPDATE, /**< Game controller sensor was updated */
    SDL_CONTROLLERUPDATECOMPLETE_RESERVED_FOR_SDL3,
    SDL_CONTROLLERSTEAMHANDLEUPDATED,
    SDL_FINGERDOWN = 0x700,
    SDL_FINGERUP,
    SDL_FINGERMOTION,
    SDL_DOLLARGESTURE = 0x800,
    SDL_DOLLARRECORD,
    SDL_MULTIGESTURE,
    SDL_CLIPBOARDUPDATE = 0x900,
    SDL_DROPFILE = 0x1000, /**< The system requests a file open */
    SDL_DROPTEXT,          /**< text/plain drag-and-drop event */
    SDL_DROPBEGIN, /**< A new set of drops is beginning (NULL filename) */
    SDL_DROPCOMPLETE,
    SDL_AUDIODEVICEADDED = 0x1100, /**< A new audio device is available */
    SDL_AUDIODEVICEREMOVED,        /**< An audio device has been removed. */
    SDL_SENSORUPDATE = 0x1200,     /**< A sensor was updated */
    SDL_RENDER_TARGETS_RESET = 0x2000,
    SDL_RENDER_DEVICE_RESET,
    SDL_POLLSENTINEL = 0x7F00, /**< Signals the end of an event poll cycle */
    SDL_USEREVENT = 0x8000,
    SDL_LASTEVENT = 0xFFFF
} SDL_EventType;

struct SDL_MouseMotionEvent
{
    Uint32 type;      /**< ::SDL_MOUSEMOTION */
    Uint32 timestamp; /**< In milliseconds, populated using SDL_GetTicks() */
    Uint32 windowID;  /**< The window with mouse focus, if any */
    Uint32 which;     /**< The mouse instance id, or SDL_TOUCH_MOUSEID */
    Uint32 state;     /**< The current button state */
    Sint32 x;         /**< X coordinate, relative to window */
    Sint32 y;         /**< Y coordinate, relative to window */
    Sint32 xrel;      /**< The relative motion in the X direction */
    Sint32 yrel;      /**< The relative motion in the Y direction */
};

/**
 *  \brief Mouse button event structure (event.button.*)
 */
struct SDL_MouseButtonEvent
{
    Uint32 type;      /**< ::SDL_MOUSEBUTTONDOWN or ::SDL_MOUSEBUTTONUP */
    Uint32 timestamp; /**< In milliseconds, populated using SDL_GetTicks() */
    Uint32 windowID;  /**< The window with mouse focus, if any */
    Uint32 which;     /**< The mouse instance id, or SDL_TOUCH_MOUSEID */
    Uint8 button;     /**< The mouse button index */
    Uint8 state;      /**< ::SDL_PRESSED or ::SDL_RELEASED */
    Uint8 clicks;     /**< 1 for single-click, 2 for double-click, etc. */
    Uint8 padding1;
    Sint32 x; /**< X coordinate, relative to window */
    Sint32 y; /**< Y coordinate, relative to window */
};

/**
 *  \brief Mouse wheel event structure (event.wheel.*)
 */
struct SDL_MouseWheelEvent
{
    Uint32 type;      /**< ::SDL_MOUSEWHEEL */
    Uint32 timestamp; /**< In milliseconds, populated using SDL_GetTicks() */
    Uint32 windowID;  /**< The window with mouse focus, if any */
    Uint32 which;     /**< The mouse instance id, or SDL_TOUCH_MOUSEID */
    Sint32 x; /**< The amount scrolled horizontally, positive to the right and
                 negative to the left */
    Sint32 y; /**< The amount scrolled vertically, positive away from the user
                 and negative toward the user */
    Uint32 direction; /**< Set to one of the SDL_MOUSEWHEEL_* defines. When
                         FLIPPED the values in X and Y will be opposite.
                         Multiply by -1 to change them back */
    float preciseX; /**< The amount scrolled horizontally, positive to the right
                       and negative to the left, with float precision (added
                       in 2.0.18) */
    float preciseY; /**< The amount scrolled vertically, positive away from the
                       user and negative toward the user, with float precision
                       (added in 2.0.18) */
    Sint32 mouseX;  /**< X coordinate, relative to window (added in 2.26.0) */
    Sint32 mouseY;  /**< Y coordinate, relative to window (added in 2.26.0) */
};

typedef enum
{
    SDL_JOYSTICK_POWER_UNKNOWN = -1,
    SDL_JOYSTICK_POWER_EMPTY,  /* <= 5% */
    SDL_JOYSTICK_POWER_LOW,    /* <= 20% */
    SDL_JOYSTICK_POWER_MEDIUM, /* <= 70% */
    SDL_JOYSTICK_POWER_FULL,   /* <= 100% */
    SDL_JOYSTICK_POWER_WIRED,
    SDL_JOYSTICK_POWER_MAX
} SDL_JoystickPowerLevel;

typedef enum
{
    SDL_SCANCODE_UNKNOWN = 0,
    SDL_SCANCODE_A = 4,
    SDL_SCANCODE_B = 5,
    SDL_SCANCODE_C = 6,
    SDL_SCANCODE_D = 7,
    SDL_SCANCODE_E = 8,
    SDL_SCANCODE_F = 9,
    SDL_SCANCODE_G = 10,
    SDL_SCANCODE_H = 11,
    SDL_SCANCODE_I = 12,
    SDL_SCANCODE_J = 13,
    SDL_SCANCODE_K = 14,
    SDL_SCANCODE_L = 15,
    SDL_SCANCODE_M = 16,
    SDL_SCANCODE_N = 17,
    SDL_SCANCODE_O = 18,
    SDL_SCANCODE_P = 19,
    SDL_SCANCODE_Q = 20,
    SDL_SCANCODE_R = 21,
    SDL_SCANCODE_S = 22,
    SDL_SCANCODE_T = 23,
    SDL_SCANCODE_U = 24,
    SDL_SCANCODE_V = 25,
    SDL_SCANCODE_W = 26,
    SDL_SCANCODE_X = 27,
    SDL_SCANCODE_Y = 28,
    SDL_SCANCODE_Z = 29,
    SDL_SCANCODE_1 = 30,
    SDL_SCANCODE_2 = 31,
    SDL_SCANCODE_3 = 32,
    SDL_SCANCODE_4 = 33,
    SDL_SCANCODE_5 = 34,
    SDL_SCANCODE_6 = 35,
    SDL_SCANCODE_7 = 36,
    SDL_SCANCODE_8 = 37,
    SDL_SCANCODE_9 = 38,
    SDL_SCANCODE_0 = 39,
    SDL_SCANCODE_RETURN = 40,
    SDL_SCANCODE_ESCAPE = 41,
    SDL_SCANCODE_BACKSPACE = 42,
    SDL_SCANCODE_TAB = 43,
    SDL_SCANCODE_SPACE = 44,
    SDL_SCANCODE_MINUS = 45,
    SDL_SCANCODE_EQUALS = 46,
    SDL_SCANCODE_LEFTBRACKET = 47,
    SDL_SCANCODE_RIGHTBRACKET = 48,
    SDL_SCANCODE_BACKSLASH = 49,
    SDL_SCANCODE_NONUSHASH = 50,
    SDL_SCANCODE_SEMICOLON = 51,
    SDL_SCANCODE_APOSTROPHE = 52,
    SDL_SCANCODE_GRAVE = 53,
    SDL_SCANCODE_COMMA = 54,
    SDL_SCANCODE_PERIOD = 55,
    SDL_SCANCODE_SLASH = 56,
    SDL_SCANCODE_CAPSLOCK = 57,
    SDL_SCANCODE_F1 = 58,
    SDL_SCANCODE_F2 = 59,
    SDL_SCANCODE_F3 = 60,
    SDL_SCANCODE_F4 = 61,
    SDL_SCANCODE_F5 = 62,
    SDL_SCANCODE_F6 = 63,
    SDL_SCANCODE_F7 = 64,
    SDL_SCANCODE_F8 = 65,
    SDL_SCANCODE_F9 = 66,
    SDL_SCANCODE_F10 = 67,
    SDL_SCANCODE_F11 = 68,
    SDL_SCANCODE_F12 = 69,
    SDL_SCANCODE_PRINTSCREEN = 70,
    SDL_SCANCODE_SCROLLLOCK = 71,
    SDL_SCANCODE_PAUSE = 72,
    SDL_SCANCODE_INSERT = 73,
    SDL_SCANCODE_HOME = 74,
    SDL_SCANCODE_PAGEUP = 75,
    SDL_SCANCODE_DELETE = 76,
    SDL_SCANCODE_END = 77,
    SDL_SCANCODE_PAGEDOWN = 78,
    SDL_SCANCODE_RIGHT = 79,
    SDL_SCANCODE_LEFT = 80,
    SDL_SCANCODE_DOWN = 81,
    SDL_SCANCODE_UP = 82,
    SDL_SCANCODE_NUMLOCKCLEAR = 83,
    SDL_SCANCODE_KP_DIVIDE = 84,
    SDL_SCANCODE_KP_MULTIPLY = 85,
    SDL_SCANCODE_KP_MINUS = 86,
    SDL_SCANCODE_KP_PLUS = 87,
    SDL_SCANCODE_KP_ENTER = 88,
    SDL_SCANCODE_KP_1 = 89,
    SDL_SCANCODE_KP_2 = 90,
    SDL_SCANCODE_KP_3 = 91,
    SDL_SCANCODE_KP_4 = 92,
    SDL_SCANCODE_KP_5 = 93,
    SDL_SCANCODE_KP_6 = 94,
    SDL_SCANCODE_KP_7 = 95,
    SDL_SCANCODE_KP_8 = 96,
    SDL_SCANCODE_KP_9 = 97,
    SDL_SCANCODE_KP_0 = 98,
    SDL_SCANCODE_KP_PERIOD = 99,
    SDL_SCANCODE_NONUSBACKSLASH = 100,
    SDL_SCANCODE_APPLICATION = 101, /**< windows contextual menu, compose */
    SDL_SCANCODE_POWER = 102,
    SDL_SCANCODE_KP_EQUALS = 103,
    SDL_SCANCODE_F13 = 104,
    SDL_SCANCODE_F14 = 105,
    SDL_SCANCODE_F15 = 106,
    SDL_SCANCODE_F16 = 107,
    SDL_SCANCODE_F17 = 108,
    SDL_SCANCODE_F18 = 109,
    SDL_SCANCODE_F19 = 110,
    SDL_SCANCODE_F20 = 111,
    SDL_SCANCODE_F21 = 112,
    SDL_SCANCODE_F22 = 113,
    SDL_SCANCODE_F23 = 114,
    SDL_SCANCODE_F24 = 115,
    SDL_SCANCODE_EXECUTE = 116,
    SDL_SCANCODE_HELP = 117, /**< AL Integrated Help Center */
    SDL_SCANCODE_MENU = 118, /**< Menu (show menu) */
    SDL_SCANCODE_SELECT = 119,
    SDL_SCANCODE_STOP = 120,  /**< AC Stop */
    SDL_SCANCODE_AGAIN = 121, /**< AC Redo/Repeat */
    SDL_SCANCODE_UNDO = 122,  /**< AC Undo */
    SDL_SCANCODE_CUT = 123,   /**< AC Cut */
    SDL_SCANCODE_COPY = 124,  /**< AC Copy */
    SDL_SCANCODE_PASTE = 125, /**< AC Paste */
    SDL_SCANCODE_FIND = 126,  /**< AC Find */
    SDL_SCANCODE_MUTE = 127,
    SDL_SCANCODE_VOLUMEUP = 128,
    SDL_SCANCODE_VOLUMEDOWN = 129,
    SDL_SCANCODE_KP_COMMA = 133,
    SDL_SCANCODE_KP_EQUALSAS400 = 134,
    SDL_SCANCODE_INTERNATIONAL1 = 135,
    SDL_SCANCODE_INTERNATIONAL2 = 136,
    SDL_SCANCODE_INTERNATIONAL3 = 137, /**< Yen */
    SDL_SCANCODE_INTERNATIONAL4 = 138,
    SDL_SCANCODE_INTERNATIONAL5 = 139,
    SDL_SCANCODE_INTERNATIONAL6 = 140,
    SDL_SCANCODE_INTERNATIONAL7 = 141,
    SDL_SCANCODE_INTERNATIONAL8 = 142,
    SDL_SCANCODE_INTERNATIONAL9 = 143,
    SDL_SCANCODE_LANG1 = 144,    /**< Hangul/English toggle */
    SDL_SCANCODE_LANG2 = 145,    /**< Hanja conversion */
    SDL_SCANCODE_LANG3 = 146,    /**< Katakana */
    SDL_SCANCODE_LANG4 = 147,    /**< Hiragana */
    SDL_SCANCODE_LANG5 = 148,    /**< Zenkaku/Hankaku */
    SDL_SCANCODE_LANG6 = 149,    /**< reserved */
    SDL_SCANCODE_LANG7 = 150,    /**< reserved */
    SDL_SCANCODE_LANG8 = 151,    /**< reserved */
    SDL_SCANCODE_LANG9 = 152,    /**< reserved */
    SDL_SCANCODE_ALTERASE = 153, /**< Erase-Eaze */
    SDL_SCANCODE_SYSREQ = 154,
    SDL_SCANCODE_CANCEL = 155, /**< AC Cancel */
    SDL_SCANCODE_CLEAR = 156,
    SDL_SCANCODE_PRIOR = 157,
    SDL_SCANCODE_RETURN2 = 158,
    SDL_SCANCODE_SEPARATOR = 159,
    SDL_SCANCODE_OUT = 160,
    SDL_SCANCODE_OPER = 161,
    SDL_SCANCODE_CLEARAGAIN = 162,
    SDL_SCANCODE_CRSEL = 163,
    SDL_SCANCODE_EXSEL = 164,
    SDL_SCANCODE_KP_00 = 176,
    SDL_SCANCODE_KP_000 = 177,
    SDL_SCANCODE_THOUSANDSSEPARATOR = 178,
    SDL_SCANCODE_DECIMALSEPARATOR = 179,
    SDL_SCANCODE_CURRENCYUNIT = 180,
    SDL_SCANCODE_CURRENCYSUBUNIT = 181,
    SDL_SCANCODE_KP_LEFTPAREN = 182,
    SDL_SCANCODE_KP_RIGHTPAREN = 183,
    SDL_SCANCODE_KP_LEFTBRACE = 184,
    SDL_SCANCODE_KP_RIGHTBRACE = 185,
    SDL_SCANCODE_KP_TAB = 186,
    SDL_SCANCODE_KP_BACKSPACE = 187,
    SDL_SCANCODE_KP_A = 188,
    SDL_SCANCODE_KP_B = 189,
    SDL_SCANCODE_KP_C = 190,
    SDL_SCANCODE_KP_D = 191,
    SDL_SCANCODE_KP_E = 192,
    SDL_SCANCODE_KP_F = 193,
    SDL_SCANCODE_KP_XOR = 194,
    SDL_SCANCODE_KP_POWER = 195,
    SDL_SCANCODE_KP_PERCENT = 196,
    SDL_SCANCODE_KP_LESS = 197,
    SDL_SCANCODE_KP_GREATER = 198,
    SDL_SCANCODE_KP_AMPERSAND = 199,
    SDL_SCANCODE_KP_DBLAMPERSAND = 200,
    SDL_SCANCODE_KP_VERTICALBAR = 201,
    SDL_SCANCODE_KP_DBLVERTICALBAR = 202,
    SDL_SCANCODE_KP_COLON = 203,
    SDL_SCANCODE_KP_HASH = 204,
    SDL_SCANCODE_KP_SPACE = 205,
    SDL_SCANCODE_KP_AT = 206,
    SDL_SCANCODE_KP_EXCLAM = 207,
    SDL_SCANCODE_KP_MEMSTORE = 208,
    SDL_SCANCODE_KP_MEMRECALL = 209,
    SDL_SCANCODE_KP_MEMCLEAR = 210,
    SDL_SCANCODE_KP_MEMADD = 211,
    SDL_SCANCODE_KP_MEMSUBTRACT = 212,
    SDL_SCANCODE_KP_MEMMULTIPLY = 213,
    SDL_SCANCODE_KP_MEMDIVIDE = 214,
    SDL_SCANCODE_KP_PLUSMINUS = 215,
    SDL_SCANCODE_KP_CLEAR = 216,
    SDL_SCANCODE_KP_CLEARENTRY = 217,
    SDL_SCANCODE_KP_BINARY = 218,
    SDL_SCANCODE_KP_OCTAL = 219,
    SDL_SCANCODE_KP_DECIMAL = 220,
    SDL_SCANCODE_KP_HEXADECIMAL = 221,
    SDL_SCANCODE_LCTRL = 224,
    SDL_SCANCODE_LSHIFT = 225,
    SDL_SCANCODE_LALT = 226, /**< alt, option */
    SDL_SCANCODE_LGUI = 227, /**< windows, command (apple), meta */
    SDL_SCANCODE_RCTRL = 228,
    SDL_SCANCODE_RSHIFT = 229,
    SDL_SCANCODE_RALT = 230, /**< alt gr, option */
    SDL_SCANCODE_RGUI = 231, /**< windows, command (apple), meta */
    SDL_SCANCODE_MODE = 257,
    SDL_SCANCODE_AUDIONEXT = 258,
    SDL_SCANCODE_AUDIOPREV = 259,
    SDL_SCANCODE_AUDIOSTOP = 260,
    SDL_SCANCODE_AUDIOPLAY = 261,
    SDL_SCANCODE_AUDIOMUTE = 262,
    SDL_SCANCODE_MEDIASELECT = 263,
    SDL_SCANCODE_WWW = 264, /**< AL Internet Browser */
    SDL_SCANCODE_MAIL = 265,
    SDL_SCANCODE_CALCULATOR = 266, /**< AL Calculator */
    SDL_SCANCODE_COMPUTER = 267,
    SDL_SCANCODE_AC_SEARCH = 268,    /**< AC Search */
    SDL_SCANCODE_AC_HOME = 269,      /**< AC Home */
    SDL_SCANCODE_AC_BACK = 270,      /**< AC Back */
    SDL_SCANCODE_AC_FORWARD = 271,   /**< AC Forward */
    SDL_SCANCODE_AC_STOP = 272,      /**< AC Stop */
    SDL_SCANCODE_AC_REFRESH = 273,   /**< AC Refresh */
    SDL_SCANCODE_AC_BOOKMARKS = 274, /**< AC Bookmarks */
    SDL_SCANCODE_BRIGHTNESSDOWN = 275,
    SDL_SCANCODE_BRIGHTNESSUP = 276,
    SDL_SCANCODE_DISPLAYSWITCH = 277,
    SDL_SCANCODE_KBDILLUMTOGGLE = 278,
    SDL_SCANCODE_KBDILLUMDOWN = 279,
    SDL_SCANCODE_KBDILLUMUP = 280,
    SDL_SCANCODE_EJECT = 281,
    SDL_SCANCODE_SLEEP = 282, /**< SC System Sleep */
    SDL_SCANCODE_APP1 = 283,
    SDL_SCANCODE_APP2 = 284,
    SDL_SCANCODE_AUDIOREWIND = 285,
    SDL_SCANCODE_AUDIOFASTFORWARD = 286,
    SDL_SCANCODE_SOFTLEFT = 287,
    SDL_SCANCODE_SOFTRIGHT = 288,
    SDL_SCANCODE_CALL = 289,    /**< Used for accepting phone calls. */
    SDL_SCANCODE_ENDCALL = 290, /**< Used for rejecting phone calls. */
    SDL_NUM_SCANCODES = 512
} SDL_Scancode;

typedef struct SDL_Keysym
{
    SDL_Scancode
        scancode; /**< SDL physical key code - see ::SDL_Scancode for details */
    SDL_Keycode
        sym;    /**< SDL virtual key code - see ::SDL_Keycode for details */
    Uint16 mod; /**< current key modifiers */
    Uint32 unused;
} SDL_Keysym;

struct SDL_KeyboardEvent
{
    Uint32 type;      /**< ::SDL_KEYDOWN or ::SDL_KEYUP */
    Uint32 timestamp; /**< In milliseconds, populated using SDL_GetTicks() */
    Uint32 windowID;  /**< The window with keyboard focus, if any */
    Uint8 state;      /**< ::SDL_PRESSED or ::SDL_RELEASED */
    Uint8 repeat;     /**< Non-zero if this is a key repeat */
    Uint8 padding2;
    Uint8 padding3;
    SDL_Keysym keysym; /**< The key that was pressed or released */
};

typedef struct SDL_JoyAxisEvent
{
    Uint32 type;      /**< ::SDL_JOYAXISMOTION */
    Uint32 timestamp; /**< In milliseconds, populated using SDL_GetTicks() */
    SDL_JoystickID which; /**< The joystick instance id */
    Uint8 axis;           /**< The joystick axis index */
    Uint8 padding1;
    Uint8 padding2;
    Uint8 padding3;
    Sint16 value; /**< The axis value (range: -32768 to 32767) */
    Uint16 padding4;
} SDL_JoyAxisEvent;

typedef struct SDL_JoyButtonEvent
{
    Uint32 type;      /**< ::SDL_JOYBUTTONDOWN or ::SDL_JOYBUTTONUP */
    Uint32 timestamp; /**< In milliseconds, populated using SDL_GetTicks() */
    SDL_JoystickID which; /**< The joystick instance id */
    Uint8 button;         /**< The joystick button index */
    Uint8 state;          /**< ::SDL_PRESSED or ::SDL_RELEASED */
    Uint8 padding1;
    Uint8 padding2;
} SDL_JoyButtonEvent;

typedef struct SDL_JoyDeviceEvent
{
    Uint32 type;      /**< ::SDL_JOYDEVICEADDED or ::SDL_JOYDEVICEREMOVED */
    Uint32 timestamp; /**< In milliseconds, populated using SDL_GetTicks() */
    Sint32 which; /**< The joystick device index for the ADDED event, instance
                     id for the REMOVED event */
} SDL_JoyDeviceEvent;

typedef struct SDL_JoyBatteryEvent
{
    Uint32 type;      /**< ::SDL_JOYBATTERYUPDATED */
    Uint32 timestamp; /**< In milliseconds, populated using SDL_GetTicks() */
    SDL_JoystickID which;         /**< The joystick instance id */
    SDL_JoystickPowerLevel level; /**< The joystick battery level */
} SDL_JoyBatteryEvent;

/**
 *  \brief General event structure
 */
typedef union SDL_Event {
    Uint32 type; /**< Event type, shared with all events */
    // SDL_CommonEvent common; /**< Common event data */
    // SDL_DisplayEvent display;               /**< Display event data */
    // SDL_WindowEvent window;                 /**< Window event data */
    SDL_KeyboardEvent key; /**< Keyboard event data */
    // SDL_TextEditingEvent edit;         /**< Text editing event data */
    // SDL_TextEditingExtEvent editExt;   /**< Extended text editing event data
    // */ SDL_TextInputEvent text;           /**< Text input event data */
    SDL_MouseMotionEvent motion; /**< Mouse motion event data */
    SDL_MouseButtonEvent button; /**< Mouse button event data */
    SDL_MouseWheelEvent wheel;   /**< Mouse wheel event data */
    SDL_JoyAxisEvent jaxis;      /**< Joystick axis event data */
    // SDL_JoyBallEvent jball;       /**< Joystick ball event data */
    // SDL_JoyHatEvent jhat;         /**< Joystick hat event data */
    SDL_JoyButtonEvent jbutton;   /**< Joystick button event data */
    SDL_JoyDeviceEvent jdevice;   /**< Joystick device change event data */
    SDL_JoyBatteryEvent jbattery; /**< Joystick battery event data */
    // SDL_ControllerAxisEvent caxis;     /**< Game Controller axis event data
    // */
    // SDL_ControllerButtonEvent cbutton; /**< Game Controller button event data
    // */ SDL_ControllerDeviceEvent cdevice; /**< Game Controller device event
    // data
    // */ SDL_ControllerTouchpadEvent ctouchpad; /**< Game Controller touchpad
    // event data */ SDL_ControllerSensorEvent csensor; /**< Game Controller
    // sensor event data */
    // SDL_AudioDeviceEvent adevice; /**< Audio device event data */
    // SDL_SensorEvent sensor;       /**< Sensor event data */
    // SDL_QuitEvent quit;           /**< Quit request event data */
    // SDL_UserEvent user;           /**< Custom event data */
    // SDL_SysWMEvent syswm;            /**< System dependent window event data
    // */ SDL_TouchFingerEvent tfinger;    /**< Touch finger event data */
    // SDL_MultiGestureEvent mgesture;  /**< Gesture event data */
    // SDL_DollarGestureEvent dgesture; /**< Gesture event data */
    // SDL_DropEvent drop;              /**< Drag and drop event data */
};

struct _SDL_Joystick
{
};
typedef _SDL_Joystick SDL_Joystick;

class SDLMock
{
  public:
    MOCK_METHOD(Uint32, SDL_GetTicks, ());
    MOCK_METHOD(void, SDL_Delay, (Uint32));
    MOCK_METHOD(void, SDL_Log, (const char*));
    MOCK_METHOD(int, SDL_PollEvent, (SDL_Event*));
    MOCK_METHOD(Uint32, SDL_GetMouseState, (int*, int*));
    MOCK_METHOD(const Uint8*, SDL_GetKeyboardState, (int*));
    MOCK_METHOD(SDL_JoystickID, SDL_JoystickGetDeviceInstanceID, (int));
    MOCK_METHOD(SDL_JoystickID, SDL_JoystickInstanceID, (SDL_Joystick*));
    MOCK_METHOD(SDL_bool, SDL_JoystickHasLED, (SDL_Joystick*));
    MOCK_METHOD(SDL_bool, SDL_JoystickHasRumble, (SDL_Joystick*));
    MOCK_METHOD(int, SDL_JoystickGetPlayerIndex, (SDL_Joystick*));
    MOCK_METHOD(Sint16, SDL_JoystickGetAxis, (SDL_Joystick*, int));
    MOCK_METHOD(Uint8, SDL_JoystickGetButton, (SDL_Joystick*, int));
    MOCK_METHOD(int, SDL_JoystickNumAxes, (SDL_Joystick*));
    MOCK_METHOD(int, SDL_JoystickNumButtons, (SDL_Joystick*));
    MOCK_METHOD(SDL_JoystickPowerLevel, SDL_JoystickCurrentPowerLevel,
                (SDL_Joystick*));
    MOCK_METHOD(int, SDL_JoystickRumble,
                (SDL_Joystick*, Uint16, Uint16, Uint32));
    MOCK_METHOD(void, SDL_JoystickSetPlayerIndex, (SDL_Joystick*, int));
    MOCK_METHOD(int, SDL_JoystickSetLED, (SDL_Joystick*, Uint8, Uint8, Uint8));
    MOCK_METHOD(const char*, SDL_JoystickNameForIndex, (int device_index));
    MOCK_METHOD(const char*, SDL_JoystickName, (SDL_Joystick*));
    MOCK_METHOD(SDL_Joystick*, SDL_JoystickOpen, (int device_index));
    MOCK_METHOD(void, SDL_JoystickClose, (SDL_Joystick * joystick));
    MOCK_METHOD(const char*, SDL_GetError, ());
};

extern doengine::mocks::SDLMock* sdlMock;

Uint32 SDL_GetTicks();
void SDL_Delay(Uint32);
void SDL_Log(const char* fmt, ...);
int SDL_PollEvent(SDL_Event* event);
Uint32 SDL_GetMouseState(int* x, int* y);
const Uint8* SDL_GetKeyboardState(int* numkeys);
void SetSDLMock(doengine::mocks::SDLMock* newSdlMock);
SDL_JoystickID SDL_JoystickGetDeviceInstanceID(int);
SDL_JoystickID SDL_JoystickInstanceID(SDL_Joystick* joystick);
SDL_bool SDL_JoystickHasLED(SDL_Joystick*);
SDL_bool SDL_JoystickHasRumble(SDL_Joystick*);
int SDL_JoystickGetPlayerIndex(SDL_Joystick* joystick);
Sint16 SDL_JoystickGetAxis(SDL_Joystick* joystick, int axis);
Uint8 SDL_JoystickGetButton(SDL_Joystick* joystick, int button);
int SDL_JoystickNumAxes(SDL_Joystick* joystick);
int SDL_JoystickNumButtons(SDL_Joystick* joystick);
SDL_JoystickPowerLevel SDL_JoystickCurrentPowerLevel(SDL_Joystick* joystick);
int SDL_JoystickRumble(SDL_Joystick*, Uint16, Uint16, Uint32);
void SDL_JoystickSetPlayerIndex(SDL_Joystick* joystick, int player_index);
int SDL_JoystickSetLED(SDL_Joystick* joystick, Uint8 red, Uint8 green,
                       Uint8 blue);
const char* SDL_JoystickNameForIndex(int device_index);
const char* SDL_JoystickName(SDL_Joystick* joystick);
SDL_Joystick* SDL_JoystickOpen(int device_index);
void SDL_JoystickClose(SDL_Joystick* joystick);
const char* SDL_GetError(void);
