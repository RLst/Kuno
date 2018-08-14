//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#pragma once
#include "Agent.h"

namespace aie {
	class Texture;
}

namespace ai {

class SpriteObject : public Agent
{
protected:
	aie::Texture*	m_tex;					//Can also be a animation/tile set (use setUVRect())
	pkr::Vector2	m_offset = { 0,0 };		//The texture offset from the BOTTOM_LEFT corner of the image
	float			m_animationSpeed;		//ms
	//std::vector<aie::Texture*>	m_animation;

public:
	SpriteObject() = default;
	SpriteObject(aie::Texture* texture);		//Texture is the first frame
	virtual ~SpriteObject();

	//Core
	void			draw(aie::Renderer2D* renderer) override;

	//Animation handling
	//void			addAnimationFrame(aie::Texture* newFrame);
	//aie::Texture*	getCurrentAnimationFrame();		//TBC
	//void			updateAnimationEngine();		//TBC
};

}
