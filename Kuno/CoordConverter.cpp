//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#include "CoordConverter.h"
#include "GameDefines.h"
#include <pkr\Vector2.h>
#include "KunoApp.h"
#include "Camera.h"

namespace util {
	
	CoordConverter::CoordConverter(Camera * camera) :
		m_cam(camera)
	{}

	CoordConverter::CoordConverter(Camera & camera) :
		m_cam(&camera)
	{}

	pkr::Vector2 CoordConverter::ViewportToCanvas(pkr::Vector2 viewport) const			//Used to be ViewportToCartesian
	{
		//Init vars for return
		pkr::Vector2 canvas = { 0,0 };

		auto windowWidth = KunoApp::Instance()->getWindowWidth();
		auto windowHeight = KunoApp::Instance()->getWindowHeight();

		/// Borrowed code ///
		//This takes into account the zoom of the camera
		float xPcentage = viewport.x / windowWidth;
		float yPcentage = viewport.y / windowHeight;

		float scaledWidth = windowWidth * m_cam->zoom;
		float scaledHeight = windowHeight * m_cam->zoom;

		float midX = m_cam->x + (windowWidth / 2.0f);
		float midY = m_cam->y + (windowHeight / 2.0f);

		float left = midX - (scaledWidth / 2.0f);
		float bottom = midY - (scaledHeight / 2.0f);

		canvas.x = left + (xPcentage * scaledWidth);
		canvas.y = bottom + (yPcentage * scaledHeight);
		/// Borrowed code ///

		return canvas;
	}

	pkr::Vector2 CoordConverter::ViewportToCanvas(float viewportX, float viewportY) const
	{
		//Just redirect
		return ViewportToCanvas(pkr::Vector2(viewportX, viewportY));
	}

	pkr::Vector2 CoordConverter::WorldToCanvas(pkr::Vector2 world) const			//Used to be cartesian to isometric
	{
		//// WAIT WHAT??? Is CANVAS actually just CARTESIAN... NOPE! IT'S CANVAS === ISOMETRIC
		pkr::Vector2 canvas = { 0,0 };
		canvas.x = world.x - world.y;
		canvas.y = (world.x + world.y) / TILE_RATIO;
		return canvas;
	}

	pkr::Vector2 CoordConverter::WorldToCanvas(float worldX, float worldY) const
	{
		return WorldToCanvas(pkr::Vector2(worldX, worldY));		//Redirect
	}

	pkr::Vector2 CoordConverter::CanvasToWorld(pkr::Vector2 canvas) const			//Used to be isometric to cartesian
	{
		pkr::Vector2 world = { 0,0 };
		world.x = (TILE_RATIO * canvas.y + canvas.x) / 2.0f;
		world.y = (TILE_RATIO * canvas.y - canvas.x) / 2.0f;
		return world;
	}

	pkr::Vector2 CoordConverter::CanvasToWorld(float canvasX, float canvasY) const
	{
		return CanvasToWorld(pkr::Vector2(canvasX, canvasY));
	}

}
