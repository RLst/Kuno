#pragma once
#include <Vector2.h>

//Forward declares
class KunoApp;
namespace aie {
	class Renderer2D;
}

namespace util {

	class Camera
	{
	private:
		float			m_edgeScrlSize = 30.0f;	//px; Pixels from edge of screen where the mouse will move 
		float			m_scrollSpeed = 20.0f;
		float			m_zoomSpeed = 0.2f;
		int				windowWidth;
		int				windowHeight;

	public:
		//// PUBLIC VARS ////
		float			x, y;			//px; position
		float			scale;			//arb; scale/zoom
		////////////////////
		
		Camera();


		void	update(float deltaTime);		//App get's passed in to access window size

	};

}