#include "WanderComponent.h"
#include "Transform2D.h"
#include "Actor.h"
#include "Agent.h"
#include "MoveComponent.h"
#include <time.h>

WanderComponent::WanderComponent(float circleDistance, float circleRadius, float wanderForce) : SteeringComponent(nullptr, wanderForce)
{
	m_circleDistance = circleDistance;
	m_circleRadius = circleRadius;
	srand(time(NULL));
}

MathLibrary::Vector2 WanderComponent::calculateForce() 
{
	MathLibrary::Vector2 ownerPosition = getOwner()->getTransform()->getWorldPosition();
	MathLibrary::Vector2 heading = getAgent()->getMoveComponent()->getVelocity().getNormalized();

	m_circlePos = ownerPosition + (heading * m_circleDistance);

	float randNum1 = (rand() % 201) - 100;
	float randNum2 = (rand() % 201) - 100;

	MathLibrary::Vector2 randDirection = MathLibrary::Vector2{ randNum1, randNum2 }.normalize() * m_circleRadius;

	m_target = randDirection + m_circlePos;

	MathLibrary::Vector2 desiredVelocity = MathLibrary::Vector2::normalize(m_target - ownerPosition) * getSteeringForce();
	MathLibrary::Vector2 force = desiredVelocity - getAgent()->getMoveComponent()->getVelocity();

	return force;
}