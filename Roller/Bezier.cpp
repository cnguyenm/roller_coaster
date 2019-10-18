#include "pch.h"
#include "Bezier.h"
#include <gameshare.h>

Bezier::Bezier()
{
	this->ctrl_points = std::vector<Vec3>();
}



void Bezier::set_points(std::vector<Vec3> p_list)
{
	this->ctrl_points = p_list;
}

void Bezier::draw()
{
	this->draw_curve(this->ctrl_points, _YELLOW);
}

bool Bezier::is_collide(GameObject obj, Hit & out_hit)
{
	// see if t, x both increase
	bool is_increasing = false;  // true if t increase, x increase
	Vec3 a1 = get_point_on_curve(0.3);
	Vec3 a2 = get_point_on_curve(0.6);
	if (a2.x > a1.x) is_increasing = true;

	// if near outside
	double error = 0.01;
	/*if (abs(obj.pos.x - ctrl_points[0].x) < error) {

	}*/

	Vec3 result;
	double step = 0.01;
	

	// mid
	double low  = -0.2;  // because t = [0,1]
	double high = 1.1;
	double mid;
	int count = 0;
	Vec3 p;

	// binary search
	while (1) {

		mid = (high + low) / 2.0;
		p = get_point_on_curve(mid);

		// just take it?
		if (count > 1000) {
			break;
		}

		// if equal
		if (abs(p.x - obj.pos.x) < error) {

			// check dist
			double dist = (obj.pos - p).magn();
			//printf("dist=%.2f\n", dist);
			if (dist > obj.size + 0.01)return false;

			out_hit.pos = p;
			out_hit.tangent = get_derivative(mid);
			//printf("hit:%.2f,%.2f,%.2f\n", p.x, p.y, p.z);
			return true;
		}

		// if smaller, find larger_half
		if (p.x < obj.pos.x) {

			if (is_increasing) { low = mid; }
			else { high = mid; }
		}

		// if larger, find smaller_half
		else {
			if (is_increasing) { high = mid; }
			else { low = mid; }
		}

		count += 1;
	}

	printf("final p: %.2f,%.2f,,%.2f\n", p.x, p.y, p.z);
	printf("sth wrong\n");
	return false;
}

void Bezier::draw_curve(std::vector<Vec3> ctrl_points, Color color)
{

	// check
	if (ctrl_points.size() < 3) return;

	Vec3 p, p1;
	double t;
	int n = ctrl_points.size() - 1;
	int k = 0;

	// draw
	color.apply();
	glBegin(GL_POINTS);

	for (t = 0.0; t < 1.0; t += 0.001) {

		p = Vec3(0, 0, 0);

		// calc point for each t
		for (unsigned int i = 0; i < ctrl_points.size(); i++) {
			// p = p0*B(3,0) + p1*B(3,1) + ... + pn*B(n,n)
			// p0 * B(n,k) = p0 * nCk * (1-t)^(n-k) * t^k
			k = i;
			p1 = ctrl_points[i] * BB(n, k, t);
			p += p1;

		}


		// draw point		
		glVertex3d(p.x, p.y, p.z);

	}
	glEnd();
}

Vec3 Bezier::get_point_on_curve(double t)
{
	Vec3 p = Vec3(0, 0, 0);
	int n = ctrl_points.size() - 1;

	for (unsigned int k = 0; k < ctrl_points.size(); k++) {
		// p = p0*B(3,0) + p1*B(3,1) + ... + pn*B(n,n)
		// p0 * B(n,k) = p0 * nCk * (1-t)^(n-k) * t^k

		Vec3 p1 = ctrl_points[k] * BB(n, k, t);
		p += p1;

	}
	return p;
}

Vec3 Bezier::get_derivative(double t)
{
	int n = ctrl_points.size() - 1;
	Vec3 sum;

	// k = 0->n-1
	for (int k = 0; k < n; k++) {

		// P'k = p_k+1 - pk
		Vec3 pk_prime = ctrl_points[k + 1] - ctrl_points[k];
		sum += pk_prime * BB(n - 1, k, t);
	}

	sum = sum * n;

	return sum;  // tangent vector
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


