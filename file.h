/**
 * @file file.h
 *
 * @brief Deklarationen für das Auslesen von Dateien.
 *
 * @date 27.11.2020
 * @author Simon
 */

#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include <stdlib.h>

#include "util.h"

/* Wird diese Datei mit einem C++ Compiler kompiliert, wird die Datei als C Quellcode gekennzeichnet. */
#ifdef __cplusplus
    extern "C" {
#endif

/**
 * @param p_file_path Der Pfad zur Datei die gelesen werden soll.
 * @param pp_file_content Der Inhalt der zu lesenden Datei.
 * @return Wenn die Funktion erfolgreich war wird LR_SUCCESS zurückgegeben.
 */
LRESULT CALLBACK read_file(
    _In_  LPCSTR  p_file_path,
    _Out_ LPCSTR* pp_file_content);

/* Schließt die umgebene Klammer aus der extern "C" Definition oben. */
#ifdef __cplusplus
    }
#endif
            
#endif /* FILE_H_INCLUDED */
