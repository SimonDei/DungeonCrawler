/**
 * @file player.h
 *
 * @brief Deklariert den Spieler und Funktionen zum laden, zeichnen, löschen u.w.
 *
 * @date 20.11.2020
 * @author Simon
 */

#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <allegro5/allegro.h>

#include "bullet.h"
#include "util.h"
#include "math.h"
#include "map.h"
#include "sprite.h"
#include "turn_direction.h"

typedef struct _ROOM*      LPROOM;
typedef struct _BULLET*    LPBULLET;
typedef const struct _MAP* LPCMAP;

struct _PLAYER {
    LPSPRITE        _sprite;
    FLOAT           _x;
    FLOAT           _y;
    FLOAT           _velocity_x;
    FLOAT           _velocity_y;
    enum _DIRECTION _active_direction;
    LPSPRITE        _explosion;
    LPBULLET        _bullets[PLAYER_MAX_BULLETS];
    UINT8           _hp;
};

typedef struct _PLAYER*       PPLAYER,  *LPPLAYER;
typedef const struct _PLAYER* PCPLAYER, *LPCPLAYER;

/* ******************************************************************/

/**
 * @param pp_player Ein Doppelpointer auf eine PLAYER Struktur, die initialisiert werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT CALLBACK create_player(
    _Out_ LPPLAYER* pp_player);

/**
 * @param p_player Ein Pointer auf eine PLAYER Struktur, die gezeichnet werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT draw_player(
    _In_ LPCPLAYER p_player);

/**
 * @param p_player Ein Pointer auf eine PLAYER Struktur, die auf dem Bildschirm bewegt werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT move_player(
    _InOut_ LPPLAYER p_player);

/**
 * @brief Setzt die Position des Spielers zurück auf die Mitte des Raums nach einem Raumwechsel.
 * @param p_player Ein Pointer auf eine PLAYER Struktur, die auf dem Bildschirm bewegt werden soll.
 * @param incoming_direction Die Richtung, aus der der Spieler kommt.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT reset_player_position(
    _In_ LPPLAYER        p_player,
    _In_ enum _DIRECTION incoming_direction);

/**
 * @param p_map Ein Pointer auf eine MAP Struktur, deren Minimap verschoben werden soll.
 * @param p_player Ein Pointer auf eine PLAYER Struktur, die auf Kollision überprüft werden soll.
 * @return TRUE, falls eine Tür erreicht wurde, ansonsten FALSE.
 */
BOOL check_player_reaches_door(
    _In_ LPCMAP   p_map,
    _In_ LPPLAYER p_player);

/**
 * @param p_player Der Spieler, von dem die Kugel abgefeuert werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT fire_bullet(
    _InOut_ LPPLAYER p_player);

/**
 * @param p_player Ein Pointer auf eine PLAYER Struktur, die gelöscht werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT destroy_player(
    _InOut_opt_ LPPLAYER p_player);

#endif /* PLAYER_H_INCLUDED */
