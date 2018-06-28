#pragma once
#include "Vector2.h"

class Vector2;

//Yuna Okuma name found here: http://www.fantasynamegenerators.com/japanese_names.php

Vector2	IsometricToCartesian(const Vector2 &isometric)
{
	Vector2 cartesian;
	cartesian.x = (2.0f * isometric.y + isometric.x) / 2.0f;
	cartesian.y = (2.0f * isometric.y - isometric.x) / 2.0f;
	return cartesian;
}

Vector2 CartesianToIsometric(const Vector2 &cartesian)
{
	return Vector2(cartesian)

	Vector2 isometric;
	isometric.x = (2.0f * cartesian.y + cartesian.x) / 2.0f;
	isometric.y = (2.0f * cartesian.y - cartesian.x) / 2.0f;
	return isometric;
}
