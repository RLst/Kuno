#include "Tile.h"

namespace PF {

PF::Tile::Tile(int xIndex, int yIndex, pkr::Vector2 pos) :
	X(xIndex),
	Y(yIndex)
{
	(*this).pos = pos;		//Node::pos
}

PF::Tile::~Tile()
{
	delete m_texture;
}

void Tile::draw(aie::Renderer2D * renderer)
{
	renderer->drawSprite(m_texture, m_pos.x, m_pos.y);
}

}
