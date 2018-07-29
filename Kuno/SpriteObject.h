#pragma once
#include "Agent.h"

namespace aie {
	class Texture;
}

namespace ai {

class SpriteObject : public Agent
{
protected:
	std::vector<aie::Texture*>	m_animation;
	pkr::Vector2	m_offset = { 0,0 };		//The texture offset from the BOTTOM_LEFT corner of the image
	float			m_animationSpeed;		//ms

public:
	SpriteObject(aie::Texture* texture);		//Texture is the first frame
	virtual ~SpriteObject();

	//Animation handling
	void			addAnimationFrame(aie::Texture* newFrame);
	aie::Texture*	getCurrentAnimationFrame();		//TBC
	void			updateAnimationEngine();		//TBC

	//Core
	void			draw(aie::Renderer2D* renderer) override;
};

}
