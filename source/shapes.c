#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

#include "render.h"
#include "shapes.h"

#define NUM_BUTTERFLY_VERTICES 66
s32 bf_pts[] = { -48,-104,
                       -88,-64,
                       -8,-64,
                       -56,-32,
                       -8,-8,
                       -80,-8,
                       -40,24,
                       0,-64,
                       40,-104,
                       80,-64,
                       48,-32,
                       0,-8,
                       72,-8,
                       32,24,
                       -48,-96,
                       -56,-88,
                       -48,-80,
                       -40,-88,
                       -36,-84,
                       -44,-76,
                       -36,-68,
                       -28,-76,
                       -60,-84,
                       -52,-76,
                       -60,-68,
                       -68,-76,
                       40,-96,
                       32,-88,
                       40,-80,
                       48,-88,
                       28,-84,
                       36,-76,
                       28,-68,
                       20,-76,
                       44,-76,
                       52,-84,
                       60,-76,
                       52,-68,
                       -40,16,
                       -28,4,
                       -40,-8,
                       -52,4,
                       32,16,
                       44,4,
                       32,-8,
                       20,4,
                       48,0,
                       40,-8,
                       48,-16,
                       56,-8,
                       16,0,
                       24,-8,
                       16,-16,
                       8,-8,
                       -24,0,
                       -32,-8,
                       -24,-16,
                       -16,-8,
                       -56,0,
                       -48,-8,
                       -56,-16,
                       -64,-8,
                       -8,-72,
                       0,-72,
                       0,0,
                       -8,0 };

#define NUM_BF_LWING_POLYS 5
s32 bf_lwing_polys[] = { 0,1,2,
                         1,3,2,
                         3,4,2,
                         3,5,4,
                         5,6,4 };

#define NUM_BF_LWING_EDGES 7
s32	bf_lwing_edges[] = { 2, 0, 1, 3, 5, 6, 4 };

#define NUM_BF_RWING_POLYS 5
s32 bf_rwing_polys[] = { 7,8,9,
                         9,10,7,
                         11,7,10,
                         11,12,10,
                         11,13,12 };

#define NUM_BF_RWING_EDGES 7
s32	bf_rwing_edges[] = { 7, 8, 9, 10, 12, 13, 11 };



#define NUM_BF_LPTRN_POLYS 12
s32 bf_lptrn_polys[] = { 14,15,16,
                         16,17,14,
                         18,19,20,
                         20,21,18,
                         22,23,24,
                         22,25,24,
                         38,39,40,
                         38,41,40,
                         54,55,56,
                         54,57,56,
                         58,59,60,
                         60,61,58 };

#define NUM_BF_RPTRN_POLYS 12
s32 bf_rptrn_polys[] = { 26,27,28,
                         28,29,26,
                         30,31,32,
                         32,33,30,
                         34,35,36,
                         34,37,36,
                         42,43,44,
                         42,45,44,
                         46,47,48,
                         46,49,48,
                         50,51,52,
                         52,53,50 };

#define NUM_BF_BODY_POLYS 2
s32 bf_body_polys[] = { 62,63,64,
                         64,62,65 };

#define NUM_STALK_VERTICES 22
s32 stalk_pts[] = { -16,0,
                       16,0,
                       16,-48,
                       -16,-48,
                       8,-88,
                       -24,-88,
                       0,-120,
                       -24,-136,
                       -48,-112,
                       -56,-160,
                       -32,-176,
                       -56,-200,
                       -32,-216,
                       -56,-216,
                       0,-152,
                       16,-160,
                       24,-152,
                       24,-136,
                       -88,-120,
                       -96,-112,
                       -96,-104,
                       -88,-96 };

#define NUM_STALK_POLYS 18
s32 stalk_polys[] = { 0,1,2,
                         0,3,2,
                         2,4,3,
                         3,5,4,
                         4,6,5,
                         5,6,7,
                         5,8,7,
                         8,9,7,
                         9,10,7,
                         9,11,10,
                         10,12,11,
                         11,13,12,
                         6,14,15,
                         6,15,16,
                         6,16,17,
                         8,18,19,
                         8,19,20,
                         8,20,21 };

#define NUM_STALK_EDGES 25
s32 stalk_edges[] = {	 0,  1,  2,  4,
						 6, 17, 16, 15,
						14,  6,  7, 10,
						12, 13, 11,  9,
						 8, 18, 19, 20,
						21,  8,  5, 3,
						 0 };

#define NUM_PETAL_VERTICES 9
s32 petal_pts[] = { -16,0,
                       16,0,
                       16,-48,
                       -16,-48,
                       32,-32,
                       12,-32,
                       -32,-32,
                       -12,-32,
                       0,-56 };

#define NUM_PETAL_POLYS 7
s32 petal_polys[] = { 0,1,2,
                         0,2,3,
                         1,4,5,
                         5,4,2,
                         0,6,7,
                         6,3,7,
                         3,8,2 };

#define NUM_PETAL_EDGES 8
s32 petal_edges[] = { 1, 4, 2, 8, 3, 6, 0, 1 };

#define NUM_STAR_VERTICES 10
f32 star_pts[] = {	-15, -20,   // 0 -
					 15, -20,   // 1 -
					  0, -65,   // 2 -
					-55, -20,   // 3 -
					-25,   5,   // 4 -
					 55, -20,   // 5 -
					 25,   5,   // 6 -
					-45,  50,   // 7 -
					  0,  20,   // 8 -
					 40,  50 }; // 9 -

#define NUM_STAR_POLYS 8
s32 star_polys[] = {	0,1,2,
						0,3,4,
						1,5,6,
						4,7,8,
						6,8,9,
						4,1,0,
						8,1,6,
						8,1,4 };

#define NUM_STAR_EDGES 11
s32 star_edges[] = { 2, 0, 3, 4, 7, 8, 9, 6, 5, 1, 2 };

Vector rotax = { 0, 0, 1 };

struct vtx sunrays[NUMRAYS*4];
struct vtx stalk[NUM_STALK_VERTICES];
struct vtx petal[NUM_PETAL_VERTICES];
struct vtx bfly[NUM_BUTTERFLY_VERTICES];
struct vtx bbfly[NUM_BUTTERFLY_VERTICES];

struct vtx cloudbot[4];
float clox1, cloy1, clr1;
float clox2, cloy2, clr2;
float clox3, cloy3, clr3;

extern Mtx GXmodelView2D;

f32 stopx, stopy;
extern f32 stalktopx, stalktopy;

void shapes_init( void )
{
	f32 scale;
	s32 i;

	scale = 640.0f/800.0f;
	for( i=0; i<NUM_STALK_VERTICES; i++ )
	{
		stalk[i].x = ((f32)stalk_pts[i*2]) * scale * 0.7f;
		stalk[i].y = ((f32)stalk_pts[i*2+1]) * scale;
	}
  
	stopx = -44.0f * scale * 0.7f;
	stopy = -216.0f * scale;
  
	scale = 640.0f/950.0f;
	for( i=0; i<NUM_PETAL_VERTICES; i++ )
	{
		petal[i].x = ((f32)petal_pts[i*2]) * scale;
		petal[i].y = ((f32)petal_pts[i*2+1]) * scale;
	}

	scale = 640.0f/1200.0f;
	for( i=0; i<NUM_BUTTERFLY_VERTICES; i++ )
	{
		bfly[i].x = ((f32)bf_pts[i*2]) * scale;
		bfly[i].y = ((f32)bf_pts[i*2+1]) * scale;
		bbfly[i].x = ((f32)bf_pts[i*2]) * scale * 0.6f;
		bbfly[i].y = ((f32)bf_pts[i*2+1]) * scale * 0.6f;
	}

	// Cloud parameters
	scale = 640.0f/16.0f;

	clr1   = 1.0f*scale;
	clr2   = 0.8f*scale;
	clr3   = 0.7f*scale;
  
	clox1  = 0.0f;
	cloy1  = -clr1;
	clox2  = -(clr2/2.0f+clr1);
	cloy2  = -clr2;
	clox3  = clr3/2.0f+clr1;
	cloy3  = -clr3;
  
	cloudbot[0].x = clox2;
	cloudbot[0].y = cloy2;
	cloudbot[1].x = clox3;
	cloudbot[1].y = cloy2;
	cloudbot[2].x = clox3;
	cloudbot[2].y = 0.0f;
	cloudbot[3].x = clox2;
	cloudbot[3].y = 0.0f;
}

void draw_bf_leftwing( f32 ca, f32 sa, f32 wscale, f32 sx, f32 sy, f32 z, u8 *col1, u8 *col2, struct vtx *bs )
{
	s32 i;
	struct vtx *a, *b, *c;
	
	GX_Begin( GX_TRIANGLES, GX_VTXFMT0, NUM_BF_LWING_POLYS*3 );	
	for( i=0; i<NUM_BF_LWING_POLYS; i++ )	
	{
		a = &bs[bf_lwing_polys[i*3]];
		b = &bs[bf_lwing_polys[i*3+1]];
		c = &bs[bf_lwing_polys[i*3+2]];

		if( a->f2 )
		{
			a->f2 = 0;
			a->sx = (a->x*wscale*ca - a->y*sa) + sx;
			a->sy = (a->x*wscale*sa + a->y*ca) + sy;
		}

		if( b->f2 )
		{
			b->f2 = 0;
			b->sx = (b->x*wscale*ca - b->y*sa) + sx;
			b->sy = (b->x*wscale*sa + b->y*ca) + sy;
		}

		if( c->f2 )
		{
			c->f2 = 0;
			c->sx = (c->x*wscale*ca - c->y*sa) + sx;
			c->sy = (c->x*wscale*sa + c->y*ca) + sy;
		}

		GX_Position3f32( a->sx, a->sy, z );
		GX_Color4u8( col1[0], col1[1], col2[2], 0xff );
		GX_Position3f32( b->sx, b->sy, z );
		GX_Color4u8( col1[0], col1[1], col2[2], 0xff );
		GX_Position3f32( c->sx, c->sy, z );
		GX_Color4u8( col1[0], col1[1], col2[2], 0xff );
	}
	GX_End();

	GX_Begin( GX_TRIANGLES, GX_VTXFMT0, NUM_BF_LPTRN_POLYS*3 );
	for( i=0; i<NUM_BF_LPTRN_POLYS; i++ )
	{
		a = &bs[bf_lptrn_polys[i*3]];
		b = &bs[bf_lptrn_polys[i*3+1]];
		c = &bs[bf_lptrn_polys[i*3+2]];

		if( a->f2 )
		{
			a->f2 = 0;
			a->sx = (a->x*wscale*ca - a->y*sa) + sx;
			a->sy = (a->x*wscale*sa + a->y*ca) + sy;
		}

		if( b->f2 )
		{
			b->f2 = 0;
			b->sx = (b->x*wscale*ca - b->y*sa) + sx;
			b->sy = (b->x*wscale*sa + b->y*ca) + sy;
		}

		if( c->f2 )
		{
			c->f2 = 0;
			c->sx = (c->x*wscale*ca - c->y*sa) + sx;
			c->sy = (c->x*wscale*sa + c->y*ca) + sy;
		}

		GX_Position3f32( a->sx, a->sy, z );
		GX_Color4u8( col2[0], col2[1], col2[2], 0xff );
		GX_Position3f32( b->sx, b->sy, z );
		GX_Color4u8( col2[0], col2[1], col2[2], 0xff );
		GX_Position3f32( c->sx, c->sy, z );
		GX_Color4u8( col2[0], col2[1], col2[2], 0xff );
	}
	GX_End();

	GX_Begin( GX_LINESTRIP, GX_VTXFMT0, NUM_BF_LWING_EDGES );
	for( i=0; i<NUM_BF_LWING_EDGES; i++ )
	{
		GX_Position3f32( bs[bf_lwing_edges[i]].sx, bs[bf_lwing_edges[i]].sy, z );
		GX_Color4u8( 0, 0, 0, 0xff );
	}
	GX_End();
}

void draw_bf_rightwing( f32 ca, f32 sa, f32 wscale, f32 sx, f32 sy, f32 z, u8 *col1, u8 *col2, struct vtx *bs )
{
	s32 i;
	struct vtx *a, *b, *c;
	
	GX_Begin( GX_TRIANGLES, GX_VTXFMT0, NUM_BF_RWING_POLYS*3 );
	for( i=0; i<NUM_BF_RWING_POLYS; i++ )
	{
		a = &bs[bf_rwing_polys[i*3]];
		b = &bs[bf_rwing_polys[i*3+1]];
		c = &bs[bf_rwing_polys[i*3+2]];

		if( a->f2 )
		{
			a->f2 = 0;
			a->sx = (a->x*wscale*ca - a->y*sa) + sx;
			a->sy = (a->x*wscale*sa + a->y*ca) + sy;
		}

		if( b->f2 )
		{
			b->f2 = 0;
			b->sx = (b->x*wscale*ca - b->y*sa) + sx;
			b->sy = (b->x*wscale*sa + b->y*ca) + sy;
		}

		if( c->f2 )
		{
			c->f2 = 0;
			c->sx = (c->x*wscale*ca - c->y*sa) + sx;
			c->sy = (c->x*wscale*sa + c->y*ca) + sy;
		}

		GX_Position3f32( a->sx, a->sy, z );
		GX_Color4u8( col1[0], col1[1], col2[2], 0xff );
		GX_Position3f32( b->sx, b->sy, z );
		GX_Color4u8( col1[0], col1[1], col2[2], 0xff );
		GX_Position3f32( c->sx, c->sy, z );
		GX_Color4u8( col1[0], col1[1], col2[2], 0xff );
	}
	GX_End();

	GX_Begin( GX_TRIANGLES, GX_VTXFMT0, NUM_BF_RPTRN_POLYS*3 );
	for( i=0; i<NUM_BF_RPTRN_POLYS; i++ )
	{
		a = &bs[bf_rptrn_polys[i*3]];
		b = &bs[bf_rptrn_polys[i*3+1]];
		c = &bs[bf_rptrn_polys[i*3+2]];

		if( a->f2 )
		{
			a->f2 = 0;
			a->sx = (a->x*wscale*ca - a->y*sa) + sx;
			a->sy = (a->x*wscale*sa + a->y*ca) + sy;
		}

		if( b->f2 )
		{
			b->f2 = 0;
			b->sx = (b->x*wscale*ca - b->y*sa) + sx;
			b->sy = (b->x*wscale*sa + b->y*ca) + sy;
		}

		if( c->f2 )
		{
			c->f2 = 0;
			c->sx = (c->x*wscale*ca - c->y*sa) + sx;
			c->sy = (c->x*wscale*sa + c->y*ca) + sy;
		}

		GX_Position3f32( a->sx, a->sy, z );
		GX_Color4u8( col2[0], col2[1], col2[2], 0xff );
		GX_Position3f32( b->sx, b->sy, z );
		GX_Color4u8( col2[0], col2[1], col2[2], 0xff );
		GX_Position3f32( c->sx, c->sy, z );
		GX_Color4u8( col2[0], col2[1], col2[2], 0xff );
	}
	GX_End();

	GX_Begin( GX_LINESTRIP, GX_VTXFMT0, NUM_BF_RWING_EDGES );
	for( i=0; i<NUM_BF_RWING_EDGES; i++ )
	{
		GX_Position3f32( bs[bf_rwing_edges[i]].sx, bs[bf_rwing_edges[i]].sy, z );
		GX_Color4u8( 0, 0, 0, 0xff );
	}
	GX_End();
}

void draw_butterfly( f32 angle, f32 wscale, f32 sx, f32 sy, f32 z, u8 *col1, u8 *col2, u8 *col3, s32 small )
{
	s32 i;
	f32 ca, sa;
	struct vtx *a, *b, *c;
	struct vtx *bs;
  
	if( small )
		bs = &bbfly[0];
	else
		bs = &bfly[0];

	ca = cos( angle );
	sa = sin( angle );
  
	for( i=0; i<NUM_BUTTERFLY_VERTICES; i++ )
	{
		bs[i].f1 = 1;
		bs[i].f2 = 1;
	}
  
	GX_Begin( GX_TRIANGLES, GX_VTXFMT0, NUM_BF_BODY_POLYS*3 );
	for( i=0; i<NUM_BF_BODY_POLYS; i++ )
	{
		a = &bs[bf_body_polys[i*3]];
		b = &bs[bf_body_polys[i*3+1]];
		c = &bs[bf_body_polys[i*3+2]];
   
		if( a->f1 )
		{
			a->f1 = 0;
			a->sx = (a->x*ca - a->y*sa) + sx;
			a->sy = (a->x*sa + a->y*ca) + sy;
		}
    
		if( b->f1 )
		{
			b->f1 = 0;
			b->sx = (b->x*ca - b->y*sa) + sx;
			b->sy = (b->x*sa + b->y*ca) + sy;
		}
    
		if( c->f1 )
		{
			c->f1 = 0;
			c->sx = (c->x*ca - c->y*sa) + sx;
			c->sy = (c->x*sa + c->y*ca) + sy;
		}
    
		GX_Position3f32( a->sx, a->sy, z );
		GX_Color4u8( col1[0], col1[1], col2[2], 0xff );
		GX_Position3f32( b->sx, b->sy, z );
		GX_Color4u8( col1[0], col1[1], col2[2], 0xff );
		GX_Position3f32( c->sx, c->sy, z );
		GX_Color4u8( col1[0], col1[1], col2[2], 0xff );
	}
	GX_End();
  
	// Bodge to give a slight "3D" look
	if( angle > 0.0f )
	{
		draw_bf_leftwing( ca, sa, wscale, sx, sy, z, col2, col3, bs );
		draw_bf_rightwing( ca, sa, wscale-0.8f, sx, sy, z, col2, col3, bs );
	} else {
		draw_bf_rightwing( ca, sa, wscale, sx, sy, z, col2, col3, bs );
		draw_bf_leftwing( ca, sa, wscale-0.8f, sx, sy, z, col2, col3, bs );
	}
}

void draw_star( f32 scale, f32 angle, f32 x, f32 y, u8 *col, u8 alpha )
{
	int i, j;
	Mtx m,m1,m2,mv;

	guMtxIdentity(m1);
	guMtxScaleApply( m1, m1, scale, scale, 1.0f );
	guMtxRotAxisRad( m2, &rotax, angle );
	guMtxConcat( m2, m1, m);

	guMtxTransApply( m, m, x, y, 0 );
	guMtxConcat( GXmodelView2D, m, mv );
	GX_LoadPosMtxImm( mv, GX_PNMTX0 );

	GX_Begin( GX_TRIANGLES, GX_VTXFMT0, 3*NUM_STAR_POLYS );
	for( i=0; i<NUM_STAR_POLYS*3; i++ )
	{
		j = star_polys[i]*2;
		GX_Position3f32( star_pts[j], star_pts[j+1], 0.0f );
		GX_Color4u8( col[0], col[1], col[2], alpha );
	}
	GX_End();

	GX_Begin( GX_LINESTRIP, GX_VTXFMT0, NUM_STAR_EDGES );
	for( i=0; i<NUM_STAR_EDGES; i++ )
	{
		j = star_edges[i]*2;
		GX_Position3f32( star_pts[j], star_pts[j+1], 0.0f );
		GX_Color4u8( 0, 0, 0, alpha );
	}
	GX_End();
	

	GX_LoadPosMtxImm (GXmodelView2D, GX_PNMTX0);

	GX_SetTevOp (GX_TEVSTAGE0, GX_PASSCLR);
  	GX_SetVtxDesc (GX_VA_TEX0, GX_NONE);
}

void circle( f32 x, f32 y, f32 r, u8 *col, u8 edge, s32 amt, f32 z )
{
	s32 segs, i;
	f32 a, aa, px, py;
	
	if( r < 1.0f )
	  return;
	
	if( r > 240.0f )
		segs = 60;
	else if( r > 160.0f )
		segs = 44;
	else if( r > 100.0f )
		segs = 36;
	else if( r > 80.0f )
		segs = 28;
	else if( r > 40.0f )
		segs = 20;
	else if( r > 20.0f )
		segs = 14;
	else if( r > 10.0f )
		segs = 10;
	else
		segs = 8;

	aa = (3.14159265f*2.0f) / (f32)segs;
	a = 0.0f;
	
	segs = (segs*amt)/100;

	GX_Begin( GX_TRIANGLEFAN, GX_VTXFMT0, segs+2 );
	GX_Position3f32( x, y, z );
	GX_Color4u8( col[0], col[1], col[2], 0xff );
		
	for( i=0; i<=segs; i++ )
	{
		px = cos( a ) * r + x;
		py = sin( a ) * r + y;
		GX_Position3f32( px, py, z );
		GX_Color4u8( col[0], col[1], col[2], 0xff );
		a -= aa;
	}
	GX_End();
	
	if( edge )
	{
		a = 0.0f;
		GX_Begin( GX_LINESTRIP, GX_VTXFMT0, segs+1 );
		for( i=0; i<=segs; i++ )
		{
			px = cos( a ) * r + x;
			py = sin( a ) * r + y;
			GX_Position3f32( px, py, z );
			GX_Color4u8( 0, 0, 0, 0xff );
			a -= aa;
		}
		GX_End();
	}
}

void draw_sun( f32 x, f32 y, f32 r, f32 ang, u8 *col )
{
	int i;
	Mtx m, mv;

	circle( x, y, r, col, 1, 100, 0.0f );
	
	guMtxIdentity( m );
	guMtxRotAxisRad( m, &rotax, ang );
	guMtxTransApply( m, m, x, y, 0 );
	guMtxConcat( GXmodelView2D, m, mv );
	GX_LoadPosMtxImm( mv, GX_PNMTX0 );

	GX_Begin( GX_QUADS, GX_VTXFMT0, NUMRAYS*4 );
	for( i=0; i<NUMRAYS; i++ )
	{
		GX_Position3f32( sunrays[i*4  ].x     , sunrays[i*4  ].y     , 0.0f );
		GX_Color4u8( col[0], col[1], col[2], 0xff );
		GX_Position3f32( sunrays[i*4+1].x     , sunrays[i*4+1].y     , 0.0f );
		GX_Color4u8( col[0], col[1], col[2], 0xff );
		GX_Position3f32( sunrays[i*4+2].x*0.9f, sunrays[i*4+2].y*0.9f, 0.0f );
		GX_Color4u8( col[0], col[1], col[2], 0xff );
		GX_Position3f32( sunrays[i*4+3].x*0.9f, sunrays[i*4+3].y*0.9f, 0.0f );
		GX_Color4u8( col[0], col[1], col[2], 0xff );
	}
	GX_End();

	for( i=0; i<NUMRAYS; i++ )
	{
		GX_Begin( GX_LINESTRIP, GX_VTXFMT0, 4 );
			GX_Position3f32( sunrays[i*4+3].x, sunrays[i*4+3].y, 0.0f );
			GX_Color4u8( 0, 0, 0, 0xff );
			GX_Position3f32( sunrays[i*4  ].x, sunrays[i*4  ].y, 0.0f );
			GX_Color4u8( 0, 0, 0, 0xff );
			GX_Position3f32( sunrays[i*4+1].x, sunrays[i*4+1].y, 0.0f );
			GX_Color4u8( 0, 0, 0, 0xff );
			GX_Position3f32( sunrays[i*4+2].x, sunrays[i*4+2].y, 0.0f );
			GX_Color4u8( 0, 0, 0, 0xff );
		GX_End();
	}
	

	GX_LoadPosMtxImm (GXmodelView2D, GX_PNMTX0);

	GX_SetTevOp (GX_TEVSTAGE0, GX_PASSCLR);
  	GX_SetVtxDesc (GX_VA_TEX0, GX_NONE);
}

void draw_stalk( f32 angle, f32 scale, f32 sx, f32 sy, u8 *col )
{
	f32 ca, sa;
	s32 i;

	if( scale < 0.2f ) return;

	ca = cos( angle );
	sa = sin( angle );

	for( i=0; i<NUM_STALK_VERTICES; i++ )
	{
		stalk[i].sx = ((stalk[i].x*ca - stalk[i].y*sa) * scale) + sx;
		stalk[i].sy = ((stalk[i].x*sa + stalk[i].y*ca) * scale) + sy;
	}

	GX_Begin( GX_TRIANGLES, GX_VTXFMT0, NUM_STALK_POLYS*3 );
	for( i=0; i<NUM_STALK_POLYS*3; i++ )
	{
		GX_Position3f32( stalk[stalk_polys[i]].sx, stalk[stalk_polys[i]].sy, 1.0f );
		GX_Color4u8( col[0], col[1], col[2], 0xff );
	}
	GX_End();
  
	GX_Begin( GX_LINESTRIP, GX_VTXFMT0, NUM_STALK_EDGES );
	for( i=0; i<NUM_STALK_EDGES; i++ )
	{
		GX_Position3f32( stalk[stalk_edges[i]].sx, stalk[stalk_edges[i]].sy, 1.0f );
		GX_Color4u8( 0, 0, 0, 0xff );
	}
	GX_End();

	stalktopx = ((stopx*ca - stopy*sa)*scale) + sx;
	stalktopy = ((stopx*sa + stopy*ca)*scale) + sy;
}

void draw_petal( f32 ca, f32 sa, f32 scx, f32 scy, f32 sx, f32 sy, f32 z, u8 *col, f32 *smx, f32 *smy, f32 *smr )
{
	int i;

	if( smx )
	{
		*smx =  18.8f * scy * sa + sx;
		*smy = -18.8f * scy * ca + sy;
		*smr =  16.0f * scy;
	}

	if( ( scx < 0.1f ) || ( scy < 0.1f ) )
		return;

	for( i=0; i<NUM_PETAL_VERTICES; i++ )
	{
		petal[i].sx = (petal[i].x*scx*ca - petal[i].y*scy*sa) + sx;
		petal[i].sy = (petal[i].x*scx*sa + petal[i].y*scy*ca) + sy;
	}
	
	GX_Begin( GX_TRIANGLES, GX_VTXFMT0, NUM_PETAL_POLYS*3 );
	for( i=0; i<NUM_PETAL_POLYS*3; i++ )
	{
		GX_Position3f32( petal[petal_polys[i]].sx, petal[petal_polys[i]].sy, z );
		GX_Color4u8( col[0], col[1], col[2], 0xff );
	}
	GX_End();

	GX_Begin( GX_LINESTRIP, GX_VTXFMT0, NUM_PETAL_EDGES );
	for( i=0; i<NUM_PETAL_EDGES; i++ )
	{
		GX_Position3f32( petal[petal_edges[i]].sx, petal[petal_edges[i]].sy, z );
		GX_Color4u8( 0, 0, 0, 0xff );
	}
	GX_End();
}

void draw_flower( struct flower *fl, f32 sx, f32 sy, u8 *col1, u8 *col2 )
{
  s32 i;
  struct petal *p;
  f32 pa, r;
  
  r = fl->r*0.92f;
  
  pa = 0.0f;

  // Position and draw all the petals
  for( i=0; i<8; i++ )
  {
    p = &fl->p[i];
    if( p->attached )
    {
		p->angle = pa;
		p->ca    = cos( pa );
		p->sa    = sin( pa );
		p->x     = p->sa * r;
		p->y     = p->ca * -r;

		p->sx    = p->x+sx;
		p->sy    = p->y+sy;
	  
		if( p->wobble )
		{
			p->scx = sin( p->wba ) * p->wbs + 1.0f;
			p->scy = cos( p->wba + 3.14159265 ) * p->wbs + 1.0f;
		}
      
		if( p->scy > 0.0f ) draw_petal( p->ca, p->sa, p->scx*fl->sc, p->scy*fl->sc, p->sx, p->sy, 2.0f, col1, &p->mx, &p->my, &p->mr );
    }
    
    pa += 3.14159265f / 4.0f;
  }

  circle( sx, sy, fl->r, col2, 0, 100, 3.0f );
}

void draw_pointer( f32 x, f32 y, f32 ang, u8 r, u8 g, u8 b )
{
	Mtx m,mv;

	guMtxRotAxisDeg( m, &rotax, ang );
	guMtxTransApply( m, m, x, y, 0 );
	guMtxConcat( GXmodelView2D, m, mv );
	GX_LoadPosMtxImm( mv, GX_PNMTX0 );

	GX_Begin( GX_TRIANGLES, GX_VTXFMT0, 3 );
		GX_Position3f32(  0.0f,  0.0f, 19.0f );
		GX_Color4u8( r, g, b, 0xa0 );
		GX_Position3f32( 32.0f, 16.0f, 19.0f );
		GX_Color4u8( r, g, b, 0xa0 );
		GX_Position3f32( 16.0f, 32.0f, 19.0f );
		GX_Color4u8( r, g, b, 0xa0 );
	GX_End();

	GX_Begin( GX_LINESTRIP, GX_VTXFMT0, 4 );
		GX_Position3f32(  0.0f,  0.0f, 19.0f );
		GX_Color4u8( 0, 0, 0, 0xff );
		GX_Position3f32( 32.0f, 16.0f, 19.0f );
		GX_Color4u8( 0, 0, 0, 0xff );
		GX_Position3f32( 16.0f, 32.0f, 19.0f );
		GX_Color4u8( 0, 0, 0, 0xff );
		GX_Position3f32(  0.0f,  0.0f, 19.0f );
		GX_Color4u8( 0, 0, 0, 0xff );
	GX_End();

	GX_LoadPosMtxImm (GXmodelView2D, GX_PNMTX0);
}

void draw_cloud( struct cloud *cd, f32 orx, f32 ory, f32 scale, u8 *col )
{
	f32 ca, sa, a2;
	f32 sx, sy;
	s32 i;

	a2 = cd->ang - (3.14159265f/2.0f);

	ca = cos( cd->ang );
	sa = sin( cd->ang );

	sx = (cos(a2)*cd->r)+orx;
	sy = (sin(a2)*cd->r)+ory;
	
	cd->px1 = (clox1*scale*ca - cloy1*scale*sa) + sx;
	cd->py1 = (clox1*scale*sa + cloy1*scale*ca) + sy;
	cd->pr1 = clr1*scale;
	cd->px2 = (clox2*scale*ca - cloy2*scale*sa) + sx;
	cd->py2 = (clox2*scale*sa + cloy2*scale*ca) + sy;
	cd->pr2 = clr2*scale;
	cd->px3 = (clox3*scale*ca - cloy3*scale*sa) + sx;
	cd->py3 = (clox3*scale*sa + cloy3*scale*ca) + sy;
	cd->pr3 = clr3*scale;

	circle( cd->px2, cd->py2, cd->pr2, col, 1, 100, 0.5f );
	circle( cd->px1, cd->py1, cd->pr1, col, 1, 100, 0.5f );
	circle( cd->px3, cd->py3, cd->pr3, col, 1, 100, 0.5f );

	cloudbot[0].sx = (cloudbot[0].x*scale*ca - cloudbot[0].y*scale*sa)+sx;
	cloudbot[0].sy = (cloudbot[0].x*scale*sa + cloudbot[0].y*scale*ca)+sy;
	cloudbot[1].sx = (cloudbot[1].x*scale*ca - cloudbot[1].y*scale*sa)+sx;
	cloudbot[1].sy = (cloudbot[1].x*scale*sa + cloudbot[1].y*scale*ca)+sy;
	cloudbot[2].sx = (cloudbot[2].x*scale*ca - cloudbot[2].y*scale*sa)+sx;
	cloudbot[2].sy = (cloudbot[2].x*scale*sa + cloudbot[2].y*scale*ca)+sy;
	cloudbot[3].sx = (cloudbot[3].x*scale*ca - cloudbot[3].y*scale*sa)+sx;
	cloudbot[3].sy = (cloudbot[3].x*scale*sa + cloudbot[3].y*scale*ca)+sy;

	GX_Begin( GX_QUADS, GX_VTXFMT0, 4 );
	for( i=0; i<4; i++ )
	{
		GX_Position3f32( cloudbot[i].sx, cloudbot[i].sy, 0.5f );
		GX_Color4u8( col[0], col[1], col[2], 0xff );
	}
	GX_End();

	// Huh!?
	if( ( cloudbot[3].sx >= 640.0f ) && ( cloudbot[2].sx >= 640.0f ) ) return;
	if( ( cloudbot[3].sx < 0.0f ) && ( cloudbot[2].sx < 0.0f ) ) return;

	GX_Begin( GX_LINESTRIP, GX_VTXFMT0, 2 );
		GX_Position3f32( cloudbot[3].sx, cloudbot[3].sy, 0.5f );
		GX_Color4u8( 0, 0, 0, 0xff );
		GX_Position3f32( cloudbot[2].sx, cloudbot[2].sy, 0.5f );
		GX_Color4u8( 0, 0, 0, 0xff );
	GX_End();
}
