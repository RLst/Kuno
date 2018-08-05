//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////

#pragma once

#include "GameDefines.h"

namespace pkr {
	class Vector2;
}

namespace util {

	class Camera;

	//Converts between coordinate systems: Viewport, Cartesian, Isometric
	//UPDATE: 4 AUG 2018
	//Viewport: The viewport
	//Canvas: The actual canvas that the renderer draws to and which we see, which is actually the ISOMETRIC world
	//World: The cartesian world that all game entities are supposed to live and move in. This is not visible to the screen, unless I make a mini map
	class CoordConverter
	{
	private:
		Camera*		m_cam;

	public:
		CoordConverter() = default;
		~CoordConverter() = default;
		CoordConverter(Camera* camera);		//ERROR: Apparently default param to = KunoApp::Instance()->Camera()
		CoordConverter(Camera& camera);		//If passing in an actual camera

		//// MAIN CONVERSION FUNCTIONS ////
		pkr::Vector2		ViewportToCanvas(pkr::Vector2 viewport) const;					//Use by the mouse			
		pkr::Vector2		ViewportToCanvas(float viewportX, float viewportY) const;

		pkr::Vector2		WorldToCanvas(pkr::Vector2 world) const;						//Use by the renderer
		pkr::Vector2		WorldToCanvas(float worldX, float worldY) const;
	
		pkr::Vector2		CanvasToWorld(pkr::Vector2 canvas) const;						//Used by keyboard controller
		pkr::Vector2		CanvasToWorld(float canvasX, float canvasY) const;				//BUG!! ONLY WORKS IF the tiles are 2x wide as their height

	};

}