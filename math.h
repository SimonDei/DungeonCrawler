/**
 * @file math.h
 *
 * @brief Deklariert benötigte mathematische Funktionen.
 *
 * @date 25.11.2020
 * @author Simon
 */

#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

#include <stdlib.h>

#include "util.h"
#include "type.h"

/**
 * @param min Der Minimalwert der zurückgegeben werden dar.
 * @param max Der Maximalwert der zurückgegeben werden dar.
 * @return Ein Zufallswert zwischen dem Minimal- und Maximalwert, beide mit einbezogen.
 */
FLOAT inclusive_random(
    _In_ FLOAT min,
    _In_ FLOAT max);

/**
 * @param value Der Wert der gerundet werden soll.
 * @return Ist der Nachkommawert über oder gleich 5 wird die nächst höhere Ganzzahl zurückgegeben,
 *         ansonsten wird der Nachkommawert abgetrennt.
 */
INT32 fast_round(
    _In_ FLOAT value);

/**
 * @param a Die erste Zahl, die verglichen werden soll.
 * @param b Die zweite Zahl, die verglichen werden soll.
 * @return Den größeren der zwei Werte.
 */
FLOAT max_float(
    _In_ FLOAT a,
    _In_ FLOAT b);

/**
 * @param a Die erste Zahl, die verglichen werden soll.
 * @param b Die zweite Zahl, die verglichen werden soll.
 * @return Den kleineren der zwei Werte.
 */
FLOAT min_float(
    _In_ FLOAT a,
    _In_ FLOAT b);

/**
 * @param a_x Die X Position, der oberen linken Ecke des ersten Rechtecks.
 * @param a_y Die Y Position, der oberen linken Ecke des ersten Rechtecks.
 * @param a_width Die Breite des ersten Rechtecks.
 * @param a_height Die Höhe des ersten Rechtecks.
 * @param b_x Die X Position, der oberen linken Ecke des zweiten Rechtecks.
 * @param b_y Die Y Position, der oberen linken Ecke des zweiten Rechtecks.
 * @param b_width Die Breite des zweiten Rechtecks.
 * @param b_height Die Höhe zweiten Rechtecks.
 * @return TRUE, falls eine Kollision vorliegt, ansonsten FALSE.
 */
BOOL rect_rect_collision(
     _In_ FLOAT a_x,
     _In_ FLOAT a_y,
     _In_ FLOAT a_width,
     _In_ FLOAT a_height,
     _In_ FLOAT b_x,
     _In_ FLOAT b_y,
     _In_ FLOAT b_width,
     _In_ FLOAT b_height);

/**
 * @param a_x Die X Position des Punkts.
 * @param a_y Die Y Position des Punkts.
 * @param b_x Die X Position, der oberen linken Ecke des zweiten Rechtecks.
 * @param b_y Die Y Position, der oberen linken Ecke des zweiten Rechtecks.
 * @param b_width Die Breite des zweiten Rechtecks.
 * @param b_height Die Höhe zweiten Rechtecks.
 * @return TRUE, falls eine Kollision vorliegt, ansonsten FALSE.
 */
BOOL point_rect_collision(
     _In_ FLOAT a_x,
     _In_ FLOAT a_y,
     _In_ FLOAT b_x,
     _In_ FLOAT b_y,
     _In_ FLOAT b_width,
     _In_ FLOAT b_height);

#endif /* MATH_H_INCLUDED */
