//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#include "SpriteObject.h"
#include "KunoApp.h"

namespace ai {


SpriteObject::SpriteObject(aie::Texture * tex) :
	m_tex(tex)
{
	//m_animation.push_back(texture);
}

SpriteObject::~SpriteObject()
{
	//Texture manager should be responsible for deleting textures
}

//void SpriteObject::addAnimationFrame(aie::Texture * newFrame)
//{
//	m_animation.push_back(newFrame);
//}
//
//aie::Texture * SpriteObject::getCurrentAnimationFrame()
//{
//	return m_animation.back();		//Temp; There should ony be one texture
//}

void SpriteObject::draw(aie::Renderer2D * renderer)
{
	auto app = KunoApp::Instance();
	auto depth = app->DepthSorter()->getSortDepth(this);
	m_iPos = app->CoordConverter()->CartesianToIsometric(m_cPos);
	renderer->drawSprite(m_tex, m_iPos.x, m_iPos.y, 0, 0, 0, depth);
	//auto currentFrame = getCurrentAnimationFrame();
	//renderer->drawSprite(currentFrame, m_pos.x + m_offset.x, m_pos.y + m_offset.y, 0, 0, 0, depth, 0,0);
}

}
