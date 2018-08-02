//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#pragma once

namespace pkr {
	class Vector2;
}

namespace util {

	class Camera;

	//Converts between coordinate systems: Viewport, Cartesian, Isometric
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
		pkr::Vector2		ViewportToCartesian(pkr::Vector2 viewportPos) const;					//Use by the mouse			
		pkr::Vector2		ViewportToCartesian(float viewportX, float viewportY) const;

		pkr::Vector2		CartesianToIsometric(pkr::Vector2 cartesianPos) const;					//Use by the renderer
		pkr::Vector2		CartesianToIsometric(float cartesianX, float cartesianY) const;
	
		pkr::Vector2		IsometricToCartesian(pkr::Vector2 iso) const;							//Used by keyboard controller
		pkr::Vector2		IsometricToCartesian(float isometricX, float isometricY) const;

	};

}