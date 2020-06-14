
# Roller coaster

Roller coaster is a 3D simulation of  the first view when sit in a roller coaster. 
This project uses 
* C++, openGL and mainly Bezier curve to render the track.
* ODEs to simulate physics for the ball

## Quick-start

* clone or download this repository
* open Roller/Roller.sln in visual studio 2017
* Run the project
  

## Demo
* when first run, there will be a control panel, allow play/pause
![control panel](docs/control.PNG  "control panel")

* and a window to see the track top-down
![top view](docs/top_view.PNG  "top viewl")

* when press play, the first view will appear
![first view](docs/first_person_view.PNG  "first view")

## Edit code

* Roller/source.cpp: the main function, can edit roller track here
* Roller/ball.cpp: physics of ball
* Roller/gameshare.cpp: program constants
* Roller/gui.cpp: handle gui in control panel