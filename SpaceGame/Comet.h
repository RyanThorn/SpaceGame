#pragma once

#include "GameObject.h"

class Comet : public GameObject
{
private:
	void (*TakeLife)(void);
	float radAngle;
	float radChange;

	float startY;
	int i;
	int step;
	int size;
	float mod;

public:
	Comet(float x, float y, ALLEGRO_BITMAP *image, void (*TakeLife)(void));
	void Destroy();

	void Update();
	void Render();

	void Collided(int objectID);
};