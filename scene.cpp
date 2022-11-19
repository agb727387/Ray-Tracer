// scene.cpp

#include "scene.hpp"

// Constructor
qbRT::scene::scene()
{
	// Configure the camera here...
	m_camera.setPosition(qbVector<double>{std::vector<double> {0.0, -10.0, 0.0}});
	m_camera.setLookAt(qbVector<double>{std::vector<double> {0.0, 0.0, 0.0}});
	m_camera.setUp(qbVector<double>{std::vector<double> {0.0, 0.0, 1.0}});
	m_camera.setHorzSize(0.25);
	m_camera.setAspect(16.0 / 9.0);
	m_camera.updateCameraGeometry();

	// Construct a test sphere here...
	m_objectList.push_back(std::make_shared<qbRT::objectSphere>(qbRT::objectSphere()));

	// Construct a test light here...
	m_lightList.push_back(std::make_shared<qbRT::pointLight>(qbRT::pointLight()));
	m_lightList.at(0)->m_location = qbVector<double>{ std::vector<double> {5.0, -10.0, -5.0} };
	m_lightList.at(0)->m_color = qbVector<double>{ std::vector<double> {255.0, 255.0, 255.0} };
}

// Function to perform the rendering
bool qbRT::scene::render(qbImage& outputImage)
{
	// Get dimensions of output image...
	int xSize = outputImage.getXSize();
	int ySize = outputImage.getYSize();

	// Loop over each pixel in our image...
	qbRT::ray cameraRay;
	qbVector<double> intPoint(3);
	qbVector<double> localNormal(3);
	qbVector<double> localColor(3);
	double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
	double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);
	double minDistance = 1e6;
	double maxDistance = 0.0;

	for (int count = 0; count < xSize; ++count)
	{
		for (int countTwo = 0; countTwo < ySize; ++countTwo)
		{
			// Normalize x and y coordinates...
			double normX = (static_cast<double>(count) * xFact) - 1.0;
			double normY = (static_cast<double>(countTwo) * yFact) - 1.0;

			// Generate the ray for this pixel...
			m_camera.generateRay(normX, normY, cameraRay);

			// Test for intersections with all objects in the scene...
			for (auto currentObject : m_objectList)
			{
				bool validInt = currentObject->testIntersection(cameraRay, intPoint, localNormal, localColor);
				// If we have a valid intersection, change the pixel color to the color purple...
				if (validInt)
				{
					// Compute intensity of the illumination...
					 double intensity;
					 qbVector<double> color{ 3 };
					 bool validIllum = false;
					 for (auto currentLight : m_lightList)
					 {
						 validIllum = currentLight->computeIllumination(intPoint, localNormal, m_objectList,
							 currentObject, color, intensity);
					 }
					// Compute the distance between the camera and the point of intersection...
					double dist = (intPoint - cameraRay.m_point1).norm();
					if (dist > maxDistance)
						maxDistance = dist;

					if (dist < minDistance)
						minDistance = dist;

				
					//outputImage.setPixel(count, countTwo, 0.0, 249.8 - ((dist - 9.0) / 0.94605) * 249.8, 0.0);
					if (validIllum)
						outputImage.setPixel(count, countTwo, 255.0 * intensity, 0.0, 0.0);
					else
					{
						outputImage.setPixel(count, countTwo, 0.0, 0.0, 0.0);
					}
				}

				else
				{
					outputImage.setPixel(count, countTwo, 0.0, 0.0, 0.0);
				}
			}
		}
	}

	std::cout << "Here is the minimum distance: " << minDistance << std::endl;
	std::cout << "Here is the maximum distance: " << maxDistance << std::endl;

	return true;
}