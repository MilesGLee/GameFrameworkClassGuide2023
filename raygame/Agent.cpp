#include "Agent.h"
#include "MoveComponent.h"
#include "SteeringComponent.h"

void Agent::start() 
{
	m_moveComponent = getComponent<MoveComponent>();
}

void Agent::update(float deltaTime)
{
	for (int i = 0; i < m_steeringComponent.getLength(); i++)
	{
		m_force = m_force + m_steeringComponent[i]->calculateForce();
	}

	if (m_force.getMagnitude() > getMaxForce())
	{
		m_force = m_force.getNormalized * getMaxForce();
	}

	getMoveComponent()->setVelocity(getMoveComponent()->getVelocity() + m_force * deltaTime);
}


void Agent::onAddComponent(Component* component)
{
	SteeringComponent* steeringComponent = dynamic_cast<SteeringComponent*>(component);
	if (steeringComponent)
		m_steeringComponent.addItem(steeringComponent);
}