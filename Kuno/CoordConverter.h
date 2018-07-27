#pragma once
#include "KunoApp.h"

namespace pkr {
	class Vector2;
}

namespace util {

class Camera;

class CoordConverter
{
private:
	Camera*		m_cam;


public:
	CoordConverter() = default;
	~CoordConverter() = default;
	CoordConverter(Camera* camera = KunoApp::getInstance()->getCamera());		//Auto get ptr to camera

	//// MAIN CONVERSION FUNCTIONS ////
	//Viewport -> Canvas -> Isometric -> Cartesian
	static pkr::Vector2		ViewportToCartesian(pkr::Vector2 vpPoint);			//Convert from viewport to cartesian world
	static pkr::Vector2		ViewportToCartesian(float vpX, float vpY);			

	//Cartesian -> Isometric
	static pkr::Vector2		CartesianToIsometric(pkr::Vector2 cart);			//Convert from cartesian world coords to isometric world coords
	static pkr::Vector2		CartesianToIsometric(float cartX, float cartY);

private:
	//// HELPER CONVERSION FUNCTIONS ////
	static pkr::Vector2		ViewportToCanvas(float viewportX, float viewportY);		//Returns the equivalent canvas coords
	static pkr::Vector2		CanvasToIsometric(pkr::Vector2 canvas);
	static pkr::Vector2		IsometricToCartesian(pkr::Vector2 iso);
};

}
