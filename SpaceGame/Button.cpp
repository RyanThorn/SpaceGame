#include "Button.h"

#define _USE_MATH_DEFINES
#include <math.h>

Button::Button(ALLEGRO_BITMAP *image, ALLEGRO_FONT *font, const char *btnText, float x, float y, int boundX, int boundY, void(*BtnAction)(void), bool bob)
{
	GameObject::Init(x, y, 0, 0, 0, 0, boundX, boundY);

	Button::BtnAction = BtnAction;
	Button::image = image;
	Button::font = font;
	Button::btnText = btnText;

	Button::startY = y;
	Button::i = 0;
	Button::step = 1;
	Button::size = 10;

	Button::bob = bob;
}

void Button::Destroy() {
	GameObject::Destroy();
}

void Button::Update(ALLEGRO_MOUSE_STATE state) {
	GameObject::Update();
	tempX = state.x;
	tempY = state.y;

	if (bob)
		y = (startY - round(sin(i * M_PI / 180) * size));
	i++;

	if ((state.x >= x && state.y >= y) &&
		(state.x <= boundX + x && state.y <= boundY + y)){
		// We have hover
		currentState = BTN_HOVER;
		if (state.buttons & 1) {
			// We have a click
			currentState = BTN_ACTIVE;
			BtnAction();
		}
	}
	else {
		currentState = BTN_NONE;
	}
}

void Button::Render() {
	GameObject::Render();

	switch (currentState){
	case BTN_NONE:
		al_draw_bitmap_region(image, 0, boundY, boundX, boundY, x, y, 0);
		break;
	case BTN_HOVER:
		al_draw_bitmap_region(image, 0, 0, boundX, boundY, x, y, 0);
		break;
	case BTN_ACTIVE:
		al_draw_bitmap_region(image, 0, 0, boundX, boundY, x, y, 0);
		break;
	default:
		al_draw_bitmap_region(image, 0, boundY, boundX, boundY, x, y, 0);
		break;
	}

	al_draw_text(font, al_map_rgb(255, 255, 255), x + (boundX / 2), y + (boundY / 2) - 17, ALLEGRO_ALIGN_CENTER, btnText);
}


