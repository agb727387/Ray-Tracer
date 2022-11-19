#include "pointLight.hpp"

qbRT::pointLight::pointLight()
{
	m_color = qbVector<double>{ std::vector<double> {1.0, 1.0, 1.0} };
	m_intensity = 1.0;
}

qbRT::pointLight::~pointLight()
{

}

// Function to complete the illumination...
bool qbRT::pointLight::computeIllumination(const qbVector<double>& intPoint, const qbVector<double>
	& localNormal, const std::vector<std::shared_ptr<qbRT::objectBase>>& objectList,
	const std::shared_ptr<qbRT::objectBase>& currentObject, qbVector<double>& color, double& intensity)
{
	// Construct a vector pointing from the intersection point to the light...
	qbVector<double> lightDir = (m_location - intPoint).Normalized();

	// Compute the starting point here...
	qbVector<double> startPoint = intPoint;

	// Compute the angle between the local normal and the light ray...
	// We assume that localNormal is a unit vector...
	double angle = acos(qbVector<double>::dot(localNormal, lightDir));

	// If the normal is pointing away from the light, then we have no illumination present...
	if (angle > 1.5708)
	{
		// No illumination...
		color = m_color;
		intensity = 0.0;
		return false;
	}
	else
	{
		// Otherwise, we do have some illumination present...
		color = m_color;
		intensity = m_intensity * (1.0 - (angle / 1.5708));
		return true;
	}
	return true;
}