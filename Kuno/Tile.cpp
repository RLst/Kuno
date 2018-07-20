#include "Tile.h"

namespace PF {

PF::Tile::Tile(int X_index, int Y_index, pkr::Vector2 position) :
	X(X_index),
	Y(Y_index)
{
	(*this).pos = position;
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
