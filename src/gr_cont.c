#ifndef GR_CONT_C_
# define GR_CONT_C_

/* gr_cont_cmd structure */
#include "grmon_interpret.h"


GrCmdType gr_cont_cmd[] = {
 	 { 0x90000020, 0xffff0000 },
 	 { 0x90400024, 0x19 },
 	 { 0x90400024, 0x19 },
 	 { 0x90000020, 0x0 },
};

#endif /* !GR_CONT_C_ */
