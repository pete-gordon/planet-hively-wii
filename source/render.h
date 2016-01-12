
#define AUDIOENABLE 1

enum
{
  PART_STARFIELD=1,
  PART_PLANET_IN,
  PART_PLANET_ZOOM,
  PART_STARS_OUT,
  PART_SUNRISE,
  PART_FLOWERGROW,
  PART_MAIN,
  PART_SUNSET
};

void render_init( void );
int render( u32 tapped );
void flip( void );
void timing( void );

#define NUMRAYS 8
struct vtx
{
	f32 x, y;
	f32 sx, sy;
	s32 f1, f2;
};
