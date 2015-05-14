#include "Button.h"

#define _USE_MATH_DEFINES
#include <math.h>

Button::Button(ALLEGRO_BITMAP *image, ALLEGRO_FONT *font, const char *btnText, float x, float y, int boundX, int boundY, void(*BtnAction)(void), bool bob)
{
	// superclass init
	GameObject::Init(x, y, 0, 0, 0, 0, boundX, boundY);

	// The action function to run when the button is clicked
	Button::BtnAction = BtnAction;
	// image of the button
	Button::image = image;
	// font of the button
	Button::font = font;
	// text inside the button
	Button::btnText = btnText;

	// This makes the button bob, really I should adapt the bobbing class so it can take a GameObject, 
	// but I did this due to limited time
	Button::startY = y;
	Button::i = 0;
	Button::step = 1;
	Button::size = 10;

	// Whether the button should actually bob up and down or not
	Button::bob = bob;
}

void Button::Destroy() {
	// superclass destroy
	GameObject::Destroy();
}

void Button::Update(ALLEGRO_MOUSE_STATE state) {
	// superclass update
	GameObject::Update();
	// the mouse coordinates x and y
	tempX = state.x;
	tempY = state.y;

	// If we are bobbing the button, run the sinewave function
	if (bob)
		y = (startY - round(sin(i * M_PI / 180) * size));
	// progress our step
	i+= step;

	// if the mouse x and y is inside the buttons bounds, and the users clicks, run the action function
	if ((state.x >= x && state.y >= y) &&
		(state.x <= boundX + x && state.y <= boundY + y)){
		// The user is hovering over the button
		currentState = BTN_HOVER;
		if (state.buttons & 1) {
			// The user clicked on the button
			currentState = BTN_ACTIVE;
			// run the buttons action
			BtnAction();
		}
	} else {
		// user is not hovering over the button
		currentState = BTN_NONE;
	}
}

void Button::Render() {
	// superclass render
	GameObject::Render();

	// switch our buttons states for rendering
	switch (currentState){
		// if they are not interacting with the button, render it in its off state
		case BTN_NONE:
			al_draw_bitmap_region(image, 0, boundY, boundX, boundY, x, y, 0);
			break;
		// if they are hovering over the button, render it in its hover state
		case BTN_HOVER:
			al_draw_bitmap_region(image, 0, 0, boundX, boundY, x, y, 0);
			break;
		// if the button is pressed down, render its active state
		case BTN_ACTIVE:
			al_draw_bitmap_region(image, 0, 0, boundX, boundY, x, y, 0);
			break;
		// if we are in some weird state for some reason and it complies with none of the above, render it in
		// its default state
		default:
			al_draw_bitmap_region(image, 0, boundY, boundX, boundY, x, y, 0);
			break;
	}

	// render the font on top of the button
	al_draw_text(font, al_map_rgb(255, 255, 255), x + (boundX / 2), y + (boundY / 2) - 17, ALLEGRO_ALIGN_CENTER, btnText);
}


