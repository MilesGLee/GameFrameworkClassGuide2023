#pragma once
#include "MoveComponent.h"
#include "Actor.h"
#include <Vector2.h>
class MoveComponent;

class Enemy : public Actor
{
public:
	Enemy(float x, float y, const char* name, float speed, int maxHealth, Actor* target);
	~Enemy() {}

	void start();
	void update(float deltaTime);
	void draw();
	float getSpeed() { return m_speed; }
	MoveComponent* getMovementComponent() { return m_moveComponent; }

private:
	int m_speed;
	int m_maxHealth;
	Actor* m_target;
	MoveComponent* m_moveComponent;
};

