#include "types.h"
#define SCREEN_WIDTH	320
#define SCREEN_HEIGHT	240

#define SCREEN_BASE_PTR		0xC0000010 
#define BACK_R	0x08
#define BACK_G	0x04
#define BACK_B	0x08
#define RGB24TO16(r,g,b)	(((r)>>3)<<11)|(((g)>>2)<<5)|((b)>>3)

unsigned char* SCREEN_BASE_ADDR;

void init_screen();
void setBufPixelRGB(unsigned char* buf, int x, int y, unsigned int r, unsigned int g, unsigned int b);
void putBufChar(unsigned short int* buf, int x, int y, char ch, int trsp);
void drwBufHoriz(unsigned char* buf, int y, int x1, int x2);
void drwBufVert(unsigned char* buf, int x, int y1, int y2);
void drwBufBox(unsigned char* buf, int x1, int y1, int x2, int y2);