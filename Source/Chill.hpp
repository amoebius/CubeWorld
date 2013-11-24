//-----------------------------
// James Payor - Evolution RTS
// Created 17/07/13
//-----------------------------
//
//------------
// Chill.hpp |
//-------------------------------------------
// Implements the main loop for the "chill"
// gameplay.
//-------------------------------------------


void chill() {

	// Create the camera:
	cam = new Graphics::Camera(vec3(0,terrain_size*0.8,0), 0, 0, 10, terrain_size*0.35, float(width)/height, 128);
	// Create the player:
	player = new Agent::Player(cam->getLoc());

	// Wrap the heightmap with scaling and tiling:
	scaledhmap = new ScaledHeightmap(hmap, terrain_size / (double)noise->size());
	finalhmap = new TiledHeightmap(scaledhmap, terrain_size);

	// Variables for FPS checking, and displaying online help:
	double recentFPS = 30, lasttimer = 0, disp_alpha = 1;
	int disp_frames = 180;

	// Disable mouse pointer:
	SYSTEMPOINTER(false);

	// While the user hasn't pressed ESCAPE:
	while(!KEY(1)) {

		// Rotate the camera in accordance to mouse movement:
		DGInt x,y,b;
		MOUSESTATE(x,y,b,b);
		x-=width/2; y-=height/2;
		SETMOUSE(width/2, height/2);
		cam->rotate(y/-4.5,x/-4.5);

		// Update the player and camera:
		player->update(*finalhmap, *cam, lasttimer);
		cam->setLoc(player->getLoc());
		cam->updateFOV(player->getVel().abs());

		// Update LOD based on frame rate:
		if(recentFPS<23) {
			World::Octree::coef *= 1.2;
			recentFPS+=1;
		}
		if(recentFPS<27) {
			World::Octree::coef *= 1.09;
			recentFPS+=1;
		}
		if(recentFPS>29.8 && World::Octree::coef > 0.01) {
			World::Octree::coef *= 0.98;
		}

		// Render the world:
		cam->setTransform();
		renderTerrain();

		// Display online help text:
		X_MAKE2D();
		if(disp_alpha<0.0001) disp_alpha = 0.0001;
		ALPHAMODE(disp_alpha);
		PRINT("Chill mode!  Explore the terrain to your heart's content.", 10, 10);
		PRINT("W A S D - walk",10,40);
		PRINT("SPACEBAR - jetpack (vertically)",10,70);
		PRINT("ESCAPE - return to menu",10,100);

		// Fade out online help after a certain number of frames have passed, unless the player isn't moving:
		if(disp_frames) disp_frames--;
		else if(player->getVel().abs2()<3) {
			if(disp_alpha<1) disp_alpha+=0.05;
			if(disp_alpha>1) disp_alpha = 1;
		} else {
			disp_alpha *= 0.9;
		}

		// Update recent FPS counter with high pass filter:
		recentFPS = (recentFPS*4 + 1000./GETTIMER()) * 0.2;
		// Get time elapsed through this frame, clamping it to 140ms:
		lasttimer = GETTIMER();
		if(lasttimer>140) lasttimer=140;

		// Perform frame step processing:
		GLB::stepFrame();
	}

	// For 30 frames...
	fo(i,30) {
		// Update as before:
		DGInt x,y,b;
		MOUSESTATE(x,y,b,b);
		x-=width/2; y-=height/2;
		SETMOUSE(width/2, height/2);
		cam->rotate(y/-4.5,x/-4.5);
		player->update(*finalhmap, *cam, lasttimer);
		cam->setLoc(player->getLoc());
		cam->updateFOV(player->getVel().abs());

		// Update LOD as before:
		if(recentFPS<23) {
			World::Octree::coef *= 1.2;
			recentFPS+=1;
		}
		if(recentFPS<27) {
			World::Octree::coef *= 1.09;
			recentFPS+=1;
		}
		if(recentFPS>29.8 && World::Octree::coef > 0.01) {
			World::Octree::coef *= 0.98;
		}

		// Render as before:
		cam->setTransform();
		renderTerrain();

		X_MAKE2D();
		if(disp_alpha<0.0001) disp_alpha = 0.0001;
		ALPHAMODE(disp_alpha);
		PRINT("Chill mode!  Explore the terrain to your heart's content.", 10, 10);
		PRINT("W A S D - walk",10,40);
		PRINT("SPACEBAR - jetpack (vertically)",10,70);
		PRINT("ESCAPE - return to menu",10,100);
		if(disp_frames) disp_frames--;
		else if(player->getVel().abs2()<3) {
			if(disp_alpha<1) disp_alpha+=0.05;
			if(disp_alpha>1) disp_alpha = 1;
		} else {
			disp_alpha *= 0.9;
		}

		// Draw a semi-transparent black rectangle over everything for a fade-out effect:
		ALPHAMODE(-(i+1)/30.);
		DRAWRECT(0,0,width,height,0);

		// Update timers and FPS counter as before:
		recentFPS = (recentFPS*4 + 1000./GETTIMER()) * 0.2;

		lasttimer = GETTIMER();
		if(lasttimer>140) lasttimer=140;

		GLB::stepFrame();
	}

	// Delete objects involved in gameplay:
	delete cam;
	delete player;
	delete scaledhmap;
	delete finalhmap;
}
