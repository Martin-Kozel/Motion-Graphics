// platform game
// Author :Monika Nusi

#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-audio-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-network-d.lib")
#else
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-audio.lib")
#pragma comment(lib,"sfml-system.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-network.lib")
#endif

#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
class Game
{
    bool jumping = false;
    bool falling = false;

    sf::Time animationDelay = sf::milliseconds(200);
    void Animation()
    {
        int frameWidth = playerTexture.getSize().x / frameCount;
        int frameHight = playerTexture.getSize().y;


        static sf::Clock animationClock;
        if (animationClock.getElapsedTime() >= animationDelay)
        {

            currentFrame = (currentFrame + 1) % frameCount;
            playerShape.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHight));
            animationClock.restart();
        }
    }

public:
    //create Window
    sf::RenderWindow window;
    sf::View view;
    float randomNum;




    sf::RectangleShape playerShape;
    bool gameWon = false;

    sf::Texture playerTexture;
    sf::Texture tile1Texture;
    sf::Texture tile2Texture;
    sf::Texture tile4Texture;

    int currentFrame = 0;
    int frameCount = 2;



    float velocityX = 0, velocityY = 0, gravity = 0.3;




    static const int numRows = 78;
    static const int numCols = 20;
    int levelData[numRows][numCols] =
    {
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,1 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0 },
    { 0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0 },
    { 0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,4,1,0,0,0,0,2,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0 },
    { 0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0 },
    { 0,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,4,1,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,3,1,0,2,1,0,0,0,0,0,0,0,0,0 } };

    sf::RectangleShape level[numRows][numCols];

    sf::Font font;
    sf::Text gameWinText;



    Game()
    {
        init();
        window.create(sf::VideoMode(800, 600), "Endless Runner Game");

        if (!font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
        }

        gameWinText.setFont(font);
        gameWinText.setCharacterSize(48);
        gameWinText.setFillColor(sf::Color::Green);
        gameWinText.setString("You Win!");
        gameWinText.setPosition(200, 200);


    }
    void init()
    {


        if (!playerTexture.loadFromFile("ASSETS\\IMAGES\\sprite.png")) {
            std::cerr << "Failed to load font!" << std::endl;
        }
        playerShape.setTexture(&playerTexture);

        if (!tile1Texture.loadFromFile("ASSETS\\IMAGES\\tile1.png")) {
            std::cerr << "Failed to load font!" << std::endl;
            return;
        }

        if (!tile2Texture.loadFromFile("ASSETS\\IMAGES\\tile2.png")) {
            std::cerr << "Failed to load font!" << std::endl;
            return;
        }
        if (!tile4Texture.loadFromFile("ASSETS\\IMAGES\\tile4.png")) {
            std::cerr << "Failed to load font!" << std::endl;
            return;
        }


        view = window.getDefaultView();
        playerShape.setSize(sf::Vector2f(50, 50));
        playerShape.setPosition(160, 500);

        for (int row = 0; row < numRows; row++)
        {
            for (int col = 0; col < numCols; col++)
            {

                if (levelData[row][col] == 1)
                {

                    level[row][col].setSize(sf::Vector2f(70, 30));
                    level[row][col].setPosition(row * 70, col * 30);
                    //level[row][col].setFillColor(sf::Color::Red);
                    level[row][col].setTexture(&tile1Texture);
                }
                if (levelData[row][col] == 0)
                {

                    level[row][col].setSize(sf::Vector2f(70, 30));
                    level[row][col].setPosition(row * 70, col * 30);
                    level[row][col].setFillColor(sf::Color::Black);
                }
                if (levelData[row][col] == 2)
                {
                    level[row][col].setSize(sf::Vector2f(70, 30));
                    level[row][col].setPosition(row * 70, col * 30);

                    level[row][col].setFillColor(sf::Color::Red);
                    level[row][col].setTexture(&tile2Texture);

                }
                if (levelData[row][col] == 3)
                {
                    level[row][col].setSize(sf::Vector2f(70, 30));
                    level[row][col].setPosition(row * 70, col * 30);

                    level[row][col].setFillColor(sf::Color::Green);
                    level[row][col].setTexture(&tile1Texture);

                }
                if (levelData[row][col] == 4)
                {
                    level[row][col].setSize(sf::Vector2f(70, 30));
                    level[row][col].setPosition(row * 70, col * 30);

                    //level[row][col].setFillColor(sf::Color::Magenta);
                    level[row][col].setTexture(&tile4Texture);
                }
                if (levelData[row][col] == 5)
                {
                    level[row][col].setSize(sf::Vector2f(70, 30));
                    level[row][col].setPosition(row * 70, col * 30);

                    level[row][col].setFillColor(sf::Color::Yellow);
                    level[row][col].setTexture(&tile1Texture);

                }
                if (levelData[row][col] == 6)
                {
                    level[row][col].setSize(sf::Vector2f(70, 30));
                    level[row][col].setPosition(row * 70, col * 30);

                    level[row][col].setFillColor(sf::Color::Blue);
                    level[row][col].setTexture(&tile1Texture);

                }

            }
            std::cout << std::endl;
        }

    }
    void run()
    {


        sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);


        sf::Time timeSinceLastUpdate = sf::Time::Zero;


        sf::Clock clock;

        clock.restart();



        while (window.isOpen())
        {

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }


            timeSinceLastUpdate += clock.restart();


            if (timeSinceLastUpdate > timePerFrame)
            {

                for (int row = 0; row < numRows; row++)
                {
                    for (int col = 0; col < numCols; col++)
                    {

                        level[row][col].move(-3.7, 0);
                    }

                }

                for (int row = 0; row < numRows; row++) {
                    for (int col = 0; col < numCols; col++) {
                        if (levelData[row][col] == 3 && playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
                        {
                            std::cout << "Level Complete!" << std::endl;
                            gameWon = true;
                        }
                    }
                }

                for (int row = 0; row < numRows; row++) {
                    for (int col = 0; col < numCols; col++) {
                        if (levelData[row][col] == 4 && playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
                        {
                            velocityY = -15.0;
                        }
                    }
                }

                for (int row = 0; row < numRows; row++) {
                    for (int col = 0; col < numCols; col++) {
                        if (levelData[row][col] == 5 && playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
                        {
                            playerShape.setSize(sf::Vector2f(20, 20));
                        }
                    }
                }

                for (int row = 0; row < numRows; row++) {
                    for (int col = 0; col < numCols; col++) {
                        if (levelData[row][col] == 6 && playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
                        {
                            playerShape.setSize(sf::Vector2f(50, 50));
                        }
                    }
                }



                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && velocityY == 0)
                {
                    velocityY = -11.8;
                }

                velocityY = velocityY + gravity;
                playerShape.move(0, velocityY);
                Animation();

                gravity = 0.6;

                for (int row = 0; row < numRows; row++)
                {
                    for (int col = 0; col < numCols; col++)
                    {
                        if (velocityY >= 0)
                        {
                            if (levelData[row][col] == 1)
                            {

                                if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
                                {
                                    if (playerShape.getPosition().y < level[row][col].getPosition().y)
                                    {
                                        gravity = 0;
                                        velocityY = 0;
                                        playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y);
                                        playerShape.move(0, -playerShape.getGlobalBounds().height);
                                        break;
                                    }
                                    else {
                                        init();
                                    }
                                }


                            }

                        }
                        if (velocityY < 0)
                        {
                            if (levelData[row][col] == 1)
                            {
                                if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
                                {
                                    init();
                                }

                            }

                        }
                        if (levelData[row][col] == 2)
                        {
                            if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
                            {
                                init();
                            }
                        }
                    }
                }

                if (playerShape.getPosition().y > 600)
                {
                    init();
                }

                window.clear();

                for (int row = 0; row < numRows; row++)
                {
                    for (int col = 0; col < numCols; col++)
                    {
                        window.draw(level[row][col]);

                    }
                }
                window.draw(playerShape);
                if (gameWon == true)
                {
                    window.draw(gameWinText);
                }

                window.display();

                timeSinceLastUpdate = sf::Time::Zero;
            }
        }
    }


};



int main()
{


    Game game;


    game.init();

    game.run();



    return 0;
}