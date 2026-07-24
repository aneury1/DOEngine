#include "NativeStructs.h"
#include <gmock/gmock-function-mocker.h>

namespace doengine
{

namespace mocks
{

class NativeTextureMock : public NativeTexture
{
  public:
    ~NativeTextureMock()
    {
    }

    MOCK_METHOD(NativeTexture*, subTexture, (Rect), (override));
    MOCK_METHOD(NativeTexture*, setNativeTexture, (void*), (override));
    MOCK_METHOD(NativeTexture*, loadFromFile, (const char* src), (override));
    MOCK_METHOD(bool, validTexture, (), (override));
    MOCK_METHOD(void, Draw, (int, int), (override));
    MOCK_METHOD(void, Draw, (const Rect& offset), (override));
    MOCK_METHOD(void, Draw, (const Rect& offset, const Rect& clipset),
                (override));
    MOCK_METHOD(void, Draw,
                (const Rect& offset, const Rect& clipset, double angle),
                (override));
    MOCK_METHOD(void, Draw,
                (const Rect& offset, const Rect& clipset, double angle,
                 const Point& center),
                (override));
    MOCK_METHOD(void, ModulateColor, (const Color& color), (override));
    MOCK_METHOD(int, getWidth, (), (override));
    MOCK_METHOD(int, getHeight, (), (override));
    MOCK_METHOD(void, SetTransparentColor, (const Color&), (override));
    MOCK_METHOD(void, Destroy, (), (override));
    MOCK_METHOD(void*, getNativeBuffer, (), (override));
};

} // namespace mocks
} // namespace doengine
