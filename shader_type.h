/**
 * @file shader_type.h
 *
 * @brief Definition für den Typen eines OpenGL Shaders.
 *
 * @date 27.11.2020
 * @author Simon
 */

#ifndef SHADER_TYPE_H_INCLUDED
#define SHADER_TYPE_H_INCLUDED

 /** Definiert die Typen eines Shaders, der dem OpenGL Programm übergeben werden kann. */
enum _SHADER_TYPE {
    SHADER_TYPE_VERTEX   = 0x00,
    SHADER_TYPE_FRAGMENT = 0x01,
    SHADER_TYPE_GEOMETRY = 0x02
};

#endif /* SHADER_TYPE_H_INCLUDED */
