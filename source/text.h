
#define TBAW 320
#define TBAAW 316
#define TBAH 1008
#define SPCW 8

void inittext( void );
void logoletter( f32 x, f32 y, s32 frame, f32 zoom, s32 l );
void setlogotex( void );
void clearlogotex( void );
void drawtextbox( f32 x, f32 y, f32 scale, f32 ang, u8 alpha );
void textbox_layout( char *str );
s32 textlen( char *str );
void fade_in( char *str, s32 immediate );
s32 do_fade( s32 fadeadd );
void dotoptprint( void );
