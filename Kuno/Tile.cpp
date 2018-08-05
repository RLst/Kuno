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
		pos = Mpos;
	}

	void Tile::draw(aie::Renderer2D * renderer)
	{
		//Calc iso position and sort depth
		cPos = KunoApp::Instance()->CoordConverter()->WorldToCanvas(pos);
		auto depth = KunoApp::Instance()->DepthSorter()->getSortDepth(cPos.y + dsOffset.y);		//for some reason iPos MINUS dsOffset works

		//Draw tile and objects
		//(Any tints set before this will be applied to both tiles and any child static objects)
		renderer->drawSprite(tex, cPos.x, cPos.y, 0, 0, 0, depth, m_originOffset.x, m_originOffset.y);		//Centred on the isometric middle of the tile
		for (auto o : objects) {
			o->draw(renderer);
		}
		
	}

}
