#include "pch.h"
#include "TeleportPoint.h"


TeleportPoint::TeleportPoint()
{
}

void TeleportPoint::set_target(GameObject * target)
{
	this->target = target;
}

void TeleportPoint::update()
{
	if (!target) {
		printf("[ERROR] tp point doesn't have target\n");
		return;
	}

	double dist = (target->pos - this->pos).magn();
	if (dist < 1) {
		target->pos = destination;
		target->pos.y += target->size + 0.01;
	}
}

