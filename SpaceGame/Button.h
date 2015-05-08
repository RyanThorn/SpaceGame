#pragma once
#include "GameObject.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class Button :
	public GameObject
{
private:
	void(*BtnAction)(void);
	enum BtnState {BTN_ACTIVE, BTN_HOVER, BTN_NONE};
	BtnState currentState;
	ALLEGRO_FONT *font;
	const char *btnText;

	float tempX, tempY;

	float startY;
	int i;
	int step;
	int size;
	float mod;
public:
	Button(ALLEGRO_BITMAP *image, ALLEGRO_FONT *font, const char *btnText, float x, float y, int boundX, int boundY, void(*BtnAction)(void));
	void Destroy();

	void Render();
	void Update(ALLEGRO_MOUSE_STATE state);

	BtnState GetState(){ return currentState; }
};

