#pragma once
#include "Renderer.h"
#include "Application.h"
#include "Geometric.h"
#include "Texture.h"
#include "Tile.h"
#include "Event.h"
#include <cstddef>
#include <string>
#include <vector>
#include <functional>

namespace doengine
{

#define VALUE_IN_ARRAY(X, Y, W, A) A[Y * W + X]


 



template<class T>
struct RenderType{
    T type;
    std::function<void(T, doengine::Renderer *)>renderFn;
};

struct TileDef
{
    std::string        textureId;
    doengine::Rect     src;   // atlas rect
    bool               solid;
    int layer;
};


struct TileMapEditor;

struct TileMap
{
    protected:
        std::string tilesetId;
        TileMapEditor* editor = nullptr;
        std::vector<RenderType<char>> primitive_chars; //// TBI in next classess
    public:
        virtual ~TileMap() = default;
        virtual bool loadTileMapFromFile(const std::string& fn) = 0;
        virtual void Update(double) = 0;
        virtual void Draw() = 0;
        void setTileSetId(std::string tilesetId){
            this->tilesetId = tilesetId;
        }
};


struct NonScrollCharTileMap : 
    public TileMap,
    public MouseEvent
{
    protected:
        bool debug = true; 
        doengine::Rect debugRect;
        char type_to_change_by_editor = 0;

        int paddingLeft = 100;
        int paddingTop  = 100;


        doengine::Renderer *renderer;
        ///std::vector<std::string> tiles;
        std::vector<Tile> tiles;
        std::unordered_map<char, TileDef> tile_defs;
        char getTile(int row, int col)const;
        int rows;
        int cols;
        int tilesize;
        virtual void MouseMove(const Mouse&) override;
        virtual void MouseButtonDown(const Mouse&) override;
        virtual void MouseButtonUp(const Mouse&) override;
    
    
    public:


        NonScrollCharTileMap();
        
        virtual ~NonScrollCharTileMap()=default;
        virtual bool loadTileMapFromFile(const std::string& fn) override;
        virtual void Update(double) override;
        virtual void Draw() override;
        void setTileDef(std::unordered_map<char, TileDef> tile_defs);
        void setTileMapEditor(TileMapEditor *ptr);
        inline const char getEditorType()const{
            return this->type_to_change_by_editor;
        }
    virtual void MouseWheel(const Mouse&)
    {}
        void changeGroupOfTileByRectCollision(char ch, doengine::Rect rect);

};



struct ScrollableCharTileMap : 
    public TileMap,
    public MouseEvent
{
    protected:
        bool debug = true; 
        doengine::Rect debugRect;
        char type_to_change_by_editor = 0;

        int paddingLeft = 100;
        int paddingTop  = 100;


        doengine::Renderer *renderer;
        ///std::vector<std::string> tiles;
        std::vector<Tile> tiles;
        std::unordered_map<char, TileDef> tile_defs;
        char getTile(int row, int col)const;
        int rows;
        int cols;
        int tilesize;
        virtual void MouseMove(const Mouse&) override;
        virtual void MouseButtonDown(const Mouse&) override;
        virtual void MouseButtonUp(const Mouse&) override;
    
    
    public:


        ScrollableCharTileMap();
        
        virtual ~ScrollableCharTileMap();
        virtual bool loadTileMapFromFile(const std::string& fn) override;
        virtual void Update(double) override;
        virtual void Draw() override;
        void setTileDef(std::unordered_map<char, TileDef> tile_defs);
        void setTileMapEditor(TileMapEditor *ptr);
        inline const char getEditorType()const{
            return this->type_to_change_by_editor;
        }

        void changeGroupOfTileByRectCollision(char ch, doengine::Rect rect);

};






}