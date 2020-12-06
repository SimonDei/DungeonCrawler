/**
 * @file buffer.h
 *
 * @brief
 * 
 * @date 30.11.2020
 * @author Simon
 */

#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED

#include <GL/glew.h>

#include "util.h"

struct _BUFFER {
    UINT32 _buffer_id;
    UINT8  _stride;
};

typedef struct _BUFFER*       PBUFFER,  *LPBUFFER;
typedef const struct _BUFFER* PCBUFFER, *LPCBUFFER;

/* ******************************************************************/

/**
 * @param pp_buffer Ein Pointer auf eine BUFFER Struktur, die gefüllt werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT CALLBACK create_buffer(
    _Out_ LPBUFFER* pp_buffer);

/**
 * @param p_buffer Eine Buffer Struktur, die mit Daten gefüllt werden soll.
 * @param p_data Ein Pointer auf float Daten, die in den Buffer geladen werden sollen.
 * @param stride Die Größe eines Werts z.B. 3 für X, Y, Z oder 2 für S, T.
 * @param size Die Größe der Daten in Bytes.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT fill_buffer(
    _In_ LPBUFFER p_buffer,
    _In_ LPFLOAT  p_data,
    _In_ UINT8    stride,
    _In_ UINT32   size);

/**
 * @param p_buffer Ein Pointer auf eine BUFFER Struktur, die gelöscht werden soll.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT destroy_buffer(
    _InOut_opt_ LPBUFFER p_buffer);

#endif /* BUFFER_H_INCLUDED */
