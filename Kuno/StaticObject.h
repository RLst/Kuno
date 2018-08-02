#pragma once
#include <pkr/Vector2.h>


namespace aie {
	class Texture;
	class Renderer2D;
}

namespace pf {

	class StaticObject
		//This is basically a tile object
		//Sole purpose is to store data and textures about an object on a tile
	{
	private:
		pkr::Vector2	m_originOffset = { 0.5f, 0.18f };
	public:
		//Texture
		aie::Texture*	tex = nullptr;
		pkr::Vector2	dsOffset = { 0,0 };		//px; depthsortOffset

		//Position
		pkr::Vector2	cPos, iPos;
		
	public:
		//~StaticObject();
		//StaticObject(aie::Renderer2D* Mtex, pkr::Vector2 &MdsOffset, );
		void			draw(aie::Renderer2D* renderer);
	};
}
