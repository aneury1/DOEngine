#pragma once
#include <map>
#include <string>

using std::map;
using std::string;

#include "Geometric.h"
#include "NativeStructs.h"
#include <Color.h>

namespace doengine
{

class NativeTexture;

class Texture
{
    NativeTexture* realNativeTexture;
    Texture()
    {
        realNativeTexture = nullptr;
    }

  public:
    Texture(std::string path);
    ~Texture();
    void Draw(const Rect& offset);
    void Draw(const Rect& offset, const Rect& clipset);
    void ModulateColor(const Color& color);
    int getWidth();
    int getHeight();
    bool validTexture();

    Texture* subTexture(const Rect& clipset);
};

class TextureManager
{

    TextureManager()
    {
    }

    static TextureManager* instance;

    std::map<string, Texture*> textures;

  public:
    static TextureManager* getTextureManager();

    void loadTextureFromFile(string id, string src);

    void loadTextureFromTexture(string id, Texture* texture,
                                const Rect& clipset);

    void addTexture(string id, Texture* texture);

    void removeTexture(string id);

    Texture* getTexture(string id);
};

} // namespace doengine