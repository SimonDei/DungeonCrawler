/**
 * @file minimap.h
 *
 * @brief Deklariert die Minimap und Funktionen zum laden, zeichnen, u.w.
 *
 * @date 20.11.2020
 * @author Simon
 */

#ifndef MINIMAP_H_INCLUDED
#define MINIMAP_H_INCLUDED

#include "util.h"
#include "map.h"

/* Vorwärtsdeklaration für MAP, damit diese als Pointer genutzt werden kann */
typedef struct _MAP*       PMAP,  *LPMAP;
typedef const struct _MAP* PCMAP, *LPCMAP;
/* ******************************************************************/

struct _MINIMAP {
    UINT8 _width;
    UINT8 _height;
    UINT8 _player_x;
    UINT8 _player_y;
    UINT8 _room_count;
    BOOL  _has_boss_room;
    BOOL  _has_gift_room;
};

typedef struct _MINIMAP*       PMINIMAP,  *LPMINIMAP;
typedef const struct _MINIMAP* PCMINIMAP, *LPCMINIMAP;

/* ******************************************************************/

/**
 * @param p_map Ein Pointer auf eine MAP Struktur, für die eine Minimap erstellt werden soll.
 * @param x Die aktuelle X Position, die vom Algorithmus geprüft wird.
 * @param y Die aktuelle Y Position, die vom Algorithmus geprüft wird.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT CALLBACK generate_minimap(
    _InOut_ LPMAP p_map,
    _In_    INT8  x,
    _In_    INT8  y);

/**
 * @param p_map Ein Pointer auf eine MAP Struktur, deren Minimap gezeichnet werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT draw_minimap(
    _In_ LPCMAP p_map);

/**
 * @param p_map Ein Pointer auf eine MAP Struktur, die die Räume zur Verfügung stellt.
 * @param offset_x Das Offset auf der sich in X Richtung bewegt werden soll.
 * @param offset_y Das Offset auf der sich in Y Richtung bewegt werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT move_minimap_position(
    _In_ LPCMAP p_map,
    _In_ INT8   offset_x,
    _In_ INT8   offset_y);

#endif /* MINIMAP_H_INCLUDED */
