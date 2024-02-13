#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{ false } //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture

	m_scrollSpeed = 300.0f;
	m_player.setSize(sf::Vector2f(30.0f, 30.0f));
	m_player.setPosition(400.0f, 500.0f);
	m_player.setFillColor(sf::Color::Black);
	m_playerSpeed = 200.0f;

	int terrainWidth = 10; // Width of the terrain based on levelData
	int terrainHeight = amountOfTiles / 10; // Height of the terrain based on levelData
	for (int i = 0; i < terrainHeight; i++)
	{
		for (int j = 0; j < terrainWidth; j++)
		{
			int index = i * terrainWidth + j;
			if (levelData[index] == 1)
			{
				m_terrain[index].setSize(sf::Vector2f(80.0f, 80.0f));
				m_terrain[index].setPosition(80.0f * j, -80.0f * i);
				m_terrain[index].setFillColor(sf::Color::Black);
				m_terrain[index].setOutlineColor(sf::Color::White);
				m_terrain[index].setOutlineThickness(2.5f);
			}
			else if (levelData[index] == 2) {
				m_terrain[index].setSize(sf::Vector2f(50.0f, 50.0f));
				float locationX = 80.0f * j;
				float locationY = -80.0f * i;
				m_terrain[index].setPosition(locationX, locationY);
				m_terrain[index].setFillColor(sf::Color::Red);
				m_terrain[index].setOutlineThickness(1);
			}
		}
	}
}

Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}

void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_gameOver) {
		restart();
	}

}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	if (m_gameOver) {
		return;
	}

	// Update terrain
	for (int i = 0; i < amountOfTiles; ++i)
	{
		m_terrain[i].move(0.0f, m_scrollSpeed * t_deltaTime.asSeconds());

		if (m_terrain[i].getPosition().y > m_window.getSize().y)
		{
			m_terrain[i].move(0.0f, -80.0f);
		}

		if (m_player.getGlobalBounds().intersects(m_terrain[i].getGlobalBounds())) {

			sf::FloatRect intersect;
			m_player.getGlobalBounds().intersects(m_terrain[i].getGlobalBounds(), intersect);

			if (intersect.width > intersect.height) {

				if (m_player.getPosition().y < m_terrain[i].getPosition().y) {
					m_player.move(0.0f, -intersect.height);
				}
				else {
					m_player.move(0.0f, intersect.height);
				}
			}
			else {
				
				if (m_player.getPosition().x < m_terrain[i].getPosition().x) {
					m_player.move(- intersect.width, 0.0f);
				}
				else {
					m_player.move(intersect.width, 0.0f);
				}
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_player.move(0.0f, -m_playerSpeed * t_deltaTime.asSeconds());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_player.move(0.0f, m_playerSpeed * t_deltaTime.asSeconds());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_player.move(-m_playerSpeed * t_deltaTime.asSeconds(), 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_player.move(m_playerSpeed * t_deltaTime.asSeconds(), 0.0f);
	}
	
	for (int i = 0; i < amountOfTiles; i++) {
		if (m_player.getGlobalBounds().intersects(m_terrain[i].getGlobalBounds())) {
			m_gameOver = true;
		}
	}
	if (m_gameOver) {
		gameOver();
	}
}

void Game::render()
{
	m_window.clear(sf::Color::Yellow);

	// Draw terrain
	for (int i = 0; i < amountOfTiles; ++i)
	{
		m_window.draw(m_terrain[i]);
	}

	// Draw player
	m_window.draw(m_player);

	if (m_gameOver) {
		gameOver();
	}

	m_window.display();
}

void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

void Game::setupSprite()
{
}

void Game::gameOver()
{
	sf::Text gameOverText;
	gameOverText.setFont(m_ArialBlackfont);
	gameOverText.setString("Game Over!");
	gameOverText.setCharacterSize(50);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setPosition(m_window.getSize().x / 2 - gameOverText.getLocalBounds().width / 2, m_window.getSize().y / 2 - gameOverText.getLocalBounds().height / 2);
	gameOverText.setOutlineColor(sf::Color::Black);
	gameOverText.setOutlineThickness(1);
	m_window.draw(gameOverText);
	m_window.display();
}

void Game::restart()
{
	m_player.setPosition(400.0f, 500.0f);
	m_gameOver = false;


	int terrainWidth = 10;
	int terrainHeight = amountOfTiles / 10;
	for (int i = 0; i < terrainHeight; ++i)
	{
		for (int j = 0; j < terrainWidth; ++j)
		{
			int index = i * terrainWidth + j;
			if (levelData[index] == 1)
			{
				m_terrain[index].setPosition(80.0f * j, -80.0f * i);
			}
			else if (levelData[index] == 2)
			{

				float xPos = 80.0f * j;
				float yPos = -80.0f * i;
				m_terrain[index].setPosition(xPos, yPos);
			}
		}
	}

}
