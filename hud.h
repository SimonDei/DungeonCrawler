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
#include "sprite.h"

struct _HUD {
    LPSPRITE _heart;
};

typedef struct _HUD*       PHUD,  *LPHUD;
typedef const struct _HUD* PCHUD, *LPCHUD;

/* ******************************************************************/

/**
 * @param pp_hud Ein Doppelpointer auf eine HUD Struktur, die initialisiert werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zur�ckgegeben.
 */
LRESULT CALLBACK create_hud(
    _Out_ LPHUD* pp_hud);

/**
 * @param p_hud Ein Pointer auf eine HUD Struktur, die gezeichnet werden soll.
 * @param player_hp Die aktuellen HP des Spielers.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zur�ckgegeben.
 */
LRESULT draw_hud(
    _In_ LPCHUD p_hud,
    _In_ UINT8  player_hp);

/**
 * @param p_hud Ein Pointer auf eine PLAYER Struktur, die gel�scht werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zur�ckgegeben.
 */
LRESULT destroy_hud(
    _InOut_opt_ LPHUD p_hud);

#endif /* HUD_H_INCLUDED */
