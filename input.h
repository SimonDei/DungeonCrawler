/**
 * @file input.h
 * 
 * @brief Deklariert Funktionen zum behandeln von Benutzereingaben über Tastatur oder Maus.
 *
 * @date 20.11.2020
 * @author Simon
 */

#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include <allegro5/events.h>

#include "util.h"
#include "player.h"

/**
 * @param p_event Das Allegro Event, das ausgelöst wurde.
 * @param p_running Ein Pointer auf den Boolean, der angibt ob das Spiel noch läuft.
 * @param p_player Ein Pointer auf die PLAYER Struktur des Spiels.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT handle_keyboard(
    _In_    ALLEGRO_EVENT* p_event,
    _InOut_ LPBOOL         p_running,
    _In_    LPPLAYER       p_player);

/**
 * @param p_event Das Allegro Event, das ausgelöst wurde.
 * @param p_running Ein Pointer auf den Boolean, der angibt ob das Spiel noch läuft.
 * @param p_player Ein Pointer auf die PLAYER Struktur des Spiels.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT handle_mouse(
    _In_    ALLEGRO_EVENT* p_event,
    _InOut_ LPBOOL         p_running,
    _In_    LPPLAYER       p_player);

#endif /* INPUT_H_INCLUDED */
