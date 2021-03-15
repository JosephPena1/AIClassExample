#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(float x, float y, float collisionRadius, const char* spriteFilePath, Actor* target, float health, float damage, float maxSpeed, float maxForce)
	: Character(x, y, collisionRadius, spriteFilePath, health, damage, maxSpeed, maxForce)
{
	setTarget(target);
}

void Enemy::update(float deltaTime)
{
	Character::update(deltaTime);

	//checks if Enemy is inside the windows boundary
    int screenWidth = Game::getScreenWidth() / 32;
    int screenHeight = Game::getScreenHeight() / 32;
	int switchOffscreen = 0;

	switch (switchOffscreen)
	{
	case 0:
		//teleports agent to the opposite side of the window if not inside the window
		if (getWorldPosition().x > screenWidth)
			setWorldPostion(MathLibrary::Vector2{ 0, getWorldPosition().y });
		if (getWorldPosition().x < -1)
			setWorldPostion(MathLibrary::Vector2{ (float)screenWidth, getWorldPosition().y });

		if (getWorldPosition().y > screenHeight)
			setWorldPostion(MathLibrary::Vector2{ getWorldPosition().x, 0 });
		if (getWorldPosition().y < -1)
			setWorldPostion(MathLibrary::Vector2{ getWorldPosition().x, (float)screenHeight });
		break;
	case 1:
		//keeps agent from going offscreen
		if (getWorldPosition().x > (screenWidth - .5f))
			setVelocity(MathLibrary::Vector2{ -1, 0 });
		if (getWorldPosition().y > (screenHeight - .5f))
			setVelocity(MathLibrary::Vector2{ 0, -1 });

		if (getWorldPosition().x < .5f)
			setVelocity(MathLibrary::Vector2{ 1, 0 });
		if (getWorldPosition().y < .5f)
			setVelocity(MathLibrary::Vector2{ 0, 1 });
		break;
	default:
		break;
	}

}
