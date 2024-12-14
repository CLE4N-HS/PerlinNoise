#include <iostream>
//#include "SFML/System.hpp"

#pragma warning(push)
#pragma warning(disable : 26495)
#include "SFML/Graphics.hpp"
#pragma warning(pop)

sf::Vector2f randomGradient(int _x, int _y)
{
	// No precomputed gradients mean this works for any number of grid coordinates
	const unsigned int w = 8 * sizeof(unsigned int);
	const unsigned int s = w / 2;
	unsigned int a = _x;
	unsigned int b = _y;

	a *= 3275157443;

	b ^= a << s | a >> w - s;
	b *= 2048419325;

	float random = a * (3.14159265 / ~(~0u >> 1));

	// Create the vector from the angle
	sf::Vector2f v;
	v.x = std::sinf(random);
	v.y = std::cosf(random);

	return v;
}

// Computes the dot product of the distance and gradient vectors.
float dotGridGradient(int _ix, int _iy, float _x, float _y)
{
	// Get gradient from integer coordinates
	sf::Vector2f gradient = randomGradient(_ix, _iy);

	// Compute the distance vector
	float dx = _x - static_cast<float>(_ix);
	float dy = _y - static_cast<float>(_iy);

	// Compute the dot-product
	return (dx * gradient.x + dy * gradient.y);
}

float interpolate(float _a0, float _a1, float _w)
{
	return ((_a1 - _a0) * (3.f - _w * 2.f) * _w * _w + _a0);
}

// Sample Perlin noise at coordinates x, y
float perlin(float _x, float _y)
{
	// Determine grid cell corner coordinates
	int x0 = static_cast<int>(_x);
	int y0 = static_cast<int>(_y);
	int x1 = x0 + 1;
	int y1 = y0 + 1;

	// Compute Interpolation wieghts
	float sx = _x - static_cast<float>(x0);
	float sy = _y - static_cast<float>(y0);

	// Compute and interpolate top two corners
	float n0 = dotGridGradient(x0, y0, _x, _y);
	float n1 = dotGridGradient(x1, y0, _x, _y);
	float ix0 = interpolate(n0, n1, sx);

	// Compute and interpolate bottom two corners
	n0 = dotGridGradient(x0, y1, _x, _y);
	n1 = dotGridGradient(x1, y1, _x, _y);
	float ix1 = interpolate(n0, n1, sx);

	// Final step: interpolate between the two prviously interpolated values, now in y
	float value = interpolate(ix0, ix1, sy);

	return value;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), sf::String("Perlin Noise"), sf::Style::Default);

	sf::Vector2i windowSize(1920, 1080);

	sf::Uint8* pixels = new sf::Uint8[windowSize.y * windowSize.x * 4];

	const int gridSize(400);

	for (int y = 0; y < windowSize.y; y++)
	{
		for (int x = 0; x < windowSize.x; x++)
		{
			int index((y * windowSize.x + x) * 4);

			float val(0.f);
			float freq(1.f);
			float ampl(1.f);

			for (int i = 0; i < 12; i++)
			{
				val += perlin(x * freq / gridSize, y * freq / gridSize) * ampl;

				freq *= 2.f;
				ampl /= 2.f;
			}

			// Contrast
			val *= 1.2f;

			// Clipping
			if (val > 1.f)
				val = 1.f;
			else if (val < -1.f)
				val = -1.f;

			// Convert 1 to -1 into 255 to 0
			int color = static_cast<int>(((val + 1.f) * 0.5f) * 255.f);

			// Set piwel color
			pixels[index] = color;
			pixels[index + 1] = color;
			pixels[index + 2] = color;
			pixels[index + 3] = 255;
		}
	}

	sf::Texture texture;
	sf::Sprite sprite;

	texture.create(windowSize.x, windowSize.y);

	texture.update(pixels);

	sprite.setTexture(texture);

	while (window.isOpen())
	{
		sf::Event sfEvent{};
		while (window.pollEvent(sfEvent))
		{
			if (sfEvent.type == sf::Event::EventType::Closed
				|| sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
			{
				window.close();
			}
		}

		window.clear();

		window.draw(sprite);

		window.display();
	}

	return EXIT_SUCCESS;
}
