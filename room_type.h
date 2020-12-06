/**
 * @file room_type.h
 *
 * @brief Definition für den Typen eines Raums.
 *
 * @date 23.11.2020
 * @author Simon
 */

#ifndef ROOM_TYPE_H_INCLUDED
#define ROOM_TYPE_H_INCLUDED

/** Definiert den Typen eines Raums, der in der Minimap gespeichert wird. */
enum _ROOM_TYPE {
    ROOM_TYPE_NONE   = 0x00,
    ROOM_TYPE_START  = 0x01,
    ROOM_TYPE_NORMAL = 0x02,
    ROOM_TYPE_BOSS   = 0x03,
    ROOM_TYPE_GIFT   = 0x04
};

#endif /* ROOM_TYPE_H_INCLUDED */
