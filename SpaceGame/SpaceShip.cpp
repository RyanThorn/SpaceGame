#include "SpaceShip.h"

SpaceShip::SpaceShip(){}

void SpaceShip::Destroy() {
	GameObject::Destroy();
}

void SpaceShip::Init(ALLEGRO_BITMAP *image) {
	GameObject::Init(20, 200, 4, 4, 0, 0, 40, 37);

	SetID(PLAYER);
	SetAlive(true);

	lives = 50;
	maxLives = lives;
	score = 0;

	maxFrame = 2;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 10;
	frameWidth = 130;
	frameHeight = 80;
	animationColumns = 2;
	animationDirection = 1;

	animationRow = 2;

	preventSideCols = false;

	if(image != NULL)
		SpaceShip::image = image;
}


void SpaceShip::Update() {
	GameObject::Update();
	if(x < 0)
		x = 0;
	else if(x > WIDTH)
		if (!preventSideCols)
			x = WIDTH;

	if(y < 100)
		y = 100;
	else if (y > HEIGHT - 20){
		
		y = HEIGHT - 20;
	}

	if(++frameCount >= frameDelay) {
		curFrame += animationDirection;
		if(curFrame >= maxFrame)
			curFrame = 0;
		else if(curFrame <= 0)
			curFrame = maxFrame;

		frameCount = 0;
	}
}

void SpaceShip::Render() {
	GameObject::Render();

	int fx = (curFrame % animationColumns) * frameWidth;
	//int fy = (curFrame / animationColumns) * frameHeight;
	int fy = animationRow * frameHeight;
	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);

	/*int fx = (curFrame % animationColumns) * frameWidth;
	int fy = animationRow * frameHeight;

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);*/
}

void SpaceShip::MoveUp() {
	dirY = -1;
}
void SpaceShip::MoveDown() {
	dirY = 1;
}
void SpaceShip::MoveLeft() {
	dirX = -1;
	animationRow = 1;
}
void SpaceShip::MoveRight() {
	dirX = 1;
	animationRow = 0;
}

void SpaceShip::ResetAnimation(int position) {
	if(position == 1) {
		dirY = 0;
	} else {
		dirX = 0;
	}
	animationRow = 2;
}

void SpaceShip::Collided(int objectID) {
	if(objectID == ENEMY)
		lives--;
}

float SpaceShip::GetLifePercent() {
	float percent = ((float)lives / 50.0) * 100.00;
	return percent;
}

void SpaceShip::MoveOffScreen() {
	preventSideCols = true;
	dirX = 1;
	animationRow = 0;
	if (SpaceShip::x > WIDTH + 100) {
		this->Destroy();
	}
}