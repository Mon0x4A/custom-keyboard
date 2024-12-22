#ifndef VAMK_KEYMAP_CONFIG_H
#define VAMK_KEYMAP_CONFIG_H

///Imports
#include "pico/stdlib.h"
#include "vamk_types.h"
#include "tusb.h"

//TODO Uncomment the desired keymap!
//#include "vok_sl_rev0_keymap.h"
//#include "qlp_22_rev1_keymap.h"
//#include "seok_38_rev0_keymap_m.h"
//#include "mskp_qlp_rev0_keymap.h"
#include "mskp_lpk20_rev0_keymap.h"

///Constants
#define LAYER_COUNT 6
#define MAX_LAYER_COUNT 10

//TODO This needs to be moved to each of the keymap files
static const bool IS_LAYER_STICKY[MAX_LAYER_COUNT] =
{
//  0  1  2  3  4  5  6  7  8  9
    0, 0, 0, 1, 1, 1, 1, 0, 0, 0
};

#endif
