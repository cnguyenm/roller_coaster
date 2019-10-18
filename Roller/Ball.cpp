#include "pch.h"
#include "Ball.h"
#include "gameshare.h"

Ball::Ball()
{
	this->pos = Vec3(0, 0.5, 0);
	this->color = _GREEN;
}

void Ball::set_cam(Camera * cam)
{
	this->cam = cam;
}

void Ball::set_obstacle(Obstacle * obs)
{
	this->obstacle = obs;
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
	if (!on_ground) apply_gravity();

	update_move();
}

void Ball::update_move() {

	// delta_time = time between updates
	double t = _DELTA_TIME / 1000.0;  // msec -> sec

	// Euler ODEs
	Vec3 V = this->vel + this->accel * t;
	Vec3 P = this->pos + this->vel * t;

	this->vel = V;
	this->pos = P;

	apply_collision();
	//printf("pos: %f,%f,%f\n", P.x, P.y, P.z);
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
		printf("no hit\n");
	}

}

