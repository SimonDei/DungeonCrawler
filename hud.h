/**
 * @file hud.h
 *
 * @brief Deklariert die Infos f�r den Infobereich des Spiels.
 *
 * @date 20.11.2020
 * @author Simon
 */

#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

#include <allegro5/allegro_primitives.h>

#include "util.h"

struct _INFOS {
    UINT8 _x;
};

/* ******************************************************************/

/**
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zur�ckgegeben.
 */
LRESULT draw_hud(
    VOID);

#endif /* HUD_H_INCLUDED */
