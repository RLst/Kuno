#pragma once
#include "PF.h"

namespace aie {
	class Texture;
}

namespace pf {

enum eTileAccess
{
	INACCESSIBLE = 0,
	ACCESSIBLE,
	//CLIMBABLE,
	TILETYPE_COUNT		//The total number of tile types
};

enum eTileTerrain
{
	NA = -1,			//Not applicatble
	SMOOTH_FLOOR = 0,		//0.5f; Easy to traverse
	GRASS,				//1.0f; Normal
	DIRT,				//1.3f
	GRAVEL,				//2.5f
	WATER,				//5.0f
	TILE_TERRAIN_COUNT
};

class Tile : public Node
{
	//// THE IDEAL TILE ////
	//Iso Tile Width: 100
	//Iso Tile Height: 50
	//Image width: 100
	//Image height: 200
private:
	bool			m_mouseOver = false;		//Tracks if the mouse is over it or not
	pkr::Vector2	m_originOffset = { 0.5f, 0.18f };		//Change for each tile set

public:	
	int				ID;

	//Terrain and accessibility
	eTileTerrain	terrain;
	eTileAccess		access;	

	//NOTE!!!
	//depthSortOffset: The point offset from cPos (cartesian world coord) at which the 
	//Depth Sorter uses to sort the depth of the tile/object
	//This point should be the isometrically furthest point from the viewer where the object
	//intersects or meets the ground ie. back corner of block
	pkr::Vector2	dsOffset = { 0,0 };		
	//Texture
	aie::Texture*	tex = nullptr;

public:
	Tile() = default;
	virtual ~Tile() = default;	//Texture manager will delete the textures

	Tile(pkr::Vector2 pos, aie::Texture* tex, pkr::Vector2 dsOffset = { 0,0 }, eTileTerrain terrain = SMOOTH_FLOOR, eTileAccess access = ACCESSIBLE);

	bool			onMouseOver() const { return m_mouseOver; }

	//Cores
	void			draw(aie::Renderer2D* renderer);
};

	//Accessors
	//aie::Texture*	getTexture() const { return tex; }
	//pkr::Vector2	getTexOffset() const { return texOffset; }
	//pkr::Vector2	getPosition() const { return posCart; }
	//eTileType		getType() const { return type; }
	//void			setTexture(aie::Texture* tex) { tex = tex; }
	//void			setTexOffset(pkr::Vector2 &texOffset) { texOffset = texOffset; }
	//void			setPosition(pkr::Vector2 &pos) { pos = pos; }
	//void			setType(eTileType type) { type = type; }
}
