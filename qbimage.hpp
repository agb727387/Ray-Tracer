#ifndef QBIMAGE_H
#define QBIMAGE_H

#include <string>
#include <vector>
#include <SDL.h>


class qbImage
{
public:
	// The constructor.
	qbImage();

	// Destructor.
	~qbImage();

	// Function to initialize.
	void initialize(const int xSize, const int ySize, SDL_Renderer* ptrRenderer);

	// Function to set color of pixel
	void setPixel(const int x, const int y, const double redColor, const double greenColor,
		const double blueColor);

	// Function to return image for display
	void display();

	// Functions to return dimensions of image.
	int getXSize();
	int getYSize();

private:
	Uint32 ConvertColor(const double red, const double green, const double blue);
	void initTexture();
private:
	// Here are some arrays to store the image data properly...
	std::vector<std::vector<double>> m_redChannel;
	std::vector<std::vector<double>> m_greenChannel;
	std::vector<std::vector<double>> m_blueChannel;

	// Store the dimenstion of the image...
	int m_xSize;
	int m_ySize;
	
	// SDL2 stuff goes here in this section...
	SDL_Renderer* m_ptrRenderer;
	SDL_Texture* m_ptrTexture;
};

#endif
