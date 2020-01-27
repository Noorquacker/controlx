#include "charmaps.h"
#include "types.h"

#define RET_MODE	1
#define TRSP_MODE	2

#define MAX_COL	(SCREEN_WIDTH/CHAR_WIDTH)
#define MAX_LGN	(SCREEN_HEIGHT/CHAR_HEIGHT)

#define dispMenu(i) outhex((i),ID_CONSOLE)

typedef char sint8_t;

uint8_t getMaxLines();
uint8_t getInterline();
void setConsole(uint8_t mode);
void dispBuf(uint8_t* buf, char* message, uint8_t newline);
void disp(char* msg);
void displn(char* msg);
void setLine(int16_t newline);
void setCol(uint8_t newcol);
uint8_t getCol();