typedef struct {
	uint16_t y;
	uint16_t x;
	uint16_t w;
	uint16_t h;
	uint32_t offset;
} splash_s;

#define NSPLASH 12
#define SPLASH_I_LOWBAT		0
#define SPLASH_I_GEARWARN1	1
#define SPLASH_I_FLOPPY		2
#define SPLASH_I_GEARWARN2	3
#define SPLASH_I_WARNING	4
#define SPLASH_I_PROGRBACK	5
#define SPLASH_I_PROGR		6
#define SPLASH_I_BACK1		7
#define SPLASH_I_BACK2		8
#define SPLASH_I_BACK3		9
#define SPLASH_I_BACK4		10
#define SPLASH_I_BACK5		11