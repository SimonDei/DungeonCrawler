/**
 * @file util.h
 *
 * @brief Deklariert Makros, die repetative Operationen oder schwer verständiche Abläufe einfacher lesbar zu machen.
 *
 * @date 20.11.2020
 * @author Simon
 */

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <memory.h>
#include <float.h>

#include "constants.h"
#include "type.h"
#include "result.h"

/* Wird diese Datei mit einem C++ Compiler kompiliert, wird die Datei als C Quellcode gekennzeichnet. */
#ifdef __cplusplus
    extern "C" {
#endif

#ifndef M_PI
    /** Definition der Zahl Pi für Kreisrechnungen. */
    #define M_PI 3.14159265358979323846
#endif

#ifndef CHANGE_OWNER
    /** Übergibt die Verwaltung von Daten auf einen anderen Pointer. */
    #define CHANGE_OWNER(x, y) (((x) != NULL ? (*(x)) = (y) : NULL), (y) = NULL)
#endif

#ifndef ALLOC_MEMORY
    /** Allokiert Speicher für eine Struktur und gibt einen Pointer darauf zurück. */
    #define ALLOC_MEMORY(x) ((x) malloc(1 * sizeof(*(x){ (void*)0 })))
#endif

#ifndef CLEAR_MEMORY
    /** Setzt den Speicher einer Struktur auf Nullen, falls Speicher allokiert wurde. */
    #define CLEAR_MEMORY(x) ((x) != NULL ? (memset((x), 0, sizeof(*(x)))) : NULL)
#endif

#ifndef FREE_MEMORY
    /** Gibt allokierten Speicher sicher wieder frei und verhindert dangeling pointers. */
    #define FREE_MEMORY(x) ((x) != NULL ? (free((x)), (x) = NULL) : NULL)
#endif

/* Gibt einen String UTF-8 formatiert aus, falls diese vorhanden ist. */
#ifndef TEXT
    #ifdef UNICODE
        #define TEXT(x) L ## x
    #else
        #define TEXT(x) x
    #endif
#endif

/* Loggt einen Error in die Konsole und achtet dabei auf die Möglichkeit, dies in UTF-8 zu tun. */
#ifndef LOG_ERROR
    #ifdef UNICODE
        #define LOG_ERROR(x) (fwprintf(stderr, L"[ERROR]: %s\n", TEXT(x)))
    #else
        #define LOG_ERROR(x) (fprintf(stderr, "[ERROR]: %s\n", TEXT(x)))
    #endif
#endif
        
/* Loggt eine Info in die Konsole und achtet dabei auf die Möglichkeit, dies in UTF-8 zu tun. */
#ifndef LOG_INFO
    #ifdef UNICODE
        #define LOG_INFO(x) (fwprintf(stdout, L"[INFO]: %s\n", TEXT(x)))
    #else
        #define LOG_INFO(x) (fprintf(stdout, "[INFO]: %s\n", TEXT(x)))
    #endif
#endif

#ifndef DEG_TO_RAD
    /** Rechnet eine Zahl von Grad in Radiant um. */
    #define DEG_TO_RAD(x) ((float) ((x) * M_PI / 180.0))
#endif

#ifndef RAD_TO_DEG
    /** Rechnet eine Zahl von Radiant in Grad um. */
    #define RAD_TO_DEG(x) ((float) ((x) * 180.0 / M_PI))
#endif

#ifndef CALLBACK
    /** Annotiert eine Funktion, die übergebene Pointer initialisiert. */
    #define CALLBACK __cdecl
#endif

#ifndef _In_
    /** Annotiert einen Pointer, der gelesen, aber nicht geändert wird. */
    #define _In_
#else
    #undef _In_
    #define _In_
#endif

#ifndef _In_opt_
    /** Wie _In_, jedoch kann der Pointer auch einen NULL Wert enthalten. */
    #define _In_opt_
#else
    #undef _In_opt_
    #define _In_opt_
#endif

#ifndef _Out_
    /** Annotiert einen Pointer, der nicht gelesen, sondern nur geschrieben wird. */
    #define _Out_
#else
    #undef _Out_
    #define _Out_
#endif

#ifndef _InOut_
    /** Annotiert einen Pointer, der gelesen und von der Funktion geändert wird. */
    #define _InOut_
#else
    #undef _InOut_
    #define _InOut_
#endif

#ifndef _InOut_opt_
    /** Wie _Out_, jedoch kann der Pointer zum Aufruf und am Ende NULL enthalten. */
    #define _InOut_opt_
#else
    #undef _InOut_opt_
    #define _InOut_opt_
#endif

/* Schließt die umgebene Klammer aus der extern "C" Definition oben. */
#ifdef __cplusplus
    }
#endif

#endif /* UTILS_H_INCLUDED */
