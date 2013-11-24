//-----------------------------
// James Payor - Evolution RTS
// Created 17/07/13
//-----------------------------
//
//-------------
// Thrill.hpp |
//-------------------------------------------
// Implements the main loop for the "thrill"
// gameplay.
//-------------------------------------------


void thrill() {

	// Flag - has the player quit yet?
	bool playing = true;

	while(playing) {

		// Initialise the camera and player:
		cam = new Graphics::Camera(vec3(0,terrain_size*0.8,0), 0, 0, 10, terrain_size*0.35, float(width)/height, 128);
		player = new Agent::Player(cam->getLoc());
		// Create some enemies:
		fo(i,700) enemies.push_back(Agent::Enemy(*player, 4*terrain_size));
		// Wrap the heightmap with scaling and tiling:
		scaledhmap = new ScaledHeightmap(hmap, terrain_size / (double)noise->size());
		finalhmap = new TiledHeightmap(scaledhmap, terrain_size);

		// Variables involved in displaying online help, player health, and FPS counting:
		double recentFPS = 30, lasttimer = 0, disp_alpha = 1, health = 1;
		int disp_frames = 180;

		// Get the starting time and disable the pointer:
		DGInt start_time = GETTIMERALL();
		SYSTEMPOINTER(false);

		// While they have health left and haven't quit...
		while(!KEY(1)&&health>0) {

			// Rotate the camera based on mouse input:
			DGInt x,y,b;
			MOUSESTATE(x,y,b,b);
			x-=width/2; y-=height/2;
			SETMOUSE(width/2, height/2);
			cam->rotate(y/-4.5,x/-4.5);

			// Update the enemies, and decrcement player health if colliding:
			fo(i,enemies.size()) enemies[i].update(*finalhmap, *player, lasttimer), health -= player->update(enemies[i]);

			// Update the player and camera:
			player->update(*finalhmap, *cam, lasttimer);
			cam->setLoc(player->getLoc());
			cam->updateFOV(player->getVel().abs());

			// Update LOD based off recent FPS:
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

			// Render the terrain andn enemies:
			cam->setTransform();
			renderTerrain();
			fo(i,enemies.size()) enemies[i].render();

			// Display online help:
			X_MAKE2D();
			if(disp_alpha<0.0001) disp_alpha = 0.0001;
			ALPHAMODE(disp_alpha);
			PRINT("Thrill mode.  Directive: Survive.", 10, 10);
			PRINT("W A S D - walk",10,40);
			PRINT("SPACEBAR - jetpack (vertically)",10,70);
			PRINT("ESCAPE - chicken out (back to menu)",10,100);
			PRINT("Keep running - avoid the incoming swarm.", 10, 130);

			// Display a red overlay as the player loses health:
			if(health<1) {
				if(health>0) health+=0.004, ALPHAMODE(-1+health*health); else ALPHAMODE(-1);
				STRETCHSPRITE(Media::Image::RedMask, 0, 0, width, height);
			}

			// Display the time the player has lived for:
			ALPHAMODE(0.9);
			DGStr timer = int((GETTIMERALL()-start_time)*0.1)*DGInt(0.01);
			PRINT(timer, width-125, 40);

			// Update online help transparency:
			if(disp_frames) disp_frames--;
			else if(player->getVel().abs2()<3) {
				if(disp_alpha<1) disp_alpha+=0.05;
				if(disp_alpha>1) disp_alpha = 1;
			} else {
				disp_alpha *= 0.9;
			}

			// Update FPS counter:
			recentFPS = (recentFPS*4 + 1000./GETTIMER()) * 0.2;
			lasttimer = GETTIMER();
			if(lasttimer>140) lasttimer=140;

			// Perform frame step processing:
			GLB::stepFrame();
		}

		// Get the amount of time they survived:
		DGInt score_time = GETTIMERALL() - start_time;

		// If they hit the escape key, update the playing flag:
		if(KEY(1)) {
			playing = false;
		} else {

			// 30 frame long fadeout:
			fo(j,30) {
				// Update enemies, player, and camera as before:
				fo(i,enemies.size()) enemies[i].update(*finalhmap, *player, lasttimer), health -= player->update(enemies[i]);
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
				fo(i,enemies.size()) enemies[i].render();

				// Online help rendering as before:
				X_MAKE2D();
				if(disp_alpha<0.0001) disp_alpha = 0.0001;
				ALPHAMODE(disp_alpha);
				PRINT("Thrill mode.  Directive: Survive.", 10, 10);
				PRINT("W A S D - walk",10,40);
				PRINT("SPACEBAR - jetpack (vertically)",10,70);
				PRINT("ESCAPE - chicken out (back to menu)",10,100);
				PRINT("Keep running - avoid the incoming swarm.", 10, 130);

				// Draw red mask over the scene:
				ALPHAMODE(-1);
				STRETCHSPRITE(Media::Image::RedMask, 0, 0, width, height);
				// Draw transparent black rectangle over scene for fade out effect:
				ALPHAMODE(-(j+1)/30.);
				DRAWRECT(0,0,width,height,0);

				// Reduce visibility of online help:
				disp_alpha *= 0.9;

				// Update recent FPS variables:
				recentFPS = (recentFPS*4 + 1000./GETTIMER()) * 0.2;
				lasttimer = GETTIMER();
				if(lasttimer>140) lasttimer=140;

				// Step frame processing:
				GLB::stepFrame();
			}

			// Initialise the fade alpha:
			double alpha = 0.01;
			while(!KEY(1)&&!MOUSEAXIS(3)) {
				drawBackground();
				// Tell the player their score and instruct them to try again:
				DGStr Text = DGStr("You survived ") + DGStr(int(score_time*0.1)*DGInt(0.01)) + DGStr(" seconds.");
				DGStr Text2 = "Click to redeploy, or hit ESCAPE to return to the menu.";
				ALPHAMODE(1);
				PRINT(Text, (width - LEN(Text,0))/2, 300);
				PRINT(Text2, (width - LEN(Text2,0))/2, 400);
				// While we haven't faded in fully:
				if(alpha < 1) {
					// Increase visibility and draw a semi-transparent black rectangle over everything:
					ALPHAMODE(-1+alpha);
					DRAWRECT(0,0,width,height,0);
					alpha += 0.1;
				}
				// Frame step processing:
				GLB::stepFrame();
			}
			// If they pressed ESCAPE, update flag:
			if(KEY(1)) playing = false;

			// 30 frame fadeout:
			fo(i,30) {
				// Draw everything:
				drawBackground();
				DGStr Text = DGStr("You survived ") + DGStr(int(score_time*0.1)*DGInt(0.01)) + DGStr(" seconds.");
				DGStr Text2 = "Click to redeploy, or hit ESCAPE to return to the menu.";
				ALPHAMODE(1);
				PRINT(Text, (width - LEN(Text,0))/2, 300);
				PRINT(Text2, (width - LEN(Text2,0))/2, 400);
				// Overlay a black rectangle:
				ALPHAMODE(-(i+1)/30.);
				DRAWRECT(0,0,width,height,0);
				// Step:
				GLB::stepFrame();
			}

		}

		// Clear the enemies array and delete objects associated with gameplay:
		delete cam;
		delete player;
		delete scaledhmap;
		delete finalhmap;
		enemies.clear();
	}
}
