#pragma once

#include <iostream>
#include <time.h>

#include "Snake.h"

using namespace sf;

class Game
{
private:
	//Window Settings
	RenderWindow* _window;
	VideoMode _screenSize;

	//Global
	int _tileSize;
	Vector2i _maxTile;
	Clock _clock;
	float _deltaTime;

	//Background
	Texture _tileTexture;
	Sprite _tileSprite;

	//Snake GameObject
	Snake snake;

	//Fruit GameObject
	Vector2i _fruitPosition;
	Texture _fruitTexture;
	Sprite _fruitSprite;

	//Game
	bool _isGameOver;
	Font _captureIt;
	Text _gameOverText;

	//Initialisations
	void Init();
	void InitBackground();
	void InitFruit();
	void CreateWindow();
	void GameOverText();

public:
	Game();
	virtual ~Game();

	//Functions
	void SetRandomFruitPosition();
	
	// Update
	void UpdateEvents();
	void UpdateClock();
	void Update();

	//Collision
	void SnakeAteFruit();

	//Renders or Draw
	void RenderBackGround();
	void RenderFruit();
	void Render();

	//Game Loop Here
	void Run();
};

