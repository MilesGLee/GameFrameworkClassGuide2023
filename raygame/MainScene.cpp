#include "MainScene.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Transform2D.h"
#include "Player.h"
#include "Enemy.h"

void MainScene::start()
{
	Player* player = new Player(50, 50, "Player");
	player->getTransform()->setScale({ 50,50 });
	player->addComponent(new SpriteComponent("Images/player.png"));
	MoveComponent* playerMove = player->addComponent<MoveComponent>();

	//playerMove->setVelocity({ 1,1 });
	addActor(player);

	Enemy* enemy = new Enemy(0, 0, "Enemy", 1, 10, player);
	enemy->getTransform()->setScale({50, 50});
	enemy->addComponent(new SpriteComponent("Images/player.png"));
	MoveComponent* enemyMove = enemy->addComponent<MoveComponent>();

	addActor(enemy);
}
