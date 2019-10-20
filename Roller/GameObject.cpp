#include "pch.h"


GameObject::GameObject()
{
	this->pos = Vec3();
	this->vel = Vec3();
	this->size = 1;
}

void GameObject::set_init_pos(Vec3 pos)
{
	this->init_pos = pos;
	this->pos = pos;
}

int GameObject::is_mouse_over (Vec3 pos) {
	printf("dad\n");
	return 0;
};
