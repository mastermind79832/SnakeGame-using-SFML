#pragma once

#include <vector>

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>

using namespace sf;

class Snake
{
private:
	// position
	Vector2i _head;
	Vector2i _direction;
	std::vector<Vector2i>* _body;

	//sprite
	Texture _texture;
	Sprite _sprite;

	//movement
	float _speed;
	float _timer = 0;

	void Init();
public:
	Snake();
	virtual ~Snake();

	//Getter
	Vector2i GetHead();
	
	//Functions
	void Create(Vector2i startPos, int bodyCount);
	void IncreaseSize();
	bool Death();
	void InputHandler();
	
	//OutOfBounds
	void CheckOutOfBounds(Vector2i maxTile);

	//Update
	void Movement(Vector2i maxTile, float deltaTime);

	//Render
	void Render(int tileSize, RenderWindow* window);
};

