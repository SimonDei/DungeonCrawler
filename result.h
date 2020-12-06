/**
 * @file result.h
 *
 * @brief Deklariert Rückgabewerte für Funktionen und Makros zum überprüfen ob eine Funktion erfolgreich war oder nicht.
 *
 * @date 24.11.2020
 * @author Simon
 */

#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#include "type.h"

/* Wird diese Datei mit einem C++ Compiler kompiliert, wird die Datei als C Quellcode gekennzeichnet. */
#ifdef __cplusplus
    extern "C" {
#endif

/**
 * @brief Definiere Ergebniswerte für Funktionen. Rückgabewerte lediglich für SRESULT Funktionen.
 *        Das steigende MSB definiert, wie schwerwiegend der Fehler ist, das LSB dient als Zähler.
 */
enum _SRESULT_CODES {
    /* ******************************************************************/
    /** Die Funktion wurde erfolgreich beendet. */
    SR_SUCCESS              = ((SRESULT) 0x0000),

    /* ******************************************************************/
    /** Die Funktion wurde vorzeitig abgebrochen. */
    SR_ABORT                = ((SRESULT) 0x1000),
    /** Eine von dieser aufgerufene Funktion ist fehlgeschlagen. */
    SR_FAILED               = ((SRESULT) 0x1001),
    /** Es wurde versucht auf einen ungültigen Speicherbereich zuzugreifen. */
    SR_SEGFAULT             = ((SRESULT) 0x1002),

    /* ******************************************************************/
    /** Es wurde versucht eine Division durch 0 durchzuführen. */
    SR_ZERO_DIVIDE          = ((SRESULT) 0x2000),
    /** Die zu öffnende Datei konnte nicht gefunden werden. */
    SR_FILE_NOT_FOUND       = ((SRESULT) 0x2001),
    /** Der Index liegt außerhalb der Größe des Arrays. */
    SR_OUT_OF_BOUNDS        = ((SRESULT) 0x2002),
    /** Das Erstellen eines OpenGL Objekts ist fehlgeschlagen. */
    SR_OPENGL_CREATE_FAILED = ((SRESULT) 0x2003),
    /** Ein OpenGL Programm wurde erfolgreich gelinkt und kann benutzt werden. */
    SR_PROGRAM_LINKED       = ((SRESULT) 0x2004),

    /* ******************************************************************/
    /** Die Initialisierung oder Allokation von Speicher ist fehlgeschlagen. */
    SR_POINTER_INIT         = ((SRESULT) 0x3000),
    /** Der übergebene Pointer ist ein ungültiger Nullpointer. */
    SR_NULL_POINTER         = ((SRESULT) 0x3001),
    /** Der übergebene Parameter ist für den erwarteten Typen ungültig. */
    SR_INVALIDARG           = ((SRESULT) 0x3002),
};

/** Definiere Ergebniswerte für Funktionen. Rückgabewerte lediglich für LRESULT Funktionen. */
enum _LRESULT_CODES {
    /* ******************************************************************/
    /** Die Funktion wurde erfolgreich beendet. */
    LR_SUCCESS              = ((LRESULT) 0x0000L),

    /* ******************************************************************/
    /** Die Funktion wurde vorzeitig abgebrochen. */
    LR_ABORT                = ((LRESULT) 0x1000L),
    /** Eine von dieser aufgerufene Funktion ist fehlgeschlagen. */
    LR_FAILED               = ((LRESULT) 0x1001L),
    /** Es wurde versucht auf einen ungültigen Speicherbereich zuzugreifen. */
    LR_SEGFAULT             = ((LRESULT) 0x1002L),

    /* ******************************************************************/                        
    /** Es wurde versucht eine Division durch 0 durchzuführen. */
    LR_ZERO_DIVIDE          = ((LRESULT) 0x2000L),
    /** Die zu öffnende Datei konnte nicht gefunden werden. */
    LR_FILE_NOT_FOUND       = ((LRESULT) 0x2001L),
    /** Der Index liegt außerhalb der Größe des Arrays. */
    LR_OUT_OF_BOUNDS        = ((LRESULT) 0x2002L),
    /** Das Erstellen eines OpenGL Objekts ist fehlgeschlagen. */
    LR_OPENGL_CREATE_FAILED = ((LRESULT) 0x2003L),
    /** Ein OpenGL Programm wurde erfolgreich gelinkt und kann benutzt werden. */
    LR_PROGRAM_LINKED       = ((LRESULT) 0x2004L),

    /* ******************************************************************/
    /** Die Initialisierung oder Allokation von Speicher ist fehlgeschlagen. */
    LR_POINTER_INIT         = ((LRESULT) 0x3000L),
    /** Der übergebene Pointer ist ein ungültiger Nullpointer. */
    LR_NULL_POINTER         = ((LRESULT) 0x3001L),
    /** Der übergebene Parameter ist für den erwarteten Typen ungültig. */
    LR_INVALIDARG           = ((LRESULT) 0x3002L),
};

#ifndef FAILED
    /** Stellt fest, ob das Initialisieren eines Pointers fehlgeschlagen ist. */
    #define FAILED(x) (((LRESULT)(x) & 0x0000FFFF) > LR_SUCCESS)
#endif

#ifndef SUCCEEDED
    /** Stellt fest, ob das Initialisieren eines Pointers erfolgreich war. */
    #define SUCCEEDED(x) (((LRESULT)(x) & 0x0000FFFF) == LR_SUCCESS)
#endif

/* Schließt die umgebene Klammer aus der extern "C" Definition oben. */
#ifdef __cplusplus
    }
#endif

#endif /* ERROR_H_INCLUDED */
