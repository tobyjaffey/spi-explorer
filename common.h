#ifndef COMMON_H
#define COMMON_H 1

#include <io.h>
#include <signal.h>

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef TRUE
#define TRUE true
#endif
#ifndef FALSE
#define FALSE false
#endif
#ifndef BOOL
typedef bool BOOL;
#endif

void driver_tick(void);

#endif

