#include "Path.h"

namespace PF {

	Path::Path()
	{
		//Allocate 

	}

	Path::~Path()
	{
		//for (auto wayPoint : m_wayPoints) {
		//	delete wayPoint;
		//	wayPoint = nullptr;
		//}
	}

	void Path::addWayPoint(const pkr::Vector2 wayPoint)
	{
		m_path.push_back(wayPoint);
	}

}
