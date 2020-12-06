/**
 * @file shader.h
 *
 * @brief Deklarationen f�r das Handling von OpenGL Shadern.
 *
 * @date 27.11.2020
 * @author Simon
 */

#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

#include <stdlib.h>

#include <GL/glew.h>

#include "util.h"
#include "shader_type.h"

struct _SHADER {
    UINT32            _shader_id;
    enum _SHADER_TYPE _type;
};

typedef struct _SHADER*       PSHADER,  *LPSHADER;
typedef const struct _SHADER* PCSHADER, *LPCSHADER;

/* ******************************************************************/

 /**
  * @param shader_type Der Typ, den der Shader beim zuordnen haben soll.
  * @param p_shader_source Der Source Code des Shaders.
  * @param pp_shader Ein Pointer auf eine SHADER Struktur die gef�llt werden soll.
  * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zur�ckgegeben.
  */
LRESULT CALLBACK create_shader(
    _In_  enum _SHADER_TYPE shader_type,
    _In_  LPCSTR            p_shader_source,
    _Out_ LPSHADER*         pp_shader);

/**
 * @param p_shader Ein Pointer auf eine SHADER Struktur, die gel�scht werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zur�ckgegeben.
 */
LRESULT destroy_shader(
    _InOut_opt_ LPSHADER p_shader);

#endif /* SHADER_H_INCLUDED */
