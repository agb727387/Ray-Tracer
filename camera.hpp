#ifndef CAMERA_H
#define CAMERA_H

#include "qbVector.h"
#include "ray.hpp"

namespace qbRT
{
	class camera
	{
	public:
		// Constructor...
		camera();

		// Functions to set camera parameters...
		void setPosition(const qbVector<double>& newPosition);
		void setLookAt(const qbVector<double>& newLookAt);
		void setUp(const qbVector<double>& upVector);
		void setLength(double newLength);
		void setHorzSize(double newSizes);
		void setAspect(double newAspect);

		// Functions to return camera parameters...
		qbVector<double> getPosition();
		qbVector<double> getLookAt();
		qbVector<double> getUp();
		qbVector<double> getU();
		qbVector<double> getV();
		qbVector<double> getScreenCenter();
		double getLength();
		double getHorzSize();
		double getAspect();

		// Here is the function to generate a ray...
		bool generateRay(float proScreenX, float proScreenY, qbRT::ray &cameraRay);

		// Function to update the camera geometry...
		void updateCameraGeometry();

	private:
		qbVector<double> m_cameraPosition{ 3 };
		qbVector<double> m_cameraLookAt{ 3 };
		qbVector<double> m_cameraUp{ 3 };
		double m_cameraLength;
		double m_cameraHorzSize;
		double m_cameraAspectRatio;

		qbVector<double> m_alignmentVector{ 3 };
		qbVector<double> m_projectionScreenU{ 3 };
		qbVector<double> m_projectionScreenV{ 3 };
		qbVector<double> m_projectionScreenCenter{ 3 };
	};
}

#endif