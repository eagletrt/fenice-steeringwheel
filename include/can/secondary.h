#ifndef SECONDARY_HOOK_H
#define SECONDARY_HOOK_H

#ifndef __STDC_VERSION__
#define __STDC_VERSION__ 201112
#endif

#include "Secondary/c/Secondary.h"
#include "Secondary/can_config.h"
#include "Secondary/ids.h"

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
