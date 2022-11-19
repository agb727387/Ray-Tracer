#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include <SDL.h>
#include "qbImage.hpp"
#include "camera.hpp"
#include "objectsphere.hpp"
#include "pointLight.hpp"

namespace qbRT
{
	class scene
	{
	public:
		// Constructor
		scene();

		// Rendering function
		bool render(qbImage& outputImage);

		// Private functions
	private:

		// Private members
	private:
		// Here is the camera that we will use...
		qbRT::camera m_camera;

		// The list of objects in the scene...
		std::vector<std::shared_ptr<qbRT::objectBase>> m_objectList;

		// Here are the list of lights in the scene...
		std::vector<std::shared_ptr<qbRT::lightbase>> m_lightList;
	};
}

#endif
