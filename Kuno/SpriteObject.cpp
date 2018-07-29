#include "SpriteObject.h"
#include "KunoApp.h"

namespace ai {


SpriteObject::SpriteObject(aie::Texture * texture)
{
	m_animation.push_back(texture);
}

SpriteObject::~SpriteObject()
{
	//Texture manager should be responsible for deleting textures
}

void SpriteObject::addAnimationFrame(aie::Texture * newFrame)
{
	m_animation.push_back(newFrame);
}

aie::Texture * SpriteObject::getCurrentAnimationFrame()
{
	return m_animation.back();		//Temp; There should ony be one texture
}

void SpriteObject::draw(aie::Renderer2D * renderer)
{
	auto depth = KunoApp::Instance()->DepthSorter()->getSortDepth(this);
	auto currentFrame = getCurrentAnimationFrame();
	renderer->drawSprite(currentFrame, m_pos.x + m_offset.x, m_pos.y + m_offset.y, 0, 0, 0, depth, 0,0);
}

}
