#include "pch.h"
#include "Bezier.h"
#include <gameshare.h>

Bezier::Bezier()
{
	this->control_points = std::vector<Vec3>();
	this->color = _YELLOW;
}

Bezier::Bezier(const std::vector<Vec3>& controls) : control_points(controls)
{
	this->color = _YELLOW;
	genControlLine();
	genCurve();
	find_length();
}

void Bezier::set_points(std::vector<Vec3> controls)
{
	this->control_points = controls;
}

void Bezier::draw()
{
	glLineWidth(5.0f);
	glBegin(GL_LINE_STRIP);
	for (Vec3 p : points) {
		glVertex3d(p.x, p.y, p.z);
	}
	glEnd();
	glLineWidth(1.0f);
}

void Bezier::draw(Camera * cam)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	cam->apply();

	color.apply();
	glLineWidth(10.0f);
		glBegin(GL_LINE_STRIP);
		for (Vec3 p : points) {
			glVertex3d(p.x, p.y, p.z);
		}
		glEnd();
	glLineWidth(1.0f);
	glPopMatrix();
}

void Bezier::draw3d()
{
	// check
	if (control_points.size() < 3) return;

	Vec3 p, p1;
	double t;
	int n = control_points.size() - 1;
	int k = 0;

	// draw
	color.apply();
	glBegin(GL_QUAD_STRIP);  // better performance than GL_POINTS

	for (t = 0.0; t < 1.0; t += 0.1) {

		p = Vec3(0, 0, 0);

		// calc point for each t
		for (unsigned int i = 0; i < control_points.size(); i++) {
			// p = p0*B(3,0) + p1*B(3,1) + ... + pn*B(n,n)
			// p0 * B(n,k) = p0 * nCk * (1-t)^(n-k) * t^k
			k = i;
			p1 = control_points[i] * BB(n, k, t);
			p += p1;

		}

		// draw point		
		//glVertex3d(p.x, p.y, p.z);
		glVertex3d(p.x, p.y, p.z - 0.25);
		glVertex3d(p.x, p.y, p.z + 0.25);
	}
	glEnd();
}

Vec3 Bezier::interp(Vec3 n1, Vec3 n2, float lambda)
{
	return n1 + lambda * (n2 - n1);
}

void Bezier::genControlLine()
{
	for (int i = 0; i < control_points.size() - 1; ++i)
		for (int j = 0; j <= control_step; ++j)
			control_line.emplace_back(interp(control_points[i], control_points[i + 1], static_cast<float>(j) / control_step));

}

void Bezier::genCurve()
{
	int step = 100;
	const Vec3& p0 = control_points[0];
	const Vec3& p1 = control_points[1];
	const Vec3& p2 = control_points[2];
	const Vec3& p3 = control_points[3];
	points.resize(step + 1);
	for (int i = 0; i <= step; ++i)
	{
		float lambda = static_cast<float>(i) / step;
		// Referring to https://en.wikipedia.org/wiki/B%C3%A9zier_curve#Higher-order_curves, Construction of a cubic B¨¦zier curve
		// The Green Lines
		Vec3 q0 = interp(p0, p1, lambda);
		Vec3 q1 = interp(p1, p2, lambda);
		Vec3 q2 = interp(p2, p3, lambda);
		// The Blue Line
		Vec3 r0 = interp(q0, q1, lambda);
		Vec3 r1 = interp(q1, q2, lambda);
		// The Black Dot
		points[i] = interp(r0, r1, lambda);
	}
}

void Bezier::find_length()
{
	// should be called after genCurve()

	// divide curve into small segments
	// sum(length of each segment)
	length = 0;
	for (int i = 0; i < points.size() - 1; i++) {
		double dist = (points[i + 1] - points[i]).magn();
		length += dist;
	}

	
}

Vec3 Bezier::get_point_on_curve(double t)
{
	Vec3 p = Vec3(0, 0, 0);
	int n = control_points.size() - 1;

	for (unsigned int k = 0; k < control_points.size(); k++) {
		// p = p0*B(3,0) + p1*B(3,1) + ... + pn*B(n,n)
		// p0 * B(n,k) = p0 * nCk * (1-t)^(n-k) * t^k

		Vec3 p1 = control_points[k] * BB(n, k, t);
		p += p1;

	}
	return p;
}

Vec3 Bezier::get_derivative(double t)
{
	int n = control_points.size() - 1;
	Vec3 sum;

	// k = 0->n-1
	for (int k = 0; k < n; k++) {

		// P'k = p_k+1 - pk
		Vec3 pk_prime = control_points[k + 1] - control_points[k];
		sum += pk_prime * BB(n - 1, k, t);
	}

	sum = sum * n;

	return sum;  // tangent vector
}

double Bezier::get_dist(Vec3 pos)
{
	double dist1 = (control_points[0] - pos).magn();
	double dist2 = (control_points[3] - pos).magn();
	return fmin(dist1, dist2);
}

void Bezier::set_start(Vec3 pos)
{
	double dist1 = (control_points[0] - pos).magn();
	double dist2 = (control_points[3] - pos).magn();
	if (dist1 < dist2) t0 = 0;
	else t0 = 1;
}

double Bezier::let_ball_run(double dist, GameObject * obj)
{
	
	return 0.0;
}

double Bezier::ball_run(double dist, GameObject * obj)
{
	// check if ball reverse direction
	Vec3 tangent = get_derivative(t0);
	Vec3 vel = obj->vel;
	double cos_a = tangent * vel;
	bool is_reverse = true;
	if (cos_a > 0) {
		is_reverse = false;
	}
	else {}

	// move ball
	double delta_t = dist / length;
	double t1;
	
	if (!is_reverse) {
		t1 = t0 + delta_t;
	}
	else {
		t1 = t0 - delta_t;
	}
	
	// see if it overshoot
	if (t1 > 1) {
		obj->pos = control_points[3];
		return (t1 - 1)*length;
	}
	// negative
	else if (t1 < 0) {
		obj->pos = control_points[0];
		return (-t1)*length;
	}
	else {
		obj->pos = get_point_on_curve(t1);
		t0 = t1;
	}

	return 0.0;
}

bool Bezier::is_collide(GameObject obj, Hit & hit)
{
	hit.tangent = get_derivative(t0);
	hit.pos = get_point_on_curve(t0);

	return true;
}

double Bezier::BB(int n, int k, double t)
{
	return (double)nChoosek(n, k)*pow(1 - t, n - k)*pow(t, k);
}

unsigned Bezier::nChoosek(unsigned n, unsigned k)
{
	if (k > n) return 0;
	if (k * n > n) k = n - k;
	if (k == 0) return 1;

	unsigned result = n;
	for (int i = 2; i <= k; i++) {
		result *= (n - i + 1);
		result /= i;
	}

	return result;
}


