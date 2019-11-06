#pragma once

#include "pch.h"

/*
 * spin design: from bottom to top
 * sliding plane design: from pos0 -> pos1
 */
class Track
{
public:

	std::vector<TrackComponent*> component_list;

	Track();
	Track(const std::vector<TrackComponent*> component_list);

	// assume collision
	bool get_collision(GameObject obj, Hit& out_hit);
	bool let_ball_run(double dist, Vec3& next_pos);

	virtual void draw(Camera * cam);
private:
	int cur_component = 0;  //index
};

