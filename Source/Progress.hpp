//-----------------------------
// James Payor - Evolution RTS
// Created 17/07/13
//-----------------------------
//
//---------------
// Progress.hpp |
//-------------------------------------------
// Implements functions handling displaying
// the progress of octree instantiation.
//-------------------------------------------

// Returns a characteristic smiley face based on the amount of time left in milliseconds:
DGStr face(DGInt left) {
	left/=1000;
	if(left < 0) return "D:";
	if(left > 5000) return ".______. (what are you doing with your life??)";
	if(left > 3000) return "q_q";
	if(left > 2000) return "._.";
	if(left > 1000) return "O_o";
	if(left > 500) return "v_v";
	if(left > 300) return "=\\";
	if(left > 150) return "=O";
	if(left > 90) return "=)";
	if(left > 3) return ":D";
	return ":D :D :D :D :D";
}

// The number of nodes that need to be instantiated:
int totalNumber;
// A method for displaying the progress in generating the octree to the user:
void Progress(Threading::ThreadedFunc &prog) {
	// Get an amount to offset initial colours:
	float amt=RND(80)*0.1,width=0;
	// Initialise starting time and number left:
	DGInt start = GETTIMERALL(), left = totalNumber-World::Octree::nodeCount;

	// While the thread hasn't finished:
	while(!prog.finished()) {
		// Inform the user of the time remaining:
		drawBackground();
		ALPHAMODE(0.8);
		amt += 0.1;
		PRINT("Deploying...",10,10);
		PRINT(DGStr(int((float)World::Octree::nodeCount*100./totalNumber))+DGStr("% complete."),10,40);
		if(World::Octree::nodeCount) left = (14*left+((totalNumber-World::Octree::nodeCount) * (GETTIMERALL()-start)/World::Octree::nodeCount))/15.;
		PRINT(DGStr("Around ")+DGStr((DGNat)left/1000)+DGStr(" seconds left! ")+face(left),10,70);
		DGInt sx,sy;
		GETSCREENSIZE(sx,sy);
		// Draw a nice progress bar:
		if(totalNumber) width = (13*width + sx*World::Octree::nodeCount*1./totalNumber)/14.;
		DRAWRECT(0,120,width,150,RGB(ABS(SIN(amt*2))*255,ABS(SIN(1+amt*0.9))*205+50,ABS(SIN(2+amt*2.3))*200+55));
		// Swap the buffers and perform frame step processing:
		SHOWSCREEN();
	}
}


// Creates an octree:
void build() {
	// Progress depth constant:
	const int progdepth = LOD-4;
	// Setup static octree variables:
	World::Octree::progressLevel = progdepth;
	World::Octree::nodeCount = 0;
	World::Octree::threadsRunning = 0;
	World::Octree::threadCap = 4;
	// Create a heightmap from Perlin noise:
	noise = new PerlinNoise(LOD-2);
	norm = new PerlinNormal(noise);
	hmap = new ScalarVectorHeightmap(*noise,*norm);

	// Initialise the totalNumber:
	totalNumber = 1<<(3*(LOD-progdepth));
	// Instantiate the octree:
	octree = new World::Octree(*hmap, LOD, vec3::diag()*noise->size()*0.5, noise->size()*0.5);
}
