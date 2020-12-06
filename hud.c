/**
 * Created by Simon on 20.11.2020.
 */

#include "hud.h"

LRESULT draw_hud(VOID) {
    al_draw_filled_rectangle(HUD_LEFT,
                             HUD_TOP,
                             HUD_RIGHT,
                             HUD_BOOTOM,
                             al_map_rgb(0, 0, 0));
    return LR_SUCCESS;
}
