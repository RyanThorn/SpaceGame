#include "Comet.h"

#define _USE_MATH_DEFINES
#include <math.h>

Comet::Comet(float x, float y, ALLEGRO_BITMAP *image, void (*TakeLife)(void)) {
	GameObject::Init(x, y, 3, 0, -1, 0, 40, 40);

	SetID(ENEMY);

	//maxFrame = 43;
	//curFrame = 0;
	//frameCount = 0;
	//frameDelay = 4;
	frameWidth = 96;
	frameHeight = 96;
	//animationColumns = 21;

	int change = rand() % 2;
	

	Comet::startY = y;
	Comet::i = 0;
	Comet::step = 1;
	if (change == 1){
		Comet::size = rand() % 100;
	}
	else{
		Comet::size = -(rand() % 100);
	}
	Comet::mod = 0;

	radAngle = 0;

	if(rand() % 2)
		radChange = 0.01;
	else
		radChange = -0.01;

	Comet::image = image;

	Comet::TakeLife = TakeLife;
}

void Comet::Destroy() {
	GameObject::Destroy();
}

void Comet::Update() {
	GameObject::Update();
	// Just rotate the bitmap
	radAngle += radChange;
	mod = (startY - round(sin(i * M_PI / 180) * size));
	i++;
	y = mod;
	// Old Sprite Code
	/*if(++frameCount >= frameDelay) {
		curFrame += animationDirection;
		if(curFrame >= maxFrame)
			curFrame = 0;
		else if(curFrame <= 0)
			curFrame = maxFrame;

		frameCount = 0;
	}*/

	if(x + frameWidth < 0)
		Collided(BORDER);
}

void Comet::Render() {
	GameObject::Render();

	//int fx = (curFrame % animationColumns) * frameWidth;
	//int fy = (curFrame / animationColumns) * frameHeight;

	//al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);
	al_draw_rotated_bitmap(image, frameWidth/2, frameHeight/2, x, y, radAngle, 0);
	
}

void Comet::Collided(int objectID) {
	if(objectID == BORDER) {
		TakeLife();
	}

	if(objectID != ENEMY)
		SetAlive(false);
}