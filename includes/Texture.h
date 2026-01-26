#pragma once
#include <map>
#include <string>
#include <variant>
#include <functional>

using std::map;
using std::string;
#include "TTFText.h"
#include "Geometric.h"
#include "NativeStructs.h"
#include <Color.h>

namespace doengine
{
class TTFText;
class NativeTexture;

class Texture
{
    NativeTexture* realNativeTexture;


  public:
    Texture();
    Texture(std::string path);
    ~Texture();
    void SetTransparentColor(const Color& color);
    void Draw(int x, int y);
    void Draw(const Rect& offset);
    void Draw(const Rect& offset, const Rect& clipset);
    void ModulateColor(const Color& color);
    int getWidth();
    int getHeight();
    bool validTexture();
    Texture* setNativeTexture(void *);
    Texture* subTexture(const Rect& clipset);
};

class TextureManager
{

    TextureManager()
    {
    }

    static TextureManager* instance;

    std::map<std::variant<std::string,int>, Texture*> textures;
    std::map<std::variant<std::string,int>, TTFText*> fonts;

  public:
    static TextureManager* getTextureManager();

    void loadTextureFromFile(const std::variant<std::string, int>& key, string src);
    void loadFont(const std::variant<std::string, int>& key, string src, int pts);
    TTFText* getFont(const std::variant<std::string, int>& id);

    void loadTextureFromTexture(string id, Texture* texture,
                                const Rect& clipset);

    void addTexture(string id, Texture* texture);
    void addTexture(const std::variant<std::string, int>& key, Texture* texture);

    void removeTexture(string id);

    Texture* getTexture(const std::variant<std::string, int>& id);
    Texture* getTextureOr(const std::variant<std::string, int>& id, std::function<void()> orCall);


    enum class TextureStatus{
      Success,
      Error,
      TextureIdInvalid
    };
    TextureStatus drawTexture(const std::string,const Rect offset ,const Rect clipset);
    TextureStatus drawTexture(const std::string id,const Rect offset);

   
};

} // namespace doengine
