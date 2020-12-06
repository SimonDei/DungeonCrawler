/**
 * @file room.h
 *
 * @brief Deklariert einen Raum und Funktionen zum zeichnen und löschen.
 *
 * @date 20.11.2020
 * @author Simon
 */

#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <allegro5/allegro_primitives.h>

#include "util.h"
#include "room_type.h"
#include "map.h"
#include "enemy.h"

/* Vorwärtsdeklaration für MAP, damit diese als Pointer genutzt werden kann */
typedef struct _MAP*       LPMAP;
typedef const struct _MAP* LPCMAP;
typedef struct _ENEMY*     LPENEMY;
/* ******************************************************************/

struct _ROOM {
    UINT8           _x;
    UINT8           _y;
    UINT8           _enemy_count;
    LPENEMY         _enemies[MAX_ENEMIES_PER_ROOM];
    enum _ROOM_TYPE _type;
};

typedef struct _ROOM*       PROOM,  *LPROOM;
typedef const struct _ROOM* PCROOM, *LPCROOM;

/* ******************************************************************/

/**
 * @param p_map Ein Pointer auf die MAP Struktur, die die Räume beinhaltet.
 * @param x Die X Position des aktuellen Raums auf der Minimap.
 * @param y Die Y Position des aktuellen Raums auf der Minimap.
 * @param depth Die aktuelle Tiefe des Raums
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT CALLBACK generate_room(
    _InOut_ LPMAP p_map,
    _In_    INT8  x,
    _In_    INT8  y,
    _In_    INT8  depth);

/**
 * @param p_room Ein Pointer auf den Raum, der gezeichnet werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT draw_room(
    _In_ LPCROOM p_room);

/**
 * @param p_room p_room Ein Pointer auf den Raum, dessen Gegner bewegt werden sollen.
 * @param player_x Die X Position des Spielers auf dem Spielfeld.
 * @param player_y Die Y Position des Spielers auf dem Spielfeld.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT move_enemies(
    _In_ LPCROOM p_room,
    _In_ FLOAT   player_x,
    _In_ FLOAT   player_y);

/**
 * @param p_room Ein Pointer auf den Raum der gelöscht werden soll
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT destroy_room(
    _InOut_opt_ LPROOM p_room);

#endif /* ROOM_H_INCLUDED */
