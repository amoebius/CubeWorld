CubeWorld
=========

My experimentation into representing volumes using sparse voxel octrees, currently with a game hastily stuck over the terrain, to be used in other projects in the future.

The project is currently linked with the libraries of GLBasic - a cross-platform BASIC dialect - for potentially cross-platform input and rendering.

In the future, terrain modification is envisaged - easily supported by the SVO data structure - but for now the terrain is static, built from an arbitrary height-map (currently using my implementation of 2D Perlin noise).

TODOs include:
- Terrain modification
- Hydrodynamics using the SVO structure
- General pathing over the volume
- An RTS that is intricately linked with its 3D terrain [sometime in the far future]

... but for now, this stands as a poorly organised implementation of an SVO structure!