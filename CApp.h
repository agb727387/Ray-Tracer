#ifndef CAPP_H
#define CAPP_H

#include <SDL.h>
#include "qbimage.hpp"
#include "scene.hpp"
#include "camera.hpp"

class CApp
{
public:
	CApp();

	int onExecute();
	bool onInit();
	void onEvent(SDL_Event* event);
	void onLoop();
	void onRender();
	void onExit();
	
private:
	void PrintVector(const qbVector<double>& inputVector);

	// An instance of qb image to store the image.
	 qbImage m_image;

	 // Define an instance of the scene class...
	 qbRT::scene m_scene;

	// SDL2 stuff goes here...
	bool isRunning;
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;
};

#endif
