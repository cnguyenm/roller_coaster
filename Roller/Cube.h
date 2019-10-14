#pragma once
#include "GameObject.h"
#include <pch.h>

class Cube :
	public GameObject
{
public:
	Cube();
	Camera * cam;

	void set_cam(Camera * cam);
	virtual void draw();
	virtual void update();


};

