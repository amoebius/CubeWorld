

#ifndef	DINGS_3D_HEADER_INCLUDED
#define DINGS_3D_HEADER_INCLUDED

//#include "rainbows3d.h"
//#include "openglrainbows.h"

// From DINGS_MAIN.cpp
// extern OpenGLRainbows*	pRbow;

namespace __GLBASIC__
{
// 3D Commands
// ------------------------------------------------------- //
void	X_MAKE2D(void);
void	X_MAKE3D(DGInt znear, DGInt zfar, DGInt fov);
void	X_MIPMAPPING(DGNat state);
void	X_SETTEXTURE(DGNat num, DGNat num_multi);
void	X_SETTEXTUREOFFSET(DGInt du, DGInt dv);
void	X_AMBIENT_LT(DGNat num, DGNat col);
void	X_SPOT_LT(DGNat num, DGNat col, DGInt x, DGInt y, DGInt z, DGInt dirx, DGInt diry, DGInt dirz, DGInt cutoff);
void	X_DRAWAXES(DGInt x, DGInt y, DGInt z);
void	X_AUTONORMALS(DGNat mode);
void	X_OBJSTART(DGNat num);
void    X_OBJSETFRAME(DGNat num);
void	X_OBJADDVERTEX(DGInt x, DGInt y, DGInt z, DGInt tx, DGInt ty, DGNat col);
void	X_OBJNEWGROUP(void);
void	X_OBJEND(void);
void	X_SAVEOBJ(DGStr s, DGNat n);
void	X_LOADOBJ(const DGStr& s, DGNat n);
void	X_DRAWANIM(DGNat num, DGNat from, DGNat to, DGInt per_mille, DGNat full_anim);
void	X_DRAWOBJ(DGNat num, DGNat frame);
void	X_CAMERAUP(DGInt x, DGInt y, DGInt z);
void	X_CAMERA(DGInt x, DGInt y, DGInt z, DGInt px, DGInt py, DGInt pz);
void	X_ROTATION(DGInt angle, DGInt x, DGInt y, DGInt z);
void	X_MOVEMENT(DGInt x, DGInt y, DGInt z);
void	X_SCALING(DGInt x, DGInt y, DGInt z);
void	X_CULLMODE(DGNat mode);
void	X_FOG(DGInt col, DGInt exp_mode, DGInt p1, DGInt p2);
void	X_SPRITE(DGNat num, DGInt x, DGInt y, DGInt z, DGInt scale);
void	X_WORLD2SCREEN(DGInt objx, DGInt objy, DGInt objz, DGInt& sx, DGInt& sy, DGInt& sz);
void	X_SCREEN2WORLD(DGInt winx, DGInt winy, DGInt winz, DGInt& sx, DGInt& sy, DGInt& sz);
DGNat	X_COLLISION(DGNat num, DGNat frame, DGInt radius, DGInt x, DGInt y, DGInt z);
DGNat	X_COLLISIONAABB(DGNat num, DGNat frame, DGInt xc, DGInt yc, DGInt zc, DGInt wx, DGInt wy, DGInt wz);
DGNat	X_COLLISIONSPHEREBOX(DGInt xc, DGInt yc, DGInt zc, DGInt r, DGInt bx, DGInt by, DGInt bz);
DGInt 	X_COLLISIONRAY(DGNat num, DGNat frame, DGInt x, DGInt y, DGInt z, DGInt dirx, DGInt diry, DGInt dirz);
void	X_PRINT(DGStr text, DGInt x, DGInt y, DGInt z, DGInt scale);
void	X_CLEAR_Z();
void	X_ENABLE_Z(DGNat enable);
void	X_DOT(DGInt xa, DGInt ya, DGInt za, DGInt size, DGNat col);
void	X_LINE(DGInt xa, DGInt ya, DGInt za, DGInt xb, DGInt yb, DGInt zb, DGInt width, DGInt col);
void	X_PUSHMATRIX();
void	X_POPMATRIX();
void	X_SPHEREMAPPING(DGNat onoff);
void	X_SETSHADER(DGNat index);
DGNat	X_LOADSHADER(DGNat index, DGStr vert, DGStr frag);
void	X_PUTSHADER(const DGStr& name, DGInt value);
void	X_SETCELSHADES(DGIntArray& vals);
void	X_MULTMATRIX(DGIntArray& mat);
void	X_GETMATRIX( DGIntArray& mat);
void	X_GETCAMERAMATRIX(DGIntArray& mat);
DGNat	X_NUMFACES(DGNat obj);
DGNat	X_GETCOLLISIONFACE();
void	X_GETFACE(DGNat obj, DGNat frame, DGNat nface, DGIntArray& face);
void	X_SCALEMODEL(DGNat id, DGInt sx, DGInt sy, DGInt sz);

}; // namespace __GLBASIC__

#endif // DINGS_3D_HEADER_INCLUDED

#pragma warning(disable: 4244) // convert DGInt to float




