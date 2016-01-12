#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

#include "render.h"
#include "shapes.h"
#include "text.h"
#include "types.h"
#include "hvl_replay.h"

char *tunename[] = { "sweeties",
                     "forsaken",
                     "freeside run",
                     "peanuts",
                     "galactic emeralds",
                     "pantsomime",
                     "testing123",
                     "incognito crust",
                     "bonus track" };

char *author[] = { "syphus/up rough",
                   "virgill/haujobb",
                   "syphus/up rough",
                   "lavaburn/hsc",
                   "monk",
                   "joey and splif",
                   "breed",
                   "m0d",
                   "???" };

char *authnotes[] = { "syphus says: started ages ago, finished at the last minute "
                      "(4.38am on 31/01/2007;), designed for clumsy "
                      "dancing and star-crossed ceiling-staring. "
                      "much love to all...",
                      
                      "virgill says: nothing!",
                      
                      "syphus says: gartantuan greets to the usuals, with extra "
                      "hearts to xeron, spotup and exobuzz for this "
                      "amazing software and for their tireless feature "
                      "implementations^:) words to d0pefish for all the "
                      "hardware help and fuckings to parapete for "
                      "killing the scene.",
                      
                      "lavaburn says: a little reggae-style piece, done in an insane hurry, "
                      "literally a couple of hours before the deadline! this "
                      "would be my first tune made in hively tracker; i am also "
                      "learning ahx...^:) thanks to syphus for giving me the "
                      "poke in the ribs necessary for me to actually do "
                      "some work. :) and huuuge thanks to xeron, spotup and "
                      "exobuzz for all their hard work in bringing us this "
                      "brilliant tracker! cheers!^:)",

                      "monk says: hey all! hivelytracker is a really wonderful tool, very "
                      "user-friendly and wonderful for old tracker-composers "
                      "like me. i seriously recommend it for anyone who has "
                      "enjoyed protracker, odintracker, goattracker, "
                      "fasttrackerii or renoise. but also for people who have "
                      "used to sequencing^- maybe this is the tracker that will "
                      "let you realize the good side about tracking also! "
                      "greetings to all #amigascne people, klegg, parazite, "
                      "my mom, zetanet, thoron, siiseli, genny and others that "
                      "i forgot. peace and love for all!",
                      
                      "joey and splif say: joey and splif graeet al friens and even haterzx!! lol "
                      "pease out nubes",

                      "breed says: long live commodore!",
                      
                      "m0d says: greetings to all the #milkytracker folks and all of my "
                      "dear friends at #modarchive on espernet, and thanks to "
                      "the folks who've been proactivly bringing freshness to "
                      "the scene i.e the hivelytracker folks :) i've been "
                      "ahx-type-tracker-composing since december 2006 (the "
                      "12th to be exact), at this point i've created 13 ahx "
                      "songs, i haven't tracked since my protracker days in "
                      "1996 and this ahx revival (and being part of it) is "
                      "really kicking some arse! although i mainly use my "
                      "trusty old amiga to run ahx, running hivelytracker "
                      "under winuae was, in a fashion, a lot of fun. "
                      "thanks for the experience, and thanks for reading "
                      "this blahness :)",
                      
                      "congratulations on finding the bonus track. you must "
                      "now listen to it non stop for 3 days, or until your "
                      "head explodes :-)" };

char *top_blah[] = { "www.hivelytracker.com",
                     "www.irishq.dk",
                     "www.uprough.net",
                     "bbcode and unicode don't work on the oneliner",
                     "super special greets to abyss. thanks for ahx :-)",
                     NULL };

char *othertexts[] = { "|welcome to\n\n"
                       "planet hively\n"
                       "\n"
                       "{this music disk contains all the entries to the "
                       "first official hively tracker competition. users of "
                       "hively tracker were invited to submit tunes to be "
                       "judged by the members of iris and up rough. the "
                       "winner was given a c64 dtv, courtesy of ggs-data!\n\n\n"
                       "|the results\n"
                       "\n"
                       "{1:sweeties by syphus\n"
                       "}(17 points)\n\n"
                       "{2:forsaken by virgill\n"
                       "}(16 points)\n\n"
                       "{3:freeside run by syphus\n"
                       "}(13 points)\n\n"
                       "{4:peanuts by lavaburn\n"
                       "}(11 points)\n\n"
                       "{4:galactic emeralds by monk\n"
                       "}(11 points)\n\n"
                       "{5:pantsomime by joey and splif\n"
                       "}(3 points)\n\n"
                       "{6:testing123 by breed\n"
                       "}(2 points)\n\n"
                       "{7:incognito crust by m0d\n"
                       "}(0 points)\n\n"
                       "{thanks to all entrants and congratulations to "
                       "syphus! hope you've enjoyed your c64 dtv for the "
                       "past year or so while waiting for this musicdisk!",
                       
                       "|credits\n"
                       "\n"
                       "{code, design, gfx\n"
                       "}xeron/iris\n\n"
                       "{design, gfx\n"
                       "}spot/up rough\n\n"
                       "{music\n"
                       "}syphus/up rough\n"
                       "virgill/haujobb\n"
                       "lavaburn/hsc\n"
                       "monk\n"
                       "joey and splif\n"
                       "breed\n"
                       "m0d\n\n"
                       "{yes, i know, this musicdisk is very, very late. "
                       "the original plan was to make it for 030 amigas "
                       "but that requires an assembler optimised "
                       "replayer. currently the replayer "
                       "only exists in fairly unoptimised c code form "
                       "and requires a fast 68k amiga. a couple "
                       "of different people offered to create an optimised "
                       "player, but here we are well over a year later without "
                       "one, so i decided to code the musicdisk in "
                       "plain c and sdl, so that it could be ported to "
                       "as many platforms as possible, and here is the "
                       "result. i hope you like it...\n"
                       "}xeron/iris",
                       
                       "|greets\n"
                       "\n"
                       "apathy, dcs, depth, drifters, ephidrena, fairlight, "
                       "haujobb, loonies, mankind, nature, perihelion, rebels, "
                       "rno, scarab, software failure, tbl, triad, tulou "
                       "and ukscene allstars!"
                       "\n\n\n"
                       "personal greets from xeron\n"
                       "\n"
                       "bonkers: hope to see you soon...\n\n"
                       "britelite: arse!\n\n"
                       "doooooom: egallib!\n\n"
                       "parapete: moo!\n\n"
                       "spot: keep on porting :-)\n\n"
                       "syphus: keep on hivelying :-)\n\n",

                       "\n\nlike these tunes? why not download the "
                       "tracker they were made in? its available "
                       "for amiga os3, os4 and aros, and it kicks "
                       "ass. download it from:\n\n"
                       "|www.hivelytracker.com\n\n"
                       "{where you'll also find friendly forums, "
                       "the latest hively news, and a very exciting "
                       "full stop.\n\n\n\n\n"
                       "do not use hively tracker if you are pregnant, "
                       "stupid, or suffer from tone deafness. "
                       "consult your doctor if symptoms persist.",
                       
                       "\n\nevening phreekz! what's up?\n"
                       "\n"
                       "spot / up rough on da keys! this disk is more "
                       "than a little delayed. life got in the way as "
                       "usual... atm my apartmen is getting a facelift "
                       "and i am living at my dads place in the middle "
                       "of the sea.... me and sabina went to strandbaren "
                       "to get some hangover food and to check out the "
                       "local fishermen types, the usual crowd of fishermen "
                       "and drunks was hanging in the bar, the food was "
                       "so-so. nothing much going on here. i hope i am "
                       "moving back to my apartment in a week or so.. "
                       "hively tracker development has been slow lately, "
                       "xeron has a lot of other projects going on and "
                       "he has also moved to a house, i think. "
                       "the tracks submitted to the compo was of quite "
                       "high quality, that's nice, my personal favourite "
                       "was the track by virgill. it has a genuine oldskool "
                       "touch to it that i like. syphus won the competition, "
                       "congrats not only for winning, but also for making "
                       "it to the top crew, welcome to up rough man!\n"
                       "\n"
                       "so what's going on in up rough then?...\n"
                       "\n"
                       "we are 10 years old! the anniversary party was a "
                       "blast! we packed the place with people, and they "
                       "all seemed to enjoy it a lot! there's lots of "
                       "videos and photos from the party to be found "
                       "on www.uprough.net. we recorded all dj sets and "
                       "live acts from the party too, there's many hours "
                       "of music waiting to be smacked into your ipods! "
                       "some of the compusphere organizers was present "
                       "at the party too, and they decided to dedicate "
                       "this years edition of compusphere to up rough! "
                       "thanx guys! we will try to deliver something fresh!\n"
                       "\n"
                       "about this disk then.. the aim was "
                       "for it to be multiplatform and we'll "
                       "do our best to get it out on as many "
                       "platforms as possible!\n"
                       "\n"
                       "gotta send this text to xeron now, "
                       "so see ya all next time!\n"
                       "\n"
                       "dipswitch on the keys. i am forced to write this "
                       "text else i will be toe'd by spot. greets to all "
                       "people who make the scene a warm place in these "
                       "cold days, and see you around the bonfire on "
                       "breakpoint!",

                       "|darkhawk speaks!\n"
                       "\n"
                       "{hey there sceners and welcome to "
                       "a new iris release, this time in "
                       "co-operation with up rough. we've "
                       "been quite silent for a while and "
                       "had some changes in the group, but "
                       "as you can see, we're not dead. "
                       "this production has been released "
                       "on several platforms, continuing "
                       "the small trend the last eurochart "
                       "started of multiplatform release. "
                       "in the future, you will see more "
                       "releases from iris on non 68k platforms, "
                       "demos mostly, but this doesn't mean we "
                       "will forget the classic amiga. perhaps "
                       "you will see a release from us at "
                       "breakpoint 2008 and perhaps our next "
                       "release will first see the light of day "
                       "later this year, but we're still here, "
                       "both giving to the scene and watching it.\n\n"
                       "keep the scene in your heart and keep "
                       "releasing your work, be it for amiga "
                       "or pc - the world needs the little "
                       "niche of computer art and creativity "
                       "here. :)",

                       "|some ramblings\nfrom syphus\n"
                       "\n"
                       "{well, we waited a year for this musicdisk to "
                       "be ready and once it finally got finished, i "
                       "held it up for another few weeks by being a lazy "
                       "bastard about writing this text... and now i don't "
                       "even know what to say. hivelytracker is fucking "
                       "amazing, first of all. since its release in 2006/7, "
                       "xeron has gone from being quiet, mild-mannered amiga genius "
                       "to the face that men and women now shut their eyes "
                       "and imagine while having loud sex.\n\n"
                       "if you're checking out this disk, you probably already "
                       "know why hivelytracker is so amazing - and not only "
                       "because of its sixteen channels of ahx-spec, "
                       "sid-reminiscent chipsynth sound, nor because of its "
                       "extra effects column, amazing ringmod capabilities, "
                       "tabbed module loading, the ability to load and save ahx "
                       "files or the 256-increment, per-instrument/per-channel "
                       "stereo positioning feature. no, it's not only for these "
                       "reasons: it also has to do with buzz/bitfellas tirelessly "
                       "porting it to 68k amiga and aros from os4 and with "
                       "spot/up rough making it look so fucking brill with a "
                       "selection of interface skins.\n\n"
                       "so while these towering bastions of manhood "
                       "doth bestride this narrow world like code-colossi, "
                       "we peons do our best to use their gift for good. "
                       "it's been loads of fun writing hvl tunes for the last "
                       "year, and it was great fun to take part in the competition "
                       "that led to this chipdisk. some great stuff's appeared "
                       "for hively, from amiga oldschoolers and tracking newcomers "
                       "alike. anyway, i don't need to ramble on about that, "
                       "since you can check that shit out for yourself.\n\n"
                       "spot and xeron need extra creds for this lovely, "
                       "multi-platform sdl musicdisk (which was well worth "
                       "waiting for) and of course shouts and smiles have to "
                       "fly to everyone who contributed. oh, and to ggs data ;)\n\n"
                       "p.s. - lavaburn: get off that fucking xbox 360 and "
                       "finish some hively tunes :d",
                       
                       "|so this is it\n"
                       "\n"
                       "it is finally done\n"
                       "\n"
                       "after many delays and let downs\n"
                       "\n"
                       "we can rest.\n"
                       "\n"
                       "\n"
                       "until the next time..." };

char nptxt[128];
char antxt[128];
char *antxtptr = NULL;
int notxttime=0;
int tbtxtnum=0;

extern struct hvl_tune *tune;

#define DEFAULT_FIFO_SIZE	(4096*1024)

extern s32 ctune;
int start_tune( int n );

#define MAXFPETS 32
struct floating_petal fpt[MAXFPETS];
s32 nextfpeta=0,nextfpetb=0;

#define SKYTEXW 8
#define SKYTEXH 512
u8 *skytex, *skytex2, *tbstex, *topttex; 
u8 skyrgb[SKYTEXH*3];
u8 skyrgb2[SKYTEXH*3];

f32 pointera=0.0f, bfbnc, deaddrop;

u32 part;
s32 starsa;

u32 fps;
f32 ffps;
u32 fb=0;
static void *xfb[2] = { NULL, NULL};
GXRModeObj *rmode;
void *gp_fifo = NULL;
Mtx GXmodelView2D;

s32 readpetal = -1;

f32 plx,  ply,  plr, ptrg;
f32 pldx, pldy, pldr;

f32 tbx, tby, tbsc, tbang, dtbsc, dtbang;
s32 tba, dtba, tbon;
extern s32 tbpressed, tbdox;
extern f32 tbyo, tbauh;
s32 tbdragger = 0;
f32 tbdragx, tbdragy;

struct ir_t ir;

int fadea=0;

#define NUMSTARS 32
struct star stars[NUMSTARS];

#define NUMBFLYS 2
struct butterfly bflys[NUMBFLYS];

#define NUMBBFLYS 2
struct butterfly bbflys[NUMBBFLYS];

#define NUMCLOUDS 4
struct cloud clouds[NUMCLOUDS];

int gcount;
f32 sunx, suny, sundy, sunty, sunr;
f32 sunang = 0.0f;
int pl_r, pl_rd, pl_g, pl_gd;

GXColor bgcol = { 0, 0, 0, 0xff };

extern struct vtx sunrays[];

f32 stalktopx, stalktopy;
struct flower flwr[2];
float fla1=0.0f, fla2=0.0f;

int topfader, topfadeadd;

// irsandupoghetlvy
// 0123456789012345
s8 llorder[] = {		0,  1,  0,  2, -1,
						3,  4,  5, -1,
						6,  7, -1,  1,  8,  6,  9, 10,

						7,  1, 11,  2, 11,  4, 12,

						7, 13,  3,  4, 11, 12, -1,
						10,  0, 14, 11, 13, 15 };

s32 introdat[] = {		0, 17, 0, 110,   //  50,
						17,  7, 0, 180,   // 118,
						24, 13, 0, 310 }; // 192

s32 introappear[17];
s32 intropart, introdoing=0;
f32 introzoom[17], introzoomsub, introzoomtarg;

#define PAL_ENTRIES 55
u8 pal[] = {	0x00, 0x00, 0x00,
				0x00, 0x00, 0x00,
				0xff, 0xff, 0x00,
				0x40, 0xff, 0x40,
				0xff, 0xff, 0xff,
				0xe0, 0xe0, 0xe0,
				0xd0, 0xd0, 0xd0,
				0xc0, 0xc0, 0xc0,
				0xb0, 0xb0, 0xb0,
				0xa0, 0xa0, 0xa0,
				0x90, 0x90, 0x90,
				0x80, 0x80, 0x80,
				0x70, 0x70, 0x70,
				0x60, 0x60, 0x60,
				0x50, 0x50, 0x50,
				0x40, 0x40, 0x40,
				0x30, 0x30, 0x30,
				0x20, 0x20, 0x20,
				0x10, 0x10, 0x10,
				0x00, 0x00, 0x00,
				0x40, 0xff, 0xff,
				0xff, 0x20, 0x20,
				0xee, 0xbb, 0x00,   // 22
				0xff, 0xff, 0xbb,   // 23
				0xa0, 0x00, 0xa0,   // 24
				0x01, 0x06, 0x08,   // 25
				0x01, 0x06, 0x08,
				0x02, 0x0c, 0x0f,
				0x03, 0x12, 0x17,
				0x03, 0x18, 0x1f,
				0x04, 0x1e, 0x26,   // 30
				0x05, 0x24, 0x2e,
				0x06, 0x2a, 0x36,
				0x07, 0x30, 0x3d,
				0x08, 0x36, 0x45,
				0x09, 0x3c, 0x4d,   // 35
				0x0a, 0x42, 0x54,
				0x0a, 0x48, 0x5c,
				0x0b, 0x4e, 0x64,
				0x0c, 0x54, 0x6b,
				0x0d, 0x5a, 0x73,   // 40
				0x0e, 0x5f, 0x7b,
				0x0f, 0x65, 0x82,
				0x10, 0x6b, 0x8a,
				0x10, 0x71, 0x92,
				0x11, 0x77, 0x99,   // 45
				0x12, 0x7d, 0xa1,
				0x13, 0x83, 0xa9,
				0x14, 0x89, 0xb0,
				0x15, 0x8f, 0xb8,
				0x16, 0x95, 0xc0,   // 50
				0x17, 0x9b, 0xc7,
				0x17, 0xa1, 0xcf,
				0x18, 0xa7, 0xd7,
				0x19, 0xad, 0xde,
				0x1a, 0xb3, 0xe6 };

void flip( void )
{
	GX_DrawDone();
	
	switch( part )
	{
		case PART_MAIN:
			dotoptprint();
			if( ( readpetal > -1 ) && ( readpetal < 8 ) )
			{
				textbox_layout( othertexts[readpetal] );
				readpetal = -1;
				tbon = 1;
			}
			break;
	}

	fb ^= 1;
	GX_SetZMode( GX_TRUE, GX_LEQUAL, GX_TRUE );
	GX_SetColorUpdate( GX_TRUE );
	GX_CopyDisp( xfb[fb], GX_TRUE );
	VIDEO_SetNextFramebuffer( xfb[fb] );
	VIDEO_Flush();
	VIDEO_WaitVSync();
}

void skyrgb_to_skytex( u8 *srgb, u8 *stex )
{
	int x, y, tx, ty;
	int r, g, b, o;

	o=0;
	for( y=0; y<SKYTEXH/4; y++ )
	{
		for( x=0; x<SKYTEXW/4; x++ )
		{
			for( ty=0; ty<4; ty++ )
			{
				r = srgb[((y*4)+ty)*3  ];
				g = srgb[((y*4)+ty)*3+1];
				b = srgb[((y*4)+ty)*3+2];
				for( tx=0; tx<4; tx++ )
				{
					stex[ty*8+tx*2+o   ] = 0xff;    // a
					stex[ty*8+tx*2+o+1 ] = r;       // r
					stex[ty*8+tx*2+o+32] = g;       // g
					stex[ty*8+tx*2+o+33] = b;       // b
				}
			}
			o += 64;
		}
	}
  
	DCFlushRange( stex, SKYTEXW*SKYTEXH*4 );
}

void create_space_bg( void )
{
	int r, g, b;
	int rd, gd, bd;
	int yt, yb;
	
	r = g = b = 0;
	rd = (85<<8) / (SKYTEXH/2);
	gd = ( 8<<8) / (SKYTEXH/2);
	bd = (65<<8) / (SKYTEXH/2);
  
	for( yt=0, yb=SKYTEXH-1; yt<(SKYTEXH/2); yt++, yb-- )
	{
		skyrgb[yt*3  ] = (r>>8)+(rand()&3);
		skyrgb[yt*3+1] = (g>>8)+(rand()&3);
		skyrgb[yt*3+2] = (b>>8)+(rand()&3);
		skyrgb[yb*3  ] = (r>>8)+(rand()&3);
		skyrgb[yb*3+1] = (g>>8)+(rand()&3);
		skyrgb[yb*3+2] = (b>>8)+(rand()&3);
		r += rd; g += gd; b += bd;
	}

	skyrgb_to_skytex( skyrgb, skytex );
}

void create_sky_bg( void )
{
	int r, g, b;
	int rd, gd, bd;
	int yb;

	r = 45<<8;
	g = 225<<8;
	b = 245<<8;
	rd = ((255<<8)-r) / SKYTEXH;
	gd = ((255<<8)-g) / SKYTEXH;
	bd = ((255<<8)-b) / SKYTEXH;
  
	for( yb=0; yb<SKYTEXH; yb++ )
	{
		skyrgb2[yb*3  ] = r>>8;
		skyrgb2[yb*3+1] = g>>8;
		skyrgb2[yb*3+2] = b>>8;
		r += rd; g += gd; b += bd;
	}
  
	skyrgb_to_skytex( skyrgb2, skytex2 );
}

void drawspace( void )
{
	GXTexObj texObj;

	GX_InitTexObj( &texObj, skytex, SKYTEXW, SKYTEXH, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE );
	GX_LoadTexObj( &texObj, GX_TEXMAP0 );
	GX_SetTevOp( GX_TEVSTAGE0, GX_MODULATE );
  	GX_SetVtxDesc( GX_VA_TEX0, GX_DIRECT );

	GX_Begin( GX_QUADS, GX_VTXFMT0, 4 );
		GX_Position3f32(   0.0f,   0.0f, 0.0f );
		GX_Color4u8( 0xff, 0xff, 0xff, 0xff );
		GX_TexCoord2f32( 0.0f, 0.0f );

		GX_Position3f32( 640.0f,   0.0f, 0.0f );
		GX_Color4u8( 0xff, 0xff, 0xff, 0xff );
		GX_TexCoord2f32( 1.0f, 0.0f );

		GX_Position3f32( 640.0f, 480.0f, 0.0f );
		GX_Color4u8( 0xff, 0xff, 0xff, 0xff );
		GX_TexCoord2f32( 1.0f, 1.0f );

		GX_Position3f32(   0.0f, 480.0f, 0.0f );
		GX_Color4u8( 0xff, 0xff, 0xff, 0xff );
		GX_TexCoord2f32( 0.0f, 1.0f );
	GX_End();

	GX_SetTevOp( GX_TEVSTAGE0, GX_PASSCLR );
  	GX_SetVtxDesc( GX_VA_TEX0, GX_NONE );
}

void drawsky( uint8 alpha )
{
	GXTexObj texObj;

	GX_InitTexObj( &texObj, skytex2, SKYTEXW, SKYTEXH, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE );
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

		GX_Position3f32( 640.0f, 480.0f, 0.0f );
		GX_Color4u8( 0xff, 0xff, 0xff, alpha );
		GX_TexCoord2f32( 1.0f, 1.0f );

		GX_Position3f32(   0.0f, 480.0f, 0.0f );
		GX_Color4u8( 0xff, 0xff, 0xff, alpha );
		GX_TexCoord2f32( 0.0f, 1.0f );

	GX_End();

	GX_SetTevOp( GX_TEVSTAGE0, GX_PASSCLR );
  	GX_SetVtxDesc( GX_VA_TEX0, GX_NONE );
}

void sort_stars( void )
{
	int i, sorted;
	struct star tstr;
	
	// Crappy bubble sort for now
	do {
		sorted = 1;
		
		for( i=0; i<(NUMSTARS-1); i++ )
		{
			if( stars[i].scale > stars[i+1].scale )
			{
				sorted = 0;
				tstr = stars[i];
				stars[i] = stars[i+1];
				stars[i+1] = tstr;
			}	
		}
	} while( !sorted );
}

void show_now_playing( int immediate )
{
	sprintf( nptxt, "now playing: \"%s\" by %s",
		tunename[ctune],
		author[ctune] );
	fade_in( nptxt, immediate );
  
	antxtptr = authnotes[ctune];
}



void reset_bbfly( s32 i )
{
	if( rand()&1 )
	{
		bbflys[i].sx = (f32)((rand()%640)-640);
		bbflys[i].tsx = (f32)((rand()%640)+640);
		bbflys[i].ang = 3.14159265/6.0f;
	} else {
		bbflys[i].sx = (f32)((rand()%640)+640);
		bbflys[i].tsx = (f32)((rand()%640)-640);
		bbflys[i].ang = -3.14159265f/6.0f;
	}
	bbflys[i].sy = (f32)((rand()%120)+240);
	bbflys[i].tsy = (f32)((rand()%120)+240);
	bbflys[i].dsx = (bbflys[i].tsx-bbflys[i].sx) / (40.0f*ffps);
	bbflys[i].dsy = (bbflys[i].tsy-bbflys[i].sy) / (40.0f*ffps);
	bbflys[i].dead = 0;
}

void reset_bfly( int i )
{
	if( rand()&1 )
	{
		bflys[i].sx = (f32)((rand()%640)-640);
		bflys[i].tsx = (f32)((rand()%640)+640);
		bflys[i].ang = 3.14159265/6.0f;
	} else {
		bflys[i].sx = (f32)((rand()%640)+640);
		bflys[i].tsx = (f32)((rand()%640)-640);
		bflys[i].ang = -3.14159265f/6.0f;
	}
	bflys[i].sy = (f32)((rand()%240)+120);
	bflys[i].tsy = (f32)((rand()%240)+120);
	bflys[i].dsx = (bflys[i].tsx-bflys[i].sx) / (20.0f*ffps);
	bflys[i].dsy = (bflys[i].tsy-bflys[i].sy) / (20.0f*ffps);
	bflys[i].dead = 0;
}

void reset_cloud( int i )
{
	clouds[i].ang   = (3.14159265f/4.0f)+(((f32)(rand()%20))/40.0f);
	clouds[i].r     = plr + 120.0f + (f32)(rand()%120);
	clouds[i].speed = ((f32)((rand()%20)+10))/(ffps*210.0f);
}

// Shitty shitty bubble sort
// but for 4 items, who cares?
void sort_clouds_by_speed( void )
{
	struct cloud c;
	s32 sorted, i;
  
	do
	{
		sorted = 1;
		for( i=0; i<(NUMCLOUDS-1); i++ )
		{
			if( clouds[i].speed > clouds[i+1].speed )
			{
				c = clouds[i];
				clouds[i] = clouds[i+1];
				clouds[i+1] = c;
				sorted = 0;
			}
		}
	} while( sorted == 0 );
}

void start_part( int n )
{
	s32 i, j;
	f32 ang, anga, fi, fj;

	switch( n )
	{
		case PART_STARFIELD:
			intropart = 0;
			introdoing = 0;

			for( i=0, j=0; i<17; i++ ) j += llorder[i]<1?20:34;
			introdat[2] = 320 - j/2 + 20;
			for( i=17, j=0; i<24; i++ ) j += llorder[i]<1?20:34;
			introdat[6] = 320 - j/2 + 20;
			for( i=24, j=0; i<37; i++ ) j += llorder[i]<1?20:34;
			introdat[10] = 320 - j/2 + 20;

			for( i=0; i<17; i++ )
			{
				introappear[i] = -(i+1) * (fps/15);
				introzoom[i] = 8.0f;
			}
			introzoomsub = 20.0f / fps;
			introzoomtarg = 2.0f;

			fadea = 255;
			for( i=0; i<NUMSTARS; i++ )
			{
				stars[i].sx = (f32)(rand()%640);
				stars[i].sy = (f32)(rand()%480);
				stars[i].ang = ((f32)(rand()&255))/160.0f;
				stars[i].speed = ((f32)(((rand()%4)+1)))*2.0f;
				stars[i].scale = ((f32)stars[i].speed)/10.0f;
				stars[i].speed = (f32)(stars[i].speed*640)/(ffps*16.0f);
			}
			sort_stars();
			break;
		
		case PART_PLANET_IN:
			ptrg = 320.0f;

			plr  = 640.0f / 32.0f;
			pldr = ((640.0f/6.0f)-plr) / (ffps*2.0f);
			plx  = 640.0f + (plr*3.0f);
			ply  = 240.0f;
			pldx = (ptrg-plx) / (ffps*2.0f);
			pldy = 0;
			break;

		case PART_PLANET_ZOOM:
			ptrg = 480.0f*2.5f;
			pldx = ((640.0f * 0.7f) - plx) / (ffps*2.0f);
			pldy = (ptrg-ply) / (ffps*2.0f);
			pldr = ((640.0f * 1.34f)-plr) / (ffps*2.0f);
			break;

		case PART_STARS_OUT:
			starsa = 255;
			break;

		case PART_SUNRISE:
			gcount = 0;
      
			sunr  = 640.0f/13.0f;
			sunx  = 640.0f/7.0f;
			suny  = 480.0f+sunr;
			sunty = (480.0f/6.0f)+24;
			sundy = (sunty-suny) / 128.0f;
      
			pl_r   = 0;
			pl_rd  = (0x20<<8)/128;
			pl_g   = 0;
			pl_gd  = (0xc0<<8)/128;

			ang = 0.0f;
			anga = 3.14159265f/NUMRAYS;
      
			fi = sunr;
			fj = fi * 1.4f;

			for( i=0; i<NUMRAYS; i++ )
			{
				sunrays[i*4  ].x = cos( ang )*fj;
				sunrays[i*4  ].y = sin( ang )*fj;
				sunrays[i*4+1].x = cos( ang+anga )*fj;
				sunrays[i*4+1].y = sin( ang+anga )*fj;
				sunrays[i*4+2].x = cos( ang+anga )*fi;
				sunrays[i*4+2].y = sin( ang+anga )*fi;
				sunrays[i*4+3].x = cos( ang )*fi;
				sunrays[i*4+3].y = sin( ang )*fi;

				ang += anga*2.0f;
			}
			break;
		
		case PART_FLOWERGROW:
			gcount = 255;
			fadea = 0;

			sunr  = 640.0f/13.0f;
			sunx  = 640.0f/7.0f;
			suny  = (480.0f/6.0f)+24;
			sunty = (480.0f/6.0f)+24;
			sundy = (sunty-(480.0f+sunr)) / 128.0f;
      
			ang = 0.0f;
			anga = 3.14159265f/NUMRAYS;
      
			fi = sunr;
			fj = fi * 1.4f;

			for( i=0; i<NUMRAYS; i++ )
			{
				sunrays[i*4  ].x = cos( ang )*fj;
				sunrays[i*4  ].y = sin( ang )*fj;
				sunrays[i*4+1].x = cos( ang+anga )*fj;
				sunrays[i*4+1].y = sin( ang+anga )*fj;
				sunrays[i*4+2].x = cos( ang+anga )*fi;
				sunrays[i*4+2].y = sin( ang+anga )*fi;
				sunrays[i*4+3].x = cos( ang )*fi;
				sunrays[i*4+3].y = sin( ang )*fi;

				ang += anga*2.0f;
			}

			pal[3] = 0x20;
			pal[4] = 0xc0;
			pal[5] = 0x20;

			plx = 640.0f * 0.7f;
			ply = 480.0f*2.5f;
			plr = 640.0f * 1.34f;

			fi = ffps * 0.666f;
		
			flwr[0].sx   = 640.0f * 0.8f;
			flwr[0].sy   = 480.0f * 0.9f;
			flwr[0].r    = 0.0f;
			flwr[0].tr   = 640.0f/15.0f;
			flwr[0].dr   = flwr[0].tr/fi;
			flwr[0].sc   = 0.0f;
      
			flwr[1].sx   = 640.0f * 0.5f;
			flwr[1].sy   = 480.0f * 0.929f;
			flwr[1].r    = 0.0f;
			flwr[1].tr   = 640.0f/19.0f;
			flwr[1].dr   = flwr[1].tr/fi;
			flwr[1].sc   = 0.0f;

			for( i=0; i<8; i++ )
			{
				flwr[0].p[i].attached = 1;
				flwr[0].p[i].wobble   = 0;
				flwr[0].p[i].cangrow  = 1;
				flwr[0].p[i].wba      = 3.14159265f;
				flwr[0].p[i].wbs      = 0.8f;
				flwr[0].p[i].scx      = -i;
				flwr[0].p[i].scy      = -i;

				flwr[1].p[i].attached = 1;
				flwr[1].p[i].wobble   = 0;
				flwr[1].p[i].cangrow  = 1;
				flwr[1].p[i].wba      = 3.14159265f;
				flwr[1].p[i].wbs      = 0.8f;
				flwr[1].p[i].scx      = -i;
				flwr[1].p[i].scy      = -i;
			}
			break;
			
		case PART_MAIN:
			WPAD_SetDataFormat( 0, WPAD_FMT_BTNS_ACC_IR );
			WPAD_SetVRes( 0, 640, 480 );

			fade_in( "click the petals! then the sun when you're done!", 1 );
			show_now_playing( 0 );
			topfader   = 0;
			topfadeadd = fps/5;

			tbx   = 240.0f;
			tby   = 160.0f;
			tbsc  = 0.1f;
			tbang = 3.14159265f;
			tba   = 0;
			tbon  = 0;
			
			dtbsc  = 0.9f / ffps;
			dtbang = 3.14159265f / ffps;
			dtba   = (255<<8) / fps;

			bfbnc = 480.0f/48.0f;
			deaddrop = 240.0f/ffps;

			for( i=0; i<NUMBBFLYS; i++ )
			{
				reset_bbfly( i );
				bbflys[i].wscale = 1.0f;
				bbflys[i].wscd = -2.0f / ffps;
			}
      
			for( i=0; i<NUMBFLYS; i++ )
			{
				reset_bfly( i );
				bflys[i].wscale = 1.0f;
				bflys[i].wscd = -2.0f / ffps;
			}

			for( i=0; i<NUMCLOUDS; i++ )
				reset_cloud( i );
			sort_clouds_by_speed();

			break;
		
		case PART_SUNSET:
			sunty = 480.0f+sunr;
			fadea = 0;
			break;
	}

	part = n;
}

void render_init( void )
{
	f32 yscale;
	u32 xfbHeight;
	Mtx perspective;
	int i;
	u32 *tmp;
	
	VIDEO_Init();
	WPAD_Init();
	WPAD_SetDataFormat( 0, WPAD_FMT_BTNS );
	
	fps = 50;
	ffps = (f32)fps;

	rmode = VIDEO_GetPreferredMode(NULL);
	xfb[0] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
	xfb[1] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

	// Set the framebuffer to all black to avoid
	// whatever is in there getting flashed up
	// briefly.
	tmp = (u32 *)xfb[fb];
	for( i=0; i<(rmode->fbWidth*rmode->xfbHeight)/2; i++ )
	  *(tmp++) = 0x00800080;
  
	VIDEO_Configure( rmode );

	VIDEO_SetNextFramebuffer( xfb[fb] );
	VIDEO_SetBlack( FALSE );
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();

	gp_fifo = memalign( 32, DEFAULT_FIFO_SIZE );
	memset( gp_fifo, 0, DEFAULT_FIFO_SIZE );

	GX_Init( gp_fifo, DEFAULT_FIFO_SIZE );

	GX_SetCopyClear( bgcol, 0x00ffffff );

	yscale = GX_GetYScaleFactor( rmode->efbHeight, rmode->xfbHeight );
	xfbHeight = GX_SetDispCopyYScale( yscale );
	GX_SetClipMode( GX_CLIP_ENABLE );
	GX_SetScissor( 0, 0, rmode->fbWidth, rmode->efbHeight );
	GX_SetDispCopySrc( 0, 0, rmode->fbWidth, rmode->efbHeight );
	GX_SetDispCopyDst( rmode->fbWidth, xfbHeight );
	GX_SetCopyFilter( rmode->aa,rmode->sample_pattern,GX_TRUE, rmode->vfilter );
	GX_SetFieldMode( rmode->field_rendering, ((rmode->viHeight==2*rmode->xfbHeight)?GX_ENABLE:GX_DISABLE) );

	if (rmode->aa)
		GX_SetPixelFmt( GX_PF_RGB565_Z16, GX_ZC_LINEAR );
	else
		GX_SetPixelFmt( GX_PF_RGB8_Z24, GX_ZC_LINEAR );

	GX_SetDispCopyGamma( GX_GM_1_0 );

	// Vertex descriptor
	GX_ClearVtxDesc();
	GX_InvVtxCache();
	GX_InvalidateTexAll();

	GX_SetVtxDesc( GX_VA_TEX0, GX_NONE );
	GX_SetVtxDesc( GX_VA_POS, GX_DIRECT );
	GX_SetVtxDesc( GX_VA_CLR0, GX_DIRECT );

	GX_SetVtxAttrFmt( GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0 );
	GX_SetVtxAttrFmt( GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0 );
	GX_SetVtxAttrFmt( GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0 );
	GX_SetZMode( GX_FALSE, GX_LEQUAL, GX_TRUE );

	GX_SetNumChans( 1 );
	GX_SetNumTexGens( 8 );
	GX_SetTevOp( GX_TEVSTAGE0, GX_PASSCLR );
	GX_SetTevOrder( GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0 );
	GX_SetTexCoordGen( GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY );

	guMtxIdentity( GXmodelView2D );
	guMtxTransApply( GXmodelView2D, GXmodelView2D, 0.0F, 0.0F, -50.0F );
	GX_LoadPosMtxImm( GXmodelView2D, GX_PNMTX0 );

	guOrtho( perspective, 0, 479, 0, 639, 0, 300);
	GX_LoadProjectionMtx( perspective, GX_ORTHOGRAPHIC );

	GX_SetViewport( 0, 0, rmode->fbWidth, rmode->efbHeight, 0, 1 );
	GX_SetBlendMode( GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR );
	GX_SetAlphaUpdate( GX_TRUE );
	
	GX_SetCullMode( GX_CULL_NONE );	

	GX_SetLineWidth( 20,GX_TO_ZERO );
	
	inittext();
	shapes_init();

	topttex = memalign( 32, 640*24*4 );
	skytex = memalign( 32, SKYTEXW*SKYTEXH*4 );
	skytex2 = memalign( 32, SKYTEXW*SKYTEXH*4 );
	tbstex = memalign( 32, TBAW*3*TBAH*4 );

	memset( topttex, 0, 640*24*4 );
	DCFlushRange( topttex, 640*24*4 );
	memset( tbstex, 0, TBAW*3*TBAH*4 );
	DCFlushRange( tbstex, TBAW*3*TBAH*4 );

	create_space_bg();
	create_sky_bg();

	start_part( PART_STARFIELD );
//	start_part( PART_FLOWERGROW );

	for( i=0; i<MAXFPETS; i++ )
		fpt[i].active = 0;
}

void intro_timing( void )
{
	int tunepos, i, j;

	if( !tune ) return; // WTF?!
	if( intropart > 2 ) return;

	tunepos = tune->ht_PosNr*64+tune->ht_NoteNr;
	j = introdat[intropart*4+1];

	switch( introdoing )
	{
		case 0:
			if( tunepos < (64*(intropart+1)) ) break;

			for( i=0; i<j; i++ )
			{
				if( introappear[i] < 24 ) introappear[i]++;
				if( ( introappear[i] > 0 ) && ( introzoom[i] > introzoomtarg ) )
				{
					introzoom[i] -= introzoomsub;
					if( introzoom[i] < introzoomtarg ) introzoom[i] = introzoomtarg;
				}
			}
      
			if( introappear[j-1] == 24 )
			{
				for( i=0; i<j; i++ )
					introappear[i] = -i*2;
				introdoing = 1;
			}
			break;
    
		case 1:
			for( i=0; i<j; i++ )
				if( introappear[i] < 24 )
				{
					introappear[i]+=2;
					if( introappear[i] > 24 ) introappear[i] = 24;
				}
			if( tunepos >= introdat[intropart*4+3] )
				introdoing = 2;
			break;
    
		case 2:
			for( i=0; i<j; i++ )
			{
				if( introappear[i] > -1 )
				{
					introappear[i]--;
					introzoom[i] -= introzoomsub;
					if( introzoom[i] < 0.02f ) introzoom[i] = 0.02f;
				}
				if( introappear[i] > 20 ) break;
			}

			if( introappear[j-1] == -1 )
			{
				intropart++;
				if( intropart > 2 ) break;
				introdoing = 0;
		
				j = introdat[intropart*4+1];
				for( i=0; i<j; i++ )
				{
					introappear[i] = -(i+1) * (fps / 15);
					introzoom[i] = 6.0f;
				}
			}
			break;
	}
}

f32 get_to( f32 current, f32 dest, f32 speed )
{
	if( current == dest ) return current;
	if( current > dest )
	{
		current -= speed;
		if( current < dest )
			current = dest;
		return current;
	}
	current += speed;
	if( current > dest )
		current = dest;
	return current;
}

void nature_timing( void )
{
	s32 i, j;

	j = 0;
	for( i=0; i<NUMCLOUDS; i++ )
	{
		clouds[i].ang -= clouds[i].speed;
		if( clouds[i].ang < -(3.14159265f/2.0f) )
		{
			reset_cloud( i );
			j = 1;
		}
	}
  
	if( j ) sort_clouds_by_speed();

	for( i=0; i<NUMBBFLYS; i++ )
	{
		if( bbflys[i].sx > bbflys[i].tsx )
		{
			bbflys[i].sx += bbflys[i].dsx;
			if( bbflys[i].sx <= bbflys[i].tsx )
			{
				reset_bbfly( i );
				continue;
			}
		} else {
			bbflys[i].sx += bbflys[i].dsx;
			if( bbflys[i].sx >= bbflys[i].tsx )
			{
				reset_bbfly( i );
				continue;
			}
		}
		bbflys[i].sy += bbflys[i].dsy;
  
		if( bbflys[i].wscd > 0.0f )
		{
			if( bbflys[i].wscale < 1.0f )
				bbflys[i].wscale += bbflys[i].wscd;
			else
				bbflys[i].wscd = -bbflys[i].wscd;
		} else {
			if( bbflys[i].wscale > 0.5f )
				bbflys[i].wscale += bbflys[i].wscd;
			else
				bbflys[i].wscd = -bbflys[i].wscd;
		}
	}  

	for( i=0; i<NUMBFLYS; i++ )
	{
		if( bflys[i].dead )
		{
			if( bflys[i].ang > 0.0f )
				bflys[i].ang += 3.1f/ffps;
			else
				bflys[i].ang -= 3.1f/ffps;

			if( bflys[i].sy < 720.0f )
				bflys[i].sy += deaddrop;
			else
				reset_bfly( i );
			continue;
		}
    
		if( bflys[i].sx > bflys[i].tsx )
		{
			bflys[i].sx += bflys[i].dsx;
			if( bflys[i].sx <= bflys[i].tsx )
			{
				reset_bfly( i );
				continue;
			}
		} else {
			bflys[i].sx += bflys[i].dsx;
			if( bflys[i].sx >= bflys[i].tsx )
			{
				reset_bfly( i );
				continue;
			}
		}
		bflys[i].sy += bflys[i].dsy;
  
		if( bflys[i].wscd > 0.0f )
		{
			if( bflys[i].wscale < 1.0f )
				bflys[i].wscale += bflys[i].wscd;
			else
				bflys[i].wscd = -bflys[i].wscd;
		} else {
			if( bflys[i].wscale > 0.5f )
				bflys[i].wscale += bflys[i].wscd;
			else
				bflys[i].wscd = -bflys[i].wscd;
		}
	}  
}

void timing( void )
{
	int i, j;
	switch( part )
	{
		case PART_STARFIELD:
			intro_timing();
			j = 0;
			for( i=0; i<NUMSTARS; i++ )
			{
				stars[i].sx -= stars[i].speed;
				if( stars[i].sx < -128.0f )
				{
					stars[i].sx = 768.0f;
					stars[i].sy = (f32)(rand()%480);
					j = 1;
				}

				stars[i].ang += 2.4f/fps;
			}      
			
			if( j ) sort_stars();
			if( fadea > 0 ) fadea--;
			break;

		case PART_PLANET_IN:
			intro_timing();

			if( plx > ptrg )
			{
				plx += pldx;
				plr += pldr;
			}

			j = 0;
			for( i=0; i<NUMSTARS; i++ )
			{
				stars[i].sx -= stars[i].speed;
				if( stars[i].sx < -128.0f )
				{
					stars[i].sx = 768.0f;
					stars[i].sy = (f32)(rand()%480);
					j = 1;
				}

				stars[i].ang += 2.4f/fps;
			}      
			
			if( j ) sort_stars();
			break;

		case PART_PLANET_ZOOM:
			if( ply < ptrg )
			{
				plx += pldx;
				ply += pldy;
				plr += pldr;
			}

			j = 0;
			for( i=0; i<NUMSTARS; i++ )
			{
				stars[i].sx -= stars[i].speed;
				if( stars[i].sx < -128.0f )
				{
					stars[i].sx = 768.0f;
					stars[i].sy = (f32)(rand()%480);
					j = 1;
				}

				stars[i].ang += 2.4f/fps;
			}      
			
			if( j ) sort_stars();
			break;
		
		case PART_STARS_OUT:
			j = 0;
			for( i=0; i<NUMSTARS; i++ )
			{
				stars[i].sx -= stars[i].speed;
				if( stars[i].sx < -128.0f )
				{
					stars[i].sx = 768.0f;
					stars[i].sy = (f32)(rand()%480);
					j = 1;
				}

				stars[i].ang += 2.4f/fps;
			}      
			
			if( j ) sort_stars();
			
			if( starsa > 0 )
			{
				starsa -= 2;
				if( starsa < 0 ) starsa = 0;
			}
			break;

		case PART_SUNRISE:
			sunang -= 1.8f/ffps;

			if( suny > sunty )
				suny += sundy;
      
			if( gcount < 255 )
			{
				gcount += 2;
				if( gcount > 255 ) gcount = 255;
				pl_r += pl_rd;
				pl_g += pl_gd;
				pal[3] = pl_r>>8;
				pal[4] = pl_g>>8;
				pal[5] = pl_r>>8;
			}
			break;

		case PART_FLOWERGROW:
			sunang -= 1.8f/ffps;
			fla1   += 1.2f/ffps;
			fla2   -= 1.35f/ffps;
      
			for( i=0; i<2; i++ )
			{
				if( flwr[i].sc < (i?0.3f:0.5f) )
					continue;

				if( flwr[i].r < flwr[i].tr )
				{
					flwr[i].r += flwr[i].dr;
					continue;
				}
        
				for( j=0; j<8; j++ )
				{

					if( flwr[i].p[j].cangrow )
					{
						if( flwr[i].p[j].scy < 1.0f )
						{
							flwr[i].p[j].scx += 7.5f/ffps;
							flwr[i].p[j].scy += 7.5f/ffps;
						} else {
							flwr[i].p[j].cangrow = 0;
							flwr[i].p[j].wobble  = 1;
							flwr[i].p[j].wbs     = 0.8f;
							flwr[i].p[j].wba     = 3.14159265f;
						}
						continue;
					}
          
					if( flwr[i].p[j].wobble )
					{
						flwr[i].p[j].wbs -= 0.30f/ffps;
						if( flwr[i].p[j].wbs < 0.0f )
						{
							flwr[i].p[j].wbs = 0.0f;
							flwr[i].p[j].wobble = 0;
						}
						flwr[i].p[j].wba += 6.5f/ffps;
					}
				}
			}

			if( flwr[0].sc < 1.0f )  flwr[0].sc += 0.015f;
			if( flwr[1].sc < 0.68f ) flwr[1].sc += 0.01f;
			break;

		case PART_MAIN:
			sunang -= 1.8f/ffps;
			fla1   += 1.2f/ffps;
			fla2   -= 1.35f/ffps;
			pointera += 2.1f/ffps;

			topfader += topfadeadd;
			
			nature_timing();
			
			if( antxtptr )
			{
				notxttime = 0;
			} else {
				notxttime++;
				if( notxttime >= fps * 10 )
				{
					fade_in( top_blah[tbtxtnum++], 0 );
					if( top_blah[tbtxtnum] == NULL )
						tbtxtnum = 0;
					notxttime = 0;
				}
			}

			if( tbon )
			{
				if( tba < (255<<8) )
				{
					tba += dtba;
					if( tba > (255<<8) ) tba = 255<<8;
				}
				if( tbsc < 1.0f )
				{
					tbsc += dtbsc;
					if( tbsc > 1.0f ) tbsc = 1.0f;
				}
				if( tbang < (3.14159265f*2.0f) )
				{
					tbang += dtbang;
					if( tbang > (3.14159265f*2.0f) ) tbang = (3.14159265f*2.0f);
				}
			} else {
				if( tba > 0 )
				{
					tba -= dtba;
					if( tba < 0 ) tba = 0;
				}
				if( tbsc > 0.1f )
				{
					tbsc -= dtbsc;
					if( tbsc < 0.1f ) tbsc = 0.1f;
				}
				if( tbang > 3.14159265f )
				{
					tbang -= dtbang;
					if( tbang < 3.14159265f ) tbang = 3.14159265f;
				}
			}

			for( i=0; i<2; i++ )
			{
				for( j=0; j<8; j++ )
				{
					if( !flwr[i].p[j].attached )
						continue;

					if( flwr[i].p[j].cangrow )
					{
						if( flwr[i].p[j].scy < 1.0f )
						{
							flwr[i].p[j].scx += 7.5f/ffps;
							flwr[i].p[j].scy += 7.5f/ffps;
						} else {
							flwr[i].p[j].cangrow = 0;
							flwr[i].p[j].wobble  = 1;
							flwr[i].p[j].wbs     = 0.8f;
							flwr[i].p[j].wba     = 3.14159265f;
						}
						continue;
					}

					if( flwr[i].p[j].wobble )
					{
						flwr[i].p[j].wbs -= 0.30f/ffps;
						if( flwr[i].p[j].wbs < 0.0f )
						{
							flwr[i].p[j].wbs = 0.0f;
							flwr[i].p[j].wobble = 0;
						}
						flwr[i].p[j].wba += 6.5f/ffps;
					}
				}
			}

			for( i=0; i<MAXFPETS; i++ )
			{
				if( fpt[i].active )
				{
					if( fpt[i].sy < fpt[i].tsy )
					{
						fpt[i].scx = get_to( fpt[i].scx, 1.0f, 1.8f/ffps );
						fpt[i].scy = get_to( fpt[i].scy, 0.2f, 1.8f/ffps );
						fpt[i].fa += 2.4f/ffps;
						fpt[i].sy += 40.0f/ffps;
						fpt[i].angle -= 1.8f/ffps;
					}
				}
			}
			break;

		case PART_SUNSET:
			sunang -= 1.8f/ffps;
			fla1   += 1.2f/ffps;
			fla2   -= 1.35f/ffps;
			
			nature_timing();

			if( tba > 0 )
			{
				tba -= dtba;
				if( tba < 0 ) tba = 0;
			}
			if( tbsc > 0.1f )
			{
				tbsc -= dtbsc;
				if( tbsc < 0.1f ) tbsc = 0.1f;
			}
			if( tbang > 3.14159265f )
			{
				tbang -= dtbang;
				if( tbang < 3.14159265f ) tbang = 3.14159265f;
			}

			if( suny < sunty )
				suny -= sundy;
			
			if( fadea < 255 )
			{
				fadea += 2;
				if( fadea > 255 ) fadea = 255;
			}

			for( i=0; i<MAXFPETS; i++ )
			{
				if( fpt[i].active )
				{
					if( fpt[i].sy < fpt[i].tsy )
					{
						fpt[i].scx = get_to( fpt[i].scx, 1.0f, 1.8f/ffps );
						fpt[i].scy = get_to( fpt[i].scy, 0.2f, 1.8f/ffps );
						fpt[i].fa += 2.4f/ffps;
						fpt[i].sy += 40.0f/ffps;
						fpt[i].angle -= 1.8f/ffps;
					}
				}
			}
			break;
	}
}

void nextauthnote( void )
{
	s32 i, j, k, l;
  
	if( !antxtptr ) return;
  
	i=0;
	while( antxtptr[i] == 32 ) i++;
	if( antxtptr[i] == 0 )
	{
		antxtptr = NULL;
		return;
	}
  
	j=0;
	for( ;; )
	{
		k = j;
		l = i;
    
		while( antxtptr[i] == 32 ) i++;
    
		if( j ) antxt[j++] = 32;
		while( ( antxtptr[i] != 32 ) && ( antxtptr[i] != 0 ) )
			antxt[j++] = antxtptr[i++];
    
		antxt[j] = 0;
		if( textlen( antxt ) > 640 )
		{
			if( k )
				antxt[k] = 0;
			else
				l = i;
      
			if( antxtptr[l] == 0 )
				antxtptr = NULL;
			else
				antxtptr = &antxtptr[l+1];
			break;
		}
    
		if( antxtptr[i] == 0 )
		{
			antxtptr = NULL;
			break;
		}    
	}
    
	fade_in( antxt, 0 );
}

void render_fade( void )
{
	GX_Begin( GX_QUADS, GX_VTXFMT0, 4 );
		GX_Position3f32(   0.0f,   0.0f, 20.0f );
		GX_Color4u8( 0, 0, 0, fadea );
		GX_Position3f32( 640.0f,   0.0f, 20.0f );
		GX_Color4u8( 0, 0, 0, fadea );
		GX_Position3f32( 640.0f, 480.0f, 20.0f );
		GX_Color4u8( 0, 0, 0, fadea );
		GX_Position3f32(   0.0f, 480.0f, 20.0f );
		GX_Color4u8( 0, 0, 0, fadea );
	GX_End();
}

void render_intro_text( int which )
{
	int i, j, k, l;
	
	if( which > 2 ) return;

	setlogotex();
	l = introdat[which*4+1];
	for( i=0, j=introdat[which*4], k=introdat[which*4+2]; i<l; i++, j++ )
	{
		if( llorder[j] != -1 )
		{
			if( ( introappear[i] > -1 ) || ( introdoing == 1 ) )
				logoletter( k, 230, introappear[i]>=0?(introappear[i]/4):6, introzoom[i], llorder[j] );
			k += llorder[j]==0?20:34;
		} else {
			k += 10;
		}
	}
	clearlogotex();
}

f32 dist( f32 x1, f32 y1, f32 x2, f32 y2 )
{
	f32 xd, yd;
	xd = (x2-x1);
	yd = (y2-y1);
	return sqrt( xd*xd+yd*yd );
}

int render( u32 tapped )
{
	int i, j;
	int done;
	f32 fx1, fx2, fy1, fy2;
	f32 scale;
	
	done = 0;

	switch( part )
	{
		case PART_STARFIELD:
			drawspace();	
			for( i=0; i<NUMSTARS; i++ )
				draw_star( stars[i].scale, stars[i].ang, stars[i].sx, stars[i].sy, &pal[2*3], 0xff );
			render_intro_text( intropart );

			if( tune->ht_PosNr >= 6 )
				start_part( PART_PLANET_IN );
			break;

		case PART_PLANET_IN:
			drawspace();	
			for( i=0; i<NUMSTARS; i++ )
				draw_star( stars[i].scale, stars[i].ang, stars[i].sx, stars[i].sy, &pal[2*3], 0xff );
			circle( plx, ply, plr, &pal[1*3], 1, 100, 0.0f );
			if( plx <= ptrg )
				start_part( PART_PLANET_ZOOM );
			break;

		case PART_PLANET_ZOOM:
			drawspace();	
			for( i=0; i<NUMSTARS; i++ )
				draw_star( stars[i].scale, stars[i].ang, stars[i].sx, stars[i].sy, &pal[2*3], 0xff );
			circle( plx, ply, plr, &pal[1*3], 1, 100, 0.0f );
			if( ply >= ptrg )
				start_part( PART_STARS_OUT );
			break;

		case PART_STARS_OUT:
			drawspace();	
			for( i=0; i<NUMSTARS; i++ )
				draw_star( stars[i].scale, stars[i].ang, stars[i].sx, stars[i].sy, &pal[2*3], starsa );
			circle( plx, ply, plr, &pal[1*3], 1, 45, 0.0f );
			if( starsa == 0 )
				start_part( PART_SUNRISE );
			break;

		case PART_SUNRISE:
			drawspace();
			drawsky( gcount );
			draw_sun( sunx, suny, sunr, sunang, &pal[2*3] );
			circle( plx, ply, plr, &pal[1*3], 1, 45, 0.0f );

			if( suny <= sunty )
				start_part( PART_FLOWERGROW );
			break;
		
		case PART_FLOWERGROW:
			drawsky( 255 );
			draw_sun( sunx, suny, sunr, sunang, &pal[2*3] );
			circle( plx, ply, plr, &pal[1*3], 1, 45, 0.0f );
			draw_stalk( sin( fla1 )*0.1f, flwr[0].sc, flwr[0].sx, flwr[0].sy, &pal[3*3] );
			if( flwr[0].r > 0.2f )
				draw_flower( &flwr[0], stalktopx, stalktopy, &pal[4*3], &pal[2*3] );
			draw_stalk( sin( fla2 )*0.08f, flwr[1].sc, flwr[1].sx, flwr[1].sy, &pal[3*3] );
			if( flwr[1].r > 0.2f )
				draw_flower( &flwr[1], stalktopx, stalktopy, &pal[4*3], &pal[2*3] );

			if( flwr[0].p[7].cangrow == 0 )
				start_part( PART_MAIN );
			break;
		
		case PART_MAIN:
			WPAD_IR( 0, &ir );

			drawsky( 255 );
			if( do_fade( topfader ) ) nextauthnote();
			topfader = 0;
			draw_sun( sunx, suny, sunr, sunang, &pal[2*3] );
			for( i=0; i<NUMCLOUDS; i++ )
			{
				scale = (clouds[i].ang + 1.5f) / 1.5f;
				draw_cloud( &clouds[i], plx, ply, scale, &pal[4*3] );
			}

			circle( plx, ply, plr, &pal[1*3], 1, 45, 0.0f );

			for( i=0; i<NUMBBFLYS; i++ )
				draw_butterfly( bbflys[i].ang, bbflys[i].wscale, bbflys[i].sx, bbflys[i].sy-(bbflys[i].wscale*bfbnc*0.6f), 0.0f, &pal[22*3], &pal[23*3], &pal[24*3], 1 );

			if( tba > 0 )
			{
				if( tbdragger )
				{
					if( tba != (255<<8) )
					{
						tbdragger = 0;
					} else {

						if( ( ir.smooth_valid ) &&
							( ir.sx >= 0.0f ) &&
							( ir.sy >= 0.0f ) &&
							( ir.sx < 640.0f ) &&
							( ir.sy < 480.0f ) )
						{
							tbx = ir.sx - tbdragx;
							tby = ir.sy - tbdragy;
							if( tby > 300.0f ) tby = 300.0f;
						}
					}
				}
				
				switch( tbpressed )
				{
					case 1:
						if( tbyo > 0.0f )
						{
							tbyo -= 4.0f;
							if( tbyo < 0.0f ) tbyo = 0.0f;
						}
						break;
					
					case 2:
						if( tbyo < (tbauh-164.0f) )
						{
							tbyo += 4.0f;
							if( tbyo > (tbauh-164.0f) ) tbyo = tbauh-164.0f;
							if( tbyo < 0.0f ) tbyo = 0.0f;
						}
						break;
				}
//				drawtextbox( tbx, tby, tbsc, tbang, tba>>8 );
			}

			// There should be no need to call this here. It should only be called above
			// where it is commented out. But for some FUCKING reason, if you don't render
			// the textbox all the fucking time, the top text gets corrupted. The texture
			// itself is fine, but the actual rendering of it gets corrupted. Note that
			// drawtextbox has fuck all to do with the top text. It doesn't use any of
			// the same variables or textures. SO WHAT THE FUCK?
			drawtextbox( tbx, tby, tbsc, tbang, tba>>8 );

			draw_stalk( sin( fla1 )*0.1f, flwr[0].sc, flwr[0].sx, flwr[0].sy, &pal[3*3] );
			draw_flower( &flwr[0], stalktopx, stalktopy, &pal[4*3], &pal[2*3] );
			fx1 = stalktopx;
			fy1 = stalktopy;
			draw_stalk( sin( fla2 )*0.08f, flwr[1].sc, flwr[1].sx, flwr[1].sy, &pal[3*3] );
			draw_flower( &flwr[1], stalktopx, stalktopy, &pal[4*3], &pal[2*3] );
			fx2 = stalktopx;
			fy2 = stalktopy;

			for( i=0; i<MAXFPETS; i++ )
			{
				if( fpt[i].active )
				{
					draw_petal( cos( fpt[i].angle ), sin( fpt[i].angle ),
								fpt[i].scx, fpt[i].scy,
								fpt[i].sx + (sin( fpt[i].fa ) * 64.0f),  fpt[i].sy, 3.0f,
								&pal[4*3],
								NULL, NULL, NULL );
				}
			}

			for( i=0; i<NUMBFLYS; i++ )
				draw_butterfly( bflys[i].ang, bflys[i].wscale, bflys[i].sx, bflys[i].sy-(bflys[i].wscale*bfbnc), 4.0f, &pal[22*3], &pal[23*3], &pal[24*3], 0 );

			
			if( ( ir.smooth_valid ) &&
			    ( ir.sx >= 0.0f ) &&
				( ir.sy >= 0.0f ) &&
				( ir.sx < 640.0f ) &&
				( ir.sy < 480.0f ) )
			{
				u32 held;
				
				held = WPAD_ButtonsHeld( 0 );

				draw_pointer( ir.sx, ir.sy, ir.angle, sin( pointera ) * 127.0f + 128.0f,
														cos( pointera * 0.91f ) * 127.0f + 128.0f,
														sin( pointera * 0.82f ) * 127.0f + 128.0f );
				
				if( ( tbon ) && ( tba == (255<<8) ) )
				{
					if( ( ir.sx > (tbx-180.0f) ) &&
					    ( ir.sx < (tbx+180.0f) ) &&
						( ir.sy > (tby-96.0f) ) &&
						( ir.sy < (tby+96.0f) ) )
					{
						tbdox = 1;
					} else {
						tbdox = 0;
					}
				}
				
				if( tapped & WPAD_BUTTON_A )
				{
					int stopit;

					stopit = 0;
					for( i=0; i<NUMBFLYS; i++ )
					{
						if( ( bflys[i].dead == 0 ) && ( dist( ir.sx, ir.sy, bflys[i].sx, bflys[i].sy ) < 40.0f ) )
						{
							bflys[i].dead = 1;
							stopit = 1;
							break;
						}
					}
					if( stopit ) break;
					
					if( ( ir.sx > (sunx-sunr) ) &&
					    ( ir.sx < (sunx+sunr) ) &&
						( ir.sy > (suny-sunr) ) &&
						( ir.sy < (suny+sunr) ) &&
						( tbdox == 0 ) )
					{
						tbon = 0;
						start_part( PART_SUNSET );
						break;
					}
					
					if( dist( ir.sx, ir.sy, fx1, fy1 ) < flwr[0].r )
					{
						j=0;
						for( i=0; i<8; i++ )
						{
							if( flwr[0].p[i].attached == 0 )
							{
								flwr[0].p[i].wba      = 3.14159265f;
								flwr[0].p[i].wbs      = 0.8f;
								flwr[0].p[i].scx      = j;
								flwr[0].p[i].scy      = j;
								flwr[0].p[i].wobble   = 0;
								flwr[0].p[i].cangrow  = 1;
								flwr[0].p[i].attached = 1;
								j--;
							}
						}
						break;
					}
					
					if( dist( ir.sx, ir.sy, fx2, fy2 ) < flwr[1].r )
					{
						j=0;
						for( i=0; i<8; i++ )
						{
							if( flwr[1].p[i].attached == 0 )
							{
								flwr[1].p[i].wba      = 3.14159265f;
								flwr[1].p[i].wbs      = 0.8f;
								flwr[1].p[i].scx      = j;
								flwr[1].p[i].scy      = j;
								flwr[1].p[i].wobble   = 0;
								flwr[1].p[i].cangrow  = 1;
								flwr[1].p[i].attached = 1;
								j--;
							}
						}
						break;
					}
					
					for( i=0; i<8; i++ )
					{
						if( ( flwr[0].p[i].attached ) &&
						    ( dist( ir.sx, ir.sy, flwr[0].p[i].mx, flwr[0].p[i].my ) < flwr[0].p[i].mr ) )
						{
							fpt[nextfpeta].angle = flwr[0].p[i].angle;
							fpt[nextfpeta].fa    = 0.0f;
							fpt[nextfpeta].scx   = flwr[0].p[i].scx * flwr[0].sc;
							fpt[nextfpeta].scy   = flwr[0].p[i].scy * flwr[0].sc;
							fpt[nextfpeta].sx    = flwr[0].p[i].sx;
							fpt[nextfpeta].sy    = flwr[0].p[i].sy;
							fpt[nextfpeta].tsy   = 480.0f*0.9f + ((f32)(rand()%48));

							fpt[nextfpeta].active = 1;
							nextfpeta = (nextfpeta+1)&15;

							flwr[0].p[i].attached = 0;
							if( i != ctune )
							{
								start_tune( i );
								show_now_playing( 1 );
							}
							break;
						}

						if( ( flwr[1].p[i].attached ) &&
						    ( dist( ir.sx, ir.sy, flwr[1].p[i].mx, flwr[1].p[i].my ) < flwr[1].p[i].mr ) )
						{
							fpt[nextfpetb+16].angle = flwr[1].p[i].angle;
							fpt[nextfpetb+16].fa    = 0.0f;
							fpt[nextfpetb+16].scx   = flwr[1].p[i].scx * flwr[1].sc;
							fpt[nextfpetb+16].scy   = flwr[1].p[i].scy * flwr[1].sc;
							fpt[nextfpetb+16].sx    = flwr[1].p[i].sx;
							fpt[nextfpetb+16].sy    = flwr[1].p[i].sy;
							fpt[nextfpetb+16].tsy   = 480.0f*0.9f + ((f32)(rand()%48));

							fpt[nextfpetb+16].active = 1;
							nextfpetb = (nextfpetb+1)&15;

							flwr[1].p[i].attached = 0;
							readpetal = i;
							break;
						}
					}
				}

				if( held & WPAD_BUTTON_A )
				{
					if( ( tbon ) && ( tba == (255<<8) ) )
					{
						if( ( ir.sx > (tbx-172.0f) ) &&
						    ( ir.sx < (tbx-149.0f) ) &&
							( ir.sy > (tby-82.0f) ) &&
							( ir.sy < (tby-59.0f) ) )
						{
							tbpressed = 3;
							break;
						}
						
						if( ( ir.sx > (tbx+144.0f) ) &&
						    ( ir.sx < (tbx+172.0f) ) )
						{
							if( ( ir.sy > (tby-82.0f) ) &&
							    ( ir.sy < (tby-54.0f) ) )
							{
								tbpressed = 1;
								break;
							}
							
							if( ( ir.sy > (tby+54.0f) ) &&
							    ( ir.sy < (tby+82.0f) ) )
							{
								tbpressed = 2;
								break;
							}
						}

						if( ( tbdox == 1 ) && ( tbdragger == 0 ) && ( tbpressed == 0 ) )
						{
							tbdragger = 1;
							tbdragx = ir.sx-tbx;
							tbdragy = ir.sy-tby;
						}
					}
				} else {
					s32 stopit;
					
					stopit = 0;
					switch( tbpressed )
					{
						case 1:
							stopit = 1;
							break;
						
						case 2:
							stopit = 1;
							break;
						
						case 3:
							tbon = 0;
							tbdox = 0;
							stopit = 1;
							break;
					}
					tbpressed = 0;
					tbdragger = 0;
					if( stopit ) break;
				}

				if( tapped & WPAD_BUTTON_A )
				{
					if( ( dist( ir.sx, ir.sy, clouds[2].px1, clouds[2].py1 ) < clouds[2].pr1 ) ||
					    ( dist( ir.sx, ir.sy, clouds[2].px2, clouds[2].py2 ) < clouds[2].pr2 ) ||
					    ( dist( ir.sx, ir.sy, clouds[2].px3, clouds[2].py3 ) < clouds[2].pr3 ) )
					{
						if( ctune != 8 )
						{
							start_tune( 8 );
							show_now_playing( 1 );
						}
					}
				}

			}
			break;
		
		case PART_SUNSET:
			drawsky( 255 );
			draw_sun( sunx, suny, sunr, sunang, &pal[2*3] );
			for( i=0; i<NUMCLOUDS; i++ )
			{
				scale = (clouds[i].ang + 1.5f) / 1.5f;
				draw_cloud( &clouds[i], plx, ply, scale, &pal[4*3] );
			}
			circle( plx, ply, plr, &pal[1*3], 1, 45, 0.0f );

			for( i=0; i<NUMBBFLYS; i++ )
				draw_butterfly( bbflys[i].ang, bbflys[i].wscale, bbflys[i].sx, bbflys[i].sy-(bbflys[i].wscale*bfbnc*0.6f), 0.0f, &pal[22*3], &pal[23*3], &pal[24*3], 1 );

			if( tba > 0 ) drawtextbox( tbx, tby, tbsc, tbang, tba>>8 );

			draw_stalk( sin( fla1 )*0.1f, flwr[0].sc, flwr[0].sx, flwr[0].sy, &pal[3*3] );
			draw_flower( &flwr[0], stalktopx, stalktopy, &pal[4*3], &pal[2*3] );
			draw_stalk( sin( fla2 )*0.08f, flwr[1].sc, flwr[1].sx, flwr[1].sy, &pal[3*3] );
			draw_flower( &flwr[1], stalktopx, stalktopy, &pal[4*3], &pal[2*3] );

			for( i=0; i<MAXFPETS; i++ )
			{
				if( fpt[i].active )
				{
					draw_petal( cos( fpt[i].angle ), sin( fpt[i].angle ),
								fpt[i].scx, fpt[i].scy,
								fpt[i].sx + (sin( fpt[i].fa ) * 64.0f),  fpt[i].sy, 3.0f,
								&pal[4*3],
								NULL, NULL, NULL );
				}
			}

			for( i=0; i<NUMBFLYS; i++ )
				draw_butterfly( bflys[i].ang, bflys[i].wscale, bflys[i].sx, bflys[i].sy-(bflys[i].wscale*bfbnc), 4.0f, &pal[22*3], &pal[23*3], &pal[24*3], 0 );
			
			if( fadea == 255 )
			  done = 1;
			break;
	}
	
	if( fadea > 0 ) render_fade();
	return done;
}
