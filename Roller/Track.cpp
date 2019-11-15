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

double Track::ball_run(double dist, GameObject * obj)
{
	if (cur_component >= component_list.size()) return dist;

	// let ball run
	double remain_dist = component_list[cur_component]->ball_run(dist, obj);
	if (remain_dist <= 0) return 0;

	// --- if still left, move to next component
	// find nearest component
	int min_component = -1;
	double error = 0.2;

	for (int i = 0; i < component_list.size(); i++) {
		if (i == cur_component) continue;

		double dist = component_list[i]->get_dist(obj->pos);
		printf("dist: %.2f\n", dist);
		if (abs(dist - 0.0) < error) {
			min_component = i;
			break;
		}
	}

	// check valid
	printf("min: %d\n", min_component);
	if (min_component == -1) return remain_dist;

	// set start
	component_list[min_component]->set_start(obj->pos);
	cur_component = min_component;
	return ball_run(remain_dist, obj);
}

void Track::draw(Camera * cam)
{
	for (int i = 0; i < component_list.size(); i++) {		
		component_list[i]->draw(cam);
	}
}

void Track::free()
{
	for (int i = 0; i < component_list.size(); i++) {
		delete component_list[i];
	}
}


