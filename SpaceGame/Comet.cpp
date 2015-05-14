#include "Comet.h"

#define _USE_MATH_DEFINES
#include <math.h>

Comet::Comet(float x, float y, ALLEGRO_BITMAP *image, void (*TakeLife)(void)) {
	// superclass inti
	GameObject::Init(x, y, 3, 0, -1, 0, 40, 40);

	// set the comet as an enemy
	SetID(ENEMY);
	// the width and height of each comet
	frameWidth = 96;
	frameHeight = 96;

	// This changes the amount of the sinewave, so the comets bob up and down in different patterns
	int change = rand() % 2;
	
	Comet::startY = y;	// start y of the comet
	Comet::i = 0;		// current step of the sine wave
	Comet::step = 1;	// amount to step each time
	if (change == 1){
		// if change is 1 we are then going to start the sinewave in a positive size
		Comet::size = rand() % 100;
	}
	else{
		// if its not 1 then we are going to start the sinewave in a negative size
		Comet::size = -(rand() % 100);
	}
	// the amount to modify the comets position
	Comet::mod = 0;
	// the current angle of the comet for rotation
	radAngle = 0;

	// make it rotate both backwards and forwards
	if(rand() % 2)
		radChange = 0.01;
	else
		radChange = -0.01;

	// our comet image
	Comet::image = image;

	// the take life from player function
	Comet::TakeLife = TakeLife;
}

void Comet::Destroy() {
	// superclass destroy
	GameObject::Destroy();
}

void Comet::Update() {
	// superclass update
	GameObject::Update();

	// Rotate the comet
	radAngle += radChange;
	// Our good ol' sine wave again, 
	mod = (startY - round(sin(i * M_PI / 180) * size));
	// step the sinewave
	i += step;
	// assign mod to y, we could just apply the sinewave directly to y, but I did this for some reason
	y = mod;

	// if the comet goes off the screen, kill it
	if(x + frameWidth < 0)
		Collided(BORDER);
}

void Comet::Render() {
	// superclass render
	GameObject::Render();
	// render the comet in the current rotation
	al_draw_rotated_bitmap(image, frameWidth/2, frameHeight/2, x, y, radAngle, 0);
	
}

void Comet::Collided(int objectID) {
	// if the comet collides with the border, the player missed the comet, take a life
	if(objectID == BORDER) {
		TakeLife();
	}
	// if it collides with anything that isnt another enemy, kill it
	if(objectID != ENEMY)
		SetAlive(false);
}