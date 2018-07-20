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
	pkr::Vector2	m_offset;
	pkr::Vector2	m_pos;

	//General properties
	eTileType		m_type;

	//Draw
public:
	//Array indices
	int				X, Y;

	Tile() = default;
	Tile(int xIndex, int yIndex, pkr::Vector2 pos);
	~Tile();

	//Cores
	void			draw(aie::Renderer2D* renderer);
};

}
