/**
 * @file sprite.h
 *
 * @brief Deklariert ein Sprite und Funktionen zum laden, zeichnen und löschen.
 *
 * @date 23.11.2020
 * @author Simon
 */

#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include <allegro5/allegro.h>

#include "util.h"

/** Ermöglicht es einem Sprite eine Rotation in Mehrfachen von 90 Grad anzugeben. */
enum _ROTATION {
    ROTATE_0   = 0x00,
    ROTATE_90  = 0x01,
    ROTATE_180 = 0x02,
    ROTATE_270 = 0x03,
    ROTATE_360 = 0x04
};

struct _SPRITE {
    ALLEGRO_BITMAP* _texture;
    FLOAT           _width;
    FLOAT           _height;
};

typedef struct _SPRITE*	      PSPRITE,  *LPSPRITE;
typedef const struct _SPRITE* PCSPRITE, *LPCSPRITE;

/* ******************************************************************/

/**
 * @param p_file_path Der Pfad zu einem Bild, das in die Struktur geladen werden soll.
 * @param pp_sprite Der Doppelpointer auf eine SPRITE Struktur, die initialisiert werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT CALLBACK create_sprite(
    _In_  LPCSTR    p_file_path,
    _Out_ LPSPRITE* pp_sprite);

/**
 * @param p_sprite Ein Pointer auf eine SPRITE Struktur, die gezeichnet werden soll.
 * @param x Die X Position, an der das Bild gezeichnet werden soll.
 * @param y Die Y Position, an der das Bild gezeichnet werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT draw_sprite(
    _In_ LPCSPRITE p_sprite,
    _In_ FLOAT     x,
    _In_ FLOAT     y);

/**
 * @param p_sprite Ein Pointer auf eine SPRITE Struktur, die gezeichnet werden soll.
 * @param x Die X Position, an der das Bild gezeichnet werden soll.
 * @param y Die Y Position, an der das Bild gezeichnet werden soll.
 * @param rotation Die Rotation, mit der das Bild rotiert werden soll
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT draw_rotated_sprite(
    _In_ LPCSPRITE      p_sprite,
    _In_ FLOAT          x,
    _In_ FLOAT          y,
    _In_ enum _ROTATION rotation);

/**
 * @param p_sprite Ein Pointer auf eine SPRITE Struktur, die gelöscht werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT destroy_sprite(
    _InOut_opt_ LPSPRITE p_sprite);

#endif /* SPRITE_H_INCLUDED */
