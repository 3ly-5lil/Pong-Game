#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include<sstream>
#include<cmath>
#include<ctime>

constexpr auto pi = 3.14159f;

using namespace std;


int main()
{
	//The Window.
	sf::RenderWindow window(sf::VideoMode(900, 600), "Pong Game", sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	//time
	sf::Clock clock;
	sf::Time time;
	time += clock.restart();

	//varibles
	int score1 = 0, score2 = 0, minutes = 0;

	sf::Font ALGER;
	if (!ALGER.loadFromFile("ALGER.ttf"))
	{
		std::cout << "not font found";
	}
	//timer word in first of all
	sf::Text timer;
	timer.setFont(ALGER);
	timer.setCharacterSize(46);
	timer.setString("00:00");
	timer.setPosition(400, 70);

	sf::Text score;
	score.setFont(ALGER);
	score.setCharacterSize(35);
	score.setPosition(410, 10);
	score.setFillColor(sf::Color::Red);
	score.setString("0:0");

	sf::Text players;
	players.setFont(ALGER);
	players.setCharacterSize(35);
	players.setPosition(30, 10);
	players.setFillColor(sf::Color::Yellow);
	players.setString(" Player 1                                                        Player 2");

	//winners 
	sf::Text player1;
	player1.setFont(ALGER);
	player1.setCharacterSize(100);
	player1.setPosition(400, 300);
	player1.setString("player 1 is the winner");

	sf::Text player2;
	player2.setFont(ALGER);
	player2.setCharacterSize(100);
	player2.setPosition(400, 300);
	player2.setString("player 2 is the winner");

	//Unreal method

	/*sf::Text Equal;
	Equal.setFont(ALGER);
	Equal.setCharacterSize(100);
	Equal.setPosition(400, 300);
	Equal.setString("Equal Result");*/

	//bakeground
	sf::RectangleShape bakeground(sf::Vector2f(900.0f, 600.0f));
	sf::Texture bg;
	bg.loadFromFile("bg.png");
	bakeground.setTexture(&bg);

	//Ball setting
	float ballangle = 0.0f;
	float ballspead = 10.0f;
	float DeltaTime = clock.restart().asSeconds();
	float factor = ballspead * DeltaTime;

	//ball
	sf::RectangleShape B(sf::Vector2f(20.0f, 25.0f));
	sf::Texture ball;
	ball.loadFromFile("ball.png");
	B.setTexture(&ball);
	B.setPosition(450, 300);

	do
	{
		ballangle = (rand() % 360) * 2 * pi / 360;

	} while (abs(cos(ballangle)) < 0.7f);

	//player1 left pad.
	sf::RectangleShape p1(sf::Vector2f(10, 100));
	p1.setFillColor(sf::Color::Green);
	//sf::Texture pad1;
	//pad1.loadFromFile("pad1.png");
	//p1.setTexture(&pad1);
	p1.setPosition(5, 250);

	//player2 right pad.
	sf::RectangleShape p2(sf::Vector2f(10, 100));
	p2.setFillColor(sf::Color::Red);
	//sf::Texture pad2;
	//pad2.loadFromFile("pad2.png");
	//p2.setTexture(&pad2);
	p2.setPosition(870, 250);

	//massage before play
	sf::RectangleShape mass(sf::Vector2f(300.0f, 100.0f));
	sf::Texture massage;
	massage.loadFromFile("massage.png");
	mass.setTexture(&massage);
	mass.setPosition(315, 250);

	//sounds
	sf::SoundBuffer hit;
	if (hit.loadFromFile("hit.wav") == 0)
	{
		return 1;
	}
	sf::Sound sound;
	sound.setBuffer(hit);

	//music
	sf::Music gamemeusic;
	if (gamemeusic.openFromFile("music.ogg") == 0)
	{
		return 1;
	}
	gamemeusic.setLoop(true);
	gamemeusic.play();

	//key states.
	bool w = false; bool s = false; bool up = false; bool down = false;  bool Space = false;

	//The Game Loop.
	while (window.isOpen())
	{
		//Process Events.
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed /*|| sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)*/)
			{
				window.close();
			}

			//movement setting
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::W) w = true;
				if (event.key.code == sf::Keyboard::S) s = true;
				if (event.key.code == sf::Keyboard::Up) up = true;
				if (event.key.code == sf::Keyboard::Down) down = true;
				if (event.key.code == sf::Keyboard::Space) Space = true;
			}

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::W) w = false;
				if (event.key.code == sf::Keyboard::S) s = false;
				if (event.key.code == sf::Keyboard::Up) up = false;
				if (event.key.code == sf::Keyboard::Down) down = false;
			}
		}

		//player 1's movement.
		if (w == true)
		{
			p1.move(0.0f, -12.0f);
		}
		if (s == true)
		{
			p1.move(0.0f, 12.0f);
		}
		if (w == true && s == true)
		{
			p1.move(0.0f, 0.0f);
		}

		//player 2's movement.
		if (up == true)
		{
			p2.move(0.0f, -12.0f);
		}
		if (down == true)
		{
			p2.move(0.0f, 12.0f);
		}
		if (up == true && down == true)
		{
			p2.move(0.0f, 0.0f);
		}


		////////Ai
		/*if (B.getPosition().y < p2.getPosition().y)
		{
			p2.move(0.0f, -10.0f);
		}
		if (B.getPosition().y > p2.getPosition.y)
		{
			p2.move(0.0f, 10.0f);
		}*/


		//bound for pads
		if (p1.getPosition().y < 0)
		{
			p1.setPosition(5, 0);
		}
		if (p1.getPosition().y > 480)
		{
			p1.setPosition(5, 480);
		}

		if (p2.getPosition().y < 0)
		{
			p2.setPosition(870, 0);
		}
		if (p2.getPosition().y > 480)
		{
			p2.setPosition(870, 480);
		}

		//timer
		const unsigned int seconds = static_cast<unsigned int>(clock.getElapsedTime().asSeconds());
		if (seconds > 59)
		{
			minutes++;
			clock.restart();
		}

		//ball movement
		if (Space == true)
		{
			B.move(cos(ballangle) * ballspead, sin(ballangle) * ballspead);

		}

		// bound for ball
		if (B.getPosition().y < 0)
		{
			ballangle = -ballangle;
		}
		if (B.getPosition().y < 595)
		{
			ballangle = -ballangle;
		}
		if (B.getPosition().x < 0)
		{
			ballangle = -ballangle;
		}
		if (B.getPosition().x < 895)
		{
			ballangle = -ballangle;
		}

		//collision 
		if (B.getGlobalBounds().intersects(p1.getGlobalBounds()) == true)
		{
			ballangle = -ballangle;
			ballspead = -ballspead;
			sound.play();
		}

		if (B.getGlobalBounds().intersects(p2.getGlobalBounds()) == true)
		{
			ballangle = -ballangle;
			ballspead = -ballspead;
			sound.play();
		}

		//score and winners
		if (B.getPosition().x < -50.0)
		{
			score1++;
			B.setPosition(450, 300);
			Space = false;
			p1.setPosition(5, 250);
			p2.setPosition(870, 250);
		}
		if (B.getPosition().x > 950.0)
		{
			score2++;
			B.setPosition(450, 300);
			Space = false;
			p1.setPosition(5, 250);
			p2.setPosition(870, 250);

		}

		window.clear();
		window.draw(bakeground);
		window.draw(B);
		//window.draw(mass);
		window.draw(p1);
		window.draw(p2);
		window.draw(players);

		stringstream text;
		text << score2 << ":" << score1;
		score.setString(text.str());
		window.draw(score);

		stringstream text1;
		text1 << minutes << ":" << seconds;
		timer.setString(text1.str());
		window.draw(timer);


		window.display();

	}

	return 0;
}