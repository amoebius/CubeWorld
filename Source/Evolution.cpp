//-----------------------------
// James Payor - Evolution RTS
// Created 05/03/12
//-----------------------------
//
//----------------
// Evolution.cpp |
//-------------------------------------------
// Defines the main routine run from GLBasic.
//-------------------------------------------


// Interface with GLBasic:
#include "glb.h"
#include "glb3D.h"

// Include OpenGL:
#include <GL/gl.h>
#include <GL/glu.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/glext.h>

// Required standard libraries:
#include <cmath>
#include <vector>

// Required project headers:
#include "../Headers/Evolution.hpp"
#include "../Headers/Net_UDP.hpp"
#include <../Headers/World_Octree.hpp>
#include <../Headers/Graphics_Camera.hpp>
#include <../Headers/Graphics_GL.hpp>
#include <../Headers/Math_Vector.hpp>
#include <../Headers/Math_PerlinNoise.hpp>
#include <../Headers/Math_Functional.hpp>
#include <../Headers/Macro.hpp>
#include <../Headers/Threading.hpp>
#include <../Headers/GLB_Interface.hpp>
#include <../Headers/Agent_Player.hpp>
#include <../Headers/Agent_Enemy.hpp>
#include <../Headers/Media.hpp>
#include <../Headers/Random.hpp>
using namespace Math;


// References to the dynamic arrays that hold the octree's vertex information for rendering:
extern vec3f *norms, *points;
extern float *tex_coords;
extern int norms_size, points_size, tex_coords_size;

// Pointers to heightmaps and structures involved in gameplay:
Graphics::Camera *cam;
World::Octree *octree;
PerlinNoise *noise;
PerlinNormal *norm;
Heightmap *hmap;
ScaledHeightmap *scaledhmap;
TiledHeightmap *finalhmap;
Agent::Player *player;
// A dynamic array of enemies:
std::vector<Agent::Enemy> enemies;

// Game level-of-detail constants:
static const double DefaultCoef = 0.02;
static const double terrain_size = 30000;
static const int LOD = 10;

// Global variables to access the screen width and height
int width, height;

// Include the implementation of components of the main game logic:
#include <../Source/MainRender.hpp>
#include <../Source/Chill.hpp>
#include <../Source/Thrill.hpp>
#include <../Source/Progress.hpp>



// Namespace __GLBASIC__ - routines visible to GLBasic:
namespace __GLBASIC__ {

	// The main game routine:
	void main() {

		// Initialise GLBasic parameters:
		AUTOPAUSE(false);
		SYSTEMPOINTER(false);
		ALLOWESCAPE(false);

		// Get width and height, and become fullscreen:
		DGNat width2, height2;
		GETDESKTOPSIZE(width2, height2);
		width = width2; height = height2;
		SETSCREEN(width2, height2, 1);

		// Initialise media and variables:
		World::Octree::coef = DefaultCoef;
		Graphics::GL::initDisplayLists();
		Media::Load();

		// Seed random numbers:
		Random::Seed();

		// Play background music:
		MUSICVOLUME(0.7);
		PLAYMUSIC("Background.mp3", true);


		// Main game loop:
		while(true) {

			// Begin creating the octree in the background using a separate thread:
			Threading::ThreadedFunc octree_gen = Threading::Create(build);
			// Enable the mouse pointer:
			SYSTEMPOINTER(true);

			// Flags:
			bool modeChill;
			bool selected = false;
			bool tutorial = false;
			bool lastb1 = false;

			// Variable used in changing colours:
			float amt=RND(70)*0.1;
			// Tutorial visibility:
			double helpAlpha = 0;

			// While user hasn't selected an option:
			while(!selected) {
				drawBackground();

				// Draw the button backgrounds, using SIN curves for trippy changing colours:
				ALPHAMODE(0.45);
				amt+=0.15;
				DRAWRECT(20,350,width/2-30,height-370-80, RGB(ABS(SIN(amt*2))*255,ABS(SIN(1+amt*0.9))*205+50,ABS(SIN(2+amt*2.3))*200+55));
				DRAWRECT(width/2+10,350,width/2-30,height-370-80, RGB(ABS(SIN((amt+20)*2))*255,ABS(SIN(1+(amt+20)*0.9))*205+50,ABS(SIN(2+(amt+20)*2.3))*200+55));
				DRAWRECT(20,20,width-40,310, RGB(ABS(SIN((amt+60)*2))*255,ABS(SIN(1+(amt+60)*0.9))*205+50,ABS(SIN(2+(amt+60)*2.3))*200+55));
				DRAWRECT(20, height-80, width-40, 60, RGB(ABS(SIN((amt+100)*2))*255,ABS(SIN(1+(amt+100)*0.9))*205+50,ABS(SIN(2+(amt+100)*2.3))*200+55));

				// Display the text for each button:
				ALPHAMODE(1);
				DGStr Title("CubeWorld"), Subtitle("(Click to exit)");
				PRINT(Title, (width-LEN(Title,0))/2, 130);
				PRINT(Subtitle, (width-LEN(Subtitle,0))/2,190);

				Title = "Chill Mode (click to begin)"; Subtitle = "Explore the world at your leisure.";
				PRINT(Title, (width/2-LEN(Title,0))/2, 500);
				PRINT(Subtitle, (width/2-LEN(Subtitle,0))/2, 560);

				Title = "Thrill Mode (click to begin)"; Subtitle = "Survive the rush.";
				PRINT(Title, width/2+(width/2-LEN(Title,0))/2, 500);
				PRINT(Subtitle, width/2+(width/2-LEN(Subtitle,0))/2, 560);

				Title = "Tutorial (First time?  Click here)";
				PRINT(Title, (width - LEN(Title,0))/2, height-63);


				// Get the mouse state:
				DGNat x,y,b1,b2;
				MOUSESTATE(x,y,b1,b2);
				// If mouse is clicked:
				if(lastb1 && !b1) {
					if(tutorial) { // If the tutorial is visible, then hide it
						tutorial = false;
					} else { // Otherwise a button was clicked:
						if(y<340) END();  // End if it was the top button.
						else if(y>height-90) tutorial = true; // Open tutorial if it was the bottom button.
						else { // If one of the middle buttons...
							selected = true;  // Mark the user as having made a selection.
							modeChill = x < width/2;  // Get which of the two modes was selected.
						}
					}
				}
				lastb1 = b1;

				// Adjust tutorial visibility:
				if(tutorial) {
					if(helpAlpha<1) helpAlpha += 0.05;
				} else {
					if(helpAlpha>0) helpAlpha -= 0.1;
				}

				// If the tutorial is visible:
				if(helpAlpha>0) {
					if(helpAlpha>1) helpAlpha=1;
					ALPHAMODE(-helpAlpha*0.95);
					DRAWRECT(70,70,width-140,height-140,0);
					ALPHAMODE(helpAlpha);
					DGStr Lines[] = {"Tutorial (click anywhere to dismiss)", "", "To begin, choose one of the two modes.",
									 "'Chill' mode gives you an endless terrain to explore.",
									 "'Thrill' mode places you on the same terrain, but your",
									 "goal is to avoid the swarm following you.  When they get",
									 "close, you'll find it more difficult to move, and slowly",
									 "get battered down.",
									 "", "When you're on the ground, walk with the W, A, S, and D keys.",
									 "In the ground or the air, press SPACEBAR for your jetpack,",
									 "which will accelerate you upwards.  Tilt to fly in a",
									 "different direction.",
									 "",
									 "Click anywhere to dismiss this tutorial, and begin!"};
					int numLines = sizeof(Lines) / sizeof(DGStr);
					int height = numLines*30;
					fo(i,numLines) PRINT(Lines[i], (width - LEN(Lines[i],0))/2, (height-numLines)/2+30*i);
				}

				// Perform GLB frame step processing:
				GLB::stepFrame();
			}

			// Display a progress report of octree generation untli it is complete:
			Progress(octree_gen);
			// Launch the appropriate gameplay:
			if(modeChill) chill(); else thrill();

			// Free the octree, heightmap, and perlin noise objects:
			delete octree;
			delete hmap;
			delete norm;
			delete noise;
		}

		// Close the program:
		STOPMUSIC();
		END();
	}
}
