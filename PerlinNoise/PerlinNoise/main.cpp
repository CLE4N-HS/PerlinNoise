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
	return 0.f;
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

	return 0.f;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), sf::String("Perlin Noise"), sf::Style::Default);

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

		sf::Vector2i windowSize(1920, 1080);

		sf::Uint8* pixels = new sf::Uint8[windowSize.y * windowSize.x * 4];

		const int gridSize(400);

		for (int y = 0; y < windowSize.y; y++)
		{
			for (int x = 0; x < windowSize.x; x++)
			{
				int index((x * windowSize.x + y) * 4);

				float val(0.f);
				float freq(1.f);
				float ampl(1.f);

				for (int i = 0; i < 12; i++)
				{
					//val += 
				}
			}
		}

		sf::Texture texture;
		sf::Sprite sprite;

		texture.create(windowSize.x, windowSize.y);

		window.clear();
		window.display();
	}

	return EXIT_SUCCESS;
}
