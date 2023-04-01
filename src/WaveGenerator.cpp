#include "WaveGenerator.h"
#include <cmath>
#include <iostream>

float BALL_RADIUS = 24.0f;
constexpr double M_PI = 3.14159265358979323846;

double radians(double degree)
{
	return (degree * (M_PI / 180));
}

WaveGenerator::WaveGenerator(unsigned windowWidth, unsigned windowHeight, std::string windowTitle, unsigned framerate) : m_window(sf::VideoMode(windowWidth, windowHeight), windowTitle),
	m_fps{ static_cast<int>(framerate) }
{
	m_window.setFramerateLimit(framerate);
	m_functionVec.emplace_back(sinf);
	m_functionVec.emplace_back(cosf);
	m_functionVec.emplace_back(tanf);

	// Wave settings
	m_aplitude = 4.0f;
	m_interval = 0.1f;
	m_phaseShift = 0.f;
	m_verticalShift = 0.f;
	m_period = 1.0f;
}

void WaveGenerator::run()
{
	while (m_window.isOpen())
	{
		update();
		m_window.clear(sf::Color::Black);
		draw();
		m_window.display();
		pollEvent();
	}
}

void WaveGenerator::pollEvent()
{
	sf::Event e;
	while (m_window.pollEvent(e))
	{
		switch (e.type)
		{
			case sf::Event::Closed:
			{
				m_window.close();
				break;
			}
			case sf::Event::KeyPressed:
			{
				switch (e.key.code)
				{
					case sf::Keyboard::Escape:
					{
						m_window.close();
						break;
					}
					case sf::Keyboard::W:
					{
						m_aplitude += 5.f;
						break;
					}
					case sf::Keyboard::S:
					{
						m_aplitude -= 5.f;
						break;
					}
					case sf::Keyboard::A:
					{
						m_period -= 0.1f;
						if (m_period < 0.1f)
						{
							m_period = 0.1f;
						}
						break;
					}
					case sf::Keyboard::D:
					{
						m_period += 0.1f;
						break;
					}
					case sf::Keyboard::Add:
					{
						m_fps += 10;
						m_window.setFramerateLimit(m_fps);
						break;
					}
					case sf::Keyboard::Subtract:
					{
						m_fps -= 10;
						if (m_fps <= 0)
						{
							m_fps = 1;
						}
						m_window.setFramerateLimit(m_fps);
						break;
					}
					case sf::Keyboard::Up:
					{
						BALL_RADIUS += 1.0f;
						break;
					}
					case sf::Keyboard::Down:
					{
						BALL_RADIUS -= 1.0f;
						break;
					}
					case sf::Keyboard::Left:
					{
						m_interval -= 0.1f;
						if (m_interval < 0.1f)
						{
							m_interval = 0.1f;
						}						
						break;
					}
					case sf::Keyboard::Right:
					{				
						m_interval += 0.1f;
						break;
					}
					case sf::Keyboard::T:
					{
						if (m_drawMode == DrawingMode::CURVE)
						{
							m_drawMode = DrawingMode::CIRCLE;
						}
						else if (m_drawMode == DrawingMode::CIRCLE)
						{
							m_drawMode = DrawingMode::CIRCLE_TRANSPARENT;
						}
						else if (m_drawMode == DrawingMode::CIRCLE_TRANSPARENT)
						{
							m_drawMode = DrawingMode::CURVE;
						}
						break;
					}
					case sf::Keyboard::F:
					{
						m_functionID++;
						if (m_functionID >= m_functionVec.size())
						{
							m_functionID = 0;
						}
					}
				}
			}
		}
	}
}

void WaveGenerator::update()
{
	m_phaseShift += 5.0f;
}

void WaveGenerator::draw()
{
	//float tempAngle = m_angle;
	if (m_drawMode == DrawingMode::CURVE)
	{
		sf::VertexArray curve(sf::PrimitiveType::LineStrip);
		for (float i = 0.f; i < static_cast<float>(m_window.getSize().x); i+=m_interval)
		{
			float y = m_aplitude * m_functionVec[m_functionID](radians((2*M_PI/m_period)* (i + m_phaseShift))) + m_verticalShift;
			//float y = m_aplitude * m_functionVec[m_functionID](i);		// Interesting
			curve.append(sf::Vertex(sf::Vector2f(static_cast<float>(i), static_cast<float>(y + m_window.getSize().y / 2))));
		}
		m_window.draw(curve);
	}
	else
	{
		// Circle settings
		sf::CircleShape shape;
		if (m_drawMode == DrawingMode::CIRCLE)
		{
			shape.setFillColor(sf::Color::White);
		}
		else
		{
			shape.setFillColor(sf::Color::Transparent);
		}
		shape.setOutlineThickness(1.0f);
		shape.setOutlineColor(sf::Color::Red);
		shape.setRadius(BALL_RADIUS);
		shape.setOrigin(BALL_RADIUS, BALL_RADIUS);
		// Draw for each
		for (float i = 0.f; i < static_cast<float>(m_window.getSize().x); i += m_interval)
		{
			float y = m_aplitude * m_functionVec[m_functionID](radians((2 * M_PI / m_period)* (i + m_phaseShift))) + m_verticalShift;
			//float y = m_aplitude * m_functionVec[m_functionID](i + m_phaseShift); // Interesting
			shape.setPosition(static_cast<float>(i), static_cast<float>(y + m_window.getSize().y / 2));
			m_window.draw(shape);
		}
	}
}
