#ifndef SECONDARY_HOOK_H
#define SECONDARY_HOOK_H

#ifndef __STDC_VERSION__
#define __STDC_VERSION__ 201112
#endif

#include "secondary/c/secondary.h"
#include "secondary/can_config.h"
#include "secondary/ids.h"

#ifdef setBit
#undef setBit
#endif

#ifdef flipBit
#undef flipBit
#endif

#ifdef getBit
#undef getBit
#endif

#endif // SECONDARY_HOOK_H
