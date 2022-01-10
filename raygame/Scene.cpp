#include "Scene.h"
#include "Transform2D.h"
#include <string.h>
#include "Engine.h"

ActorArray Scene::m_actorsToDelete = ActorArray();

Scene::Scene()
{
    m_actorCount = 0;
    m_actors = ActorArray();
    m_world = new MathLibrary::Matrix3();
}

MathLibrary::Matrix3* Scene::getWorld()
{
    return m_world;
}

void Scene::addUIElement(Actor* actor)
{
    m_UIElements.addActor(actor);

    //Adds all children of the UI to the scene
    for (int i = 0; i < actor->getTransform()->getChildCount(); i++)
    {
        m_UIElements.addActor(actor->getTransform()->getChildren()[i]->getOwner());
    }
}

bool Scene::removeUIElement(int index)
{
    return m_UIElements.removeActor(index);
}

bool Scene::removeUIElement(Actor* actor)
{
    return m_UIElements.removeActor(actor);
}

void Scene::addActor(Actor* actor)
{
    m_actors.addActor(actor);

    //Adds all children of the actor to the scene
    for (int i = 0; i < actor->getTransform()->getChildCount(); i++)
    {
        m_actors.addActor(actor->getTransform()->getChildren()[i]->getOwner());
    }
}

bool Scene::removeActor(int index)
{
    return m_actors.removeActor(index);
}

bool Scene::removeActor(Actor* actor)
{
    return m_actors.removeActor(actor);
}

void Scene::addActorToDeletionList(Actor* actor)
{
    //return if the actor is already going to be deleted
    if (m_actorsToDelete.contains(actor))
        return;

    //Add actor to deletion list
    m_actorsToDelete.addActor(actor);

    //Add all the actors children to the deletion list
    for (int i = 0; i < actor->getTransform()->getChildCount(); i++)
    {
        m_actorsToDelete.addActor(actor->getTransform()->getChildren()[i]->getOwner());
    }
}

void Scene::destroy(Actor* actor)
{
    addActorToDeletionList(actor);
}

void Scene::destroyActorsInList()
{
    //Iterate through deletion list
    for (int i = 0; i < m_actorsToDelete.getLength(); i++)
    {
        //Remove actor from the scene
        Actor* actorToDelete = m_actorsToDelete.getActor(i);
        if (!removeActor(actorToDelete))
            removeUIElement(actorToDelete);

        //Call actors clean up functions
        actorToDelete->end();
        actorToDelete->onDestroy();

        //Delete the actor
        delete actorToDelete;
    }

    //Clear the array
    m_actorsToDelete = ActorArray();
}


Actor* Scene::getActor(int index)
{
    return m_actors.getActor(index);
}

void Scene::start()
{
    m_started = true;
}

void Scene::update(float deltaTime)
{
    //Clean up actors marked for destruction
    destroyActorsInList();

    //Updates all actors
    for (int i = 0; i < m_actors.getLength(); i++)
    {
        if (!m_actors.getActor(i)->getStarted())
            m_actors.getActor(i)->start();

        m_actors.getActor(i)->update(deltaTime);
    }

    //Checks collision for all actors
    for (int i = 0; i < m_actors.getLength(); i++)
    {
        for (int j = 0; j < m_actors.getLength(); j++)
        {
            if (m_actors.getActor(i)->checkForCollision(m_actors.getActor(j)) && j != i && m_actors.getActor(j)->getStarted())
                m_actors.getActor(i)->onCollision(m_actors.getActor(j));
        }
    }
}

void Scene::updateUI(float deltaTime)
{
    //Calls update for all actors in UI array
    for (int i = 0; i < m_UIElements.getLength(); i++)
    {
        if (!m_UIElements.getActor(i)->getStarted())
            m_UIElements.getActor(i)->start();

        m_UIElements.getActor(i)->update(deltaTime);
    }
}

void Scene::draw()
{
    //Calls draw for all actors in the array
    for (int i = 0; i < m_actors.getLength(); i++)
    {
        m_actors.getActor(i)->draw();
    }
}

void Scene::drawUI()
{
    //Calls draw for all actors in UI array
    for (int i = 0; i < m_UIElements.getLength(); i++)
    {
        m_UIElements.getActor(i)->draw();
    }
}

void Scene::end()
{
    //Calls end for all actors in the array
    for (int i = 0; i < m_actors.getLength(); i++)
    {
        if (m_actors.getActor(i)->getStarted())
            m_actors.getActor(i)->end();
    }

    m_started = false;
}