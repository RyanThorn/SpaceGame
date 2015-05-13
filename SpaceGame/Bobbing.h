#pragma once
#include "GameObject.h"
class Bobbing :
	public GameObject
{
private:
	float startY;
	int i;
	int step;
	int size;
public:
	Bobbing(float x, float y, ALLEGRO_BITMAP *image, float step, float size);
	void Destroy();

	void Update();
	void Render();
};

