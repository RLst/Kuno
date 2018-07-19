//pkr Math Library
//Author: Tony Le
//Version: 1.0

#pragma once

namespace pkr {

const double PI = 3.1415926535897932384626433832795;

float DegToRad(float degrees) {
	float (degrees * 180.0f / PI);
}

float RadToDeg(float radians) {
	return (radians * PI / 180.0f);
}

}
