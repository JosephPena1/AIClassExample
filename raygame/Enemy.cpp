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

    if (getWorldPosition().x > screenWidth)
        setWorldPostion(MathLibrary::Vector2{ 0, getWorldPosition().y });
    if (getWorldPosition().x < -1)
        setWorldPostion(MathLibrary::Vector2{ (float)screenWidth, getWorldPosition().y });

    if (getWorldPosition().y > screenHeight)
        setWorldPostion(MathLibrary::Vector2{ getWorldPosition().x, 0 });
    if (getWorldPosition().y < -1)
        setWorldPostion(MathLibrary::Vector2{ getWorldPosition().x, (float)screenHeight });
}
