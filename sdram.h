/* SDRAM map
1st bank:
0x10000000 						: OS					[raw:25MiB]
0x10100000 (offset+=1MiB)		: Linux-Kernel
0x10601000 (offset+=~5MiB)		: raw splash buffer		[12x 320*240*2 ~1.75MiB]
0x107C1000 (offset+=~1.75MiB)	: Linux-DTB				[~23.25MiB]
0x107C3000 (offset+=~1.75MiB)	: ControlX low buffer	[~23.25MiB]
0x11200000 (offset+=11MiB)		: Boot1.5/INSTALL		[raw:14MiB/comp:11MiB]
0x11800000 (offset+=6MiB)		: Boot2					[raw:8MiB/comp:17MiB]
2nd bank:
0x12000000						: Linux-Initrd
*/

#define LINUX_KERNEL_PTR	0x10100000
#define SPLASH_RAW_PTR		0x10601000
#define SAFE_RAM_LOW_PTR	0x107C3000
#define LINUX_DTB_PTR		(SAFE_RAM_LOW_PTR-0x2000)
#define SAFE_RAM_HIGH_PTR	0x11E00000
