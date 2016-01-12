
struct star
{
  int sx, sy;
  float ang, scale;
  int speed;
};

struct petal
{
  s32 attached;
  s32 wobble;
  s32 cangrow;
  f32 x, y;
  f32 scx, scy;
  f32 angle, ca, sa;
  f32 wba, wbs;
  f32 sx, sy;
  f32 mx, my, mr;
};

struct flower
{
  f32 sx, sy;
  s32 stkp;
  f32 r, tr, dr;
  f32 sc;
  struct petal p[8];
};


struct floating_petal
{
  s32 active;
  f32 angle;
  f32 fa;
  f32 scx, scy;
  f32 sx, sy, tsy;
};

struct butterfly
{
  f32 sx, sy, tsx, tsy, dsx, dsy;
  s32 dead;
  f32 ang, wscale, wscd;
};

struct cloud
{
  f32 ang, r;
  f32 speed;
  
  f32 px1, py1, pr1;
  f32 px2, py2, pr2;
  f32 px3, py3, pr3;
};

void draw_star( f32 scale, f32 angle, f32 x, f32 y, u8 *col, u8 alpha );
void circle( f32 x, f32 y, f32 r, u8 *col, u8 edge, s32 amt, f32 z );
void draw_sun( f32 x, f32 y, f32 r, f32 ang, u8 *col );
void shapes_init( void );
void draw_stalk( f32 angle, f32 scale, f32 sx, f32 sy, u8 *col );
void draw_flower( struct flower *fl, f32 sx, f32 sy, u8 *col1, u8 *col2 );
void draw_pointer( f32 x, f32 y, f32 ang, u8 r, u8 g, u8 b );
void draw_petal( f32 ca, f32 sa, f32 scx, f32 scy, f32 sx, f32 sy, f32 z, u8 *col, f32 *smx, f32 *smy, f32 *smr );
void draw_butterfly( f32 angle, f32 wscale, f32 sx, f32 sy, f32 z, u8 *col1, u8 *col2, u8 *col3, s32 small );
void draw_cloud( struct cloud *cd, f32 orx, f32 ory, f32 scale, u8 *col );
