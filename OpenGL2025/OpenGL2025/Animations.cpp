#include "Animations.h"

void Animations::basicAnim(Cube &obj)
{
	obj.translate(glm::vec3(0, 0.001f, 0));
	obj.rotate(-0.1f);
}
