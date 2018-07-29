#include "CoordConverter.h"
#include "GameDefines.h"
#include <Vector2.h>
#include "KunoApp.h"
#include "Camera.h"

namespace util {
	
	CoordConverter::CoordConverter(Camera * camera) :
		m_cam(camera)
	{}

	CoordConverter::CoordConverter(Camera & camera) :
		m_cam(&camera)
	{}

	pkr::Vector2 CoordConverter::ViewportToCartesian(pkr::Vector2 viewport) const
	{
		//Init vars for return
		pkr::Vector2 canvas = { 0,0 };

		auto windowWidth = KunoApp::getInstance()->getWindowWidth();
		auto windowHeight = KunoApp::getInstance()->getWindowHeight();

		/// Borrowed code ///
		//This takes into account the zoom of the camera
		float xPcentage = viewport.x / windowWidth;
		float yPcentage = viewport.y / windowHeight;

		float scaledWidth = windowWidth * m_cam->scale;
		float scaledHeight = windowHeight * m_cam->scale;

		float midX = m_cam->x + (windowWidth / 2.0f);
		float midY = m_cam->y + (windowHeight / 2.0f);

		float left = midX - (scaledWidth / 2.0f);
		float bottom = midY - (scaledHeight / 2.0f);

		canvas.x = left + (xPcentage * scaledWidth);
		canvas.y = bottom + (yPcentage * scaledHeight);
		/// Borrowed code ///

		return canvas;
	}

	pkr::Vector2 CoordConverter::ViewportToCartesian(float viewportX, float viewportY) const
	{
		//Just redirect
		return ViewportToCartesian(pkr::Vector2(viewportX, viewportY));

		////Init vars for return
		//pkr::Vector2 canvas = { 0,0 };

		//auto windowWidth = KunoApp::getInstance()->getWindowWidth();
		//auto windowHeight = KunoApp::getInstance()->getWindowHeight();

		///// Borrowed code ///
		//float xPcentage = viewportX / windowWidth;
		//float yPcentage = viewportY / windowHeight;

		//float scaledWidth = windowWidth * m_cam->scale;
		//float scaledHeight = windowHeight * m_cam->scale;

		//float midX = m_cam->x + (windowWidth / 2.0f);
		//float midY = m_cam->y + (windowHeight / 2.0f);

		//float left = midX - (scaledWidth / 2.0f);
		//float bottom = midY - (scaledHeight / 2.0f);

		//canvas.x = left + (xPcentage * scaledWidth);
		//canvas.y = bottom + (yPcentage * scaledHeight);
		///// Borrowed code ///

		//return canvas;
	}

	pkr::Vector2 CoordConverter::CartesianToIsometric(pkr::Vector2 canvas) const
	{
		//// WAIT WHAT??? Is CANVAS actually just CARTESIAN
		pkr::Vector2 iso = { 0,0 };
		iso.x = canvas.x - canvas.y;
		iso.y = (canvas.x + canvas.y) / TILE_RATIO;
		return iso;
	}

	pkr::Vector2 CoordConverter::CartesianToIsometric(float canvasX, float canvasY) const
	{
		return CartesianToIsometric(pkr::Vector2(canvasX, canvasY));		//Redirect
	}

	pkr::Vector2 CoordConverter::IsometricToCartesian(pkr::Vector2 iso) const
	{
		pkr::Vector2 cart;
		cart.x = (TILE_RATIO * iso.y + iso.x) / TILE_RATIO;
		cart.y = (TILE_RATIO * iso.y - iso.x) / TILE_RATIO;
		return cart;
	}

}
