#include "objectbase.hpp"
#include <cmath>

#define EPSILON 1e-21f;

// Default constructor goes here...
qbRT::objectBase::objectBase()
{

}

// The destructor...
qbRT::objectBase::~objectBase()
{

}

// Here is the function to test for the intersections...
bool qbRT::objectBase::testIntersection(const ray& castRay, qbVector<double>& intPoint, qbVector<double>
	& localNormal, qbVector<double>& localColor)
{
	return false;
}

// Function to test whether two floating point-numbers are close to being equal...
bool qbRT::objectBase::closeEnough(const double f1, const double f2)
{
	return fabs(f1 - f2) < EPSILON;
}