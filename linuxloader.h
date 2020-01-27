#ifndef HEADER_H
#define HEADER_H
#include "sdram.h"
#include <stdint.h>

static void *dtb_dest = (void*)LINUX_DTB_PTR, *kernel_dest = (void*)0x10100000, *initrd_dest = (void*)0x12000000;

static const uint32_t LLHeader_sig = 0xDEDC0FFE;

typedef struct LLHeader {
	uint32_t signature; // 0xDEDC0FFE
	uint32_t dtb_size;
	uint32_t initrd_size;
	uint32_t kernel_size;
} LLHeader;
#endif
