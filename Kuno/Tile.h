#pragma once
#include "PF.h"

namespace aie {
	class Texture;
}

namespace PF {

enum eTileType
{
	INACCESSIBLE = 0,
	ACCESSIBLE,
	CLIMBABLE,
	TILETYPE_COUNT		//The total number of tile types
};

class Tile : public Node
{
protected:	
	//Texture properties
	aie::Texture*	m_texture;

	//Tile properties
	eTileType		m_type;

	//Draw...
public:
	///////////////////////
	//PUBLIC VARS
	//Array indices
	int				X, Y;
	//pkr::Vector2	offset;
	//pkr::Vector2	pos;		//Position info for tiles only
	///////////////////////////

	Tile() = default;
	Tile(aie::Texture* texture);
	~Tile();
	//Tile(int xIndex, int yIndex, pkr::Vector2 pos);

	//Accessors
	aie::Texture*	getTexture() const { return m_texture; }

	//Cores
	//void			draw(aie::Renderer2D* renderer);
};

}
