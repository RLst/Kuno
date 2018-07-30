#pragma once
#include "PF.h"

namespace aie {
	class Texture;
}

namespace pf {

enum eTileType
{
	INACCESSIBLE = 0,
	ACCESSIBLE,
	CLIMBABLE,
	TILETYPE_COUNT		//The total number of tile types
};

class Tile : public Node
{
	//// THE IDEAL TILE ////
	//Iso Tile Width: 100
	//Iso Tile Height: 50
	//Image width: 100
	//Image height: 200
	//
private:
	bool			m_mouseOver = false;		//Tracks if the mouse is over it or not

public:	
	//Texture
	aie::Texture*	tex = nullptr;
	pkr::Vector2	texOffset = { 0,0 };		//This should be added onto the isoPos

	//pkr::Vector2	posCart;			//cartesian
	//pkr::Vector2	posIso;				//isometric
	eTileType		type;

public:
	Tile() = default;
	virtual ~Tile() = default;	//Texture manager will delete the textures

	Tile(pkr::Vector2 position, aie::Texture* tex, pkr::Vector2 texOffset = { 0,0 }, eTileType type = ACCESSIBLE);

	//Accessors
	//aie::Texture*	getTexture() const { return tex; }
	//pkr::Vector2	getTexOffset() const { return texOffset; }
	//pkr::Vector2	getPosition() const { return posCart; }
	//eTileType		getType() const { return type; }
	bool			onMouseOver() const { return m_mouseOver; }

	//void			setTexture(aie::Texture* tex) { tex = tex; }
	//void			setTexOffset(pkr::Vector2 &texOffset) { texOffset = texOffset; }
	//void			setPosition(pkr::Vector2 &pos) { pos = pos; }
	//void			setType(eTileType type) { type = type; }

	//Cores
	void			draw(aie::Renderer2D* renderer);
};

}
