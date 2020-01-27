GCC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
GCCFLAGS = -Os -Wall -W -marm -mcpu=arm926ej-s -s -fPIE -ffreestanding -std=c11
LDFLAGS = -nostdlib -nostartfiles -e ndless_loader -PIE -T ldscript
OBJCOPY := "$(shell which arm-elf-objcopy 2>/dev/null)"
ifeq (${OBJCOPY},"")
	OBJCOPY := arm-none-eabi-objcopy
endif
BINCXC = ../ndless_loader_cx_cas.bin
BINCXN = ../ndless_loader_cx_num.bin
BINCXCD = ../ndless_loader_cx_cas_dvt.bin
BINCXND = ../ndless_loader_cx_num_dvt.bin
BINCMC = ../ndless_loader_cm_cas.bin
BINCMN = ../ndless_loader_cm_num.bin

# WARNING : each of the 6 different payloads (CX, CXCAS, CM, CMCAS, CXDVT, CXCASDVT) has to fit within the Boot2
# 1776KiB : ok with  Boot2 4.0.3 + 4.4
# 1780KiB : fails with Boot2 4.0.3
# 1808KiB : ok with  Boot2 4.4
# DO NOT include all OS patches !

# CX + CX CAS + CM + CM CAS patches
PATCHES :=	 			-DOS_310_392 -DOS_320_1212 -DOS_320_1219
#						-DOS_310_392 -DOS_320_1212 -DOS_320_1219

# add CX + CX CAS patches
PATCHES := $(PATCHES)	                                     -DOS_323 -DOS_324 -DOS_330_538 -DOS_360_546_550 -DOS_390_461 -DOS_390_463 -DOS_391 -DOS_400 -DOS_402 -DOS_403 -DOS_42 -DOS_430_702 -DOS_440_532 -DOS_450_1180 -DOS_451_X -DOS_452_8
#						-DOS_301 -DOS_302_1791 -DOS_302_1793 -DOS_323 -DOS_324 -DOS_330_538 -DOS_360_546_550 -DOS_390_461 -DOS_390_463 -DOS_391 -DOS_400 -DOS_402 -DOS_403 -DOS_42 -DOS_430_702 -DOS_440_532 -DOS_450_1180 -DOS_451_X -DOS_452_8

# add CX CAS patches
#PATCHES := $(PATCHES)	-DOS_430_547 -DOS_440_531

# add CX patches
#PATCHES := $(PATCHES)	-DOS_450_845

# add CX CAS patches DVT
PATCHES := $(PATCHES)	-DOS_330_218 -DOS_360_427 -DOS_360_521

# add CX + CX CAS patches DVT
PATCHES := $(PATCHES)	-DOS_320_776 -DOS_320_1030 -DOS_320_1180

# add CX patches DVT
PATCHES := $(PATCHES)	-DOS_300_0 -DOS_300_1045 -DOS_300_1503

# add CM CAS patches
PATCHES := $(PATCHES)	-DOS_310_157

# add CM patches
PATCHES := $(PATCHES)	-DOS_310_0 -DOS_310_236

all: $(BINCXC) $(BINCXCD) $(BINCXN) $(BINCXND) $(BINCMC) $(BINCMN)

ndless_loader_cm_cas.o: ndless_loader.c
	$(GCC) $(GCCFLAGS) -o $@ -DCM -DCAS $(PATCHES) -c $<

ndless_loader_cm_num.o: ndless_loader.c
	$(GCC) $(GCCFLAGS) -o $@ -DCM $(PATCHES) -c $<
	
ndless_loader_cx_cas.o: ndless_loader.c
	$(GCC) $(GCCFLAGS) -o $@ -DCAS $(PATCHES) -c $<

ndless_loader_cx_cas_dvt.o: ndless_loader.c
	$(GCC) $(GCCFLAGS) -o $@ -DDVT -DCAS $(PATCHES) -c $<

ndless_loader_cx_num.o: ndless_loader.c
	$(GCC) $(GCCFLAGS) -o $@ $(PATCHES) -c $<

ndless_loader_cx_num_dvt.o: ndless_loader.c
	$(GCC) $(GCCFLAGS) -o $@ -DDVT $(PATCHES) -c $<

$(BINCXC): ndless_loader_cx_cas.o
	$(LD) $(LDFLAGS) $^ -o $(<:.o=.elf)
	$(OBJCOPY) -O binary $(<:.o=.elf) $@

$(BINCXCD): ndless_loader_cx_cas_dvt.o
	$(LD) $(LDFLAGS) $^ -o $(<:.o=.elf)
	$(OBJCOPY) -O binary $(<:.o=.elf) $@

$(BINCXN): ndless_loader_cx_num.o
	$(LD) $(LDFLAGS) $^ -o $(<:.o=.elf)
	$(OBJCOPY) -O binary $(<:.o=.elf) $@

$(BINCXND): ndless_loader_cx_num_dvt.o
	$(LD) $(LDFLAGS) $^ -o $(<:.o=.elf)
	$(OBJCOPY) -O binary $(<:.o=.elf) $@

$(BINCMC): ndless_loader_cm_cas.o
	$(LD) $(LDFLAGS) $^ -o $(<:.o=.elf)
	$(OBJCOPY) -O binary $(<:.o=.elf) $@
	
$(BINCMN): ndless_loader_cm_num.o
	$(LD) $(LDFLAGS) $^ -o $(<:.o=.elf)
	$(OBJCOPY) -O binary $(<:.o=.elf) $@
clean:
	rm -f *.o *.elf
	rm -f $(BINCXC) $(BINCXCD) $(BINCXN) $(BINCXND) $(BINCMC) $(BINCMN)