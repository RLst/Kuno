//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#include "Tile.h"
#include "KunoApp.h"
#include "StaticObject.h"

namespace pf {
	Tile::~Tile()
	{
		for (auto &o : objects) {
			delete o;
			o = nullptr;
		}
	}
	Tile::Tile(pkr::Vector2 Mpos, aie::Texture * Mtex, pkr::Vector2 MdsOffset, eTileTerrain Mterrain, eTileTraversable Mtraversibility) :
		tex(Mtex), dsOffset(MdsOffset), terrain(Mterrain), access(Mtraversibility)
	{
		cPos = Mpos;
	}

	void Tile::draw(aie::Renderer2D * renderer)
	{
		//Calc iso position and sort depth
		iPos = KunoApp::Instance()->CoordConverter()->CartesianToIsometric(cPos);
		auto depth = KunoApp::Instance()->DepthSorter()->getSortDepth(iPos.y + dsOffset.y);		//for some reason iPos MINUS dsOffset works

		//Draw tile
		renderer->drawSprite(tex, iPos.x, iPos.y, 0, 0, 0, depth, m_originOffset.x, m_originOffset.y);		//Centred on the isometric middle of the tile

		//Draw any objects
		for (auto o : objects) {
			o->draw(renderer);
		}
		
	}

}
