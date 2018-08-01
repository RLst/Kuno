#include "Tile.h"
#include "KunoApp.h"

namespace pf {

	Tile::Tile(pkr::Vector2 pos, aie::Texture * tex, pkr::Vector2 texOffset, eTileType type) :
		tex(tex), dsOffset(texOffset), type(type)
	{
		cPos = pos;
	}

	void Tile::draw(aie::Renderer2D * renderer)
	{
		//Calc iso position and sort depth
		iPos = KunoApp::Instance()->CoordConverter()->CartesianToIsometric(cPos);
		auto depth = KunoApp::Instance()->DepthSorter()->getSortDepth(iPos.y - dsOffset.y);		//for some reason it should be iPos MINUS dsOffset

		//Draw
		pkr::Vector2 originOffset = { 0.5f, 0.18f };
		renderer->drawSprite(tex, iPos.x, iPos.y, 0, 0, 0, depth, originOffset.x, originOffset.y);		//Centred on the isometric middle of the tile
		//renderer->drawSprite(tex, iPos.x + depthSortOffset.x, iPos.y + depthSortOffset.y, 0, 0, 0, depth);
	}

}
