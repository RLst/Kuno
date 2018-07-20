#pragma once
#include "PF.h"

namespace aie {
	class Texture;
}

namespace PF {

enum eTileType
{
	WALKABLE,
	CLIMBABLE,
	TILETYPE_COUNT		//The total number of type tiles
};

class Tile : public Node
{
protected:
	//Texture specs
	aie::Texture*	m_texture;
	pkr::Vector2	m_offset;
	pkr::Vector2	m_pos;

	//General tile info
	eTileType		m_type;

	//Draw
public:
	//Array indices
	int				X, Y;

	Tile() = default;
	Tile(int X_index, int Y_index, pkr::Vector2 position);
	~Tile();

	//Cores
	void			draw(aie::Renderer2D* renderer);
};

}
