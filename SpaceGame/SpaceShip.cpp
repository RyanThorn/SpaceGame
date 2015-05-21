#include "SpaceShip.h"

SpaceShip::SpaceShip(){}

// Our spaceshit destroy function
void SpaceShip::Destroy() {
	// runs superclass destroy
	GameObject::Destroy();
}

void SpaceShip::Init(ALLEGRO_BITMAP *image) {
	// superclass init
	GameObject::Init(20, 200, 4, 4, 0, 0, 40, 37);

	// Set the ID of this object to a PLAYER
	SetID(PLAYER);
	// make it alive
	SetAlive(true);

	// The maximum lives of a player
	lives = 700000;
	// A storage of what the maximum lives was
	maxLives = lives;
	// current player score set to 0
	score = 0;

	// Variables to create the different animations for the players ship
	maxFrame = 2;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 10;
	frameWidth = 130;
	frameHeight = 80;
	animationColumns = 2;
	animationDirection = 1;

	animationRow = 2;
	// Whether we should stop the ship colliding with the sides. We do this at the end
	// when the ship flies off the screen.
	preventSideCols = false;

	// if the image is null, set its image
	if(image != NULL)
		SpaceShip::image = image;
}


void SpaceShip::Update() {
	// superclass update
	GameObject::Update();
	// if its x is less then 0, stop it going off the screen
	if(x < 0)
		x = 0;
	// if its on the other side of the screen, stop it going off the screen,
	else if(x > WIDTH)
		// unless we want it to (at the end of the game)
		if (!preventSideCols)
			x = WIDTH;

	// stop the ship going off the top and bottom of the screen
	if(y < 100)
		y = 100;
	else if (y > HEIGHT - 20){
		y = HEIGHT - 20;
	}

	// The spritesheet calculcations
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
	// superclass render
	GameObject::Render();

	// the place where we want to render in the spritesheet
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = animationRow * frameHeight;

	// draw the region of the spritesheet
	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);
}

void SpaceShip::MoveUp() {
	// move the ship up setting its direction Y to -1
	dirY = -1;
}
void SpaceShip::MoveDown() {
	// move the ship down by setting its direction Y to 1
	dirY = 1;
}
void SpaceShip::MoveLeft() {
	// move ship left by setting direction x to -1 and also change which part of the spritesheet to render
	dirX = -1;
	animationRow = 1;
}
void SpaceShip::MoveRight() {
	// move ship right by setting the direction x to 1 and also change what part of the spritesheet to render
	dirX = 1;
	animationRow = 0;
}


// when the player is not moving the ship at all, reset the animation to the default section of the spritesheet
void SpaceShip::ResetAnimation(int position) {
	if(position == 1) {
		dirY = 0;
	} else {
		dirX = 0;
	}
	animationRow = 2;
}

void SpaceShip::Collided(int objectID) {
	// if they collide with an enemy, minus the lives
	if(objectID == ENEMY)
		lives--;
}

float SpaceShip::GetLifePercent() {
	// convert the players lives into a percentage
	float percent = ((float)lives / 70.0) * 100.00;
	return percent;
}

void SpaceShip::MoveOffScreen() {
	// at the end, move the ship off the screen into the vast, vast space!
	preventSideCols = true;
	dirX = 1;
	animationRow = 0;
	if (SpaceShip::x > WIDTH + 100) {
		this->Destroy();
	}
}