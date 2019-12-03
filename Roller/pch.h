// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H

// TODO: add headers that you want to pre-compile here

// parent class go first
// if classB ref classA, fileA goes first
#include <GL/freeglut.h>
#include <GL/glui.h>
#include <math.h>

#include "Camera.h"
#include "Vec3.h"
#include "Color.h"
#include "GameObject.h"

#include "TrackComponent.h"
#include "Bezier.h"

#include "Track.h"
#include "Ball.h"
#include "TeleportPoint.h"
#include "SlidingPlane.h"

#include "gui.h"
#include "play.h"

#endif //PCH_H
