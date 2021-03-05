#include "Player.h"
#include "Game.h"
#include "Scene.h"
#include "raylib.h"
#include <iostream>
#include "Bullet.h"

Player::Player(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float maxForce) : Agent(x, y, collisionRadius, spriteFilePath, maxSpeed, maxForce)
{

}

void Player::update(float deltatime)
{
    int screenWidth = 35;
    int screenHeight = 25;

    if (getWorldPosition().x > screenWidth)
        setWorldPostion(MathLibrary::Vector2{ 0, getWorldPosition().y });
    else if (getWorldPosition().x < -2)
        setWorldPostion(MathLibrary::Vector2{ (float)screenWidth, getWorldPosition().y });

    if (getWorldPosition().y > screenHeight)
        setWorldPostion(MathLibrary::Vector2{ getWorldPosition().x, 0 });
    else if (getWorldPosition().y < -2)
        setWorldPostion(MathLibrary::Vector2{ getWorldPosition().x, (float)screenHeight });

    //Gets the player's input to determine which direction the actor will move on each axis 
    int xDirection = -Game::getKeyDown(KEY_A) + Game::getKeyDown(KEY_D);
    int yDirection = -Game::getKeyDown(KEY_W) + Game::getKeyDown(KEY_S);
    
    setAcceleration(MathLibrary::Vector2(xDirection, yDirection));

    if (getVelocity().getMagnitude() > 0)
        lookAt(getWorldPosition() + getVelocity().getNormalized());

    if (Game::getKeyPressed(KEY_SPACE))
        Game::getCurrentScene()->addActor(new Bullet(
            getWorldPosition().x, getWorldPosition().y, 2, "Images/bullet.png", 5, getForward() * 5));

    if (Game::getKeyDown(KEY_LEFT_CONTROL))
        setVelocity(getVelocity() / 2);

    Actor::update(deltatime);
}

void Player::debug()
{
    std::cout << "X: " << getWorldPosition().x << " Y: "<< getWorldPosition().y << std::endl;
}
