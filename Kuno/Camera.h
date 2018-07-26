#pragma once
#include <Vector2.h>

//Forward declares
class KunoApp;
namespace aie {
	class Renderer2D;
}

namespace Util {

	class Camera
	{
	private:
		float			m_edgeScrlSize = 30.0f;	//px; Pixels from edge of screen where the mouse will move 
		float			m_scrollSpeed = 100.0f;
		float			m_zoomSpeed = 0.2f;
		int				windowWidth;
		int				windowHeight;

	public:
		//// PUBLIC VARS ////
		float			x, y;			//px; position
		float			scale;			//arb; scale/zoom
		////////////////////
		
		Camera();

		pkr::Vector2	ViewportToCanvas(float viewportX, float viewportY);		//Returns the equivalent canvas coords
		//Viewport: The screen area you're looking through ie: input->getMouse() returns viewport coords
		//Canvas: The actual working 2D area that's being rendered

		void	update(float deltaTime);		//App get's passed in to access window size

		//// DEBUG ////
		void	testViewportToCanvas(aie::Renderer2D* renderer);
		///////////////
	};

}
