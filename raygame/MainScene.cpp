#include "MainScene.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Transform2D.h"
#include "Player.h"

void MainScene::start()
{
	Player* player = new Player(50, 50, "Player");
	player->getTransform()->setScale({ 50,50 });
	player->addComponent(new SpriteComponent("Images/player.png"));
	MoveComponent* playerMove = player->addComponent<MoveComponent>();

	playerMove->setVelocity({ 1,1 });
	addActor(player);
}
