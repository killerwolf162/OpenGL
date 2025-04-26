#include "Animations.h"
#include <iostream>

void Animations::basicAnim(Cube& obj)
{
	obj.translate(obj.translateSpeed);
	obj.rotate(obj.rotationSpeed);

	if (obj.world[3][1] > 0.75)
	{
		obj.translateSpeed.y *= -1.0f;
		obj.rotationSpeed *= -1;
	}
	else if (obj.world[3][1] < -0.75f)
	{
		obj.translateSpeed.y *= -1.0f;
		obj.rotationSpeed *= -1;
	}
}

void Animations::movementInBoxAnim(Cube& obj, int maxX, int maxY)
{
	if (obj.world[3][0] > maxX)
		obj.translateSpeed.x = -obj.translateSpeed.x;	
	else if (obj.world[3][0] < -maxX)
		obj.translateSpeed.x = -obj.translateSpeed.x;
		
	if (obj.world[3][1] > maxY)
		obj.translateSpeed.y = -obj.translateSpeed.y;
	else if (obj.world[3][1] < -maxY)
		obj.translateSpeed.y = -obj.translateSpeed.y;

	obj.translate(obj.translateSpeed);
	obj.rotate(obj.rotationSpeed);
}