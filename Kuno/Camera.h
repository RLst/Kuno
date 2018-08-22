//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#pragma once
#include <pkr\Vector2.h>

//Forward declares
class KunoApp;
namespace aie {
	class Renderer2D;
}

namespace util {

	//Camera controller
	class Camera
	{
	private:
		//Edge scroll and panning
		float			m_borderZone = 20.0f;	//px; Pixels from edge of screen to trigger edge scroll
		float			m_panSpeed = 1000.0f;

		//Zoom
		float			m_minZoom = 7.5f;
		float			m_maxZoom = 0.5f;
		float			m_zoomSpeedMultiplier = 12.0f;
		float			m_lastScrollPos = 0;		//Holds the previous mouse wheel position (if you don't default this to zero then it'll start off fully zoomed in etc)

#ifdef _DEBUG
friend class KunoApp;
#endif // _DEBUG


	public:
		float			x, y;			//px; position (canvas)
		float			zoom;			//arb; scale/zoom; higher = far zoom, lower = close zoom

	public:
		Camera() {}
		~Camera() {}
		Camera(float x = 0, float y = 0, float zoom = 1.0f);

		//Accessors

		void			update(float deltaTime);						//App get's passed in to access window size
		void			translate(aie::Renderer2D* renderer);		//Actually translate the camera
	};
}