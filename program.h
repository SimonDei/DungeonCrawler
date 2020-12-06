/**
 * @file program.h
 *
 * @brief Deklarationen für das Handling von OpenGL Programmen.
 *
 * @date 28.11.2020
 * @author Simon
 */

#ifndef PROGRAM_H_INCLUDED
#define PROGRAM_H_INCLUDED

#include <stdlib.h>

#include <GL/glew.h>

#include "buffer.h"
#include "util.h"
#include "file.h"
#include "shader_type.h"
#include "sprite.h"

struct _PROGRAM {
    UINT32  _program_id;
    BOOL    _linked;
    UINT32  _vertex_shader_id;
    UINT32  _fragment_shader_id;
    UINT32  _geometry_shader_id;
};

typedef struct _PROGRAM*       PPROGRAM,  *LPPROGRAM;
typedef const struct _PROGRAM* PCPROGRAM, *LPCPROGRAM;

/* ******************************************************************/

 /**
  * @param pp_program Ein Pointer auf eine PROGRAM Struktur, die gefüllt werden soll.
  * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
  */
LRESULT CALLBACK create_program(
    _Out_ LPPROGRAM* pp_program);

/**
 * @param p_program Das Programm, an den der Shader angefügt werden soll.
 * @param shader_type Der Shader, der dem Programm hinzugefügt werden soll.
 * @param p_file_path Der Source Code des Shaders.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT attach_shader_to_program(
    _In_ LPPROGRAM         p_program,
    _In_ enum _SHADER_TYPE shader_type,
    _In_ LPCSTR            p_file_path);

/**
 * @param attrib_location Die Position des Attributs im Shader Sourc Code.
 * @param p_buffer Die Daten, die für den aktuellen Vektor benutzt werden sollen.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */ 
LRESULT set_program_vertex_attrib(
    _In_ UINT8     attrib_location,
    _In_ LPCBUFFER p_buffer);

/**
 * @param p_program Das Programm, dessen Uniform Variablen gefüllt werden soll.
 * @param p_uniform_name Der Name der Uniform Variablen im Shader Source Code.
 * @param p_uniform_value Der Wert, mit dem die Uniform Variable gefüllt werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT set_program_uniform(
    _In_ LPCPROGRAM p_program,
    _In_ LPCSTR     p_uniform_name,
    _In_ LPFLOAT    p_uniform_value);

/**
 * @param p_sprite Das Sprite, dessen Textur genutzt werden soll. Ist dieser Parameter NULL, wird
 *                 die Textur ID direkt an OpenGL gebunden, ohne das eine neue Textur erstellt wird.
 * @param p_texture_id Die OpenGL ID der neuen Textur, die verwaltet werden muss.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT set_texture(
    _In_        LPCSPRITE p_sprite,
    _InOut_opt_ LPUINT32  p_texture_id);

/**
 * @param p_program Das Programm das aktiviert werden soll.
 *                  Falls das Programm noch nicht gelinkt wurde wird es vorher gelinkt.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.            
 */
LRESULT activate_program(
    _In_ LPPROGRAM p_program);

/**
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.        
 */
LRESULT deactivate_program(
    VOID);

/**
 * @param p_program Ein Pointer auf eine PROGRAM Struktur, die gelöscht werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT destroy_program(
    _InOut_opt_ LPPROGRAM p_program);

#endif
