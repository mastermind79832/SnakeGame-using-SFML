#include "Snake.h"

void Snake::Init()
{
	_texture.loadFromFile("images/red.png");
	_sprite.setTexture(_texture);
	_direction = Vector2i(1, 0);
	_speed = 0.1;
}

Snake::Snake()
{
	Init();
}

Snake::~Snake()
{
	_body->clear();
	delete _body;
}

Vector2i Snake::GetHead()
{
	return _head;
}

void Snake::Create(Vector2i startPos, int bodyCount)
{
	_head = startPos;
	_body = new std::vector<Vector2i>();
	_body->push_back(_head - _direction);
	if (bodyCount > 2)
	{
		for (int i = 1; i < bodyCount; i++)
		{
			_body->push_back((*_body)[i - 1] - _direction);
		}
	}
}

void Snake::IncreaseSize()
{
	_body->push_back(Vector2i((*_body)[0].x ,(*_body)[0].y));
}

bool Snake::Death()
{
	for (int i = 1; i < (*_body).size(); i++)
	{
		if (_head == (*_body)[i])
			return true;
	}
	return false;
}

void Snake::InputHandler()
{
	// Lefgt
	if (Keyboard::isKeyPressed(Keyboard::A) && _direction != Vector2i(1,0))
		_direction = Vector2i(-1, 0);
	// UP
	if (Keyboard::isKeyPressed(Keyboard::W) && _direction != Vector2i(0, 1))
		_direction = Vector2i(0, -1);
	// Right
	if (Keyboard::isKeyPressed(Keyboard::D) && _direction != Vector2i(-1, 0))
		_direction = Vector2i(1, 0);
	// Down
	if (Keyboard::isKeyPressed(Keyboard::S) && _direction != Vector2i(0, -1))
		_direction = Vector2i(0, 1);
}

void Snake::CheckOutOfBounds(Vector2i maxTile)
{
	if (_head.x < 0)
		_head.x = maxTile.x - 1;
	else if (_head.x >= maxTile.x)
		_head.x = 0;

	if (_head.y < 0)
		_head.y = maxTile.y - 1;
	else if (_head.y >= maxTile.y)
		_head.y = 0;
}

void Snake::Movement(Vector2i maxTile, float deltaTime)
{
	_timer += deltaTime;
	if (_timer < _speed)
		return;
	
	_timer = 0;
	for (int i = (*_body).size() -1 ; i > 0; i--)
	{
		(*_body)[i] = (*_body)[i - 1];
	}
	(*_body)[0] = _head;
	_head += _direction;

	CheckOutOfBounds(maxTile);
}

void Snake::Render(int tileSize, RenderWindow* window)
{
	for (int i = 0; i < (*_body).size(); i++)
	{
		_sprite.setPosition((*_body)[i].x * tileSize , (*_body)[i].y * tileSize);
		window->draw(_sprite);
	}
	_sprite.setPosition(_head.x * tileSize, _head.y * tileSize);
	window->draw(_sprite);
}