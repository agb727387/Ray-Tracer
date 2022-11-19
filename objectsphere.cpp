#include "objectsphere.hpp"
#include <cmath>

// Default constructor...
qbRT::objectSphere::objectSphere()
{

}

// Destructor
qbRT::objectSphere::~objectSphere()
{

}

// Function to test for intersections...
bool qbRT::objectSphere::testIntersection(const qbRT::ray& castRay, qbVector<double>& intPoint,
	qbVector<double>& localNormal, qbVector<double>& localColor)
{
	// Compute the values of a, b, and c.
	qbVector<double> vhat = castRay.m_lab;
	vhat.Normalize();

	/*
	
		Note that a is equal to the squared magnitude of the direction of the cast ray. As this will
		be a unit vector, we can come to the conclusion that the value of 'a' will always be 1.

		a = 1.0;
	*/

	// Calculate b.
	double b = 2.0 * qbVector<double>::dot(castRay.m_point1, vhat);

	// Calculate c.
	double c = qbVector<double>::dot(castRay.m_point1, castRay.m_point1) - 1.0;

	// Test whether there actually exists an intersection...
	double intTest = (b * b) - 4.0 * c;

	if (intTest > 0.0)
	{
		double numSQRT = sqrtf(intTest);
		double answerOne = (-b + numSQRT) / 2.0;
		double answerTwo = (-b - numSQRT) / 2.0;

		// If either answerOne or answerTwo are negative, then at least part of the object is
		// behind the camera and so it will then be ignored as a result...

		if ((answerOne < 0.0) || (answerTwo < 0.0))
			return false;
		else
		{
			// Determine which point of intersection was closest to the camera...
			if (answerOne < answerTwo)
				intPoint = castRay.m_point1 + (vhat * answerOne);
			else
				intPoint = castRay.m_point1 + (vhat * answerTwo);

			// Compute the local normal (easy for a sphere at the origin...)
			localNormal = intPoint;
			localNormal.Normalize();
		}
		return true;
	}
	else
		return false;
}