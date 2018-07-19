#include "Iso.h"

namespace Iso {
	pkr::Vector2 IsometricToCartesian(const pkr::Vector2 & isometric)
	{
		pkr::Vector2 cartesian;
		cartesian.x = (2.0f * isometric.y + isometric.x) / 2.0f;
		cartesian.y = (2.0f * isometric.y - isometric.x) / 2.0f;
		return cartesian;
	}

	pkr::Vector2 CartesianToIsometric(const pkr::Vector2 & cartesian)
	{
		//return Vector2(cartesian)
		pkr::Vector2 isometric;
		isometric.x = (2.0f * cartesian.y + cartesian.x) / 2.0f;
		isometric.y = (2.0f * cartesian.y - cartesian.x) / 2.0f;
		return isometric;
	}
}