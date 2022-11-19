#ifndef OBJECTSPHERE_H
#define OBJECTSPHERE_H

#include "objectbase.hpp"

namespace qbRT
{
	class objectSphere : public objectBase
	{
	public:
		// Default constuctor (Defines a unit sphere at the origin)
		objectSphere();

		// Override the destructor
		virtual ~objectSphere() override;

		// Override the function to test for the intersections...
		virtual bool testIntersection(const qbRT::ray& castRay, qbVector<double>& intPoint, qbVector<double>
			& localNormal, qbVector<double>& localColor);

	private:

	};
}

#endif