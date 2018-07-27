#pragma once
#include <cassert>

//#define SCREEN_WIDTH 1280
//#define SCREEN_HEIGHT 720

#define WORLD_WIDTH 5		//Tiles along X axis
#define WORLD_DEPTH 5		//Tiles along Y axis

#define CART_TILE_WIDTH 128		//In this case, the tiles in this world (orthogonal)
#define CART_TILE_HEIGHT 128		//is 128x128
//#define CART_TILE_WIDTH -128		//In this case, the tiles in this world (orthogonal)
//#define CART_TILE_HEIGHT -128		//is 128x128

//#define ISO_TILE_WIDTH 100		//px; Width of isometric tile; Must change according to assets
//#define ISO_TILE_HEIGHT 50		//px; Height of isometric tile; Must change according to assets
#define ISO_TILE_WIDTH 255		//px; Width of isometric tile; Must change according to assets
#define ISO_TILE_HEIGHT 148		//px; Height of isometric tile; Must change according to assets
const float TILE_RATIO = (float)ISO_TILE_WIDTH / (float)ISO_TILE_HEIGHT;	//Used for Iso<>Cart conversions

namespace pkr {

int Random(int min, int max);		//int RNG

template <typename T>
T Clamp(const T& value, const T& min, const T& max)
{
	if (value < min)
		return min;
	else if (value > max)
		return max;
	//Else it is already clamped OR the min/max values are invalid :P
}

}
