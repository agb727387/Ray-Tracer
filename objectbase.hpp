#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "qbVector.h"
#include "ray.hpp"

namespace qbRT
{
	class objectBase
	{
	public:
		// Constructor and the destructor...
		objectBase();
		virtual ~objectBase();

		// Function to test for intersections goes here...
		virtual bool testIntersection(const ray& castRay, qbVector<double>& intPoint, qbVector<double>
			& localNormal, qbVector<double>& localColor);

		// Function to test whether two floating point numbers are close to being equal...
		bool closeEnough(const double f1, const double f2);

		// Public access specifier variables...
	public:
		// Base color of obj...
		qbVector<double> m_baseColor{ 3 };
	};
}


#endif