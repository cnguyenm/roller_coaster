#pragma once
#include "GameObject.h"
class Gate :
	public GameObject
{
public:

	double w = 6.0;  // width
	double h = 3.0;  // height
	double d = 4.0;  // depth
	Camera *cam;

	Gate();
	void set_cam(Camera * cam);
	virtual void draw();
};

