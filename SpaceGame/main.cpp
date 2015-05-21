
// All the main includes to run the game.
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

// Our custom classes includes.
#include "GameObject.h"
#include "SpaceShip.h"
#include "Bullet.h"
#include "Comet.h"
#include "Explosion.h"
#include "Background.h"
#include "Globals.h"
#include "Button.h"
#include "Bobbing.h"

// Our global keys array and enum. This will let us know if the key is pressed down or not.
bool keys[] = { false, false, false, false, false };
enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE };

// This is a constant that is the total amount of comets that will ever spawn
const int TOTAL_SPAWNS = 807;
// These are our comet spawn times. We look at the games elapsed time and spawn a comet at this time
// These times are matched to the bassline of our song. If I had time, I would do away with this array 
// and build in the song analysis into the code, for now though I just used Audacities analysis tools
// to get the correct timings.
float spawnTimes[TOTAL_SPAWNS] = { 0.91, 0.95, 0.99, 1.04, 1.08, 1.10, 14.57, 14.62, 
								   14.74, 14.77, 15.03, 15.06, 15.10, 15.19, 22.07, 
								   22.11, 22.15, 22.24, 29.13, 29.19, 29.21, 29.23, 
								   29.54, 29.57, 29.61, 30.01, 30.02, 30.03, 30.07, 
								   30.46, 30.53, 30.90, 31.34, 31.79, 31.85, 32.23, 
								   32.61, 32.65, 32.76, 33.10, 33.54, 33.61, 33.98, 
								   33.99, 34.07, 34.42, 34.43, 34.52, 34.82, 34.83, 
								   34.86, 35.27, 35.30, 35.31, 35.40, 35.75, 35.85, 
								   35.96, 35.99, 36.19, 36.26, 36.63, 36.73, 37.07, 
								   37.14, 37.51, 37.95, 38.39, 38.46, 38.49, 38.84, 
								   39.27, 39.71, 39.81, 40.16, 40.62, 40.69, 41.04, 
								   41.48, 41.51, 41.92, 41.99, 42.35, 42.43, 42.45, 
								   42.80, 42.87, 43.04, 43.09, 43.24, 43.68, 43.76, 
								   44.12, 44.56, 44.66, 45.00, 45.01, 45.10, 45.45, 
								   45.89, 45.98, 46.32, 46.42, 46.72, 46.73, 46.77, 
								   47.21, 47.65, 48.09, 48.53, 48.97, 49.42, 49.85, 
								   49.95, 50.07, 50.08, 50.13, 50.30, 50.31, 50.73, 
								   50.83, 51.14, 51.17, 51.62, 52.05, 52.50, 52.59, 
								   52.94, 53.03, 53.38, 53.77, 53.82, 54.26, 54.71, 
								   55.14, 55.24, 55.59, 56.02, 56.46, 56.56, 56.91, 
								   57.00, 57.12, 57.35, 57.44, 57.79, 58.23, 58.32,
								   58.67, 59.11, 59.55, 59.65, 60.00, 60.44, 60.83, 
								   60.84, 60.87, 61.31, 61.39, 61.75, 61.83, 62.20, 
								   62.64, 63.07, 63.17, 63.52, 63.59, 63.97, 63.98, 
								   64.19, 64.20, 64.41, 64.85, 65.28, 65.73, 65.74, 
								   65.80, 66.17, 66.61, 66.70, 67.01, 67.04, 67.48, 
								   67.58, 67.93, 68.00, 68.38, 68.82, 69.25, 69.35, 
								   69.69, 70.14, 70.23, 70.57, 71.02, 71.23, 71.31, 
								   71.46, 71.90, 71.99, 72.33, 72.39, 72.41, 72.43, 
								   72.78, 72.87, 73.19, 73.22, 73.31, 73.66, 73.66, 
								   74.10, 74.55, 74.56, 74.58, 74.95, 74.98, 75.39, 
								   75.42, 75.86, 76.30, 76.71, 76.74, 76.80, 76.82, 
								   76.84, 77.18, 77.63, 77.70, 78.06, 78.29, 78.32, 
								   78.36, 78.52, 78.58, 78.95, 79.04, 79.40, 79.44, 
								   79.47, 79.83, 80.27, 80.71, 80.78, 81.15, 81.21, 
								   81.23, 81.60, 81.67, 82.04, 82.06, 82.48, 82.53, 
								   82.55, 82.92, 82.92, 83.37, 83.38, 83.41, 83.43, 
								   83.81, 83.87, 84.06, 84.09, 84.12, 84.26, 84.28, 
								   84.30, 84.32, 84.50, 84.70, 84.94, 84.98, 85.00, 
								   85.14, 85.16, 85.18, 85.20, 85.37, 85.38, 85.40, 
								   85.42, 85.56, 85.61, 92.60, 92.62, 92.65, 92.77, 
								   94.36, 94.39, 94.41, 94.50, 94.54, 94.56, 95.05, 
								   95.08, 95.20, 95.23, 95.71, 95.74, 95.76, 95.78, 
								   95.86, 96.15, 96.18, 96.20, 96.22, 96.30, 99.66, 
								   99.76, 99.84, 113.35, 113.38, 113.41, 113.50, 113.55, 
								   113.58, 113.59, 113.63, 113.77, 113.81, 113.83, 113.86, 
								   113.87, 120.81, 120.81, 120.86, 120.89, 120.97, 120.98, 
								   127.43, 127.46, 127.50, 127.58, 127.64, 127.72, 127.86, 
								   127.91, 149.03, 149.06, 149.12, 149.48, 149.51, 149.93, 
								   149.97, 150.36, 150.39, 150.43, 150.80, 150.81, 150.83, 
								   150.85, 150.87, 151.25, 151.27, 151.67, 151.69, 152.12, 
								   152.14, 152.15, 152.17, 152.52, 152.56, 152.58, 152.99, 
								   153.07, 153.39, 153.44, 153.47, 153.49, 153.51, 153.88, 
								   153.93, 154.33, 154.34, 154.41, 154.43, 154.78, 154.80, 
								   155.17, 155.21, 155.65, 155.70, 155.87, 156.10, 156.11, 
								   156.16, 156.53, 156.58, 156.97, 157.00, 157.02, 157.04, 
								   157.41, 157.86, 157.92, 158.31, 158.74, 158.75, 158.78, 
								   159.18, 159.19, 159.22, 159.24, 159.62, 159.66, 159.68, 
								   160.06, 160.07, 160.50, 160.57, 160.94, 161.01, 161.38, 
								   161.39, 161.41, 161.82, 161.85, 161.87, 162.26, 162.26, 
								   162.31, 162.70, 162.75, 162.92, 162.94, 162.95, 162.97, 
								   162.99, 163.16, 163.17, 163.60, 163.63, 163.65, 164.04, 
								   164.06, 164.07, 164.47, 164.48, 164.91, 164.97, 165.35, 
								   165.79, 166.23, 166.28, 166.67, 166.74, 167.11, 167.16, 
								   167.18, 167.56, 167.98, 168.04, 168.45, 168.88, 168.92, 
								   169.32, 169.76, 169.79, 169.97, 169.99, 170.02, 170.20,
								   170.21, 170.23, 170.25, 170.27, 170.29, 170.63, 170.65, 
								   170.71, 171.08, 171.09, 171.11, 171.13, 171.52, 171.96,
								   172.40, 172.41, 172.85, 172.86, 172.87, 173.29, 173.34, 
								   173.35, 173.38, 173.73, 173.79, 174.17, 174.20, 174.21,
								   174.60, 174.61, 174.68, 175.08, 175.10, 175.12, 175.14, 
								   175.49, 175.50, 175.93, 175.96, 175.98, 176.00, 176.38, 
								   176.42, 177.10, 177.29, 177.30, 177.70, 177.74, 178.15, 
								   178.16, 178.18, 178.61, 178.63, 178.64, 179.02, 179.08, 
								   179.11, 179.46, 179.47, 179.49, 179.90, 180.33, 180.39, 
								   180.78, 180.85, 181.24, 181.66, 181.73, 182.12, 182.55, 
								   182.57, 182.98, 183.03, 183.42, 183.44, 183.47, 183.50, 
								   183.52, 183.54, 183.90, 183.93, 184.10, 184.13, 184.16, 
								   184.32, 184.34, 184.78, 184.82, 185.15, 185.19, 185.20, 
								   185.22, 185.24, 185.26, 185.63, 185.70, 186.07, 186.12, 
								   186.14, 186.51, 186.53, 186.58, 186.96, 186.98, 187.43, 
								   187.82, 187.88, 188.28, 188.31, 188.32, 188.72, 188.77, 
								   188.79, 189.16, 189.17, 189.60, 189.65, 189.69, 189.71,
								   189.85, 189.87, 189.89, 190.05, 190.29, 190.33, 190.75,
								   190.77, 190.94, 191.18, 191.21, 191.38, 191.39, 191.85,
								   191.87, 191.90, 192.26, 192.70, 192.75, 193.14, 193.15, 
								   193.58, 194.01, 194.02, 194.04, 194.07, 194.48, 194.50,
								   194.82, 194.89, 194.90, 194.92, 194.94, 194.96, 194.98,
								   195.32, 195.36, 195.38, 195.40, 195.79, 196.21, 196.23, 
								   196.65, 196.70, 196.72, 196.74, 196.76, 197.11, 197.14, 
								   197.54, 197.99, 198.04, 198.19, 198.43, 198.45, 198.47, 
								   198.49, 198.87, 198.89, 199.31, 199.37, 199.74, 199.79, 
								   199.81, 200.18, 200.19, 200.25, 200.62, 200.65, 200.67, 
								   201.06, 201.13, 201.50, 201.55, 201.96, 201.97, 202.01, 
								   202.39, 202.43, 202.45, 202.83, 202.86, 202.88, 202.90,
								   203.27, 203.30, 203.31, 203.72, 203.82, 203.84, 204.15,
								   204.18, 204.22, 204.59, 205.03, 205.25, 205.49, 205.52,
								   205.54, 205.91, 205.93, 206.35, 206.38, 206.40, 206.42,
								   206.79, 206.81, 206.87, 207.24, 207.30, 207.67, 208.12, 
								   208.17, 208.56, 209.00, 209.01, 209.05, 209.07, 209.44,
								   209.53, 209.90, 209.95, 210.34, 210.39, 210.78, 210.79,
								   210.81, 210.83, 211.20, 211.22, 211.25, 211.27, 211.66, 
								   211.67, 211.69, 211.71, 211.73, 211.75, 211.78, 212.10,
								   212.12, 212.13, 212.34, 212.53, 212.54, 212.56, 212.58,
								   212.60, 212.98, 213.02, 213.04, 213.41, 213.44, 213.47,
								   213.87, 213.90, 214.29, 214.36, 214.74, 215.20, 215.61,
								   215.68, 215.70, 216.05, 216.07, 216.10, 216.50, 216.54,
								   216.56, 216.94, 216.95, 216.97, 217.00, 217.37, 217.43,
								   217.45, 217.85, 218.27, 218.29, 218.75, 218.77, 219.15,
								   219.15, 219.19, 219.37, 219.43, 219.57, 219.59, 219.75 };
// An array that stores true or false if that comet at that time has spawned
float hasSpawned[TOTAL_SPAWNS] = { };
// The number of comets spawned
int numSpawned = 0;
// The number of comets the player has killed
int numKilled = 0;
// The number of comets the player has missed
int numMissed = 0;

// Our main game objects
SpaceShip *ship;							// The players ship
std::list<GameObject *> objects;			// A list of game objects to be looped through to render and update
std::list<GameObject *>::iterator iter;		// A iterator list used to loop through our game objects
std::list<GameObject *>::iterator iter2;	// Second iterator used for collisions between two game objects
Background *titleScreen;					// Our Title Screen background object
Background *lostScreen;						// Our Lost Screen background object
Background *wonScreen;						// Our Won Screen background object
Background *instrScreen;					// Our Instruction Screen background object
ALLEGRO_SAMPLE_INSTANCE *songInstance;		// The song instance for the song playing in the PLAYING state
ALLEGRO_SAMPLE_INSTANCE *lossSongInst;		// The song instance for the song playing in the LOST state

bool hasFinished = false;					// A bool which indicates whether the player has completed the required stages for the game
float stateTime = 0;						// The system time where the player enters a different state. Used to calculated the PLAYING states elapsedTime
float elapsedTime = 0;		// The amount of time that has passed since the player began the PLAYING state
// Init state as -1 which is effectively no state
int state = -1;
// This is our done variable which when true will exit the game loop
bool done = false;
// Main prototype functions, we do this so they are present for usage throughout the code
void __cdecl TakeLife();	// Takes life from player, this is passed into our comet object when init
void __cdecl ScorePoint();	// Scores a point for the player, this is passed into our bullet object
void __cdecl BtnToPlay();	// The function that occurs when the play button is pressed, passed into the play button object
void __cdecl BtnToQuit();	// The function that occurs when the quit button is pressed, passed into the quit button object
void __cdecl BtnToInstr();	// The function that occurs when the help button is pressed, passed into the help button object
void __cdecl BtnToMenu();	// The function that occurs when the menu button is pressed, passed into the menu button object

// Our ChangeState prototype
void ChangeState(int &state, int newState);
// Our DrawPercentBar prototype
void DrawPercentBar(int x, int y, int w, int h, float percent, ALLEGRO_BITMAP * border, ALLEGRO_BITMAP * bar, ALLEGRO_FONT* font);

// Variables to store information about our camera postion and rotation
int camX = 0, camY = 0;
float camAng = 0.0;
// Our camera object
ALLEGRO_TRANSFORM cam;

// The main function!
int main(int argc, char **argv) {
	
	// Here we setup our hasSpawned array to have false for every comet timing.
	for (int i = 0; i < TOTAL_SPAWNS; i++){
		hasSpawned[i] = false;
	}

	// Local variables
	bool render = false;		// Whether we should render or not
	bool showColBox = false;	// Whether to render collision boxes around GameObjects

	int frames = 0;				// Amount of frames that have been rendered
	int gameFPS = 0;			// The current game FPS, calculated using gameTime and frames
	float gameTime = 0;			// The current gameTime from initialisation
	
	// Our ship object (A.K.A the player object)
	ship = new SpaceShip();	

	// Allegro Variables
	ALLEGRO_BITMAP *shipImage = NULL;			// The bitmap that stores our ship image
	ALLEGRO_BITMAP *cometImage = NULL;			// The bitmap that stores our comet image
	ALLEGRO_BITMAP *explImage = NULL;			// The bitmap that stores our explosion image
	ALLEGRO_BITMAP *bgImage = NULL;				// The bitmap that stores our background image 
	ALLEGRO_BITMAP *mgImage = NULL;				// The bitmap that stores our midground image
	ALLEGRO_BITMAP *fgImage = NULL;				// The bitmap that stores our foreground image
	ALLEGRO_BITMAP *titleImage = NULL;			// The bitmap that stores our title image
	ALLEGRO_BITMAP *lostImage = NULL;			// The bitmap that stores our lost image
	ALLEGRO_BITMAP *wonImage = NULL;			// The bitmap that stores our won image
	ALLEGRO_BITMAP *healthbar_border = NULL;	// The bitmap that stores our healthbar border
	ALLEGRO_BITMAP *healthbar_bar = NULL;		// The bitmap that stores our healthbar bar
	ALLEGRO_BITMAP *top_bar = NULL;				// The bitmap that stores our top_bar image
	ALLEGRO_BITMAP *buttonImg = NULL;			// The bitmap that stores our main button image
	ALLEGRO_BITMAP *buttonImgSm = NULL;			// The bitmap that stores our small button image
	ALLEGRO_BITMAP *logo = NULL;				// The bitmap that stores our logo image
	ALLEGRO_BITMAP *contrArrows = NULL;			// The bitmap that stores our arrow keys image
	ALLEGRO_BITMAP *contrSpace = NULL;			// The bitmap that stores our spacebar image

	ALLEGRO_SAMPLE *shot = NULL;				// This stores the sound sample for our shooting sound
	ALLEGRO_SAMPLE *boom = NULL;				// This stores the sound sample for our comet death sound
	ALLEGRO_SAMPLE *death = NULL;				// This stores the sound sample for our player death sound
	ALLEGRO_SAMPLE *song = NULL;				// This stores the sound sample for our PLAYING state song
	ALLEGRO_SAMPLE *lost_song = NULL;			// This stores the sound sample for our LOST state song

	ALLEGRO_DISPLAY *display = NULL;			// Stores the allegro display
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;	// Stores our event queue
	ALLEGRO_TIMER *timer;						// Stores our timer

	ALLEGRO_FONT *arial_font12;					// Stores our fonts
	ALLEGRO_FONT *arial_font18;					// Stores our fonts
	ALLEGRO_FONT *arial_font28;					// Stores our fonts

	ALLEGRO_FONT *pix_font12_rg;				// Stores our fonts
	ALLEGRO_FONT *pix_font16_rg;				// Stores our fonts
	ALLEGRO_FONT *pix_font18_rg;				// Stores our fonts
	ALLEGRO_FONT *pix_font28_rg;				// Stores our fonts

	ALLEGRO_FONT *pix_font12_b;					// Stores our fonts
	ALLEGRO_FONT *pix_font18_b;					// Stores our fonts
	ALLEGRO_FONT *pix_font28_b;					// Stores our fonts

	
	ALLEGRO_MOUSE_STATE mouseState;				// Stores our mouse state
	
	// Init Allegro
	if(!al_init())
		return -1;	// returns -1 which means an error occured.

	// Create our display
	display = al_create_display(WIDTH, HEIGHT);

	if(!display)
		return -1;	// return -1 if we cannot create our display

	// The title of our game window at the top.
	al_set_window_title(display, "SpaceGame - By Ryan Thorn - v0.9");

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

	// Here we load all our fonts into their respective variables
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

	// Here we reserve the samples in our mixer for our game soudns
	al_reserve_samples(15);

	// Loading the logo image
	logo = al_load_bitmap("media/img/gamelogo.png");

	// Loading the background, midground and foreground images
	bgImage = al_load_bitmap("media/img/starBG.png");
	mgImage = al_load_bitmap("media/img/planets-nostar.png");
	fgImage = al_load_bitmap("media/img/starFG.png");
	
	// Loading our help images
	contrArrows = al_load_bitmap("media/img/controlsARROWS.png");
	contrSpace = al_load_bitmap("media/img/controlsSPACE.png");

	// Our healthbar and top bar image
	healthbar_border = al_load_bitmap("media/img/healthbar_border.png");
	healthbar_bar = al_load_bitmap("media/img/healthbar_bar.png");
	top_bar = al_load_bitmap("media/img/top_bar.png");

	// here we create our background objects and push them into our objects list
	Background *bg = new Background(bgImage, 1);
	objects.push_back(bg);

	bg = new Background(mgImage, 2);
	objects.push_back(bg);

	bg = new Background(fgImage, 3);
	objects.push_back(bg);

	// Here we load our spaceship sprite
	shipImage = al_load_bitmap("media/img/SpaceshipSprite.png");
	// We then init our spaceship object
	ship->Init(shipImage);
	// and then we push it into the objects list
	objects.push_back(ship);

	// Here we load the rest of the images in our game
	cometImage = al_load_bitmap("media/img/comet.png");
	explImage = al_load_bitmap("media/img/explosion.png");

	titleImage = al_load_bitmap("media/img/1280x720-titlemenu.png");
	lostImage = al_load_bitmap("media/img/lostScreen.png");
	wonImage = al_load_bitmap("media/img/wonScreen.png");

	buttonImg = al_load_bitmap("media/img/button-main.png");
	buttonImgSm = al_load_bitmap("media/img/button-small.png");

	// Here we create new Background objects for our different screens
	titleScreen = new Background(titleImage, 0);
	lostScreen = new Background(lostImage, 0);
	wonScreen = new Background(wonImage, 0);
	instrScreen = new Background(titleImage, 0);

	// This is making use of our bobbing class, we specify the x and y that the object will begin at
	// we then specify the image we want to bob up an ddown, and then put the step amount and size for the
	// sine wave used to create the bobbing effect.
	Bobbing *logoBob = new Bobbing((WIDTH / 2) - 412, 50, logo, 1, 20);
	
	// Here we create our different buttons that are used throughout the game
	Button *playBtn = new Button(buttonImg, pix_font28_b, "Play", (WIDTH / 2) - 256, 220, 512, 128, &BtnToPlay, true);
	Button *instrBtn = new Button(buttonImg, pix_font28_b, "Help", (WIDTH / 2) - 256, 378, 512, 128, &BtnToInstr, true);
	Button *quitBtn = new Button(buttonImg, pix_font28_b, "Quit", (WIDTH / 2) - 256, 536, 512, 128, &BtnToQuit, true);
	Button *BkToMenu = new Button(buttonImgSm, pix_font18_b, "Menu", 30, 630, 177, 66, &BtnToMenu, false);

	// Here we load all the different sounds for our game into their variables
	shot = al_load_sample("media/sound/laser_shot.ogg");
	boom = al_load_sample("media/sound/comet_explosion.ogg");
	death = al_load_sample("media/sound/death.ogg");
	song = al_load_sample("media/sound/darude.ogg");
	lost_song = al_load_sample("media/sound/loss-music.ogg");

	// We now create the songInstance for our PLAYING state song and LOST state song
	songInstance = al_create_sample_instance(song);
	al_set_sample_instance_gain(songInstance, 2);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_ONCE);
	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

	lossSongInst = al_create_sample_instance(lost_song);
	al_set_sample_instance_playmode(lossSongInst, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(lossSongInst, al_get_default_mixer());

	// We then change the state to TITLE 
	ChangeState(state, TITLE);

	// We seed our random function
	srand(time(NULL));

	// Timer Init and Start
	// We create our event queue and our timer which is locked to our framerate of 100fps
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	// We register two events, one is the timer event source and the other is the keyboard event
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	// We then start the timer, get the gameTime
	al_start_timer(timer);
	gameTime = al_current_time();
	
	/*********
	 MAIN GAME LOOP
	 *********/
	while(!done) {
		// Our event storage
		ALLEGRO_EVENT ev;
		// We wait for an event to occur
		al_wait_for_event(event_queue, &ev);
		
		// User Inputs 
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			// We switch the different keycodes that could be currently pressed
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
						// If we are in the TITLE state, pressing space will change the state to PLAYING
						ChangeState(state, PLAYING);
					} else if (state == PLAYING) {
						// If we are in the PLAYING state, pressing space will fire a bullet
						Bullet *bullet1 = new Bullet(ship->GetX() + 38, ship->GetY() - 22, &ScorePoint);
						Bullet *bullet2 = new Bullet(ship->GetX() + 38, ship->GetY() + 20, &ScorePoint);
						objects.push_back(bullet1);
						objects.push_back(bullet2);
						// Play our sound for the bullet
						al_play_sample(shot, 0.6, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					}
					break;
				case ALLEGRO_KEY_F:
					if (state == LOST) {
						// If in LOST state then change to PLAYING state
						ChangeState(state, PLAYING);
					}
					if (state == WIN) {
						// If in WIN state then change to PLAYING state
						ChangeState(state, PLAYING);
					}
					break;
				case ALLEGRO_KEY_F1:
					// Display the collision boxes for GameObjects
					if (state == PLAYING) {
						showColBox = !showColBox;
					}
					break;

			}
		} else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			// Check for the key up to let us know when a player releases the key
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
			render = true;	// We now allow rendering
			frames++;		// Plus our frames
			al_get_mouse_state(&mouseState);	//get our current mouse state
			
			// If the player reaches 225 seconds in and they have not already finished, set the game to finished
			if (elapsedTime >= 225 && hasFinished == false){
				hasFinished = true;
				std::cout << "Debug: Game Finished Sequence Began." << std::endl;
			}

			// After 230 seconds we will finish the game by changing the state to the WIN state
			if (elapsedTime >= 230 && elapsedTime <= 232 && hasFinished){
				ChangeState(state, WIN);
			}

			// here we calculate the current frames per second
			if (al_current_time() - gameTime >= 1) {
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}

			if (state == PLAYING) {
				// Here we calculate our elapsedTime
				elapsedTime = roundf((al_current_time() - stateTime) * 100) / 100;
				// if the player has not finished, let them have control of the spaceship
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
					// This will move the ship off the screen which occurs when the player has finished the game.
					ship->MoveOffScreen();
				}
				// This section of code finds a specific spawn time in our spawnTimes array based on the current elapsedTime
				size_t spawnTimesSize = sizeof(spawnTimes) / sizeof(int);
				float *end = spawnTimes + spawnTimesSize;
				// So if our elapsedTime == a time inside our spawnTimes array, and that time has not already spawned, then spawn a comet
				auto it = std::find(spawnTimes, end, elapsedTime);
				if (it >= end) {
				} else {
					if ((bool)hasSpawned[it - spawnTimes] == false) {
						Comet *comet = new Comet(WIDTH + (rand() % 30), 100 + rand() % (HEIGHT - 110), cometImage, &TakeLife);
						objects.push_back(comet);

						hasSpawned[it - spawnTimes] = true;
						numSpawned++;
					} else {
						std::cout << "Already Spawned" << std::endl;
					}
				}

				// Our updates and collision detection
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
							// Create an explosion because a comet has exploded.
							Explosion *explosion = new Explosion(((*iter)->GetX() + (*iter2)->GetX()) / 2, ((*iter)->GetY() + (*iter2)->GetY()) / 2, explImage);

							objects.push_back(explosion);
							// Play our comet explosion sound
							al_play_sample(boom, 0.6, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						}
					}
				}

				if (ship->GetLives() <= 0) {
					// If the players lives reach less than or equal to 0, the player has died and lost the game.
					al_play_sample(death, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					ChangeState(state, LOST);
				}
			} else if (state == TITLE){
				// Our updates for the buttons and logo on the TITLE state
				playBtn->Update(mouseState);
				quitBtn->Update(mouseState);
				instrBtn->Update(mouseState);
				logoBob->Update();
			} else if (state == INSTRUCTIONS) {
				// Our update for the back to menu button on the instructions screen.
				BkToMenu->Update(mouseState);
			}

			// Here we run through all the objects inside our objects list and delete them if they are dead
			// It frees up memory and prevents memory leaks.
			for(iter = objects.begin(); iter != objects.end(); ) {
				if(! (*iter)->GetAlive()) {
					delete (*iter);
					iter = objects.erase(iter);
				} else {
					iter++;
				}
			}
		}

		// Here we perform the rendering of the game.
		if(render && al_is_event_queue_empty(event_queue)) {
			// if rendering is true and the event queue is empty, start rendering.
			render = false;	// Set rendering false, so it only renders once the updates have occured
			if(state == TITLE) {
				// Rendering of our TITLE state
				titleScreen->Render();
				playBtn->Render();
				quitBtn->Render();
				instrBtn->Render();
				logoBob->Render();
				
			} else if(state == PLAYING) {
				// Rendering of our PLAYING state, the loop goes through all the GameObjects in our PLAYING state
				for (iter = objects.begin(); iter != objects.end(); ++iter) {
					(*iter)->Render();
					if (showColBox)
						(*iter)->ToggleRenderColBox();
				}
				// Here we draw a scaled version of our top bar
				al_draw_scaled_bitmap(top_bar, 0, 0, 640, 30, 0, 0, 1280, 60, 0);
				// We then draw our players health bar ontop of the top bar
				DrawPercentBar(70, 10, 290, 30, ship->GetLifePercent(), healthbar_border, healthbar_bar, pix_font12_rg);
				// Here are some stats and statistics about how well our player is doing.
				al_draw_textf(pix_font16_rg, al_map_rgb(200, 200, 200), WIDTH - 205, 14, 0, "Time: %i", (int)round(elapsedTime));
				al_draw_textf(pix_font16_rg, al_map_rgb(200, 200, 200), WIDTH - 410, 14, 0, "Score: %i", ship->GetScore());
				// These three stats are considered debugging and will be removed once the game is finished (or will be added to some debug window)
				al_draw_textf(pix_font16_rg, al_map_rgb(200, 200, 200), WIDTH / 2, 14, 0, "Spawned: %i", numSpawned);
				al_draw_textf(pix_font16_rg, al_map_rgb(200, 200, 200), WIDTH / 2, 40, 0, "Killed: %i", numKilled);
				al_draw_textf(pix_font16_rg, al_map_rgb(200, 200, 200), WIDTH / 2, 60, 0, "Missed: %i", numMissed);

				// Here we handle shaking the screen, if the elapsedTime is in part of the song that is intense, we shake the screen.
				// SIDE NOTE: I have disabled this for now as it requires some tweaking. Some monitors do not work well with the intense shaking.
				/*if ((elapsedTime > 29 && elapsedTime < 85) || (elapsedTime > 150 && elapsedTime < 220)){
					// The updates for our camera movements are here
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
				// We apply our camera transformations so that it actually shakes the screen
				// This makes use of matricies.
				al_identity_transform(&cam);
				al_translate_transform(&cam, -(WIDTH / 2) + camX, -(HEIGHT / 2) + camY);
				al_rotate_transform(&cam, camAng);
				al_translate_transform(&cam, WIDTH / 2, HEIGHT / 2);
				al_use_transform(&cam);*/

			} else if(state == LOST) {
				// If we are in our LOST state, render the lost screen
				lostScreen->Render();
			} else if (state == WIN) {
				// If we are in our WIN state, render the win screen
				wonScreen->Render();
				al_draw_textf(pix_font18_b, al_map_rgb(200, 0, 0), 305, 190, 0, "Score: %i", ship->GetScore());
			} else if (state == INSTRUCTIONS) {
				// If we are in our INSTRUCTIONS (help) state, render our help state
				instrScreen->Render();
				al_draw_text(pix_font28_b, al_map_rgb(255, 255, 255), 30, 30, 0, "Instructions");
				al_draw_bitmap(contrArrows, 200, 230, 0);
				// Couldnt figure out how to have multiple colours in one text render, so I made two text renders 
				al_draw_text(pix_font18_b, al_map_rgb(255, 255, 255), 331, 430, ALLEGRO_ALIGN_CENTRE, "Use the                   to move the ship!");
				al_draw_text(pix_font18_b, al_map_rgb(200, 0, 0), 190, 430, 0, "Arrow Keys");
				// Couldnt figure out how to have multiple colours in one text render, so I made two text renders 
				al_draw_bitmap(contrSpace, 750, 280, 0);
				al_draw_text(pix_font18_b, al_map_rgb(255, 255, 255), 750 + 173, 430, ALLEGRO_ALIGN_CENTRE, "Use the                  to fire the guns!");
				al_draw_text(pix_font18_b, al_map_rgb(200, 0, 0), 798, 430, 0, "Space Key");
				// Render our back to menu button
				BkToMenu->Render();
			}
			// Render our current FPS, this is for debugging
			al_draw_textf(pix_font12_rg, al_map_rgb(255, 255, 255), WIDTH - 80, HEIGHT - 50, 0, "FPS: %i", gameFPS);
			
			// Flip the buffer and clear the screen colour to black
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}

	// End of game loop and clean up ALL GameObjects, whether they are alive or not.
	for(iter = objects.begin(); iter != objects.end(); ) {
		(*iter)->Destroy();
		delete (*iter);
		iter = objects.erase(iter);
	}

	// All our Destroy methods for the different objects
	lostScreen->Destroy();
	wonScreen->Destroy();
	titleScreen->Destroy();
	instrScreen->Destroy();
	playBtn->Destroy();
	quitBtn->Destroy();
	instrBtn->Destroy();
	BkToMenu->Destroy();
	logoBob->Destroy();
	
	// Delete our containers for the lost and title screen.
	delete lostScreen;
	delete wonScreen;
	delete titleScreen;
	delete instrScreen;

	// Destroy all the bitmaps in our game
	al_destroy_bitmap(mgImage);
	al_destroy_bitmap(fgImage);
	al_destroy_bitmap(bgImage);
	al_destroy_bitmap(explImage);
	al_destroy_bitmap(shipImage);
	al_destroy_bitmap(cometImage);
	al_destroy_bitmap(titleImage);
	al_destroy_bitmap(lostImage);
	al_destroy_bitmap(buttonImg);
	al_destroy_bitmap(healthbar_border);
	al_destroy_bitmap(healthbar_bar);
	al_destroy_bitmap(top_bar);
	al_destroy_bitmap(buttonImgSm);
	al_destroy_bitmap(logo);
	al_destroy_bitmap(contrArrows);
	al_destroy_bitmap(contrSpace);

	// Destroy all our sound samples in our games
	al_destroy_sample(boom);
	al_destroy_sample(song);
	al_destroy_sample(lost_song);
	al_destroy_sample(shot);
	al_destroy_sample(death);
	
	// Destroy our sample instances
	al_destroy_sample_instance(lossSongInst);
	al_destroy_sample_instance(songInstance);

	// Destroy our display, timer and event queue
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	
	// Destroy all our fonts
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

	// And finally, return 0 as a normal program exit (0x0)
	return 0;
}

// Misc functions

void __cdecl TakeLife() {
	// Plus our number of misses
	numMissed++;
	// Run the ships lose life function
	ship->LoseLife();
}

void __cdecl ScorePoint() {
	// Plus our number of kills
	numKilled++;
	// Run our ships add point function
	ship->AddPoint();
}

void __cdecl BtnToPlay() {
	// Change the state to PLAYING
	ChangeState(state, PLAYING);
}

void __cdecl BtnToQuit() {
	// Exit our game by quitting our game loop
	done = true;
}

void __cdecl BtnToInstr() {
	// Change the state to INSTRUCTIONS (help screen)
	ChangeState(state, INSTRUCTIONS);
}

void __cdecl BtnToMenu() {
	// Change the state to TITLE
	ChangeState(state, TITLE);
}

// Our ChangeState function
void ChangeState(int &state, int newState) {
	// Debugging to see when a state change occurs
	std::cout << "Debug: GameState has been changed from " << state << " to " << newState << std::endl;
	// Get the time of the state change
	stateTime = al_current_time();
	// We we are current in x do y
	if(state == TITLE) {
		// We dont want to do anything special for transitioning from TITLE to x
	} else if(state == PLAYING) {
		// If we are transitioning from the PLAYING state, we want to set all our GameObjects to not be alive
		for(iter = objects.begin(); iter != objects.end(); ++iter) {
			if ((*iter)->GetID() != PLAYER && (*iter)->GetID() != MISC) {
				(*iter)->SetAlive(false);
			}
		}
		// And we want to stop the song instance
		al_stop_sample_instance(songInstance);
	} else if(state == LOST) {
		// Stop our lossSong
		al_stop_sample_instance(lossSongInst);
	}

	// We set our state to our new state
	state = newState;
	
	// What we want to do as soon as we enter our new state
	if(state == TITLE){
		// Nothing special for TITLE
	} else if(state == PLAYING) {
		// As soon as we enter the PLAYING state, set all our spawning arrays to false
		for (int i = 0; i < TOTAL_SPAWNS; i++){
			hasSpawned[i] = false;
		}
		// Reset our statistics
		numSpawned = 0;
		numKilled = 0;
		numMissed = 0;
		hasFinished = false;
		elapsedTime = 0;

		// Init our ship
		ship->Init();
		
		// Play our playing state song
		al_play_sample_instance(songInstance);
		
	} else if(state == LOST) {
		// Play our lost song
		al_play_sample_instance(lossSongInst);
	}
}

// Function to draw a percent bar takes x, y coords for placement and a width and height, the amount of percent to draw, the bitmap for the border
// and the bitmap for the bar and the font for the text inside the percent bar
void DrawPercentBar(int x, int y, int w, int h, float percent, ALLEGRO_BITMAP * border, ALLEGRO_BITMAP * bar, ALLEGRO_FONT* font) {
	al_draw_bitmap_region(bar, 0, 0, 5 + ((w) * percent / 100), y + h, x, y, 0);
	al_draw_bitmap(border, x, y, 0);
	al_draw_textf(font, al_map_rgb(255, 255, 255), x + w / 2, y + h / 2 - 8, ALLEGRO_ALIGN_CENTRE, "%i%%", (int)round(percent));
}
