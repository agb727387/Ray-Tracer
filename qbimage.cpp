#include "qbimage.hpp"

// The default constructor goes right here...
qbImage::qbImage()
{
	m_xSize = 0;
	m_ySize = 0;
	m_ptrTexture = nullptr;
}

// The destructor goes here...
qbImage::~qbImage()
{
	if (m_ptrTexture != nullptr)
		SDL_DestroyTexture(m_ptrTexture);
}

// Function to initalize
void qbImage::initialize(const int xSize, const int ySize, SDL_Renderer* ptrRenderer)
{
	// Resize the image arrays.
	m_redChannel.resize(xSize, std::vector<double>(ySize, 0.0));
	m_greenChannel.resize(xSize, std::vector<double>(ySize, 0.0));
	m_blueChannel.resize(xSize, std::vector<double>(ySize, 0.0));

	// Store the dimensions.
	m_xSize = xSize;
	m_ySize = ySize;

	// Store the pointer to the renderer.
	m_ptrRenderer = ptrRenderer;

	// Initialize the texture.
	initTexture();
}

// Function to set pixels.
void qbImage::setPixel(const int x, const int y, const double redColor, const double greenColor,
	const double blueColor)
{
	m_redChannel.at(x).at(y) = redColor;
	m_greenChannel.at(x).at(y) = greenColor;
	m_blueChannel.at(x).at(y) = blueColor;
}

// Function to generate the display properly...
void qbImage::display()
{
	// Allocate memory for a pixel buffer.
	Uint32* tempPixels = new Uint32[m_xSize * m_ySize];

	// Clear the pixel buffer...
	memset(tempPixels, 0, m_xSize * m_ySize * sizeof(Uint32));

	for (int count = 0; count < m_xSize; ++count)
		for (int countTwo = 0; countTwo < m_ySize; ++countTwo)
			tempPixels[(countTwo * m_xSize) + count] = ConvertColor(m_redChannel.at(count).at(countTwo)
				, m_greenChannel.at(count).at(countTwo), m_blueChannel.at(count).at(countTwo));

	// Update the texture with the pixel buffer.
	SDL_UpdateTexture(m_ptrTexture, nullptr, tempPixels, m_xSize * sizeof(Uint32));

	// Delete the pixel buffer.
	delete[] tempPixels;

	// Copy the texture to the renderer.
	SDL_Rect srcRect, bounds;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = m_xSize;
	srcRect.h = m_ySize;
	bounds = srcRect;
	SDL_RenderCopy(m_ptrRenderer, m_ptrTexture, &srcRect, &bounds);
}

// Function to initialize the texture goes here...

void qbImage::initTexture()
{
	// Initialize the texture...
	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	// Delete any previously created texture.
	if (m_ptrTexture != nullptr)
		SDL_DestroyTexture(m_ptrTexture);

	// Create the texture that will store the image.
	SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
	m_ptrTexture = SDL_CreateTextureFromSurface(m_ptrRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}

// Function to convert colors to Uint32
Uint32 qbImage::ConvertColor(const double red, const double green, const double blue)
{
	// Convert the colors to unsigned integers...
	unsigned char r = static_cast<unsigned char>(red);
	unsigned char g = static_cast<unsigned char>(green);
	unsigned char b = static_cast<unsigned char>(blue);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	Uint32 pixelColor = (b << 24) + (g << 16) + (b << 8) + 255;
#else
	Uint32 pixelColor = (255 << 24) + (b << 16) + (g << 8) + r;
#endif

	return pixelColor;

}

// Functions to return the dimensions of the image.
int qbImage::getXSize()
{
	return m_xSize;
}
int qbImage::getYSize()
{
	return m_ySize;
}
