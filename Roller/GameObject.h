#pragma once

#include "Vec3.h"
#include "Color.h"
#include "Camera.h"
#include <iostream>

class GameObject
{
public:

	Vec3 pos;	// position
	Vec3 vel;	// velocity
	Vec3 accel;
	Color color; // color rgb
	Color color_hover;  // color when hover over
	Vec3 init_pos;  // pos0

	double size = 1;
	double weight = 1;
	bool is_hovered = false;

	GameObject();
	virtual void set_init_pos(Vec3 pos);
	virtual void update() {};
	virtual void draw() {};
	//virtual void draw(Camera *cam) {};

	// check if mouse is hovering over
	// param: mousePos in world_coord
	virtual int is_mouse_over(Vec3 pos);
};

