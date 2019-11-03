#include "pch.h"
#include "BezierCurve.h"



BezierCurve::BezierCurve()
{
}

BezierCurve::BezierCurve(const std::vector<Vec3>& controls) : controls(controls)
{
	genControlLine();
	genCurve();
}

void BezierCurve::draw()
{
	glLineWidth(5.0f);
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glVertexPointer(3, GL_FLOAT, 0, points.data());
	//glDrawArrays(GL_LINE_STRIP, 0, points.size());
	glBegin(GL_LINE_STRIP);
	for (Vec3 p : points){
		glVertex3d(p.x, p.y, p.z);
	}
	glEnd();
	glLineWidth(1.0f);
}

Vec3 BezierCurve::interp(Vec3 n1, Vec3 n2, float lambda)
{
	return n1 + lambda * (n2 - n1);
}

void BezierCurve::genControlLine()
{
	for (int i = 0; i < controls.size() - 1; ++i)
		for (int j = 0; j <= control_step; ++j)
			controlLine.emplace_back(interp(controls[i], controls[i + 1], static_cast<float>(j) / control_step));

}

void BezierCurve::genCurve()
{
	int step = 100;
	const Vec3& p0 = controls[0];
	const Vec3& p1 = controls[1];
	const Vec3& p2 = controls[2];
	const Vec3& p3 = controls[3];
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
