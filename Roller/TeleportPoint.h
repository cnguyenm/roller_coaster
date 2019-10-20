#pragma once
#include "GameObject.h"
class TeleportPoint :
	public GameObject
{
public:

	Vec3 destination;
	GameObject * target = NULL;

	TeleportPoint();

	// if target approach telePoint, tp it
	void set_target(GameObject * target);

	// call every frame_update
	virtual void update();

};

