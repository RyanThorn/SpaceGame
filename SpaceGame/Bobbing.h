#pragma once
#include "GameObject.h"
class Bobbing :
	public GameObject
{
private:
	bool goingUp;
	float startY;
	int i;
	int step;
	int size;
	float mod;
public:
	Bobbing(float x, float y, ALLEGRO_BITMAP *image, float time, float duration, float change, float beginning);
	void Destroy();

	void Update();
	void Render();
};

