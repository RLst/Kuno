#pragma once
#include <vector>
#include <Vector2.h>

namespace PF {

	typedef std::vector<pkr::Vector2> PointList;

	class Path
	{
	private:
		PointList		m_path;	//Should this be a vector of pointers??? How do dat?
	public:
		Path();
		~Path();

		void			addWayPoint(const pkr::Vector2 wayPoint);
		PointList		getPath() const { return m_path; }
	};

}
