#include "pch.h"
#include "Ball.h"
#include "gameshare.h"

Ball::Ball()
{
	this->pos = Vec3(0, 0.5, 0);
	this->color = _BLUE;
}

void Ball::set_cam(Camera * cam)
{
	this->cam = cam;
}

void Ball::set_obstacle(Obstacle * obs)
{
	this->obstacle = obs;
}

void Ball::set_track(Track * track)
{
	this->track = track;
}

void Ball::draw()
{
	if (!cam) {
		printf("[ERROR] Ball doesn't have camera\n");
		return;
	}

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	cam->apply();

	// --- draw 
	this->color.apply();
	glTranslated(this->pos.x, this->pos.y, this->pos.z);
	//glutWireSphere(this->size, 16, 16);
	glutSolidSphere(this->size, 16, 16);
	glPopMatrix();
}

void Ball::update()
{
	//this->pos.x += 0.05;
	if (on_track) run_on_track();
	else {
		if (!on_ground) apply_gravity();
		update_move();  // normal move
	}

	//update_move();
}

void Ball::update_move() {

	// delta_time = time between updates
	double t = _DELTA_TIME / 1000.0;  // msec -> sec

	// Euler ODEs
	Vec3 V = this->vel + this->accel * t;
	Vec3 P = this->pos + this->vel * t;

	this->vel = V;
	this->pos = P;

	//apply_collision();
	//printf("vel: %f,%f,%f\n", V.x, V.y, V.z);
}

Vec3 Ball::find_force(Hit hit)
{
	// calculate angle_alpha = angle(gravity, resistance_penetration)
	// =  | 90 - angle(gravity,tangent) |
	Vec3 g = Vec3(0, -1, 0);  // gravity vector
	Vec3 t = hit.tangent;  // tangent vector

	double cos_beta = (g*t) / (g.magn() * t.magn());
	double beta = acos(cos_beta);  // in rad

	// because alpha+beta = 90degree = 1/2 rad
	double pi = _PI;
	double alpha = 0.5*pi - beta; // in rad 

	// F = mg*sin(alpha) * t_unit
	// t_unit there: add direction to force
	double gravity = 10.0;  // for easy
	Vec3 t_unit = t.normalized();
	Vec3 F = this->weight * gravity * sin(alpha) * t_unit;

	return F;
}
//
//void Ball::run_on_track()
//{
//	// find accel, vel at time t0
//	Hit hit;
//	if (!track->get_collision(*this, hit)) return;
//
//	// find accel
//	double t = _DELTA_TIME / 1000.0;  // msec -> sec
//	accel = find_force(hit);
//
//	// convert vel to tangent direction (projection formula)
//	// find dist travel
//	double cos_a = Vec3::cos(vel, hit.tangent);
//	if (cos_a == 0) cos_a = 1;  // in case right angle
//	vel = (vel.magn() * cos_a) * hit.tangent.normalized();
//	vel = vel + accel * t;
//	double dist = (vel * t).magn();
//	
//	// convert dist_travel to next_pos on curve
//	Vec3 next_pos;
//	if (track->let_ball_run(dist, next_pos)) {
//		pos = next_pos;
//		pos.y += size;
//		track->ball_run(dist, this);
//	}
//	else {	
//		on_track = false;
//	}
//}

void Ball::run_on_track() {
	// find accel, vel at time t0
	Hit hit;
	if (!track->get_collision(*this, hit)) return;

	// find accel
	double t = _DELTA_TIME / 1000.0;  // msec -> sec
	accel = find_force(hit);

	// convert vel to tangent direction (projection formula)
	// find dist travel
	double cos_a = Vec3::cos(vel, hit.tangent);
	if (cos_a == 0) cos_a = 1;  // in case right angle
	vel = (vel.magn() * cos_a) * hit.tangent.normalized();
	vel = vel + accel * t;
	double dist = (vel * t).magn();

	// convert dist_travel to next_pos on curve
	Vec3 next_pos;
	double remain_dist = track->ball_run(dist, this);
	pos.y += size;
	if (remain_dist > 0) {
		printf("off track\n");
		on_track = false;
	}
}

void Ball::run_on_plane()
{
	// find accel, vel at time t0
	Hit hit;
	if (!plane->is_collide(*this, hit)) return;

	// find accel
	double t = _DELTA_TIME / 1000.0;  // msec -> sec
	accel = find_force(hit);

	// convert vel to tangent direction
	// find dist travel
	double cos_a = Vec3::cos(vel, hit.tangent);
	vel = (vel.magn() * cos_a) * hit.tangent.normalized();
	vel = vel + accel * t;
	double dist = (vel * t).magn();

	// convert dist_travel to next_pos on curve
	Vec3 next_pos;
	if (plane->let_ball_run(dist, next_pos)) {
		pos = next_pos;
		pos.y += size;
	}
	else {		
		on_track = false;	
	}

	printf("vel= %2.f, %.2f %.2f \n", vel.x, vel.y, vel.z);

}

void Ball::apply_gravity()
{
	this->accel = Vec3(0, -_GRAVITY_FORCE, 0);
}

void Ball::apply_collision()
{
	// hit base_ground
	double error = 0.01;
	if (pos.y < 0.0 + size + error) {
		pos.y = 0.0 + this->size;
	}

	// if hit obstacle
	Hit out_hit;
	if (obstacle->is_collide(*this, out_hit)) {
		//printf("hit\n");
		pos		= out_hit.pos;
		pos.y	+= this->size;
		this->accel = find_force(out_hit) / weight;// F = ma

		if (!on_ground) {
			on_ground = true;
			//this->vel = Vec3(0, 0, 0);  // reset vel
			
		}
	}
	else {
		on_ground = false;
		//printf("no hit\n");
	}

}

