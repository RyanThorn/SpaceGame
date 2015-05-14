
#include "Explosion.h"

Explosion::Explosion(float x, float y, ALLEGRO_BITMAP *image) {
	// superclass init
	GameObject::Init(x, y, 0, 0, 0, 0, 0, 0);

	// set id to an explosion
	SetID(EXPLOSION);
	// make explosions not collidable
	SetCollidable(false);

	// Our various variables for looping through the sprite sheet
	maxFrame = 31;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 2;
	frameWidth = 128;
	frameHeight = 128;
	animationColumns = 8;
	animationDirection = 1;

	// our sprite sheet for the explosion
	Explosion::image = image;
}

void Explosion::Destroy() {
	// superclass destroy
	GameObject::Destroy();
}

void Explosion::Update() {
	// superclass update
	GameObject::Update();

	// draw each section of the spritesheet one after another, using the above variables
	if(++frameCount >= frameDelay) {
		curFrame += animationDirection;
		if(curFrame >= maxFrame)
			SetAlive(false);

		frameCount = 0;
	}
}

void Explosion::Render() {
	// superclass render
	GameObject::Render();

	// this defines what section of the spritesheet to draw
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;
	// draw the specific region of the sprite sheet
	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);
}