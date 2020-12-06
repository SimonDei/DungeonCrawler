/**
 * @file turn_direction.h
 *
 * @brief Definition für die Blickrichtung eines Sprites.
 *
 * @date 23.11.2020
 * @author Simon
 */

#ifndef TURN_DIRECTION_H_INCLUDED
#define TURN_DIRECTION_H_INCLUDED

/** Definiert die Richtung, in die der Spieler oder ein Gegner gerade guckt. */
enum _DIRECTION {
    DIRECTION_LEFT  = 0x00,
    DIRECTION_RIGHT = 0x01,
    DIRECTION_UP    = 0x02,
    DIRECTION_DOWN  = 0x03
};

#endif /* TURN_DIRECTION_H_INCLUDED */
