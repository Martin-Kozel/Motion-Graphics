/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1000U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	makeCircles();
	makeEnemy();
	makePlayer();
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
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
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_direction = m_direction * -1;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

ResetCircles();
	BeadsCollision();
	EnemyRun();
	moveplayer();
	playerCollision();
	UpdateScore();
	
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{

	m_window.clear(sf::Color::Black);
	m_window.draw(m_welcomeMessage);
	m_window.draw(m_Score);
	for (int i = 0; i < NUM_OF_CIRCLES; i++)
	{
		m_window.draw(circles[i]);
	}
	m_window.draw(player);
	m_window.draw(enemy);
	m_window.display();
	
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("PAKU PAKU");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(130.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

	m_Score.setFont(m_ArialBlackfont);
	m_Score.setString("SCORE :");
	m_Score.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_Score.setPosition(200.0f, 200.0f);
	m_Score.setCharacterSize(40U);
	m_Score.setOutlineColor(sf::Color::Red);
	m_Score.setFillColor(sf::Color::Black);
	m_Score.setOutlineThickness(3.0f);
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{

}

void Game::makeCircles()			
{
	for (int i = 0; i < NUM_OF_CIRCLES; i++)
	{
		circles[i].setRadius(circleRadius);
		circles[i].setFillColor(sf::Color::Green);
		circles[i].setPosition(circlesCords);
		circles[i].setOrigin(sf::Vector2f(circleRadius * 0.5, circleRadius * 0.5));
		circlesCords.x += 55;
	}

	int number = rand() % NUM_OF_CIRCLES;

	circles[number].setRadius(20.0f);
	circles[number].setFillColor(sf::Color::Red);
}

void Game::makePlayer()
{
	player.setFillColor(sf::Color::Yellow);
	player.setPosition(400.0f, 305.0f);
	player.setSize(sf::Vector2f(50.0f, 50.0f));
	player.setOrigin(sf::Vector2f(10.f, -25.0f));
}

void Game::BeadsCollision()
{
	for (int i = 0; i < NUM_OF_CIRCLES; i++) {
		if (player.getGlobalBounds().intersects(circles[i].getGlobalBounds()))
		{
			circles[i].setPosition(-10, -10);
			points = points + 1;

			if (circles[i].getRadius() == 20) {
				m_Run = true;
			}
		}
	}

}

void Game::ResetCircles()
{
	circlesCords = sf::Vector2f{ 30,350 };

	bool SamePlace = true;
	sf::Vector2f firstPos;

	for (int i = 0; i < NUM_OF_CIRCLES; i++) {
		if (circles[i].getPosition() != sf::Vector2f{ -10,-10 }) {
			SamePlace = false;
		}
	}

	if (SamePlace) {
		for (int i = 0; i < NUM_OF_CIRCLES; i++) {
			circles[i].setPosition(circlesCords);
			circlesCords.x += 55;
		}
	}

}

void Game::EnemyRun()
{
	if (!m_Run) {
		if (enemy.getPosition().x <= player.getPosition().x) {
			enemy.move(1.0f, 0);
		}
		if (enemy.getPosition().x >= player.getPosition().x) {
			enemy.move(-1.0f, 0);
		}


		if (enemy.getPosition().x <= -30) {
			enemy.setPosition(1100, 305);
		}
		if (enemy.getPosition().x >= 1200) {
			enemy.setPosition(-20, 305);
		}
	}
	if (m_Run) {
		if (enemy.getPosition().x <= player.getPosition().x) {
			enemy.move(-1.0f, 0);
		}
		if (enemy.getPosition().x >= player.getPosition().x) {
			enemy.move(1.0f, 0);
		}

		if (enemy.getPosition().x <= -30) {
			enemy.setPosition(1100,305);
		}
		if (enemy.getPosition().x >= 1200) {
			enemy.setPosition(-20,305);
		}
	}

}

void Game::makeEnemy()
{
	
	enemy.setFillColor(sf::Color::Red);
	enemy.setPosition(800.0f, 305.0f);
	enemy.setSize(sf::Vector2f(50.0f, 50.0f));
	enemy.setOrigin(sf::Vector2f(10.f, -25.0f));

}

void Game::moveplayer()
{
	if (m_direction == 1)
		player.move(sf::Vector2f(2.0f, 0.0f));
	if (m_direction == -1)
		player.move(sf::Vector2f(-2.0f, 0.0f));

	if (player.getPosition().x >= 1100) {
		player.setPosition(-10, 305);
	}
	if (player.getPosition().x <= -20) {
		player.setPosition(1050, 305);
	}

}

void Game::playerCollision()
{
	if (!m_Run) {
		if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
			player.setPosition(0, 0);
		}
	}
	else {
		if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
			enemy.setPosition(0, 0);
			m_Run = false;
		}
	}

}

void Game::UpdateScore()
{
	m_Score.setString("SCORE : " + std::to_string(points));
}
