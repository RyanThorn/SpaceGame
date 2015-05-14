/*
	This is our overall GameObject super class. All objects in the game will inherit this class
*/

#include "GameObject.h"

GameObject::GameObject() {
	// Here are all the generic variables needed for an object in our game
	// such as its positional coordinates, velocity, direction, bounding boxes
	// and the variables for spritesheet animation
	x = 0;
	y = 0;

	velX = 0;
	velY = 0;

	dirX = 0;
	dirY = 0;

	boundX = 0;
	boundY = 0;

	maxFrame = 0;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 0;
	frameWidth = 0;
	frameHeight = 0;
	animationColumns = 0;
	animationDirection = 0;

	// image of our object
	image = NULL;

	// make it alive and collidable by default
	alive = true;
	collidable = true;
}

// Our destroy function which is inherited by all gameobjects
void GameObject::Destroy() {}

// Our init function which is inherited by all gameobjects, this will setup all game object
void GameObject::Init(float x, float y, float velX, float velY, int dirX, int dirY, int boundX, int boundY) {
	// assign all the neccessary variables
	GameObject::x = x;
	GameObject::y = y;

	GameObject::velX = velX;
	GameObject::velY = velY;

	GameObject::dirX = dirX;
	GameObject::dirY = dirY;

	GameObject::boundX = boundX;
	GameObject::boundY = boundY;
}

void GameObject::Update() {
	// move our gameobject with the desired settings
	x += velX * dirX;
	y += velY * dirY;
}

// render function which is overridden by the gameobjects that inherit this
void GameObject::Render() {
}

// this checks to see if a gameobject has collided with another object
bool GameObject::CheckCollisions(GameObject *otherObject) {
	// other objects placement values
	float oX = otherObject->GetX();
	float oY = otherObject->GetY();
	// other objects bounding box
	int obX = otherObject->GetBoundX();
	int obY = otherObject->GetBoundY();

	// check the bounding box of this object, and the other image to see if
	// there is an intersection and collision
	if (x + boundX > oX - obX && x - boundX < oX + obX &&
		y + boundY > oY - obY && y - boundY < oY + obY) {
		// collided
		return true;
	} else {
		// no collision
		return false;
	}
}

// our collided function which is overridden
void GameObject::Collided(int objectID) {}

bool GameObject::Collidable() {
	// return whether it is collidable, which also requires it to be alive
	return alive && collidable;
}

void GameObject::ToggleRenderColBox() {
	// this function toggles the rendering of a game objects bounding box for debug purposes
	if (collidable)
		al_draw_filled_rectangle(x - boundX, y - boundY, x + boundX, y + boundY, al_map_rgba(255, 0, 255, 15));
}