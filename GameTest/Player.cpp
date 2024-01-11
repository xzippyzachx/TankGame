#include "stdafx.h"
#include "app\app.h"

#include "Player.h"

Player::Player(const char* fileName, float posX, float posY) : Entity(fileName, posX, posY)
{
	float animSpeed = 0.025f;
	sprite->CreateAnimation(MOVE, speed, { 0,1 });
}

void Player::Update(float deltaTime)
{
	Entity::Update(deltaTime);

	float inputX = App::GetController().GetLeftThumbStickX();
	float inputY = App::GetController().GetLeftThumbStickY();

	if (inputX > 0.1f || inputX < -0.1f || inputY > 0.1f || inputY < -0.1f)
	{
		sprite->SetAnimation(MOVE);
		float x, y;
		sprite->GetPosition(x, y);
		x += inputX * speed * deltaTime;
		y += inputY * speed * deltaTime;
		sprite->SetPosition(x, y);
	}
	else
	{
		sprite->SetFrame(0);
	}
}