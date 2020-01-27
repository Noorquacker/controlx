/*
 * ControlX
 *
 * Copyright (C) 2016 Excale
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.
 */

/* Warning: this code is quite horrible.
   We recommend that you do not try to understand it */
   
#include "patchboot2.h"

extern char __ndless_boot2_prestage_start__;
extern char __ndless_boot2_prestage_end__;

extern char __ndless_loader_before403_start__;
extern char __ndless_loader_before403_end__;

extern char __ndless_loader_cx_cas_start__;
extern char __ndless_loader_cx_cas_end__;

extern char __ndless_loader_cx_num_start__;
extern char __ndless_loader_cx_num_end__;

extern char __ndless_loader_cx_cas_dvt_start__;
extern char __ndless_loader_cx_cas_dvt_end__;

extern char __ndless_loader_cx_num_dvt_start__;
extern char __ndless_loader_cx_num_dvt_end__;

extern char __ndless_loader_cm_cas_start__;
extern char __ndless_loader_cm_cas_end__;

extern char __ndless_loader_cm_num_start__;
extern char __ndless_loader_cm_num_end__;

asm(R"controlx(
.globl __ndless_boot2_prestage_start__
.globl __ndless_boot2_prestage_end__
.globl __ndless_loader_before403_start__
.globl __ndless_loader_before403_end__
.globl __ndless_loader_cx_cas_start__
.globl __ndless_loader_cx_cas_end__
.globl __ndless_loader_cx_num_start__
.globl __ndless_loader_cx_num_end__
.globl __ndless_loader_cx_cas_dvt_start__
.globl __ndless_loader_cx_cas_dvt_end__
.globl __ndless_loader_cx_num_dvt_start__
.globl __ndless_loader_cx_num_dvt_end__
.globl __ndless_loader_cm_cas_start__
.globl __ndless_loader_cm_cas_end__
.globl __ndless_loader_cm_num_start__
.globl __ndless_loader_cm_num_end__
__ndless_loader_cx_cas_start__:
.incbin "ndless_loader_cx_cas.bin"
__ndless_loader_cx_cas_end__:
__ndless_loader_cx_num_start__:
.incbin "ndless_loader_cx_num.bin"
__ndless_loader_cx_num_end__:
__ndless_loader_cx_cas_dvt_start__:
.incbin "ndless_loader_cx_cas_dvt.bin"
__ndless_loader_cx_cas_dvt_end__:
__ndless_loader_cx_num_dvt_start__:
.incbin "ndless_loader_cx_num_dvt.bin"
__ndless_loader_cx_num_dvt_end__:
__ndless_loader_cm_cas_start__:
.incbin "ndless_loader_cm_cas.bin"
__ndless_loader_cm_cas_end__:
__ndless_loader_cm_num_start__:
.incbin "ndless_loader_cm_num.bin"
__ndless_loader_cm_num_end__:
__ndless_loader_before403_start__:
LDR    R0, [PC, #8]
LDRD   R2, R3, [PC, #12]
STRD   R2, R3, [R0]
LDR    PC, [PC]
.word 0x11AE1C48
.word 0x1187E99C
LDR    PC, [PC, #-4]
.word 0x11908090
__ndless_loader_before403_end__:
__ndless_boot2_prestage_start__:
LDR    PC, [PC, #-4]
__ndless_boot2_prestage_end__:
)controlx");

#define NDLESS_LOC ((id==CXB403_49)?0x11908070:0x1170F000)

void ndless_boot2_prestage(uint32_t id, uint8_t* ptr) {
	uint32_t adr=NDLESS_LOC;
	memcpy((void*)ptr, &__ndless_boot2_prestage_start__, &__ndless_boot2_prestage_end__-&__ndless_boot2_prestage_start__);
	ptr+=&__ndless_boot2_prestage_end__-&__ndless_boot2_prestage_start__;
	memcpy((void*)ptr, &adr, 4);
}

int ndless_loader(image_info * flashimage) {
    const char boot2_str[] = "BOOT2";
    if(!memcmp(flashimage->type, boot2_str, sizeof(boot2_str))) {
		uint32_t id=*((volatile uint32_t *)0x11800020);
		if(id==CXB403_49 || id==CXB440_8) {
			uint8_t *ndless_loader_start=0, *ndless_loader_end=0, *ndless_loader_before_start=0, *ndless_loader_before_end=0;

			ndless_boot2_prestage(id,(id==CXB403_49)?0x1187E994:0x1187d300);
			if(id==CXB440_8) ndless_boot2_prestage(id,0x1187d334);

			if(id==CXB403_49) {
				ndless_loader_before_start=&__ndless_loader_before403_start__;
				ndless_loader_before_end=&__ndless_loader_before403_end__;
			}
			memcpy((void *)NDLESS_LOC, ndless_loader_before_start , ndless_loader_before_end-ndless_loader_before_start);
			
			switch(modelid) {
				case 0x0F:
					ndless_loader_start=bootkeys?&__ndless_loader_cx_cas_dvt_start__:&__ndless_loader_cx_cas_start__;
					ndless_loader_end=bootkeys?&__ndless_loader_cx_cas_dvt_end__:&__ndless_loader_cx_cas_end__;
					break;
				case 0x10:
					ndless_loader_start=bootkeys?&__ndless_loader_cx_num_dvt_start__:&__ndless_loader_cx_num_start__;
					ndless_loader_end=bootkeys?&__ndless_loader_cx_num_dvt_end__:&__ndless_loader_cx_num_end__;
					break;
				case 0x11:
					ndless_loader_start=&__ndless_loader_cm_cas_start__;
					ndless_loader_end=&__ndless_loader_cm_cas_end__;
					break;
				case 0x12:
					ndless_loader_start=&__ndless_loader_cm_num_start__;
					ndless_loader_end=&__ndless_loader_cm_num_end__;
					break;
				default:
					return 0;
			}
			if((ndless_loader_end-ndless_loader_start)+(ndless_loader_before_end-ndless_loader_before_start)<=0x714) {
				memcpy((void *)(NDLESS_LOC+ndless_loader_before_end-ndless_loader_before_start), ndless_loader_start , ndless_loader_end-ndless_loader_start);
				return 1;
			}
		}
	}
	return 0;
}