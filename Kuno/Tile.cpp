#include "Tile.h"
#include "KunoApp.h"

namespace pf {

	Tile::Tile(pkr::Vector2 Mpos, aie::Texture * Mtex, pkr::Vector2 MdsOffset, eTileTerrain Mterrain, eTileAccess Mtype) :
		tex(Mtex), dsOffset(MdsOffset), terrain(Mterrain), access(Mtype)
	{
		cPos = Mpos;
	}

	void Tile::draw(aie::Renderer2D * renderer)
	{
		//Calc iso position and sort depth
		iPos = KunoApp::Instance()->CoordConverter()->CartesianToIsometric(cPos);
		auto depth = KunoApp::Instance()->DepthSorter()->getSortDepth(iPos.y + dsOffset.y);		//for some reason iPos MINUS dsOffset works

		//Draw
		renderer->drawSprite(tex, iPos.x, iPos.y, 0, 0, 0, depth, m_originOffset.x, m_originOffset.y);		//Centred on the isometric middle of the tile
		//renderer->drawSprite(tex, iPos.x + depthSortOffset.x, iPos.y + depthSortOffset.y, 0, 0, 0, depth);
	}

}
