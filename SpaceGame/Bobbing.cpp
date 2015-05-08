#include "Bobbing.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

Bobbing::Bobbing(float x, float y, ALLEGRO_BITMAP *image, float time, float duration, float change, float beginning) {
	GameObject::Init(x, y, 0, 0, 0, 0, 825, 99);

	Bobbing::image = image;
	Bobbing::startY = y;
	Bobbing::i = 0;
	Bobbing::step = 1;
	Bobbing::size = 40;
	Bobbing::mod = 0;
}

void Bobbing::Destroy() {
	GameObject::Destroy();
}

void Bobbing::Update() {
	GameObject::Update();
	mod = (startY - round(sin(i * M_PI / 180) * size));
	
	i+= step;
	std::cout << mod << std::endl;

	
	if (y < startY - 30) {
		goingUp = false;
	}
	else if (y > startY + 30) {
		goingUp = true;
	}
	y = mod;
	/*if (goingUp){
		
	}
	else if (!goingUp){
		y += mod;;
	}*/
}

void Bobbing::Render() {
	GameObject::Render();

	al_draw_bitmap(image, x, y, 0);
}