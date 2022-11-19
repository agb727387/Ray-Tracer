#include "CApp.h"
#include "qbVector.h"

// The constructor (default)
CApp::CApp()
{
	isRunning = true;
	pWindow = nullptr;
	pRenderer = nullptr;
}

bool CApp::onInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	int screenWidth = 1280;
	int screenHeight = 720;

	pWindow = SDL_CreateWindow("Ray Tracer: Guided by youtuber QuantitativeBytes!",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

	if (pWindow != nullptr)
	{
		pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

		// Initialize the qbImage instance.
		m_image.initialize(screenWidth, screenHeight, pRenderer);

		// Set the background color to white...
		SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
		SDL_RenderClear(pRenderer);

		// Render the scene...
		m_scene.render(m_image);

		// Display the image...
		m_image.display();

		// Show the result..
		SDL_RenderPresent(pRenderer);


	}
	else
		return false;

	return true;
}

int CApp::onExecute()
{
	SDL_Event currentEvent;

	if (onInit() == false)
		return -1;
	while (isRunning)
	{
		while (SDL_PollEvent(&currentEvent) != 0)
			onEvent(&currentEvent);

		onLoop();
		onRender();
	}
}

void CApp::onEvent(SDL_Event* event)
{
	if (event->type == SDL_QUIT)
		isRunning = false;
}

void CApp::onLoop()
{

}

void CApp::onRender()
{
	/*
	// Set the background color to white
	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(pRenderer);

	// This is the place where the scene will be renderer properly...
	m_scene.render(m_image);

	// Display the image
	m_image.display();

	// Show the result.
	SDL_RenderPresent(pRenderer);
	*/
}

void CApp::onExit()
{
	// Tidy up SDL2 stuff with destructor...
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	pWindow = nullptr;
	SDL_Quit();
}

// Private functions go here...
void CApp::PrintVector(const qbVector<double>& inputVector)
{
	int nRows = inputVector.GetNumDims();
	for (int row = 0; row < nRows; ++row)
	{
		std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << std::endl;
	}
}