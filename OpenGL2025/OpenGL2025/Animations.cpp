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
