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
		KunoApp*		m_app;				//this required to access screen width and height?
		float			m_edgeScrlSize = 30.0f;	//px; Pixels from edge of screen where the mouse will move 
		float			m_scrollSpeed = 100.0f;
		float			m_zoomSpeed = 0.2f;
		int				m_windowWidth;
		int				m_windowHeight;

	public:
		//// PUBLIC VARS ////
		float			x, y;			//px; position
		float			scale;			//arb; scale/zoom
		////////////////////
		
		Camera(KunoApp* app);

		pkr::Vector2	WindowToCanvas(float &windowX, float &windowY);	//Input screen pos passed in as reference will be converted to world pos 

		void	update(float deltaTime);		//App get's passed in to access window size\

		//// DEBUG ////
		void	testWindowToCanvas(aie::Renderer2D* renderer);
		///////////////
	};

}
