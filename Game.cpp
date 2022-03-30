#include "Game.h"

// Initialzations
void Game::Init()
{
	_isGameOver = false;

	_tileSize = 16*1.2;
	_maxTile.x = 30;
	_maxTile.y = 20;

	// size of screen will depend on size of single tile and MaxTile
	_screenSize.width = _maxTile.x * _tileSize;
	_screenSize.height = _maxTile.y * _tileSize;

	InitBackground();
	InitFruit();
	
	GameOverText();
}

void Game::InitBackground()
{
	_tileTexture.loadFromFile("images/white.png");
	_tileSprite.setTexture(_tileTexture);
}

void Game::InitFruit()
{
	_fruitTexture.loadFromFile("images/green.png");
	_fruitSprite.setTexture(_fruitTexture);
	SetRandomFruitPosition();
}

void Game::GameOverText()
{
	_gameOverText.setString("Game\nOver");
	_gameOverText.setFillColor(Color::Red);
	_captureIt.loadFromFile("Fonts/Capture_it.ttf");
	_gameOverText.setFont(_captureIt);
	_gameOverText.setCharacterSize(std::min(_screenSize.width, _screenSize.height) / 3);
	_gameOverText.setPosition(_screenSize.width/2 - _gameOverText.getLocalBounds().width/2,0);
}

void Game::CreateWindow()
{
	_window = new RenderWindow(_screenSize, "Snake Game");
	_window->setFramerateLimit(24);
}

// Constructor / Destructor
Game::Game()
{
	Init();
	CreateWindow();
	snake.Create(Vector2i(_maxTile / 2), 4);
}

Game::~Game()
{
	delete _window;
}
// Functions
void Game::SetRandomFruitPosition()
{
	srand(time(0));
	// randoim position
	_fruitPosition = Vector2i(rand() % _maxTile.x, rand() % _maxTile.y);
	_fruitSprite.setPosition(_fruitPosition.x * _tileSize, _fruitPosition.y * _tileSize);
}

// Update
void Game::UpdateEvents()
{
	Event e;
	while (_window->pollEvent(e))
	{
		if (e.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			_window->close();
	}
	snake.InputHandler();
}

void Game::UpdateClock()
{
	_deltaTime = _clock.getElapsedTime().asSeconds();
	_clock.restart();
}

void Game::Update()
{
	UpdateClock();
	UpdateEvents();
	
	if (_isGameOver)
		return;

	if (snake.Death())
	{
		_isGameOver = true;
		std::cout << "Death";
		return;
	}

	snake.Movement(_maxTile ,_deltaTime);
	SnakeAteFruit();
}

// Collision
void Game::SnakeAteFruit()
{
	if (snake.GetHead() == _fruitPosition)
	{
		snake.IncreaseSize();
		SetRandomFruitPosition();
	}
}

// Render
void Game::RenderBackGround()
{
	for (int i = 0; i < _maxTile.x; i++)
	{
		for (int j = 0; j< _maxTile.y; j++)
		{
			_tileSprite.setPosition(i * _tileSize, j * _tileSize);
			_window->draw(_tileSprite);
		}
	}
}

void Game::RenderFruit()
{
	_window->draw(_fruitSprite);
}

void Game::Render()
{
	_window->clear();

	RenderBackGround();
	RenderFruit();
	snake.Render(_tileSize, _window);

	if (_isGameOver)
		_window->draw(_gameOverText);

	_window->display();
}

// Game Loop
void Game::Run()
{
	while (_window->isOpen())
	{
		Update();
		Render();
	}
}


