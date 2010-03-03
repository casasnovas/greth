/* gr_debug_cmd structure     */
#include "greth.h"


grmon_command_t gr_debug_cmd[] = {
 	 { 0x80000100, 0x90000010 },
 	 { 0x90000000, 0xf },
 	 { 0x90000020, 0xffff },
 	 { 0x90000000, 0xf },
 	 { 0x90400024, 0x2 },
 	 { 0x90400024, 0x2 },
 	 { 0x90400024, 0x2 },
 	 { 0x90400060, 0x0 },
 	 { 0x90400064, 0x0 },
 	 { 0x90400068, 0x0 },
 	 { 0x9040006c, 0x0 },
 	 { 0x90400070, 0x0 },
 	 { 0x90400074, 0x0 },
 	 { 0x90400078, 0x0 },
 	 { 0x9040007c, 0x0 },
 	 { 0x90000050, 0x0 },
 	 { 0x90000054, 0x0 },
 	 { 0x90000058, 0x0 },
 	 { 0x9000005c, 0x0 },
 	 { 0x90110000, 0xffffffff },
 	 { 0x90110000, 0x33 },
 	 { 0x90400024, 0x2 },
 	 { 0x90400024, 0x19 },
 	 { 0x90700000, 0x0 },
 	 { 0x90400024, 0x19 },
 	 { 0x90400024, 0x19 },
 	 { 0x91000000, 0xf },
 	 { 0x91400024, 0x2 },
 	 { 0x91400024, 0x2 },
 	 { 0x90400024, 0x2 },
 	 { 0x91400060, 0x0 },
 	 { 0x91400064, 0x0 },
 	 { 0x91400068, 0x0 },
 	 { 0x9140006c, 0x0 },
 	 { 0x91400070, 0x0 },
 	 { 0x91400074, 0x0 },
 	 { 0x91400078, 0x0 },
 	 { 0x9140007c, 0x0 },
 	 { 0x91400060, 0x0 },
 	 { 0x91400064, 0x0 },
 	 { 0x91400068, 0x0 },
 	 { 0x9140006c, 0x0 },
 	 { 0x91400070, 0x0 },
 	 { 0x91400074, 0x0 },
 	 { 0x91400078, 0x0 },
 	 { 0x9140007c, 0x0 },
 	 { 0x91000050, 0x0 },
 	 { 0x91000054, 0x0 },
 	 { 0x91000058, 0x0 },
 	 { 0x9100005c, 0x0 },
 	 { 0x91110000, 0xffffffff },
 	 { 0x91110000, 0x0 },
 	 { 0x91400024, 0x2 },
 	 { 0x90400024, 0x19 },
 	 { 0x90700000, 0x0 },
 	 { 0x90400024, 0x19 },
 	 { 0x90400024, 0x19 },
 	 { 0x92000000, 0xf },
 	 { 0x92400024, 0x2 },
 	 { 0x92400024, 0x2 },
 	 { 0x90400024, 0x2 },
 	 { 0x92400060, 0x0 },
 	 { 0x92400064, 0x0 },
 	 { 0x92400068, 0x0 },
 	 { 0x9240006c, 0x0 },
 	 { 0x92400070, 0x0 },
 	 { 0x92400074, 0x0 },
 	 { 0x92400078, 0x0 },
 	 { 0x9240007c, 0x0 },
 	 { 0x92000050, 0x0 },
 	 { 0x92000054, 0x0 },
 	 { 0x92000058, 0x0 },
 	 { 0x9200005c, 0x0 },
 	 { 0x92110000, 0xffffffff },
 	 { 0x92110000, 0x0 },
 	 { 0x92400024, 0x2 },
 	 { 0x90400024, 0x19 },
 	 { 0x90700000, 0x0 },
 	 { 0x90400024, 0x19 },
 	 { 0x90400024, 0x19 },
 	 { 0x93000000, 0xf },
 	 { 0x93400024, 0x2 },
 	 { 0x93400024, 0x2 },
 	 { 0x90400024, 0x2 },
 	 { 0x93400060, 0x0 },
 	 { 0x93400064, 0x0 },
 	 { 0x93400068, 0x0 },
 	 { 0x9340006c, 0x0 },
 	 { 0x93400070, 0x0 },
 	 { 0x93400074, 0x0 },
 	 { 0x93400078, 0x0 },
 	 { 0x9340007c, 0x0 },
 	 { 0x93000050, 0x0 },
 	 { 0x93000054, 0x0 },
 	 { 0x93000058, 0x0 },
 	 { 0x9300005c, 0x0 },
 	 { 0x93110000, 0xffffffff },
 	 { 0x93110000, 0x0 },
 	 { 0x93400024, 0x2 },
 	 { 0x90400024, 0x19 },
 	 { 0x90700000, 0x0 },
 	 { 0x90400024, 0x19 },
 	 { 0x90400024, 0x19 },
 	 { 0x90000040, 0xffff0000 },
 	 { 0x90000040, 0x1 },
 	 { 0x90400024, 0x2 },
 	 { 0x90400024, 0x2 },
 	 { 0x90400024, 0x2 },
 	 { 0x90400040, 0x0 },
 	 { 0x91400024, 0x2 },
 	 { 0x91400024, 0x2 },
 	 { 0x91400024, 0x2 },
 	 { 0x91400024, 0x2 },
 	 { 0x91400040, 0x0 },
 	 { 0x92400024, 0x2 },
 	 { 0x92400024, 0x2 },
 	 { 0x92400024, 0x2 },
 	 { 0x92400040, 0x0 },
 	 { 0x93400024, 0x2 },
 	 { 0x93400024, 0x2 },
 	 { 0x93400024, 0x2 },
 	 { 0x93400040, 0x0 },
 	 { 0xf00eff0c, 0xffffffff },
 	 { 0xf00eff08, 0x2000000 },
 	 { 0xf00eff00, 0x3e1ffff },
 	 { 0xf00eff00, 0x83e0ffff },
 	 { 0x40001000, 0x0 },
 	 { 0x40000800, 0x0 },
 	 { 0x40000400, 0x0 },
 	 { 0x40000200, 0x0 },
 	 { 0x40000000, 0x0 },
 	 { 0x40000000, 0x1 },
 	 { 0x40000004, 0x0 },
 	 { 0xf00eff00, 0x8380ffff },
 	 { 0x47c00000, 0x47c00000 },
 	 { 0x47800000, 0x47800000 },
 	 { 0x47400000, 0x47400000 },
 	 { 0x47000000, 0x47000000 },
 	 { 0x46c00000, 0x46c00000 },
 	 { 0x46800000, 0x46800000 },
 	 { 0x46400000, 0x46400000 },
 	 { 0x46000000, 0x46000000 },
 	 { 0x45c00000, 0x45c00000 },
 	 { 0x45800000, 0x45800000 },
 	 { 0x45400000, 0x45400000 },
 	 { 0x45000000, 0x45000000 },
 	 { 0x44c00000, 0x44c00000 },
 	 { 0x44800000, 0x44800000 },
 	 { 0x44400000, 0x44400000 },
 	 { 0x44000000, 0x44000000 },
 	 { 0x43c00000, 0x43c00000 },
 	 { 0x43800000, 0x43800000 },
 	 { 0x43400000, 0x43400000 },
 	 { 0x43000000, 0x43000000 },
 	 { 0x42c00000, 0x42c00000 },
 	 { 0x42800000, 0x42800000 },
 	 { 0x42400000, 0x42400000 },
 	 { 0x42000000, 0x42000000 },
 	 { 0x42000000, 0x42000000 },
 	 { 0x41c00000, 0x41c00000 },
 	 { 0x41800000, 0x41800000 },
 	 { 0x41400000, 0x41400000 },
 	 { 0x41000000, 0x41000000 },
 	 { 0x40c00000, 0x40c00000 },
 	 { 0x40800000, 0x40800000 },
 	 { 0x40400000, 0x40400000 },
 	 { 0x40000000, 0x40000000 },
 	 { 0xf00eff00, 0x8300ffff },
 	 { 0x60000000, 0x1234567 },
 	 { 0x60000004, 0x0 },
	 { 0xDEADDEAD, 0xDEADDEAD}
};

