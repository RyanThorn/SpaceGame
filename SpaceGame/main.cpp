
// includes
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <algorithm>
#include <math.h>

#include <list>

#include "GameObject.h"
#include "SpaceShip.h"
#include "Bullet.h"
#include "Comet.h"
#include "Explosion.h"
#include "Background.h"
#include "Globals.h"
#include "Button.h"
#include "Bobbing.h"

// Globals for main
bool keys[] = { false, false, false, false, false };
enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE };

const int TOTAL_SPAWNS = 807;
float spawnTimes[TOTAL_SPAWNS] = { 0.91, 0.95, 0.99, 1.04, 1.08, 1.10, 14.57, 14.62, 14.74, 14.77, 15.03, 15.06, 15.10, 15.19, 22.07, 22.11, 22.15, 22.24, 29.13, 29.19, 29.21, 29.23, 29.54, 29.57, 29.61, 30.01, 30.02, 30.03, 30.07, 30.46, 30.53, 30.90, 31.34, 31.79, 31.85, 32.23, 32.61, 32.65, 32.76, 33.10, 33.54, 33.61, 33.98, 33.99, 34.07, 34.42, 34.43, 34.52, 34.82, 34.83, 34.86, 35.27, 35.30, 35.31, 35.40, 35.75, 35.85, 35.96, 35.99, 36.19, 36.26, 36.63, 36.73, 37.07, 37.14, 37.51, 37.95, 38.39, 38.46, 38.49, 38.84, 39.27, 39.71, 39.81, 40.16, 40.62, 40.69, 41.04, 41.48, 41.51, 41.92, 41.99, 42.35, 42.43, 42.45, 42.80, 42.87, 43.04, 43.09, 43.24, 43.68, 43.76, 44.12, 44.56, 44.66, 45.00, 45.01, 45.10, 45.45, 45.89, 45.98, 46.32, 46.42, 46.72, 46.73, 46.77, 47.21, 47.65, 48.09, 48.53, 48.97, 49.42, 49.85, 49.95, 50.07, 50.08, 50.13, 50.30, 50.31, 50.73, 50.83, 51.14, 51.17, 51.62, 52.05, 52.50, 52.59, 52.94, 53.03, 53.38, 53.77, 53.82, 54.26, 54.71, 55.14, 55.24, 55.59, 56.02, 56.46, 56.56, 56.91, 57.00, 57.12, 57.35, 57.44, 57.79, 58.23, 58.32, 58.67, 59.11, 59.55, 59.65, 60.00, 60.44, 60.83, 60.84, 60.87, 61.31, 61.39, 61.75, 61.83, 62.20, 62.64, 63.07, 63.17, 63.52, 63.59, 63.97, 63.98, 64.19, 64.20, 64.41, 64.85, 65.28, 65.73, 65.74, 65.80, 66.17, 66.61, 66.70, 67.01, 67.04, 67.48, 67.58, 67.93, 68.00, 68.38, 68.82, 69.25, 69.35, 69.69, 70.14, 70.23, 70.57, 71.02, 71.23, 71.31, 71.46, 71.90, 71.99, 72.33, 72.39, 72.41, 72.43, 72.78, 72.87, 73.19, 73.22, 73.31, 73.66, 73.66, 74.10, 74.55, 74.56, 74.58, 74.95, 74.98, 75.39, 75.42, 75.86, 76.30, 76.71, 76.74, 76.80, 76.82, 76.84, 77.18, 77.63, 77.70, 78.06, 78.29, 78.32, 78.36, 78.52, 78.58, 78.95, 79.04, 79.40, 79.44, 79.47, 79.83, 80.27, 80.71, 80.78, 81.15, 81.21, 81.23, 81.60, 81.67, 82.04, 82.06, 82.48, 82.53, 82.55, 82.92, 82.92, 83.37, 83.38, 83.41, 83.43, 83.81, 83.87, 84.06, 84.09, 84.12, 84.26, 84.28, 84.30, 84.32, 84.50, 84.70, 84.94, 84.98, 85.00, 85.14, 85.16, 85.18, 85.20, 85.37, 85.38, 85.40, 85.42, 85.56, 85.61, 92.60, 92.62, 92.65, 92.77, 94.36, 94.39, 94.41, 94.50, 94.54, 94.56, 95.05, 95.08, 95.20, 95.23, 95.71, 95.74, 95.76, 95.78, 95.86, 96.15, 96.18, 96.20, 96.22, 96.30, 99.66, 99.76, 99.84, 113.35, 113.38, 113.41, 113.50, 113.55, 113.58, 113.59, 113.63, 113.77, 113.81, 113.83, 113.86, 113.87, 120.81, 120.81, 120.86, 120.89, 120.97, 120.98, 127.43, 127.46, 127.50, 127.58, 127.64, 127.72, 127.86, 127.91, 149.03, 149.06, 149.12, 149.48, 149.51, 149.93, 149.97, 150.36, 150.39, 150.43, 150.80, 150.81, 150.83, 150.85, 150.87, 151.25, 151.27, 151.67, 151.69, 152.12, 152.14, 152.15, 152.17, 152.52, 152.56, 152.58, 152.99, 153.07, 153.39, 153.44, 153.47, 153.49, 153.51, 153.88, 153.93, 154.33, 154.34, 154.41, 154.43, 154.78, 154.80, 155.17, 155.21, 155.65, 155.70, 155.87, 156.10, 156.11, 156.16, 156.53, 156.58, 156.97, 157.00, 157.02, 157.04, 157.41, 157.86, 157.92, 158.31, 158.74, 158.75, 158.78, 159.18, 159.19, 159.22, 159.24, 159.62, 159.66, 159.68, 160.06, 160.07, 160.50, 160.57, 160.94, 161.01, 161.38, 161.39, 161.41, 161.82, 161.85, 161.87, 162.26, 162.26, 162.31, 162.70, 162.75, 162.92, 162.94, 162.95, 162.97, 162.99, 163.16, 163.17, 163.60, 163.63, 163.65, 164.04, 164.06, 164.07, 164.47, 164.48, 164.91, 164.97, 165.35, 165.79, 166.23, 166.28, 166.67, 166.74, 167.11, 167.16, 167.18, 167.56, 167.98, 168.04, 168.45, 168.88, 168.92, 169.32, 169.76, 169.79, 169.97, 169.99, 170.02, 170.20, 170.21, 170.23, 170.25, 170.27, 170.29, 170.63, 170.65, 170.71, 171.08, 171.09, 171.11, 171.13, 171.52, 171.96, 172.40, 172.41, 172.85, 172.86, 172.87, 173.29, 173.34, 173.35, 173.38, 173.73, 173.79, 174.17, 174.20, 174.21, 174.60, 174.61, 174.68, 175.08, 175.10, 175.12, 175.14, 175.49, 175.50, 175.93, 175.96, 175.98, 176.00, 176.38, 176.42, 177.10, 177.29, 177.30, 177.70, 177.74, 178.15, 178.16, 178.18, 178.61, 178.63, 178.64, 179.02, 179.08, 179.11, 179.46, 179.47, 179.49, 179.90, 180.33, 180.39, 180.78, 180.85, 181.24, 181.66, 181.73, 182.12, 182.55, 182.57, 182.98, 183.03, 183.42, 183.44, 183.47, 183.50, 183.52, 183.54, 183.90, 183.93, 184.10, 184.13, 184.16, 184.32, 184.34, 184.78, 184.82, 185.15, 185.19, 185.20, 185.22, 185.24, 185.26, 185.63, 185.70, 186.07, 186.12, 186.14, 186.51, 186.53, 186.58, 186.96, 186.98, 187.43, 187.82, 187.88, 188.28, 188.31, 188.32, 188.72, 188.77, 188.79, 189.16, 189.17, 189.60, 189.65, 189.69, 189.71, 189.85, 189.87, 189.89, 190.05, 190.29, 190.33, 190.75, 190.77, 190.94, 191.18, 191.21, 191.38, 191.39, 191.85, 191.87, 191.90, 192.26, 192.70, 192.75, 193.14, 193.15, 193.58, 194.01, 194.02, 194.04, 194.07, 194.48, 194.50, 194.82, 194.89, 194.90, 194.92, 194.94, 194.96, 194.98, 195.32, 195.36, 195.38, 195.40, 195.79, 196.21, 196.23, 196.65, 196.70, 196.72, 196.74, 196.76, 197.11, 197.14, 197.54, 197.99, 198.04, 198.19, 198.43, 198.45, 198.47, 198.49, 198.87, 198.89, 199.31, 199.37, 199.74, 199.79, 199.81, 200.18, 200.19, 200.25, 200.62, 200.65, 200.67, 201.06, 201.13, 201.50, 201.55, 201.96, 201.97, 202.01, 202.39, 202.43, 202.45, 202.83, 202.86, 202.88, 202.90, 203.27, 203.30, 203.31, 203.72, 203.82, 203.84, 204.15, 204.18, 204.22, 204.59, 205.03, 205.25, 205.49, 205.52, 205.54, 205.91, 205.93, 206.35, 206.38, 206.40, 206.42, 206.79, 206.81, 206.87, 207.24, 207.30, 207.67, 208.12, 208.17, 208.56, 209.00, 209.01, 209.05, 209.07, 209.44, 209.53, 209.90, 209.95, 210.34, 210.39, 210.78, 210.79, 210.81, 210.83, 211.20, 211.22, 211.25, 211.27, 211.66, 211.67, 211.69, 211.71, 211.73, 211.75, 211.78, 212.10, 212.12, 212.13, 212.34, 212.53, 212.54, 212.56, 212.58, 212.60, 212.98, 213.02, 213.04, 213.41, 213.44, 213.47, 213.87, 213.90, 214.29, 214.36, 214.74, 215.20, 215.61, 215.68, 215.70, 216.05, 216.07, 216.10, 216.50, 216.54, 216.56, 216.94, 216.95, 216.97, 217.00, 217.37, 217.43, 217.45, 217.85, 218.27, 218.29, 218.75, 218.77, 219.15, 219.15, 219.19, 219.37, 219.43, 219.57, 219.59, 219.75 };
float hasSpawned[TOTAL_SPAWNS] = { };
int numSpawned = 0;
int numKilled = 0;
int numMissed = 0;

// Objects (Global)
SpaceShip *ship;
std::list<GameObject *> objects;
std::list<GameObject *>::iterator iter;
std::list<GameObject *>::iterator iter2;
Background *titleScreen;
Background *lostScreen;
Background *instrScreen;
ALLEGRO_SAMPLE_INSTANCE *songInstance;
ALLEGRO_SAMPLE_INSTANCE *lossSongInst;
ALLEGRO_AUDIO_STREAM *songStream;

bool hasFinished = false;
float stateTime = 0;
// Init state as -1 (no state)
int state = -1;
bool done = false;
// Main prototype functions
void __cdecl TakeLife();
void __cdecl ScorePoint();
void __cdecl BtnToPlay();
void __cdecl BtnToQuit();
void __cdecl BtnToInstr();
void __cdecl BtnToMenu();

void ChangeState(int &state, int newState);
void DrawPercentBar(int x, int y, int w, int h, float percent, ALLEGRO_BITMAP * border, ALLEGRO_BITMAP * bar, ALLEGRO_FONT* font);

int camX = 0, camY = 0;
float camAng = 0.0;
ALLEGRO_TRANSFORM cam;

int main(int argc, char **argv) {
	
	for (int i = 0; i < TOTAL_SPAWNS; i++){
		hasSpawned[i] = false;
	}

	// Local variables
	bool render = false;
	bool showColBox = false;

	int frames = 0;
	int gameFPS = 0;
	float elapsedTime = 0;
	float initTime = 0;
	float gameTime = 0;
	float lastFound = 0;

	ship = new SpaceShip();	

	// Allegro Variables
	ALLEGRO_BITMAP *shipImage = NULL;
	ALLEGRO_BITMAP *cometImage = NULL;
	ALLEGRO_BITMAP *explImage = NULL;
	ALLEGRO_BITMAP *bgImage = NULL;
	ALLEGRO_BITMAP *mgImage = NULL;
	ALLEGRO_BITMAP *fgImage = NULL;
	ALLEGRO_BITMAP *titleImage = NULL;
	ALLEGRO_BITMAP *lostImage = NULL;
	ALLEGRO_BITMAP *healthbar_border = NULL;
	ALLEGRO_BITMAP *healthbar_bar = NULL;
	ALLEGRO_BITMAP *top_bar = NULL;
	ALLEGRO_BITMAP *buttonImg = NULL;
	ALLEGRO_BITMAP *buttonImgSm = NULL;
	ALLEGRO_BITMAP *logo = NULL;
	ALLEGRO_BITMAP *contrArrows = NULL;
	ALLEGRO_BITMAP *contrSpace = NULL;

	ALLEGRO_SAMPLE *shot = NULL;
	ALLEGRO_SAMPLE *boom = NULL;
	ALLEGRO_SAMPLE *death = NULL;
	ALLEGRO_SAMPLE *song = NULL;
	ALLEGRO_SAMPLE *lost_song = NULL;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;

	ALLEGRO_FONT *arial_font12;
	ALLEGRO_FONT *arial_font18;
	ALLEGRO_FONT *arial_font28;

	ALLEGRO_FONT *pix_font12_rg;
	ALLEGRO_FONT *pix_font16_rg;
	ALLEGRO_FONT *pix_font18_rg;
	ALLEGRO_FONT *pix_font28_rg;

	ALLEGRO_FONT *pix_font12_b;
	ALLEGRO_FONT *pix_font18_b;
	ALLEGRO_FONT *pix_font28_b;

	
	ALLEGRO_MOUSE_STATE mouseState;
	
	// Init Allegro
	if(!al_init())
		return -1;

	display = al_create_display(WIDTH, HEIGHT);

	if(!display)
		return -1;

	al_set_window_title(display, "SpaceGame - By Ryan Thorn - v0.8");

	// Addon init and installs
	al_install_keyboard();
	al_install_mouse();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();

	// Init variables

	arial_font12 = al_load_font("media/font/arial.ttf", 12, 0);
	arial_font18 = al_load_font("media/font/arial.ttf", 18, 0);
	arial_font28 = al_load_font("media/font/arial.ttf", 28, 0);

	pix_font12_rg = al_load_font("media/font/pixarial_RG.ttf", 12, 0);
	pix_font16_rg = al_load_font("media/font/pixarial_RG.ttf", 16, 0);
	pix_font18_rg = al_load_font("media/font/pixarial_RG.ttf", 18, 0);
	pix_font28_rg = al_load_font("media/font/pixarial_RG.ttf", 28, 0);

	pix_font12_b = al_load_font("media/font/pixarial_B.ttf", 12, 0);
	pix_font18_b = al_load_font("media/font/pixarial_B.ttf", 18, 0);
	pix_font28_b = al_load_font("media/font/pixarial_B.ttf", 28, 0);

	al_reserve_samples(15);

	logo = al_load_bitmap("media/img/gamelogo.png");

	bgImage = al_load_bitmap("media/img/starBG.png");
	mgImage = al_load_bitmap("media/img/planets-nostar.png");
	fgImage = al_load_bitmap("media/img/starFG.png");
	
	contrArrows = al_load_bitmap("media/img/controlsARROWS.png");
	contrSpace = al_load_bitmap("media/img/controlsSPACE.png");

	healthbar_border = al_load_bitmap("media/img/healthbar_border.png");
	healthbar_bar = al_load_bitmap("media/img/healthbar_bar.png");
	top_bar = al_load_bitmap("media/img/top_bar.png");

	Background *bg = new Background(bgImage, 1);
	objects.push_back(bg);

	bg = new Background(mgImage, 2);
	objects.push_back(bg);

	bg = new Background(fgImage, 3);
	objects.push_back(bg);

	shipImage = al_load_bitmap("media/img/SpaceshipSprite.png");
	ship->Init(shipImage);

	objects.push_back(ship);

	cometImage = al_load_bitmap("media/img/comet.png");
	explImage = al_load_bitmap("media/img/explosion.png");

	titleImage = al_load_bitmap("media/img/1280x720-titlemenu.png");
	lostImage = al_load_bitmap("media/img/background.png");

	titleScreen = new Background(titleImage, 0);
	lostScreen = new Background(lostImage, 0);
	instrScreen = new Background(titleImage, 0);

	buttonImg = al_load_bitmap("media/img/button-main.png");
	buttonImgSm = al_load_bitmap("media/img/button-small.png");

	Bobbing *logoBob = new Bobbing((WIDTH / 2) - 412, 50, logo, 1, 20);
	Button *playBtn = new Button(buttonImg, pix_font28_b, "Play", (WIDTH / 2) - 256, 220, 512, 128, &BtnToPlay, true);
	Button *instrBtn = new Button(buttonImg, pix_font28_b, "Help", (WIDTH / 2) - 256, 378, 512, 128, &BtnToInstr, true);
	Button *quitBtn = new Button(buttonImg, pix_font28_b, "Quit", (WIDTH / 2) - 256, 536, 512, 128, &BtnToQuit, true);

	Button *BkToMenu = new Button(buttonImgSm, pix_font18_b, "Menu", 30, 630, 177, 66, &BtnToMenu, false);

	shot = al_load_sample("media/sound/laser_shot.ogg");
	boom = al_load_sample("media/sound/comet_explosion.ogg");
	death = al_load_sample("media/sound/death.ogg");
	song = al_load_sample("media/sound/darude.ogg");
	lost_song = al_load_sample("media/sound/loss-music.ogg");

	songInstance = al_create_sample_instance(song);
	al_set_sample_instance_gain(songInstance, 2);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_ONCE);
	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

	lossSongInst = al_create_sample_instance(lost_song);
	al_set_sample_instance_playmode(lossSongInst, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(lossSongInst, al_get_default_mixer());

	ChangeState(state, TITLE);

	srand(time(NULL));

	// Timer Init and Start

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	gameTime = al_current_time();
	initTime = al_current_time();
	while(!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		// User Inputs
		
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = true;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = true;
					break;
				case ALLEGRO_KEY_UP:
					keys[UP] = true;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = true;
					break;
				case ALLEGRO_KEY_SPACE:
					keys[SPACE] = true;
					if (state == TITLE) {
						ChangeState(state, PLAYING);
					} else if (state == PLAYING) {
						Bullet *bullet1 = new Bullet(ship->GetX() + 50, ship->GetY() - 22, &ScorePoint);
						Bullet *bullet2 = new Bullet(ship->GetX() + 38, ship->GetY() + 20, &ScorePoint);
						objects.push_back(bullet1);
						objects.push_back(bullet2);
						al_play_sample(shot, 0.6, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					}
					break;
				case ALLEGRO_KEY_F:
					if (state == LOST) {
						ChangeState(state, PLAYING);
					}
					break;
				case ALLEGRO_KEY_F1:
					if (state == PLAYING) {
						showColBox = !showColBox;
					}
					break;

			}
		} else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = false;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = false;
					break;
				case ALLEGRO_KEY_UP:
					keys[UP] = false;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = false;
					break;
				case ALLEGRO_KEY_SPACE:
					keys[SPACE] = false;
					break;
			}
		} else if(ev.type == ALLEGRO_EVENT_TIMER) {
			// Update Game Objs
			render = true;
			frames++;
			al_get_mouse_state(&mouseState);
			
			if (elapsedTime >= 225 && hasFinished == false){
				hasFinished = true;
				std::cout << "Debug: Game Finished Sequence Began." << std::endl;
			}

			if (elapsedTime >= 230 && elapsedTime <= 232 && hasFinished){
				ChangeState(state, WIN);
			}

			if (al_current_time() - gameTime >= 1) {
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}

			if (state == PLAYING) {
				elapsedTime = roundf((al_current_time() - stateTime) * 100) / 100;
				if (!hasFinished){
					if (keys[UP])
						ship->MoveUp();
					else if (keys[DOWN])
						ship->MoveDown();
					else {
							ship->ResetAnimation(1);
					}

					if (keys[LEFT])
						ship->MoveLeft();
					else if (keys[RIGHT])
						ship->MoveRight();
					else {
							ship->ResetAnimation(0);
					}
				} else {
					
					ship->MoveOffScreen();
				}
				size_t spawnTimesSize = sizeof(spawnTimes) / sizeof(int);
				float *end = spawnTimes + spawnTimesSize;

				auto it = std::find(spawnTimes, end, elapsedTime);
				if (it >= end) {
				} else {
					if ((bool)hasSpawned[it - spawnTimes] == false) {
						Comet *comet = new Comet(WIDTH, 100 + rand() % (HEIGHT - 110), cometImage, &TakeLife);
						objects.push_back(comet);

						hasSpawned[it - spawnTimes] = true;
						numSpawned++;
					} else {
						std::cout << "Already Spawned" << std::endl;
					}
				}

				// updates and collisions
				for (iter = objects.begin(); iter != objects.end(); ++iter) {
					(*iter)->Update();
				}
					
				for(iter = objects.begin(); iter != objects.end(); ++iter) {
					if (!(*iter)->Collidable()) {
						continue;
					}

					for(iter2 = iter; iter2 != objects.end(); ++iter2) {
						if (!(*iter2)->Collidable()) {
							continue;
						}
						
						if ((*iter)->GetID() == (*iter2)->GetID()) {
							continue;
						}

						if ((*iter)->CheckCollisions((*iter2))) {
							(*iter)->Collided((*iter2)->GetID());
							(*iter2)->Collided((*iter)->GetID());

							Explosion *explosion = new Explosion(((*iter)->GetX() + (*iter2)->GetX()) / 2, ((*iter)->GetY() + (*iter2)->GetY()) / 2, explImage);

							objects.push_back(explosion);
							al_play_sample(boom, 0.6, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						}
					}
				}

				if (ship->GetLives() <= 0) {
					al_play_sample(death, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					ChangeState(state, LOST);
				}
			} else if (state == TITLE){
				playBtn->Update(mouseState);
				quitBtn->Update(mouseState);
				instrBtn->Update(mouseState);
				logoBob->Update();
			} else if (state == INSTRUCTIONS) {
				BkToMenu->Update(mouseState);
			}

			// delete dead objects
			for(iter = objects.begin(); iter != objects.end(); ) {
				if(! (*iter)->GetAlive()) {
					delete (*iter);
					iter = objects.erase(iter);
				} else {
					iter++;
				}
			}
		}

		// Rendering of game
		if(render && al_is_event_queue_empty(event_queue)) {
			render = false;
			if(state == TITLE) {
				titleScreen->Render();
				playBtn->Render();
				quitBtn->Render();
				instrBtn->Render();
				logoBob->Render();
				
			} else if(state == PLAYING) {
				for (iter = objects.begin(); iter != objects.end(); ++iter) {
					(*iter)->Render();
					if (showColBox)
						(*iter)->ToggleRenderColBox();
				}
				al_draw_scaled_bitmap(top_bar, 0, 0, 640, 30, 0, 0, 1280, 60, 0);
				DrawPercentBar(70, 10, 290, 30, ship->GetLifePercent(), healthbar_border, healthbar_bar, pix_font12_rg);
				al_draw_textf(pix_font16_rg, al_map_rgb(200, 200, 200), WIDTH - 205, 14, 0, "Time: %i", (int)round(elapsedTime));
				al_draw_textf(pix_font16_rg, al_map_rgb(200, 200, 200), WIDTH - 410, 14, 0, "Score: %i", ship->GetScore());
				al_draw_textf(pix_font16_rg, al_map_rgb(200, 200, 200), WIDTH / 2, 14, 0, "Spawned: %i", numSpawned);
				al_draw_textf(pix_font16_rg, al_map_rgb(200, 200, 200), WIDTH / 2, 40, 0, "Killed: %i", numKilled);
				al_draw_textf(pix_font16_rg, al_map_rgb(200, 200, 200), WIDTH / 2, 60, 0, "Missed: %i", numMissed);
				if ((elapsedTime > 29 && elapsedTime < 85) || (elapsedTime > 150 && elapsedTime < 220)){
					camAng += 0.1;
					if (camAng >= 0.1){
						camAng = 0.0;
					}
					else {
						camAng = 0.1;
					}
					if (camX == 0){
						camX = 5;
					}
					else if (camX == 5) {
						camX = 0;
					}
					if (camY == 0){
						camY = 5;
					}
					else if (camY == 5) {
						camY = 0;
					}
				}
				else {
					camAng = 0;
					camX = 0;
					camY = 0;
				}

				al_identity_transform(&cam);
				al_translate_transform(&cam, -(WIDTH / 2) + camX, -(HEIGHT / 2) + camY);
				al_rotate_transform(&cam, camAng);
				al_translate_transform(&cam, WIDTH / 2, HEIGHT / 2);
				al_use_transform(&cam);

			} else if(state == LOST) {
				lostScreen->Render();
			} else if (state == WIN) {
				al_draw_textf(pix_font18_b, al_map_rgb(255, 255, 255), WIDTH / 2 - 200, HEIGHT / 2, 0, "You won with a score of %i", ship->GetScore());
				al_draw_textf(pix_font18_b, al_map_rgb(255, 255, 255), WIDTH / 2 - 180, HEIGHT / 2 + 25, 0, "You lasted %f seconds", elapsedTime);
				al_draw_text(pix_font18_b, al_map_rgb(255, 0, 0), WIDTH - 600, HEIGHT - 25, 0, "This win screen is temporary");
			} else if (state == INSTRUCTIONS) {
				instrScreen->Render();
				al_draw_text(pix_font28_b, al_map_rgb(255, 255, 255), 30, 30, 0, "Instructions");
				al_draw_bitmap(contrArrows, 200, 230, 0);
				al_draw_text(pix_font18_b, al_map_rgb(255, 255, 255), 331, 430, ALLEGRO_ALIGN_CENTRE, "Use the                   to move the ship!");
				al_draw_text(pix_font18_b, al_map_rgb(200, 0, 0), 190, 430, 0, "Arrow Keys");

				al_draw_bitmap(contrSpace, 750, 280, 0);
				al_draw_text(pix_font18_b, al_map_rgb(255, 255, 255), 750 + 173, 430, ALLEGRO_ALIGN_CENTRE, "Use the                  to fire the guns!");
				al_draw_text(pix_font18_b, al_map_rgb(200, 0, 0), 798, 430, 0, "Space Key");

				BkToMenu->Render();
			}
			
			al_draw_textf(pix_font12_rg, al_map_rgb(255, 255, 255), WIDTH - 80, HEIGHT - 50, 0, "FPS: %i", gameFPS);
			
			// Flip the buffer
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}

	// End of game loop clean up process
	for(iter = objects.begin(); iter != objects.end(); ) {
		(*iter)->Destroy();
		delete (*iter);
		iter = objects.erase(iter);
	}

	lostScreen->Destroy();
	titleScreen->Destroy();

	playBtn->Destroy();
	quitBtn->Destroy();
	instrBtn->Destroy();
	BkToMenu->Destroy();
	logoBob->Destroy();
	
	delete lostScreen;
	delete titleScreen;
	
	//al_destroy_bitmap(mgImage);
	al_destroy_bitmap(fgImage);
	al_destroy_bitmap(bgImage);
	al_destroy_bitmap(explImage);
	al_destroy_bitmap(shipImage);
	al_destroy_bitmap(cometImage);
	al_destroy_bitmap(titleImage);
	al_destroy_bitmap(lostImage);
	al_destroy_bitmap(buttonImg);
	
	al_destroy_sample(boom);
	al_destroy_sample(song);
	al_destroy_sample(lost_song);
	al_destroy_sample(shot);
	al_destroy_sample(death);
	
	al_destroy_sample_instance(lossSongInst);
	al_destroy_sample_instance(songInstance);

	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	
	al_destroy_font(arial_font12);
	al_destroy_font(arial_font18);
	al_destroy_font(arial_font28);

	al_destroy_font(pix_font12_rg);
	al_destroy_font(pix_font16_rg);
	al_destroy_font(pix_font18_rg);
	al_destroy_font(pix_font28_rg);

	al_destroy_font(pix_font12_b);
	al_destroy_font(pix_font18_b);
	al_destroy_font(pix_font28_b);

	return 0;
}

// Misc functions

void __cdecl TakeLife() {
	numMissed++;
	ship->LoseLife();
}

void __cdecl ScorePoint() {
	numKilled++;
	ship->AddPoint();
}

void __cdecl BtnToPlay() {
	ChangeState(state, PLAYING);
}

void __cdecl BtnToQuit() {
	done = true;
}

void __cdecl BtnToInstr() {
	ChangeState(state, INSTRUCTIONS);
}

void __cdecl BtnToMenu() {
	ChangeState(state, TITLE);
}

void ChangeState(int &state, int newState) {
	std::cout << "Debug: GameState has been changed from " << state << " to " << newState << std::endl;
	stateTime = al_current_time();
	if(state == TITLE) {
	
	} else if(state == PLAYING) {
		for(iter = objects.begin(); iter != objects.end(); ++iter) {
			if ((*iter)->GetID() != PLAYER && (*iter)->GetID() != MISC) {
				(*iter)->SetAlive(false);
			}
		}
		al_stop_sample_instance(songInstance);
	} else if(state == LOST) {
	
	}

	state = newState;
	
	if(state == TITLE){
	
	} else if(state == PLAYING) {
		for (int i = 0; i < TOTAL_SPAWNS; i++){
			hasSpawned[i] = false;
		}
		numSpawned = 0;
		numKilled = 0;
		numMissed = 0;

		ship->Init();
		al_stop_sample_instance(lossSongInst);
		al_play_sample_instance(songInstance);
		
	} else if(state == LOST) {
		al_stop_sample_instance(songInstance);
		al_play_sample_instance(lossSongInst);
	}
}

void DrawPercentBar(int x, int y, int w, int h, float percent, ALLEGRO_BITMAP * border, ALLEGRO_BITMAP * bar, ALLEGRO_FONT* font) {
	al_draw_bitmap_region(bar, 0, 0, 5 + ((w) * percent / 100), y + h, x, y, 0);
	al_draw_bitmap(border, x, y, 0);
	al_draw_textf(font, al_map_rgb(255, 255, 255), x + w / 2, y + h / 2 - 8, ALLEGRO_ALIGN_CENTRE, "%i%%", (int)round(percent));
}
