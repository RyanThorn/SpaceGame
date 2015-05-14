#include "Background.h"

Background::Background(ALLEGRO_BITMAP *image, float velX)
{
	// Run the superclasses Init function
	GameObject::Init(0, 0, velX, 0, -1, 0, 0, 0);

	// Set ID to MISC
	SetID(MISC);
	// Not collidable
	SetCollidable(false);

	// Set our background image
	Background::image = image;
	// Get the width of the image as our frameWidth
	frameWidth = al_get_bitmap_width(image);
}

void Background::Destroy()
{
	// Run the superclass destroy 
	GameObject::Destroy();
}

void Background::Update()
{
	// Run the supeclass update
	GameObject::Update();
	// if the background reaches the width of the image, set its x back to 0
	if(x + frameWidth <= 0)
		x = 0;
}

void Background::Render()
{
	// Run our superclass Render
	GameObject::Render();

	// Draw the bitmap
	al_draw_bitmap(image, x, y, 0);

	// Draw another of the same image after the first image to give the effect of a repeating background.
	if(x + frameWidth < WIDTH)
		al_draw_bitmap(image, x + frameWidth, y, 0);
}