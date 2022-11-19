#include "lightbase.hpp"

qbRT::lightbase::lightbase()
{

}

qbRT::lightbase::~lightbase()
{

}

// Function to compute illumination goes here...
bool qbRT::lightbase::computeIllumination(const qbVector<double>& intPoint, const qbVector<double>
	& localNormal, const std::vector<std::shared_ptr<qbRT::objectBase>>& objectList,
	const std::shared_ptr<qbRT::objectBase>& currentObject, qbVector<double>& color, double& intensity)
{
	return false;
}