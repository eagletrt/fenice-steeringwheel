#ifndef PRIMARY_HOOK_H
#define PRIMARY_HOOK_H

#ifndef __STDC_VERSION__
#define __STDC_VERSION__ 201112
#endif

#include "primary/c/primary.h"
#include "primary/can_config.h"
#include "primary/ids.h"

#ifdef setBit
#undef setBit
#endif

#ifdef flipBit
#undef flipBit
#endif

#ifdef getBit
#undef getBit
#endif

#endif // PRIMARY_HOOK_H
