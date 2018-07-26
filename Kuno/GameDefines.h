#pragma once

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define WORLD_WIDTH 10		//Tiles along X axis
#define WORLD_DEPTH 10		//Tiles along Y axis

#define ISO_TILE_WIDTH 255		//Width of isometric tile in px
#define ISO_TILE_HEIGHT 148		//Height of isometric tile in px

#define CART_TILE_WIDTH -128		//In this case, the tiles in this world (orthogonal)
#define CART_TILE_HEIGHT -128		//is 128x128
//127,344: Top corner of tile
//Tiles are ~147px square

int Random(int min, int max);


//#include "Vector2.h"
//
//class Vector2;
//
////Yuna Okuma name found here: http://www.fantasynamegenerators.com/japanese_names.php
//
//Vector2	IsometricToCartesian(const Vector2 &isometric)
//{
//	Vector2 cartesian;
//	cartesian.x = (2.0f * isometric.y + isometric.x) / 2.0f;
//	cartesian.y = (2.0f * isometric.y - isometric.x) / 2.0f;
//	return cartesian;
//}
//
//Vector2 CartesianToIsometric(const Vector2 &cartesian)
//{
//	return Vector2(cartesian)
//
//	Vector2 isometric;
//	isometric.x = (2.0f * cartesian.y + cartesian.x) / 2.0f;
//	isometric.y = (2.0f * cartesian.y - cartesian.x) / 2.0f;
//	return isometric;
//}


