#include "Bobbing.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

Bobbing::Bobbing(float x, float y, ALLEGRO_BITMAP *image, float step, float size) {
	// Run the superclass init
	GameObject::Init(x, y, 0, 0, 0, 0, 825, 99);

	// Setup our variables for the bobbing effect
	Bobbing::image = image;
	Bobbing::startY = y;
	Bobbing::i = 0;
	Bobbing::step = step;
	Bobbing::size = size;
}

void Bobbing::Destroy() {
	// Super class destroy
	GameObject::Destroy();
}

void Bobbing::Update() {
	// Super class update
	GameObject::Update();
	// Here we create a sinewave which gives us the path of our bobbing effect.
	// We take the starting Y position of the object, and then minus sin of the step(i) multiplied by PI which is then divided by 180,
	// we then multiply that by the size to create the desired size of the bobbing effect.
	y = (float)(startY - round(sin(i * M_PI / 180) * size));
	// We plus the step to progress the sine wave
	i+= step;
}

void Bobbing::Render() {
	// super class render
	GameObject::Render();
	// draw the bitmap
	al_draw_bitmap(image, x, y, 0);
}