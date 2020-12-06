/**
 * @file enemy.h
 *
 * @brief Deklariert einen Gegner und Funktionen zum laden, zeichnen und löschen.
 *
 * @date 23.11.2020
 * @author Simon
 */

#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <allegro5/allegro_primitives.h>

#include "util.h"
#include "math.h"
#include "minimap.h"
#include "turn_direction.h"
#include "sprite.h"
#include "player.h"

typedef struct _PLAYER* LPPLAYER;

struct _ENEMY {
    LPSPRITE        _sprite;
    FLOAT           _x;
    FLOAT           _y;
    FLOAT           _velocity_x;
    FLOAT           _velocity_y;
    enum _DIRECTION _active_direction;
    INT8            _hp;
};

typedef struct _ENEMY*       PENEMY,  *LPENEMY;
typedef const struct _ENEMY* PCENEMY, *LPCENEMY;

/* ******************************************************************/

/**
 * @param pp_enemy Der Doppelpointer auf eine ENEMY Struktur, die initialisiert werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT CALLBACK create_enemy(
    _Out_ LPENEMY* pp_enemy);

/**
 * @param p_enemy Ein Pointer auf eine ENEMY Struktur, die gezeichnet werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT draw_enemy(
    _In_ LPCENEMY p_enemy);

/**
 * @param p_enemy Ein Pointer auf eine ENEMY Struktur, die auf dem Bildschirm bewegt werden soll.
 * @param player_x Die X Position des Spielers auf dem Spielfeld.
 * @param player_y Die Y Position des Spielers auf dem Spielfeld.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT move_single_enemy(
    _InOut_ LPENEMY p_enemy,
    _In_    FLOAT   player_x,
    _In_    FLOAT   player_y);

/**
 * @param p_map Ein Pointer auf eine MAP Struktur, die den aktuellen Raum enthält.
 * @param p_player Ein Pointer auf eine PLAYER Struktur, dessen Kollision geprüft werden soll.
 * @param player_x Die aktuelle X Position des Spielers auf der Minimap.
 * @param player_y Die aktuelle Y Position des Spielers auf der Minimap.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT check_enemy_hits_player(
    _In_ LPCMAP   p_map,
    _In_ LPPLAYER p_player,
    _In_ UINT8    player_x,
    _In_ UINT8    player_y);

/**
 * @param p_enemy Ein Pointer auf eine ENEMY Struktur, die gelöscht werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT destroy_enemy(
    _InOut_opt_ LPENEMY p_enemy);

#endif /* ENEMY_H_INCLUDED */
