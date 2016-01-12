/*---------------------------------------------------------------------------------

	PLANET HIVELY WIIIIIII!

---------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

#include "render.h"
#include "types.h"
#include "hvl_replay.h"

#include "embedded_tunes/syphus-sweeties.h"
#include "embedded_tunes/Virgill-Forsaken.h"
#include "embedded_tunes/syphus-freeside_run.h"
#include "embedded_tunes/lb-peanuts.h"
#include "embedded_tunes/galactic_emeralds.h"
#include "embedded_tunes/joey_splif-pantsomime.h"
#include "embedded_tunes/testing123.h"
#include "embedded_tunes/m0d_-_incognito_crust.h"

#define FREQ 48000
#define HIVELY_LEN FREQ/50
#define OUTPUT_LEN (3840<<2)

extern u8 tempdata[];

static vu32 curr_audio = 0;
static u8 audioBuf[2][OUTPUT_LEN] ATTRIBUTE_ALIGN(32);

static BOOL sndPlaying = FALSE;

s16 hivelyLeft[HIVELY_LEN], hivelyRight[HIVELY_LEN];
size_t hivelyIndex=0;

struct hvl_tune *tune;
s32 ctune = 0;

static void mixcallback(void *usrdata,u8 *stream,u32 length)
{
	s16 *out;
	s32 i, alen;
	size_t streamPos;

	alen = length/2;
	streamPos = 0;

	if( tune )
	{
		// Mix to 16bit interleaved stereo
		out = (s16*) stream;
		// Flush remains of previous frame
		for(i = hivelyIndex; i < (HIVELY_LEN) && streamPos < alen; i++)
		{
			out[streamPos++] = hivelyLeft[i];
			out[streamPos++] = hivelyRight[i];
		}

		while(streamPos < alen)
		{
			hvl_DecodeFrame( tune, (int8 *) hivelyLeft, (int8 *) hivelyRight, 2 );
			for(i = 0; i < (HIVELY_LEN) && streamPos < alen; i++)
			{
				out[streamPos++] = hivelyLeft[i];
				out[streamPos++] = hivelyRight[i];
			}
		}
		hivelyIndex = i;
	}
}

static void dmaCallback()
{   
	AUDIO_StopDMA();
	AUDIO_InitDMA( (u32)audioBuf[curr_audio], OUTPUT_LEN );
	DCFlushRange( audioBuf[curr_audio], OUTPUT_LEN );
	AUDIO_StartDMA();

	curr_audio ^= 1;
	mixcallback( NULL, (u8*)audioBuf[curr_audio], OUTPUT_LEN );
}

void initmusicstuff( void )
{
	AUDIO_Init( NULL );
	hvl_InitReplayer(); 

	sndPlaying = FALSE;

	AUDIO_SetDSPSampleRate( AI_SAMPLERATE_48KHZ );
}

void startmusic( void )
{
	if( sndPlaying ) return;

	memset( audioBuf[0], 0, OUTPUT_LEN );
	memset( audioBuf[1], 0, OUTPUT_LEN );

	DCFlushRange( audioBuf[0], OUTPUT_LEN );
	DCFlushRange( audioBuf[1], OUTPUT_LEN );

	curr_audio = 0;
	sndPlaying = TRUE;

	AUDIO_RegisterDMACallback( dmaCallback );
	AUDIO_InitDMA((u32)audioBuf[curr_audio], OUTPUT_LEN );
	AUDIO_StartDMA();
	curr_audio ^= 1;
}

void stopmusic()
{
	if(!sndPlaying) return;

	AUDIO_StopDMA();
	AUDIO_RegisterDMACallback(NULL);

	curr_audio = 0;
	sndPlaying = FALSE;
}

int start_tune( int n )
{
#if AUDIOENABLE
	stopmusic();

	if( tune ) hvl_FreeTune( tune );
 
	switch (n)
	{
		case 0:
			tune = hvl_reset( (uint8 *)syphus_sweeties_hvl, SYPHUS_SWEETIES_HVL_LEN, 4, FREQ, 0 );
			break;
		case 1:
			tune = hvl_reset( (uint8 *)Virgill_Forsaken_hvl, VIRGILL_FORSAKEN_HVL_LEN, 4, FREQ, 0 );
			break;
		case 2:
			tune = hvl_reset( (uint8 *)syphus_freeside_run_hvl, SYPHUS_FREESIDE_RUN_HVL_LEN, 4, FREQ, 0 );
			break;
		case 3:
			tune = hvl_reset( (uint8 *)lb_peanuts_hvl, LB_PEANUTS_HVL_LEN, 4, FREQ, 0 );
			break;
		case 4:
			tune = hvl_reset( (uint8 *)galactic_emeralds_hvl, GALACTIC_EMERALDS_HVL_LEN, 4, FREQ, 0 );
			break;
		case 5:
			tune = hvl_reset( (uint8 *)joey_splif_pantsomime_hvl, JOEY_SPLIF_PANTSOMIME_HVL_LEN, 4, FREQ, 0 );
			break;
		case 6:
			tune = hvl_reset( (uint8 *)testing123_hvl, TESTING123_HVL_LEN, 4, FREQ, 0 );
			break;
		case 7:
			tune = hvl_reset( (uint8 *)m0d_incognito_crust_hvl, M0D_INCOGNITO_CRUST_HVL_LEN, 4, FREQ, 0 );
			break;
		case 8:
			tune = hvl_reset( (uint8 *)tempdata, 1388, 4, FREQ, 0 );
			break;
  }

  hvl_InitSubsong( tune, 0 );

  startmusic();
#endif
  ctune = n;
  return 1;
}

//---------------------------------------------------------------------------------
int main( int argc, char **argv ){
//---------------------------------------------------------------------------------
	render_init();
#if AUDIOENABLE
	initmusicstuff();
	start_tune( 0 );
#endif

	while(1)
	{
		u32 tapped;
		WPAD_ScanPads();
		
		tapped = WPAD_ButtonsDown( 0 );
		
		if( tapped & WPAD_BUTTON_HOME ) break;

		timing();
		if( render( tapped ) )
			break;
		flip();
	}
	
#if AUDIOENABLE
	stopmusic();
	hvl_FreeTune( tune );
#endif
	return 0;
}
 
