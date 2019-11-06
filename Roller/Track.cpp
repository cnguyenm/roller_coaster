#include "pch.h"
#include "Track.h"


Track::Track()
{
}

Track::Track(const std::vector<TrackComponent*> component_list)
{
	this->component_list = component_list;
}

bool Track::get_collision(GameObject obj, Hit & out_hit)
{
	if (cur_component >= component_list.size()) return false;

	bool ret = component_list[cur_component]->is_collide(obj, out_hit);
	return ret;
}

bool Track::let_ball_run(double dist, Vec3 & new_pos)
{
	if (cur_component >= component_list.size()) return false;

	double remain_dist = component_list[cur_component]->let_ball_run(dist, new_pos);

	if (remain_dist > 0) {
		cur_component += 1;  // move to next component
		return let_ball_run(remain_dist, new_pos);
	}

	return true;
}

void Track::draw(Camera * cam)
{
	for (int i = 0; i < component_list.size(); i++) {		
		component_list[i]->draw(cam);
	}
}


