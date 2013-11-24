//-----------------------------
// James Payor - Evolution RTS
// Created 17/07/13
//-----------------------------
//
//-----------------
// MainRender.hpp |
//-------------------------------------------
// Implements key rendering functions for use
// in the main game loops.
//-------------------------------------------


// Renders the terrain:
void renderTerrain() {

	// Reset the size of the arrays storing vertex data:
	points_size = 0;
	norms_size = 0;
	tex_coords_size = 0;

	// Get the (x,z) offset to render at (surrounding the player):
	double offset_x = player->getLoc().x, offset_z = player->getLoc().z;
	offset_x -= fmod(offset_x, terrain_size);
	offset_z -= fmod(offset_z, terrain_size);

	// Draw octrees surrounding the player (note this isn't inefficient due to culling optimisations):
	fo(x,4) fo(z,4) octree->render(terrain_size, vec3f(offset_x+(x-1.5)*terrain_size,terrain_size*0.5,offset_z+(z-1.5)*terrain_size), cam->getFrustum());

	// Set the texture:
	X_SETTEXTURE(Media::Texture::TerrainChilled,-1);
	int num = points_size;

	// Setup vertex arrays:
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, points);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, tex_coords);
	// Draw!
	glDrawArrays(GL_QUADS, 0, num);
	// Disable them again:
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


// Renders a nice background:
void drawBackground() {
	// Persistent background coordinates:
	static float x=0,y=0,a=0;

	// Update coordinates:
	x+=2, y+=3; a += 0.02;
	x += SIN(a)*15; y += SIN(a+3)*12;

	// Draw one rectangle by vertices:
	ALPHAMODE(0.22);
	STARTPOLY(Media::Image::Moire, 2);
	POLYVECTOR(0,0,x,y);
	POLYVECTOR(width,0,x+width,y);
	POLYVECTOR(0,height,x,y+height);
	POLYVECTOR(width,height,x+width,y+height);
	POLYNEWSTRIP();

	// Draw another rectangle by vertices:
	ALPHAMODE(0.08);
	POLYVECTOR(0,0,x/4,y/4);
	POLYVECTOR(width,0,x/4+width/2,y/4);
	POLYVECTOR(0,height,x/4,y/4+height/2);
	POLYVECTOR(width,height,x/4+width/2,y/4+height/2);
	ENDPOLY();
}
