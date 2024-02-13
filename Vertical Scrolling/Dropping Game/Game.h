/// <summary>
/// author Martin Kozel
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
const int amountOfTiles = 720;
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
	void gameOver();
	void restart();

	sf::RectangleShape m_terrain[amountOfTiles];
	sf::RectangleShape m_player;
	float m_scrollSpeed;
	float m_playerSpeed;

	int levelData[amountOfTiles] =
	{ 1,1,1,1,0,0,0,1,1,1,
	1,0,0,0,0,0,0,0,0,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,2,1,1,
	1,1,1,1,1,0,0,0,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,0,0,0,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,1,0,1,1,1,
	1,1,1,2,0,0,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,1,0,0,0,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,2,1,1,
	1,1,1,1,1,0,0,0,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,2,0,0,0,1,1,1,
	1,1,1,1,1,0,0,0,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,1,0,0,0,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,
	1,1,1,2,0,0,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,1,0,0,0,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,1,0,2,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,1,0,0,0,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,2,0,1,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,1,0,0,0,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,0,1,1,1,
	1,1,1,1,0,0,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,
	};


	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game
	bool m_gameOver{ false };

};

#endif // !GAME_HPP