#include "camera.hpp"
#include "ray.hpp"
#include <cmath>

qbRT::camera::camera()
{
	// Default constructor...
	m_cameraPosition = qbVector<double>{ std::vector<double> {0.0, -10.0, 0.0} };
	m_cameraLookAt = qbVector<double>{ std::vector<double> {0.0, 0.0, 0.0} };
	m_cameraUp = qbVector<double>{ std::vector<double>{0.0, 0.0, 1.0} };
	m_cameraLength = 1.0;
	m_cameraHorzSize = 1.0;
	m_cameraAspectRatio = 1.0;
}

void qbRT::camera::setPosition(const qbVector<double>& newPosition)
{
	m_cameraPosition = newPosition;
}

void qbRT::camera::setLookAt(const qbVector<double>& newLookAt)
{
	m_cameraLookAt = newLookAt;
}

void qbRT::camera::setUp(const qbVector<double>& upVector)
{
	m_cameraUp = upVector;
}

void qbRT::camera::setLength(double newLength)
{
	m_cameraLength = newLength;
}

void qbRT::camera::setHorzSize(double newHorzSize)
{
	m_cameraHorzSize = newHorzSize;
}

void qbRT::camera::setAspect(double newAspect)
{
	m_cameraAspectRatio = newAspect;
}

// Method to return the position of the camera.
qbVector<double> qbRT::camera::getPosition()
{
	return m_cameraPosition;
}

// Method to return the lookAt of the camera goes here...
qbVector<double> qbRT::camera::getLookAt()
{
	return m_cameraLookAt;
}

// Method to return the up vector of the camera goes here...
qbVector<double> qbRT::camera::getUp()
{
	return m_cameraUp;
}

// Method to return the length of the camera goes here...
double qbRT::camera::getLength()
{
	return m_cameraLength;
}

// Method to return the horizontal size.
double qbRT::camera::getHorzSize()
{
	return m_cameraHorzSize;
}

// Method to return the camera aspect ratio goes here...
double qbRT::camera::getAspect()
{
	return m_cameraAspectRatio;
}

// Method to return the U vector goes here...
qbVector<double> qbRT::camera::getU()
{
	return m_projectionScreenU;
}

// Method to return the V vector goes here...
qbVector<double> qbRT::camera::getV()
{
	return m_projectionScreenV;
}

// Method to return the projection screen center goes here...
qbVector<double> qbRT::camera::getScreenCenter()
{
	return m_projectionScreenCenter;
}

// Function to compute camera geometry goes here...
void qbRT::camera::updateCameraGeometry()
{
	// First, compute the vector from the camera position to the lookAt position...
	m_alignmentVector = m_cameraLookAt - m_cameraPosition;
	m_alignmentVector.Normalize();

	// Second, compute the U and V vectors.
	m_projectionScreenU = qbVector<double>::cross(m_alignmentVector, m_cameraUp);
	m_projectionScreenU.Normalize();
	m_projectionScreenV = qbVector<double>::cross(m_projectionScreenU, m_alignmentVector);
	m_projectionScreenV.Normalize();

	// Third, compute the position of the center point of the screen...
	m_projectionScreenCenter = m_cameraPosition + (m_cameraLength * m_alignmentVector);

	// Finally, modify the U and V vectors to match the size and aspect ratio...
	m_projectionScreenU = m_projectionScreenU * m_cameraHorzSize;
	m_projectionScreenV = m_projectionScreenV * (m_cameraHorzSize / m_cameraAspectRatio);

}

bool qbRT::camera::generateRay(float proScreenX, float proScreenY, qbRT:: ray &cameraRay)
{
	// Compute the location of the screen point in world coordinates.
	qbVector<double> screenWorldPart1 = m_projectionScreenCenter + (m_projectionScreenU * proScreenX);
	qbVector<double> screenWorldCoordinate = screenWorldPart1 + (m_projectionScreenV * proScreenY);

	// Use this point along with the camera position to compute the ray...
	cameraRay.m_point1 = m_cameraPosition;
	cameraRay.m_point2 = screenWorldCoordinate;
	cameraRay.m_lab = screenWorldCoordinate - m_cameraPosition;

	return true;

}