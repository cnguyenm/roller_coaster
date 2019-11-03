#pragma once
#include <GameObject.h>
#include <Vec3.h>


class BezierCurve :
	public GameObject
{
public:

	std::vector<Vec3> controls;
	std::vector<Vec3> controlLine;
	std::vector<Vec3> points;
	int control_step = 9;

	BezierCurve();
	BezierCurve(const std::vector<Vec3>& controls);
	virtual void draw();

private:
	Vec3 interp(Vec3 n1, Vec3 n2, float lambda);
	void genControlLine();
	void genCurve();
};

