#ifndef ENEMY_H
#define ENEMY_H
#include "Vector3.h"

class Enemy
{
private:
	Vector3 position;
	int upperLimit; //for patrolling
	int lowerLimit;
	int moveState;
	char directionToMoveIn; //x or z
	float turnAngle;
	float waitTime;

public:
	Enemy();
	~Enemy();

	void init(const Vector3& position, int upperLimit, int lowerLimit, char direction, float turnAngle, int moveState);
	void update(double dt);
	Vector3 getPosition(void);
	void setPosition(float x, float y, float z);
	float getTurnAngle(void);
	char getDirection(void);
	int getMoveState(void);

};

#endif