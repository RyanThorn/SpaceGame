#pragma once

#include "GameObject.h"

class SpaceShip : public GameObject
{
private:
	int lives;
	int score;
	int animationRow;
	int maxLives;

	bool preventSideCols;

public:
	SpaceShip();
	void Destroy();

	void Init(ALLEGRO_BITMAP *image = NULL);
	void Update();
	void Render();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void MoveOffScreen();

	void ResetAnimation(int position);

	int GetLives() { return lives; }
	float GetLifePercent();
	int GetScore() { return score; }

	void LoseLife() { lives--; }
	void AddPoint() { score++; }

	void Collided(int objectID);
};