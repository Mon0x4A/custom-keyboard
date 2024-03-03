#ifndef VAMK_KEYMAP_CONFIG_H
#define VAMK_KEYMAP_CONFIG_H

///Imports
#include "pico/stdlib.h"
#include "vamk_types.h"
#include "tusb.h"

//#if IS_VOK_SL_MODEL
//#include "vok_sl_rev0_keymap.h"
//#endif

//#if IS_QLP_MODEL
//#endif

//TODO this should be under preprocessor logic (above) but for some reason
//it's not working. This needs to be sorted out.
//#include "qlp_22_rev1_keymap.h"

#include "seok_38_rev0_keymap_m.h"

///Constants
#define LAYER_COUNT 3
#define MAX_LAYER_COUNT 10

//TODO This needs to be moved to each of the keymap files
static const bool IS_LAYER_STICKY[MAX_LAYER_COUNT] =
{
//  0  1  2  3  4  5  6  7  8  9
    0, 0, 0, 1, 1, 1, 1, 0, 0, 0
};

#endif
