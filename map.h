/**
 * @file map.h
 *
 * @brief Deklariert eine Karte und Funktionen zum laden, zeichnen, löschen u.w.
 *
 * @date 20.11.2020
 * @author Simon
 */

#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "util.h"
#include "sprite.h"
#include "room.h"
#include "minimap.h"

/* Vorwärtsdeklaration für MINIMAP, damit diese als Pointer genutzt werden kann */
typedef struct _MINIMAP*       LPMINIMAP;
typedef const struct _MINIMAP* LPCMINIMAP;
typedef struct _ROOM*          LPROOM;
/* ******************************************************************/

struct _MAP {
    LPMINIMAP _minimap;
    LPROOM    _rooms[MINIMAP_HEIGHT_IN_TILES][MINIMAP_WIDTH_IN_TILES];
    LPSPRITE  _wall_sprite;
    LPSPRITE  _door_sprite;
    LPSPRITE  _door_open_sprite;
};

typedef struct _MAP*       PMAP,  *LPMAP;
typedef const struct _MAP* PCMAP, *LPCMAP;

/* ******************************************************************/

/**
 * @param pp_map Der Doppelpointer auf eine MAP Struktur, die initialisiert werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT CALLBACK create_map(
    _Out_ LPMAP* pp_map);

/**
 * @param p_map Ein Pointer auf eine MAP Struktur die gezeichnet werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT draw_map(
    _In_ LPCMAP p_map);

/**
 * @param p_map Ein Pointer auf eine MAP Struktur, deren Minimap in der Konsole augegeben werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT log_map(
    _In_ LPCMAP p_map);

/**
 * @param p_map Ein Pointer auf eine MAP Struktur, die gelöscht werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT destroy_map(
    _InOut_opt_ LPMAP p_map);

#endif /* MAP_H_INCLUDED */
