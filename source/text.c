#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <gccore.h>

#include "text.h"
#include "logotex.h"
#include "tb_bg.h"
#include "tb_btns.h"
#include "thefont.h"

extern Mtx GXmodelView2D;
GXTexObj logotexObj;
GXTexObj tbbgtexObj;
GXTexObj tbbtnstexObj;
GXTexObj tbstexObj;

s32 toptprintneeded = 0;

extern Vector rotax;
extern u8 *tbstex, *topttex;

static char *fadetext = NULL;
static char *nextfadetext = NULL;
static int fadepos, fadeend;

// Text box buttons texture coordinates
#define TXL (0.0f)
#define TXT (0.0f)
#define TXR (23.0f/TBBTNSTEXW)
#define TXB (23.0f/TBBTNSTEXH)

#define TUL (32.0f/TBBTNSTEXW)
#define TUT (0.0f)
#define TUR ((32.0f+28.0f)/TBBTNSTEXW)
#define TUB (28.0f/TBBTNSTEXH)

#define TDL (64.0f/TBBTNSTEXW)
#define TDT (0.0f)
#define TDR ((64.0f+28.0f)/TBBTNSTEXW)
#define TDB (28.0f/TBBTNSTEXH)

#define TXGL (96.0f/TBBTNSTEXW)
#define TXGT (0.0f)
#define TXGR ((96.0f+64.0f)/TBBTNSTEXW)
#define TXGB (64.0f/TBBTNSTEXH)

// Y offset for pressed versions
#define PROFFS (32.0f/TBBTNSTEXH)

s32 tbpressed = 0;
s32 tbdox = 0;
f32 tbauh=0.0f, tbyo;


char *fntab = "abcdefghijklmnopqrstuvwxyz0123456789!=.,:;()\"/_-#%*'?@";
s32 foffs[] = {   0,  16,  30,  48,  65,  78,  90, 108,
                 125, 132, 146, 162, 174, 195, 212, 231,
				 245, 264, 278, 291, 306, 321, 338, 359,
				 375, 389, 403, 421, 430, 443, 456, 471,
				 484, 497, 509, 521, 536, 543, 557, 564,
				 570, 577, 584, 595, 605, 615, 625, 637,
				 645, 658, 677, 688, 693, 706, 724 };


void inittext( void )
{
	GX_InitTexObj( &logotexObj,   logotex,   LOGOTEXW,   LOGOTEXH,   GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE );
	GX_InitTexObj( &tbbgtexObj,   tbbgtex,   TBBGTEXW,   TBBGTEXH,   GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE );
	GX_InitTexObj( &tbbtnstexObj, tbbtnstex, TBBTNSTEXW, TBBTNSTEXH, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE );
	GX_InitTexObj( &tbstexObj,    tbstex,    TBAW*3,     TBAH,       GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE );
}

s32 charwidth( char c )
{
  s32 ch;

  for( ch=0; fntab[ch]; ch++ )
    if( fntab[ch] == c ) break;
    
  if( !fntab[ch] )
    return SPCW;

  return (foffs[ch+1]-foffs[ch])-1;
}

s32 textlen( char *str )
{
  s32 i, ch;
  s32 len;
  
  i=0; len=0;
  while( str[i] )
  {
    for( ch=0; fntab[ch]; ch++ )
      if( fntab[ch] == str[i] ) break;
    
    if( !fntab[ch] )
    {
      len += SPCW;
      i++;
      continue;
    }

    len += (foffs[ch+1]-foffs[ch])-1;
    i++;
  }
  
  return len;
}

static inline void toptplota( s32 x, s32 y, u8 a )
{
	s32 tile, tx, ty;
	
	// Tiles are 2x32 = 64 bytes
	tile = ((y/4)*(640/4)+(x/4))*64;

	tx   = x&3;
	ty   = y&3;

	topttex[tile+(ty*4*2)+(tx*2)] = a;
}



void toptprint( char *str )
{
	s32 i, ch;
	s32 x, xc, yc, xs, xe, fx, fw, pw;

	x = 320 - textlen( str )/2;
	memset( topttex, 0, 640*24*4 );
  
	i=0;
	while( str[i] )
	{
		for( ch=0; fntab[ch]; ch++ )
			if( fntab[ch] == str[i] ) break;
    
		if( !fntab[ch] )
		{
			x += SPCW;
			i++;
			continue;
		}
    
		fx = foffs[ch];
		fw = foffs[ch+1]-fx;
    
		xs = x;
		xe = x+fw;
    
		if( xs < 0 )  xs = 0;
		if( xe > 640 ) xe = 640;
		
		pw = xe-xs;
		
		for( yc=0; yc<24; yc++ )
		{
			for( xc=xs; xc<xe; xc++, fx++ )
				toptplota( xc, yc, thefont[fx] );
			fx += 724-pw;
		}
    
		x += fw-1;
    
		i++;
	}

	DCFlushRange( topttex, 640*24*4 );	
}

void showtopt( s32 alpha )
{
	GXTexObj texObj;

	GX_InitTexObj( &texObj, topttex, 640, 24, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE );
	GX_LoadTexObj( &texObj, GX_TEXMAP0 );
	GX_SetTevOp( GX_TEVSTAGE0, GX_MODULATE );
  	GX_SetVtxDesc( GX_VA_TEX0, GX_DIRECT );

	GX_Begin( GX_QUADS, GX_VTXFMT0, 4 );
		GX_Position3f32(   0.0f,   0.0f, 0.0f );
		GX_Color4u8( 0xff, 0xff, 0xff, alpha );
		GX_TexCoord2f32( 0.0f, 0.0f );

		GX_Position3f32( 640.0f,   0.0f, 0.0f );
		GX_Color4u8( 0xff, 0xff, 0xff, alpha );
		GX_TexCoord2f32( 1.0f, 0.0f );

		GX_Position3f32( 640.0f,  24.0f, 0.0f );
		GX_Color4u8( 0xff, 0xff, 0xff, alpha );
		GX_TexCoord2f32( 1.0f, 1.0f );

		GX_Position3f32(   0.0f,  24.0f, 0.0f );
		GX_Color4u8( 0xff, 0xff, 0xff, alpha );
		GX_TexCoord2f32( 0.0f, 1.0f );
	GX_End();

	GX_SetTevOp( GX_TEVSTAGE0, GX_PASSCLR );
  	GX_SetVtxDesc( GX_VA_TEX0, GX_NONE );
}

void dotoptprint( void )
{
	if( !toptprintneeded ) return;
	
	if( fadetext ) toptprint( fadetext );
	toptprintneeded = 0;
}

void fade_in( char *str, s32 immediate )
{
	if( fadetext == NULL )
	{
		fadetext     = str;
		nextfadetext = NULL;
		fadepos      = 0;
		fadeend      = strlen( str )*8+720;
		toptprintneeded = 1;
		return;
	}
  
	nextfadetext = str;
	if( immediate )
	{
		fadeend = 720;
		fadepos = 720+256;
	}
}

s32 do_fade( s32 fadeadd )
{
	s32 fd;

	if( !fadetext )
	{
		if( nextfadetext )
		{
			fadetext = nextfadetext;
      
			nextfadetext = NULL;
			fadepos = 0;
			fadeend = strlen( fadetext )*8+720;
			toptprintneeded = 1;
		} else {
			fadepos = 0;
			return 1;
		}
	}

	if( toptprintneeded ) return 0;

	fadepos += fadeadd;
  
	if( fadepos < 256 )
	{
		showtopt( fadepos );
		return 0;
	}
	
	if( fadepos < fadeend )
	{
		showtopt( 255 );
		return 0;
	}
	
	fd = 255-(fadepos-fadeend);
	if( fd <= 0 )
	{
		if( nextfadetext )
		{
			fadetext = nextfadetext;
      
			nextfadetext = NULL;
			fadepos = 0;
			fadeend = strlen( fadetext )*8+720;
			
			toptprintneeded = 1;
			return 0;
		}
  
		fadetext = NULL;
		fadepos = 0;
		return 1;
	}
	
	showtopt( fd );
	return 0;
}

static inline void textboxplota( s32 x, s32 y, u8 a )
{
	s32 tile, tx, ty;
	
	// Tiles are 2x32 = 64 bytes
	tile = ((y/4)*((TBAW*3)/4)+(x/4))*64;

	tx   = x&3;
	ty   = y&3;

	tbstex[tile+(ty*4*2)+(tx*2)] = a;
}

void textboxprint( s32 xo, s32 x, s32 y, char *str )
{
	s32 i, ch;
	s32 xc, yc, xs, xe, ye, fx, fw, pw;
  
	i=0;
	while( str[i] )
	{
		if( x >= TBAAW ) break;

		for( ch=0; fntab[ch]; ch++ )
			if( fntab[ch] == str[i] ) break;
    
		if( !fntab[ch] )
		{
			x += SPCW;
			i++;
			continue;
		}
    
		fx = foffs[ch];
		fw = foffs[ch+1]-fx;
    
		xs = x;
		xe = x+fw;
    
		if( xs < 0 )  xs = 0;
		if( xe > TBAAW ) xe = TBAAW;
		
		pw = xe-xs;
		
		ye = y+24;
		for( yc=y; yc<ye; yc++ )
		{
			for( xc=xs; xc<xe; xc++, fx++ )
				textboxplota( xc+xo, yc, thefont[fx] );
			fx += 724-pw;
		}
    
		x += fw-1;
    
		i++;
	}
}

void textbox_layout( char *str )
{
	s32 xl, x, y, by, i, j, k, l, m, lw, w;
	s32 just;
	char line[64];
	
	tbauh = 0.0f;
	tbyo  = 0.0f;
  
	if( !str )
		return;

	memset( tbstex, 0, TBAW*3*TBAH*4 );
	  
	just = 0;
	xl=0; x=0; y=0; by=0; i=0;
	while( str[i] )
	{
		if( y >= TBAH )
		{
			if( xl < (TBAW*2) )
			{
				xl += TBAW;
				y = 0;
			} else {
				break;
			}
		}

		w=0;
		j=0;
		l=0;
		for( ;; )
		{
			// Skip initial whitespace
			while( ( str[i] == 32 ) || ( str[i] == '{' ) || ( str[i] == '}' ) || ( str[i] == '|' ) )
			{
				if( str[i] == '{' ) just = 0;
				if( str[i] == '}' ) just = 1;
				if( str[i] == '|' ) just = 2;
				i++;
			}
    
			lw = w;
			k = j;
			m = i;
			while( ( str[i] != 32 ) && ( str[i] != 0 ) && ( str[i] != '\n' ) )
			{
				if( str[i] == '{' ) { just = 0; i++; continue; }
				if( str[i] == '}' ) { just = 1; i++; continue; }
				if( str[i] == '|' ) { just = 2; i++; continue; }

				l = charwidth( str[i] );
				w += l;
				if( w > TBAAW ) break;
				line[j++] = str[i++];
			}
      
			if( w > TBAAW )
			{
				if( k != 0 )
				{
					w = lw;
					j = k;
					i = m;
				} else {
					w -= l;
				}
				break;
			}
      
			if( str[i] == 0 )
				break;
      
			if( str[i] == '\n' )
			{
				i++;
				break;
			}
      
			line[j++] = 32;
			w += SPCW;
		}

		line[j] = 0;

		switch( just )
		{
			case 0:
				x = 0;
				break;
      
			case 1:
				x = TBAAW - w;
				break;
      
			case 2:
				x = (TBAAW-w) / 2;
				break;
		}
    
		textboxprint( xl, x, y, line );

		y += 24;
		by += 24;
	}
  
	tbauh = (f32)by;
	DCFlushRange( tbstex, TBAW*3*TBAH*4 );	
	GX_InitTexObj( &tbstexObj,    tbstex,    TBAW*3,       TBAH,       GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE );
}


void drawtextbox( f32 x, f32 y, f32 scale, f32 ang, u8 alpha )
{
	Mtx m,m1,m2,mv;
	f32 po;
	f32 tl, tt, tr, tb;
	f32 vl, vt, vr, vb;

	guMtxIdentity( m1 );
	guMtxScaleApply( m1, m1, scale, scale, 1.0f );
	guMtxRotAxisRad( m2, &rotax, ang );
	guMtxConcat( m2, m1, m );

	guMtxTransApply( m, m, x, y, 0 );
	guMtxConcat( GXmodelView2D, m, mv );
	GX_LoadPosMtxImm( mv, GX_PNMTX0 );

	GX_LoadTexObj( &tbbgtexObj, GX_TEXMAP0 );
	GX_SetTevOp( GX_TEVSTAGE0, GX_MODULATE );
	GX_SetVtxDesc( GX_VA_TEX0, GX_DIRECT );

	GX_Begin( GX_QUADS, GX_VTXFMT0, 4 );
		GX_Position3f32( -180.0f, -96.0f, 0.7f );
		GX_Color4u8( 0xff, 0xff, 0xff, alpha );
		GX_TexCoord2f32( 0.0f, 0.0f );

		GX_Position3f32(  180.0f, -96.0f, 0.7f );
		GX_Color4u8( 0xff, 0xff, 0xff, alpha );
		GX_TexCoord2f32( 1.0f, 0.0f );

		GX_Position3f32(  180.0f,  96.0f, 0.7f );
		GX_Color4u8( 0xff, 0xff, 0xff, alpha );
		GX_TexCoord2f32( 1.0f, 1.0f );

		GX_Position3f32( -180.0f,  96.0f, 0.7f );
		GX_Color4u8( 0xff, 0xff, 0xff, alpha );
		GX_TexCoord2f32( 0.0f, 1.0f );
	GX_End();

	GX_LoadTexObj( &tbbtnstexObj, GX_TEXMAP0 );

	GX_Begin( GX_QUADS, GX_VTXFMT0, 8 );
	
		po = (tbpressed==1) ? PROFFS : 0.0f;
	
		GX_Position3f32(  144.0f, -82.0f, 0.7f );
		GX_Color4u8( 0xff, 0xff, 0xff, alpha );
		GX_TexCoord2f32( TUL, TUT+po );

		GX_Position3f32(  172.0f, -82.0f, 0.7f );
		GX_Color4u8( 0xff, 0xff, 0xff, alpha );
		GX_TexCoord2f32( TUR, TUT+po );

		GX_Position3f32(  172.0f, -54.0f, 0.7f );
		GX_Color4u8( 0xff, 0xff, 0xff, alpha );
		GX_TexCoord2f32( TUR, TUB+po );

		GX_Position3f32(  144.0f, -54.0f, 0.7f );
		GX_Color4u8( 0xff, 0xff, 0xff, alpha );
		GX_TexCoord2f32( TUL, TUB+po );

		po = (tbpressed==2) ? PROFFS : 0.0f;

		GX_Position3f32(  144.0f,  54.0f, 0.7f );
		GX_Color4u8( 0xff, 0xff, 0xff, alpha );
		GX_TexCoord2f32( TDL, TDT+po );

		GX_Position3f32(  172.0f,  54.0f, 0.7f );
		GX_Color4u8( 0xff, 0xff, 0xff, alpha );
		GX_TexCoord2f32( TDR, TDT+po );

		GX_Position3f32(  172.0f,  82.0f, 0.7f );
		GX_Color4u8( 0xff, 0xff, 0xff, alpha );
		GX_TexCoord2f32( TDR, TDB+po );

		GX_Position3f32(  144.0f,  82.0f, 0.7f );
		GX_Color4u8( 0xff, 0xff, 0xff, alpha );
		GX_TexCoord2f32( TDL, TDB+po );
	GX_End();
	
	if( tbauh > 0.0f )
	{
		GX_LoadTexObj( &tbstexObj, GX_TEXMAP0 );

		vl = -172.0f;
		vr =  144.0f;
		
		if( tbyo < TBAH )
		{
			vt = -82.0f;
			vb =  82.0f;
			
			tt = tbyo / TBAH;
			tb = tbyo + 164.0f;
			
			if( tb > TBAH )
			{
				vb -= (tb-TBAH);
				tb = TBAH;
			}
			
			tb /= TBAH;

			tl = 0.0f;
			tr = TBAAW / (TBAW*3.0f);

			GX_Begin( GX_QUADS, GX_VTXFMT0, 4 );
				GX_Position3f32( vl, vt, 0.8f );
				GX_Color4u8( 0xff, 0xff, 0xff, alpha );
				GX_TexCoord2f32( tl, tt );

				GX_Position3f32( vr, vt, 0.8f );
				GX_Color4u8( 0xff, 0xff, 0xff, alpha );
				GX_TexCoord2f32( tr, tt );

				GX_Position3f32( vr, vb, 0.8f );
				GX_Color4u8( 0xff, 0xff, 0xff, alpha );
				GX_TexCoord2f32( tr, tb );

				GX_Position3f32( vl, vb, 0.8f );
				GX_Color4u8( 0xff, 0xff, 0xff, alpha );
				GX_TexCoord2f32( tl, tb );
			GX_End();
		}

		if( ( (tbyo+164.0f) > TBAH ) &&
		    ( tbyo < (TBAH*2.0f) ) )
		{
			vt = -82.0f;
			vb =  82.0f;
			
			if( tbyo < TBAH )
			{
				vt += (TBAH-tbyo);
				tt = 0.0f;
				tb = (vb-vt) / TBAH;
			} else {
				tt = (tbyo-TBAH) / TBAH;
				tb = ((tbyo-TBAH)+164.0f);

				if( tb > TBAH )
				{
					vb -= (tb-TBAH);
					tb = TBAH;
				}
				
				tb /= TBAH;
			}
			
			tl = 1.0f/3.0f;
			tr = tl + (TBAAW / (TBAW*3.0f));

			GX_Begin( GX_QUADS, GX_VTXFMT0, 4 );
				GX_Position3f32( vl, vt, 0.8f );
				GX_Color4u8( 0xff, 0xff, 0xff, alpha );
				GX_TexCoord2f32( tl, tt );

				GX_Position3f32( vr, vt, 0.8f );
				GX_Color4u8( 0xff, 0xff, 0xff, alpha );
				GX_TexCoord2f32( tr, tt );

				GX_Position3f32( vr, vb, 0.8f );
				GX_Color4u8( 0xff, 0xff, 0xff, alpha );
				GX_TexCoord2f32( tr, tb );

				GX_Position3f32( vl, vb, 0.8f );
				GX_Color4u8( 0xff, 0xff, 0xff, alpha );
				GX_TexCoord2f32( tl, tb );
			GX_End();
		}

		if( (tbyo+164.0f) > (TBAH*2.0f) )
		{
			vt = -82.0f;
			vb =  82.0f;
			
			if( tbyo < (TBAH*2.0f) )
			{
				vt += (TBAH*2.0f-tbyo);
				tt = 0.0f;
				tb = (vb-vt) / TBAH;
			} else {
				tt = (tbyo-TBAH*2.0f) / TBAH;
				tb = ((tbyo-TBAH*2.0f)+164.0f) / TBAH;
			}
			
			tl = 2.0f/3.0f;
			tr = tl + (TBAAW / (TBAW*3.0f));

			GX_Begin( GX_QUADS, GX_VTXFMT0, 4 );
				GX_Position3f32( vl, vt, 0.8f );
				GX_Color4u8( 0xff, 0xff, 0xff, alpha );
				GX_TexCoord2f32( tl, tt );

				GX_Position3f32( vr, vt, 0.8f );
				GX_Color4u8( 0xff, 0xff, 0xff, alpha );
				GX_TexCoord2f32( tr, tt );

				GX_Position3f32( vr, vb, 0.8f );
				GX_Color4u8( 0xff, 0xff, 0xff, alpha );
				GX_TexCoord2f32( tr, tb );

				GX_Position3f32( vl, vb, 0.8f );
				GX_Color4u8( 0xff, 0xff, 0xff, alpha );
				GX_TexCoord2f32( tl, tb );
			GX_End();
		}
	}

	if( tbdox )
	{
		GX_LoadTexObj( &tbbtnstexObj, GX_TEXMAP0 );
		GX_Begin( GX_QUADS, GX_VTXFMT0, 8 );
	
			po = (tbpressed==3) ? PROFFS : 0.0f;
	
			GX_Position3f32( -174.0f, -84.0f, 0.9f );
			GX_Color4u8( 0xff, 0xff, 0xff, alpha );
			GX_TexCoord2f32( TXGL, TXGT );

			GX_Position3f32( -110.0f, -84.0f, 0.9f );
			GX_Color4u8( 0xff, 0xff, 0xff, alpha );
			GX_TexCoord2f32( TXGR, TXGT );

			GX_Position3f32( -110.0f, -20.0f, 0.9f );
			GX_Color4u8( 0xff, 0xff, 0xff, alpha );
			GX_TexCoord2f32( TXGR, TXGB );

			GX_Position3f32( -174.0f, -20.0f, 0.9f );
			GX_Color4u8( 0xff, 0xff, 0xff, alpha );
			GX_TexCoord2f32( TXGL, TXGB );

			GX_Position3f32( -172.0f, -82.0f, 0.9f );
			GX_Color4u8( 0xff, 0xff, 0xff, alpha );
			GX_TexCoord2f32( TXL, TXT+po );

			GX_Position3f32( -149.0f, -82.0f, 0.9f );
			GX_Color4u8( 0xff, 0xff, 0xff, alpha );
			GX_TexCoord2f32( TXR, TXT+po );

			GX_Position3f32( -149.0f, -59.0f, 0.9f );
			GX_Color4u8( 0xff, 0xff, 0xff, alpha );
			GX_TexCoord2f32( TXR, TXB+po );

			GX_Position3f32( -172.0f, -59.0f, 0.9f );
			GX_Color4u8( 0xff, 0xff, 0xff, alpha );
			GX_TexCoord2f32( TXL, TXB+po );
		GX_End();
	}


	GX_LoadPosMtxImm (GXmodelView2D, GX_PNMTX0);

	GX_SetTevOp (GX_TEVSTAGE0, GX_PASSCLR);
	GX_SetVtxDesc (GX_VA_TEX0, GX_NONE);
}

void setlogotex( void )
{
	GX_LoadTexObj( &logotexObj, GX_TEXMAP0 );
	GX_SetTevOp( GX_TEVSTAGE0, GX_MODULATE );
	GX_SetVtxDesc( GX_VA_TEX0, GX_DIRECT );
}

void clearlogotex( void )
{
	GX_SetTevOp (GX_TEVSTAGE0, GX_PASSCLR);
	GX_SetVtxDesc (GX_VA_TEX0, GX_NONE);
}

void logoletter( f32 x, f32 y, s32 frame, f32 zoom, s32 l )
{
	f32 tl, tt, tr, tb;
	Mtx m,mv;
	
	if( zoom < 0.3f ) return;
	
	guMtxIdentity(m);
	guMtxScaleApply( m, m, zoom, zoom, 1.0f );
	guMtxTransApply( m, m, x, y, 0 );
	guMtxConcat( GXmodelView2D, m, mv );
	GX_LoadPosMtxImm( mv, GX_PNMTX0 );
	
	if( frame < 0 ) frame = 0;
	if( frame > 6 ) frame = 6;

	tl = ((f32)l)*20.0f;
	tt = ((f32)frame)*22.0f;
	
	tr = (tl+18.0f) * (1.0f/320.0f);
	tb = (tt+20.0f) * (1.0f/160.0f);
	
	tl *= 1.0f/320.0f;
	tt *= 1.0f/160.0f;


	GX_Begin( GX_QUADS, GX_VTXFMT0, 4 );
		GX_Position3f32( -9.0f, -10.0f, 0.0f );
		GX_Color4u8( 0xff, 0xff, 0xff, 0xff );
		GX_TexCoord2f32( tl, tt );

		GX_Position3f32(  9.0f, -10.0f, 0.0f );
		GX_Color4u8( 0xff, 0xff,  0xff, 0xff );
		GX_TexCoord2f32( tr, tt );

		GX_Position3f32(  9.0f,  10.0f, 0.0f );
		GX_Color4u8( 0xff, 0xff, 0xff, 0xff );
		GX_TexCoord2f32( tr, tb );

		GX_Position3f32( -9.0f,  10.0f, 0.0f );
		GX_Color4u8( 0xff, 0xff, 0xff, 0xff );
		GX_TexCoord2f32( tl, tb );
	GX_End();

	GX_LoadPosMtxImm (GXmodelView2D, GX_PNMTX0);
}
