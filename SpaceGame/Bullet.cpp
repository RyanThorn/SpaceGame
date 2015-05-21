#include "Bullet.h"

Bullet::Bullet(float x, float y, void(*ScorePoint)(void))
{
	// super class init
	GameObject::Init(x, y, 16, 0, 1, 0, 0, 0);

	// set this objects ID to BULLET
	SetID(BULLET);
	// assign our scorepoint function to a local function
	Bullet::ScorePoint = ScorePoint;
}

void Bullet::Destroy()
{
	// super class destroy
	GameObject::Destroy();
}

void Bullet::Update()
{
	// super class update
	GameObject::Update();

	// If our bullet reaches the far side of the screen, make it collide with the border, therefore killing it
	if(x > WIDTH)
		Collided(BORDER);
}

void Bullet::Render()
{
	// Render our bullet as a primitive circle
	al_draw_filled_circle(x, y, 2, al_map_rgb(255, 255, 255));
}


void Bullet::Collided(int objectID)
{
	// if the bullet collides with the enemy or the border, kill the bullet
	if(objectID == ENEMY || objectID == BORDER)
		SetAlive(false);
	// if the bullet hits an enemy, score a point for the player
	if(objectID == ENEMY)
		ScorePoint();
}