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
#include "qlp_22_rev0_keymap.h"

///Constants
#define LAYER_COUNT 3
#define MAX_LAYER_COUNT 10

static const bool IS_LAYER_STICKY[MAX_LAYER_COUNT] =
{
//  0  1  2  3  4  5  6  7  8  9
    0, 0, 0, 1, 1, 1, 1, 0, 0, 0
};

#define CONTROLLER_IS_LEFT_SIDE 1
#define CONTROLLER_IS_RIGHT_SIDE 0
#if (CONTROLLER_IS_LEFT_SIDE && CONTROLLER_IS_RIGHT_SIDE) || !(CONTROLLER_IS_LEFT_SIDE || CONTROLLER_IS_RIGHT_SIDE)
#error "Controller must be on one (and only one) side in a split configuration"
#endif

#endif
