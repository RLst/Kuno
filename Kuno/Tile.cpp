#include "Tile.h"
#include "KunoApp.h"

namespace pf {

	Tile::Tile(pkr::Vector2 pos, aie::Texture * tex, pkr::Vector2 texOffset, eTileType type) :
		/*pos(pos), */tex(tex), depthSortOffset(texOffset), type(type)
	{
		cPos = pos;
	}

	void Tile::draw(aie::Renderer2D * renderer)
	{
		//Calc iso position and sort depth
		iPos = KunoApp::Instance()->CoordConverter()->CartesianToIsometric(cPos);
		auto depth = KunoApp::Instance()->DepthSorter()->getSortDepth(iPos.y + depthSortOffset.y);

		//Draw
		renderer->drawSprite(tex, iPos.x, iPos.y, 0, 0, 0, depth, 0.0f, 0.5f);
		//renderer->drawSprite(tex, iPos.x + depthSortOffset.x, iPos.y + depthSortOffset.y, 0, 0, 0, depth);
	
	
	}

}
