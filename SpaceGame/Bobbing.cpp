#include "Bobbing.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

Bobbing::Bobbing(float x, float y, ALLEGRO_BITMAP *image, float step, float size) {
	GameObject::Init(x, y, 0, 0, 0, 0, 825, 99);

	Bobbing::image = image;
	Bobbing::startY = y;
	Bobbing::i = 0;
	Bobbing::step = step;
	Bobbing::size = size;
}

void Bobbing::Destroy() {
	GameObject::Destroy();
}

void Bobbing::Update() {
	GameObject::Update();
	y = (float)(startY - round(sin(i * M_PI / 180) * size));
	
	i+= step;
}

void Bobbing::Render() {
	GameObject::Render();

	al_draw_bitmap(image, x, y, 0);
}