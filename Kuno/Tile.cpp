#include "Tile.h"
#include "KunoApp.h"

namespace pf {

	Tile::Tile(pkr::Vector2 pos, aie::Texture * tex, pkr::Vector2 texOffset, eTileType type) :
		/*pos(pos), */tex(tex), texOffset(texOffset), type(type)
	{
		cPos = pos;
	}

	void Tile::draw(aie::Renderer2D * renderer)
	{
		//Calc iso position and sort depth
		iPos = KunoApp::Instance()->CoordConverter()->CartesianToIsometric(cPos);
		auto depth = KunoApp::Instance()->DepthSorter()->getSortDepth(iPos.y);

		//Draw
		renderer->drawSprite(tex, iPos.x + texOffset.x, iPos.y + texOffset.y, 0, 0, 0, depth);
	}

}
