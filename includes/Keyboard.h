#pragma once

#include <bitset>
#include <cstddef>

namespace doengine::devices
{

enum class Keymod : unsigned char
{
    None,
    LeftCtrl,
    LeftShift,
    LeftAlt,
    LeftGui,
    RightCtrl,
    RightShift,
    RightAlt,
    RightGui,
    Caps,
    Num,
    Mode,
    Scroll
};

enum class Keycode : unsigned short
{
    KeyUnknown = 0,
    KeyA = 4,
    KeyB = 5,
    KeyC = 6,
    KeyD = 7,
    KeyE = 8,
    KeyF = 9,
    KeyG = 10,
    KeyH = 11,
    KeyI = 12,
    KeyJ = 13,
    KeyK = 14,
    KeyL = 15,
    KeyM = 16,
    KeyN = 17,
    KeyO = 18,
    KeyP = 19,
    KeyQ = 20,
    KeyR = 21,
    KeyS = 22,
    KeyT = 23,
    KeyU = 24,
    KeyV = 25,
    KeyW = 26,
    KeyX = 27,
    KeyY = 28,
    KeyZ = 29,
    Key1 = 30,
    Key2 = 31,
    Key3 = 32,
    Key4 = 33,
    Key5 = 34,
    Key6 = 35,
    Key7 = 36,
    Key8 = 37,
    Key9 = 38,
    Key0 = 39,
    KeyReturn = 40,
    KeyEscap = 41,
    KeyBackspace = 42,
    KeyTab = 43,
    KeySpace = 44,
    KeyMinus = 45,
    KeyEquals = 46,
    KeyLeftBracket = 47,
    KeyRightBracket = 48,
    KeyBackslash = 49,
    KeyNonUsHash = 50,
    KeySemiColon = 51,
    KeyApostrophe = 52,
    KeyGrave = 53,
    KeyComma = 54,
    KeyPeriod = 55,
    KeySlash = 56,
    KeyCapslock = 57,
    KeyF1 = 58,
    KeyF2 = 59,
    KeyF3 = 60,
    KeyF4 = 61,
    KeyF5 = 62,
    KeyF6 = 63,
    KeyF7 = 64,
    KeyF8 = 65,
    KeyF9 = 66,
    KeyF10 = 67,
    KeyF11 = 68,
    KeyF12 = 69,
    KeyPrintscreen = 70,
    KeyScrollLock = 71,
    KeyPause = 72,
    KeyInsert = 73,
    KeyHome = 74,
    KeyPageUp = 75,
    KeyDelete = 76,
    KeyEnd = 77,
    KeyPageDown = 78,
    KeyRight = 79,
    KeyLeft = 80,
    KeyDown = 81,
    KeyUp = 82,
    KeyNumLockClear = 83,
    KeyKpDivide = 84,
    KeyKpMultiply = 85,
    KeyKpMinus = 86,
    KeyKpPlus = 87,
    KeyKpEnter = 88,
    KeyKp1 = 89,
    KeyKp2 = 90,
    KeyKp3 = 91,
    KeyKp4 = 92,
    KeyKp5 = 93,
    KeyKp6 = 94,
    KeyKp7 = 95,
    KeyKp8 = 96,
    KeyKp9 = 97,
    KeyKp0 = 98,
    KeyKpPeriod = 99,
    KeyNoNUsBackslash = 100,
    KeyApplication = 101, /**< windows contextual menu, compose */
    KeyPower = 102,
    KeyKpEquals = 103,
    KeyF13 = 104,
    KeyF14 = 105,
    KeyF15 = 106,
    KeyF16 = 107,
    KeyF17 = 108,
    KeyF18 = 109,
    KeyF19 = 110,
    KeyF20 = 111,
    KeyF21 = 112,
    KeyF22 = 113,
    KeyF23 = 114,
    KeyF24 = 115,
    KeyExecute = 116,
    KeyHelp = 117, /**< AL Integrated Help Center */
    KeyMenu = 118, /**< Menu (show menu) */
    KeySelect = 119,
    KeyStop = 120,  /**< AC Stop */
    KeyAgain = 121, /**< AC Redo/Repeat */
    KeyUndo = 122,  /**< AC Undo */
    KeyCut = 123,   /**< AC Cut */
    KeyCopy = 124,  /**< AC Copy */
    KeyPaste = 125, /**< AC Paste */
    KeyFind = 126,  /**< AC Find */
    KeyMute = 127,
    KeyVolumeUp = 128,
    KeyVolumeDown = 129,
    KeyKpComma = 133,
    KeyKpEqualsAS400 = 134,
    KeyInternational1 = 135,
    KeyInternational2 = 136,
    KeyInternational3 = 137, /**< Yen */
    KeyInternational4 = 138,
    KeyInternational5 = 139,
    KeyInternational6 = 140,
    KeyInternational7 = 141,
    KeyInternational8 = 142,
    KeyInternational9 = 143,
    KeyLang1 = 144,    /**< Hangul/English toggle */
    KeyLang2 = 145,    /**< Hanja conversion */
    KeyLang3 = 146,    /**< Katakana */
    KeyLang4 = 147,    /**< Hiragana */
    KeyLang5 = 148,    /**< Zenkaku/Hankaku */
    KeyLang6 = 149,    /**< reserved */
    KeyLang7 = 150,    /**< reserved */
    KeyLang8 = 151,    /**< reserved */
    KeyLang9 = 152,    /**< reserved */
    KeyAlterase = 153, /**< Erase-Eaze */
    KeySYSREQ = 154,
    KeyCancel = 155, /**< AC Cancel */
    KeyClear = 156,
    KeyPrior = 157,
    KeyReturn2 = 158,
    KeySeparator = 159,
    KeyOut = 160,
    KeyOper = 161,
    KeyClearAgain = 162,
    KeyCRSEL = 163,
    KeyEXSEL = 164,
    KeyKp00 = 176,
    KeyKp000 = 177,
    KeyThousandsSeparator = 178,
    KeyDecimalSeparator = 179,
    KeyCurrencyUnit = 180,
    KeyCurrencySubUnit = 181,
    KeyKpLeftParen = 182,
    KeyKpRightParen = 183,
    KeyKpLeftBrace = 184,
    KeyKpRightBrace = 185,
    KeyKpTab = 186,
    KeyKpBackspace = 187,
    KeyKpA = 188,
    KeyKpB = 189,
    KeyKpC = 190,
    KeyKpD = 191,
    KeyKpE = 192,
    KeyKpF = 193,
    KeyKpXor = 194,
    KeyKpPower = 195,
    KeyKpPercent = 196,
    KeyKpLess = 197,
    KeyKpGreater = 198,
    KeyKpAmpersand = 199,
    KeyKpDoubleAmpersand = 200,
    KeyKpVerticalBar = 201,
    KeyKpDoubleVerticalBar = 202,
    KeyKpColon = 203,
    KeyKpHash = 204,
    KeyKpSpace = 205,
    KeyKpAt = 206,
    KeyKpExclam = 207,
    KeyKpMemStore = 208,
    KeyKpMemRecall = 209,
    KeyKpMemClear = 210,
    KeyKpMemAdd = 211,
    KeyKpMemSubtract = 212,
    KeyKpMemMultiply = 213,
    KeyKpMemDivide = 214,
    KeyKpPlusMinus = 215,
    KeyKpClear = 216,
    KeyKpClearEntry = 217,
    KeyKpBinary = 218,
    KeyKpOctal = 219,
    KeyKpDecimal = 220,
    KeyKpHexadecimal = 221,
    KeyLeftCtrl = 224,
    KeyLeftShift = 225,
    KeyLeftAlt = 226, /**< alt, option */
    KeyLeftGui = 227, /**< windows, command (apple), meta */
    KeyRightCtrl = 228,
    KeyRightShift = 229,
    KeyRightAlt = 230, /**< alt gr, option */
    KeyRightGui = 231, /**< windows, command (apple), meta */
    KeyMode = 257,
    KeyAudioNext = 258,
    KeyAudioPrev = 259,
    KeyAudioStop = 260,
    KeyAudioPlay = 261,
    KeyAudioMute = 262,
    KeyMediaSelect = 263,
    KeyWWW = 264, /**< AL Internet Browser */
    KeyMail = 265,
    KeyCalculator = 266, /**< AL Calculator */
    KeyComputer = 267,
    KeyAcSearch = 268,    /**< AC Search */
    KeyAcHome = 269,      /**< AC Home */
    KeyAcBack = 270,      /**< AC Back */
    KeyAcForward = 271,   /**< AC Forward */
    KeyAcStop = 272,      /**< AC Stop */
    KeyAcRefresh = 273,   /**< AC Refresh */
    KeyACBookmarks = 274, /**< AC Bookmarks */
    KeyBrightnessDown = 275,
    KeyBrightnessUp = 276,
    KeyDisplaySwitch = 277,
    KeyKbDillumToggle = 278,
    KeyKbDillumDown = 279,
    KeyKbDillumUp = 280,
    KeyEject = 281,
    KeySleep = 282, /**< SC System Sleep */
    KeyApp1 = 283,
    KeyApp2 = 284,
    KeyAudioRewind = 285,
    KeyAudioFastForward = 286,
    KeySoftLeft = 287,
    KeySoftRight = 288,
    KeyCall = 289,    /**< Used for accepting phone calls. */
    KeyEndCall = 290, /**< Used for rejecting phone calls. */
};

class Keyboard
{
  public:
    static const size_t BUTTONS_COUNT = 246u;
    virtual const unsigned char* getKeysBitset() const = 0;
};

} // namespace doengine::devices
