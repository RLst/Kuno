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
		//Edge scroll and panning
		float			m_borderZone = 20.0f;	//px; Pixels from edge of screen to trigger edge scroll
		float			m_panSpeed = 20.0f;

		//Zoom
		float			m_zoomSpeedMultiplier = 0.2f;
		float			m_lastScrollPos = 0;		//Holds the previous mouse wheel position (if you don't default this to zero then it'll start off fully zoomed in etc)

	public:
		float			x, y;			//px; position
		float			zoom;			//arb; scale/zoom; higher = far zoom, lower = close zoom

	public:
		Camera() {}
		~Camera() {}
		Camera(float x = 0, float y = 0, float zoom = 1.0f);

		//Accessors
		

		void			update(float deltaTime);		//App get's passed in to access window size
	};

}