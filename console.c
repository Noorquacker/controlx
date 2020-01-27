#include "console.h"
#include "screen.h"
#include "boot1.h"
#include "tools.h"

uint8_t console_mode=0;

uint8_t col=0;
uint8_t line=0;
uint8_t iline=CHAR_HEIGHT;

uint8_t getCol() {
	return col;
}

void setConsole(uint8_t mode) {
	console_mode=mode;
}

void setLine(int16_t newline) {
	if(newline<0)
		line=newline+SCREEN_HEIGHT;
	else
		line=newline;
}

void setCol(uint8_t newcol) {
	col=newcol;
}

void setInterline(uint8_t i) {
	iline=i;
}

uint8_t getInterline() {
	return iline;
}

uint8_t getMaxLines() {
	char h=SCREEN_HEIGHT;
	uint8_t c=0;
	while(h>=iline) {
		h-=iline;
		c++;
	}
	return c;
}

void dispBuf( uint8_t* buf, char* message, uint8_t newline) {
  uint8_t i;
  char c;
  for (i = 0; i < strlen(message) && col<MAX_COL; i++) {
	c=message[i];
	if(c=='\n') {
		col=-1;
		line+=iline;
		
	}
	else
		putBufChar(buf, col*CHAR_WIDTH, line, c, console_mode&TRSP_MODE);
	col++;
  }
  if(newline) {
	  col=0;
	  line+=iline;
  }
}

void disp(char* msg) {
	dispBuf(SCREEN_BASE_ADDR,msg,0);
}

void displn(char* msg) {
	dispBuf(SCREEN_BASE_ADDR,msg,1);
}
