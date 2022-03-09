#pragma once
#include "Component.h"
#include <Vector2.h>

class Actor;
class MoveComponent;

class SteeringComponent :
	public Component
{
public:
	SteeringComponent() { m_target = nullptr; m_steeringForce = 0; };
	SteeringComponent(Actor* actor, float steeringForce) { m_target = actor; m_steeringForce = steeringForce; }

	void start() override;

	virtual MathLibrary::Vector2 calculateForce() = 0;

	float getSteeringForce() { return m_steeringForce; }
	void setSteeringFoce(float steeringForce) { m_steeringForce = steeringForce; }

	Actor* getTarget() { return m_target; }
	void setTarget(Actor* target) { m_target = target; }

private:
	float m_steeringForce = 0;
	Actor* m_target = nullptr;
};

