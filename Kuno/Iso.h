#pragma once
#include "Vector2.h"

//Isometric to Cartesian conversion functions
namespace Iso {

	class Vector2;

	//Yuna Okuma name found here: http://www.fantasynamegenerators.com/japanese_names.php

	pkr::Vector2	IsometricToCartesian(const pkr::Vector2 &isometric);

	pkr::Vector2	CartesianToIsometric(const pkr::Vector2 &cartesian);
	
}