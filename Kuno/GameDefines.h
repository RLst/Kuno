#pragma once
#include "Vector2.h"

class Vector2;

//Yuna Okuma named found here: http://www.fantasynamegenerators.com/japanese_names.php

Vector2	ConvertIsoTo2D(const Vector2 &pointISO)
{
	Vector2 point2D;
	point2D.x = (2.0f * pointISO.y + pointISO.x) / 2.0f;
	point2D.y = (2.0f * pointISO.y - pointISO.x) / 2.0f;
	return point2D;
}

Vector2 Convert2DtoISO(const Vector2 &point2D)
{
	Vector2 pointISO;
	pointISO.x = (2.0f * point2D.y + point2D.x) / 2.0f;
	pointISO.y = (2.0f * point2D.y - point2D.x) / 2.0f;
	return pointISO;
}
