#include "CoordConverter.h"
#include "GameDefines.h"
#include <Vector2.h>
#include "KunoApp.h"
#include "Camera.h"

namespace util {
	
	CoordConverter::CoordConverter(Camera * camera) :
		m_cam(camera)
	{}

	pkr::Vector2 CoordConverter::ViewportToCanvas(float viewportX, float viewportY)
	{
		//Init vars for return
		pkr::Vector2 canvas = { 0,0 };

		auto windowWidth = KunoApp::getInstance()->getWindowWidth();
		auto windowHeight = KunoApp::getInstance()->getWindowHeight();

		//Borrowed code
		float xPcentage = viewportX / windowWidth;
		float yPcentage = viewportY / windowHeight;

		float scaledWidth = windowWidth * m_cam->scale;
		float scaledHeight = windowHeight * m_cam->scale;

		float midX = m_cam->x + (windowWidth / 2.0f);
		float midY = m_cam->y + (windowHeight / 2.0f);

		float left = midX - (scaledWidth / 2.0f);
		float bottom = midY - (scaledHeight / 2.0f);

		canvas.x = left + (xPcentage * scaledWidth);
		canvas.y = bottom + (yPcentage * scaledHeight);

		return canvas;
	}
}
