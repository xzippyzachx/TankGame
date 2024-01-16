#include "stdafx.h"
#include "app\app.h"

#include "Player.h"

Player::Player() : Entity()
{
	float animSpeed = 0.025f;
}

void Player::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	
	float inputX = App::GetController().GetLeftThumbStickX();
	float inputY = App::GetController().GetLeftThumbStickY();

	if (inputX > 0.25f || inputX < -0.25f || inputY > 0.25f || inputY < -0.25f)
	{
		sprite->SetAnimation(MOVE);

		position.x += inputX * speed * deltaTime;
		position.y += inputY * speed * deltaTime;
	}
	else
	{
		sprite->SetFrame(0);
	}
	
}

void Player::SetSprite(char* fileName)
{
	Entity::SetSprite(fileName);
	sprite->CreateAnimation(MOVE, speed, { 0,1 });
}

