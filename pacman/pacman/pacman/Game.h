/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();
	void makeCircles();
	void makePlayer();
	void BeadsCollision();
	void ResetCircles();
	void EnemyRun();
	void makeEnemy();
	void moveplayer();
	void playerCollision();
	void UpdateScore();


	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Text m_Score;
	int points = 0;
	sf::RenderWindow m_window; // main SFML window

	static const int NUM_OF_CIRCLES = 15;
	bool m_Run = false;
	sf::CircleShape circles[NUM_OF_CIRCLES];
	sf::Vector2f circlesCords = sf::Vector2f{ 30,350 };
	float circleRadius = 10.0f;
	float distance = 5.4f * circleRadius;

	sf::RectangleShape player;
	sf::RectangleShape enemy;
	int m_direction = 1;

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

