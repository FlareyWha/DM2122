#include "Enemy.h"

Enemy::Enemy() //default constructor
{

}

Enemy::~Enemy() //default destructor
{
}

void Enemy::init(const Vector3& position, int upperLimit, int lowerLimit, char direction, float turnAngle, int moveState) //init
{
	this->position = position; //position should be in middle
	this->directionToMoveIn = direction;
	if (direction == 'x')
	{
		this->upperLimit = upperLimit + position.x;
		this->lowerLimit = lowerLimit + position.x;
	}
	else if (direction == 'z')
	{
		this->upperLimit = upperLimit + position.z;
		this->lowerLimit = lowerLimit + position.z;
	}
	this->moveState = moveState;
	this->turnAngle = turnAngle;
	waitTime = 0;
}

void Enemy::update(double dt)
{
	if (directionToMoveIn == 'x')
	{
		if (waitTime == 0)
			position.x += (float)(moveState * 20 * dt);
		if (position.x >= upperLimit)
		{
			waitTime += dt;
			if (waitTime >= 2)
			{
				moveState = -1;
				turnAngle = -90;
				waitTime = 0;
			}
		}
		else if (position.x <= lowerLimit)
		{
			waitTime += dt;
			if (waitTime >= 2)
			{
				moveState = 1;
				turnAngle = 90;
				waitTime = 0;
			}
		}
	}
	else if (directionToMoveIn == 'z')
	{
		if (waitTime == 0)
			position.z += (float)(moveState * 20 * dt);
		if (position.z >= upperLimit)
		{
			waitTime += dt;
			if (waitTime >= 2)
			{
				moveState = -1;
				turnAngle = 180;
				waitTime = 0;
			}
		}
		else if (position.z <= lowerLimit)
		{
			waitTime += dt;
			if (waitTime >= 2)
			{
				moveState = 1;
				turnAngle = 0;
				waitTime = 0;
			}
		}
	}
}

Vector3 Enemy::getPosition(void)
{
	return position;
}

void Enemy::setPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

float Enemy::getTurnAngle(void)
{
	return turnAngle;
}

char Enemy::getDirection(void)
{
	return directionToMoveIn;
}

int Enemy::getMoveState(void)
{
	return moveState;
}
