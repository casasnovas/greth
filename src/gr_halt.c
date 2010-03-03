#ifndef GR_HALT_C_
# define GR_HALT_C_

/* gr_halt_cmd structure */
#include "grmon_interpret.h"


GrCmdType gr_halt_cmd[] = {
 	 { 0x90000020, 0xffff },
 	 { 0x90400024, 0x19 },
 	 { 0x90400024, 0x19 },
 	 { 0x90000050, 0x0 },
 	 { 0x90000054, 0x0 },
 	 { 0x90000058, 0x0 },
 	 { 0x9000005c, 0x0 },
};

#endif /* !GR_HALT_C_ */
