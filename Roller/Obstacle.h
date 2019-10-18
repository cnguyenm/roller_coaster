#pragma once

#include "Vec3.h"
#include "GameObject.h"

class Obstacle
{
public:
	Obstacle();
	
	virtual bool is_collide(GameObject obj, Hit& hit) {
		return false;
	}
};

