#ifndef SYS_VAR_H
#define SYS_VAR_H

#include <QMetaType>

namespace sys_var {

void registerMetaTypes();

// Working Time
typedef int working_time;

// Morning Time: 	0650-1450
// Day Time:		1450-2250
// Night Time:		2250-0650
enum {MORNING=0, DAY=1, NIGHT=2};

// Datafile Info
// -DEALERS_DATAFILE[MORNING]: morning-time dealers datafile
// -DEALERS_DATAFILE[DAY]: day-time dealers datafile
// -DEALERS_DATAFILE[NIGHT]: night-time dealers datafile
const char * const DEALERS_DATAFILE[3] = {"mndlr.dat", "dydlr.dat", "ngtdlr.dat"};

}

Q_DECLARE_METATYPE(sys_var::working_time)

#endif // SYS_VAR_H
