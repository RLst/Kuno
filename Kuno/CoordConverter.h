#pragma once

namespace pkr {
	class Vector2;
}

namespace util {

	class Camera;

	class CoordConverter
	{
	private:
		Camera*		m_cam;

		//// HELPER CONVERSION FUNCTIONS ////
		pkr::Vector2		IsometricToCartesian(pkr::Vector2 iso) const;					//Not really required

		//Viewport -> Canvas -> Isometric -> Cartesian
		//pkr::Vector2		ViewportToCartesian(pkr::Vector2 vpPoint);			//Convert from viewport to cartesian world
		//pkr::Vector2		ViewportToCartesian(float vpX, float vpY);			
		//Cartesian -> Isometric
		//pkr::Vector2		CartesianToIsometric(pkr::Vector2 cart);			//Convert from cartesian world coords to isometric world coords
		//pkr::Vector2		CartesianToIsometric(float cartX, float cartY);
	public:
		CoordConverter() = default;
		~CoordConverter() = default;
		CoordConverter(Camera* camera);		//Auto get ptr to camera/// apparently camera can't be default to KunoApp::getInstance()->getCamera()....

		//// MAIN CONVERSION FUNCTIONS ////
		pkr::Vector2		ViewportToCartesian(pkr::Vector2 vpPos) const;					//Use by the mouse			
		pkr::Vector2		ViewportToCartesian(float vpX, float vpY) const;

		pkr::Vector2		CartesianToIsometric(pkr::Vector2 canvas) const;				//Use by the renderer
		pkr::Vector2		CartesianToIsometric(float canvasX, float canvasY) const;
	};

}