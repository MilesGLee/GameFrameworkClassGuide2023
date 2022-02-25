#include "Enemy.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"

Enemy::Enemy(float x, float y, const char* name, float speed, int maxHealth, Actor* target) : Actor::Actor(x, y, name)
{
	m_target = target;
	m_speed = speed;
	m_maxHealth = maxHealth;
}

void Enemy::start()
{
	m_moveComponent = dynamic_cast<MoveComponent*>(addComponent(new MoveComponent()));
	SpriteComponent* spriteComponent = new SpriteComponent("Images/player.png");
	addComponent(spriteComponent);

	Actor::start();
}

void Enemy::update(float deltaTime)
{
	Actor::update(deltaTime);
}

void Enemy::draw() 
{
	Actor::draw();
}