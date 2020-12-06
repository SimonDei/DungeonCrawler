/**
 * @file bullet.h
 *
 * @brief Deklariert eine Kugel des Spielers oder der Gegner und Funktionen zum laden, zeichnen, u.w. 
 * 
 * @date 26.11.2020
 * @author Simon
 */

#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "player.h"
#include "util.h"
#include "sprite.h"
#include "turn_direction.h"

typedef struct _PLAYER* LPPLAYER;
typedef struct _ROOM*   LPROOM;

struct _BULLET {
    LPSPRITE _sprite;
    FLOAT    _x;
    FLOAT    _y;
    enum _DIRECTION _active_direction;
};

typedef struct _BULLET*       PBULLET,  *LPBULLET;
typedef const struct _BULLET* PCBULLET, *LPCBULLET;

/* ******************************************************************/

/**
 * @param pp_bullet Der Doppelpointer auf eine BULLET Struktur, die initialisiert werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT CALLBACK create_bullet(
    _Out_ LPBULLET* pp_bullet);

/**
 * @param p_bullet Ein Pointer auf eine BULLET Struktur, die gezeichnet werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT draw_bullet(
    _In_ LPBULLET p_bullet);

/**
 * @param p_player Der Spieler, dessen Kugeln geprüft werden soll.
 * @param p_room Der Raum, dessen Gegner geprüft werden sollen.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT check_bullet_hits_enemy(
    _In_ LPPLAYER p_player,
    _In_ LPROOM   p_room);

/**
 * @param p_player Der Spieler, dessen Kugeln geprüft werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT check_bullet_hits_wall(
    _In_ LPPLAYER p_player);

/**
 * @param p_bullet Ein Pointer auf eine BULLET Struktur, die gelöscht werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT destroy_bullet(
    _InOut_opt_ LPBULLET p_bullet);

#endif /* BULLET_H_INCLUDED */
