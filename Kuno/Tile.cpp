#include "Tile.h"
#include "KunoApp.h"

namespace pf {

	Tile::Tile(pkr::Vector2 pos, aie::Texture * tex, pkr::Vector2 texOffset, eTileType type) :
		m_pos(pos), m_tex(tex), m_texOffset(texOffset), m_type(type)
	{
	}

	void Tile::draw(aie::Renderer2D * renderer)
	{
		//Calc z buffer depth
		auto depth = KunoApp::getInstance()->getDepthSorter()->getSortDepth(m_pos.y);

		//Draw
		renderer->drawSprite(m_tex, m_pos.x, m_pos.y, 0, 0, 0, depth);
	}






}
