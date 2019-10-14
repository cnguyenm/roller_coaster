#include "pch.h"
#include "Bezier.h"


Bezier::Bezier()
{
}

void Bezier::draw_curve(Camera * cam, 
	std::vector<Vec3> ctrl_points,
	Color color)
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


