#pragma once
#include <functional>
#include "SFML/Graphics.hpp"

enum class DrawingMode
{
	CURVE,
	CIRCLE,
	CIRCLE_TRANSPARENT
};

class WaveGenerator
{
public:
	WaveGenerator(unsigned windowWidth, unsigned windowHeight, std::string windowTitle, unsigned framerate);
	/// <summary>
	/// Run Simulation
	/// </summary>
	void run();
private:
	/// <summary>
	/// Handle use event
	/// </summary>
	void pollEvent();
	/// <summary>
	/// Update
	/// </summary>
	void update();
	/// <summary>
	/// Draw on window
	/// </summary>
	void draw();
private:
	sf::RenderWindow m_window;										//!< Window to draw on
	std::vector < std::function<float(float)>> m_functionVec;		//!< Functions vector to simulate
	int m_fps;														//!< Simulation Framerate;
	int m_functionID{ 0 };											//!< Id of current function
	DrawingMode m_drawMode{ DrawingMode::CURVE };					//!< Drawing mode of each point
	// Function settings
	float m_aplitude;												//!< Wave amplitude
	float m_interval;												//!< Precision (distance between x points)
	float m_phaseShift;												//!< Horizontal shift
	float m_verticalShift;											//!< Vertical shift
	float m_period;													//!< Distance between peaks
};