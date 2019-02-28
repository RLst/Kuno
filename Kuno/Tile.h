//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#pragma once
#include "PF.h"

namespace aie {
	class Texture;
}

namespace pf {

	class StaticObject;

	enum eTileTraversable
	{
		UNTRAVERSABLE = 0,
		TRAVERSABLE,
		TILETYPE_COUNT		//The total number of tile types
	};

	enum eTileTerrain : int
	{
		NA = -1,			//Not applicatble
		
		// Portfolio
		//FLOOR = 0,
		//FLOOR_GRASSROUND,
		//SLAB,
		//SMALLBLOCK,
		//LARGEBLOCK,
		//HUGEBLOCK,
		//COLUMN,
		//STEPS,
		//WALLCORNER,		

		 //Kuno Tiles
		//SMOOTH_FLOOR = 0,	
		PATH = 0,				
		GRASS,	
		DIRT,	
		SAND,
		GRAVEL,	
		WATER,
		DEEPWATER,
		
		TILE_TERRAIN_COUNT
	};

	class Tile : public Node
	{
		//// THE IDEAL TILE ////bas
		//Iso Tile Width: 100
		//Iso Tile Height: 50
		//Image width: 100
		//Image height: 200
	private:
		
		//This is the centre of the tile in canvas coordinates/percentages
		// ** MUST BE MODIFED IF CHANGING TILE SETS
		pkr::Vector2	m_originOffset = { 0.5f, 0.28f };	//KunoCustom Tileset
		//pkr::Vector2	m_originOffset = { 0.5f, 0.18f };	//Prototype	Tileset

	public:
		int				ID;

		std::vector<StaticObject*> objects;		//StaticObjects include walls and unmovable objects

		//Terrain and accessibility
		eTileTerrain			terrain;
		eTileTraversable		access;

		//NOTE!!!
		//depthSortOffset: The point offset from canvas world pos at which the 
		//Depth Sorter uses to sort the depth of the tile/object
		//This point should be the isometrically furthest point from the viewer where the object
		//intersects or meets the ground ie. back corner of block
		pkr::Vector2	dsOffset = { 0,0 };
		//Texture
		aie::Texture*	tex = nullptr;

	public:
		Tile() = default;
		~Tile();	//Texture manager will delete the textures

		Tile(pkr::Vector2 pos, aie::Texture* tex, pkr::Vector2 dsOffset = { 0,0 }, eTileTerrain terrain = PATH, eTileTraversable = TRAVERSABLE);

		//Cores
		void			draw(aie::Renderer2D* renderer);
	};

}
