//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////

#include "StaticObject.h"

#include "KunoApp.h"

namespace pf {


	void StaticObject::draw(aie::Renderer2D * renderer)
	{
		//Calc iso position and sort depth
		cPos = KunoApp::Instance()->CoordConverter()->WorldToCanvas(pos);
		auto depth = KunoApp::Instance()->DepthSorter()->getSortDepth(cPos.y + dsOffset.y);		//for some reason iPos MINUS dsOffset works
																								//Draw
		renderer->drawSprite(tex, cPos.x, cPos.y, 0, 0, 0, depth, m_originOffset.x, m_originOffset.y);		//Centred on the isometric middle of the tile
																											//renderer->drawSprite(tex, iPos.x + depthSortOffset.x, iPos.y + depthSortOffset.y, 0, 0, 0, depth);
	}

}