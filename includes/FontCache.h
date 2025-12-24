#ifndef FONTCACHE_H_DEFINED
#define FONTCACHE_H_DEFINED
#include <Texture.h>
#include <Renderer.h>
namespace doengine
{

constexpr const char *defaultGlyph =
" !\"#$%&\'()*+\'-/0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_'abcdefghijklmnopqrstuvwyz{|}~";

struct FontCache
{
   Texture *glyph_texture;

   FontCache(const std::string& fontname);

   void createGlyph();

   void DrawText(int x, int y, int max_width);


};



}

#endif