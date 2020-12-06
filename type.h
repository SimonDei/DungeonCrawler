/**
 * @file type.h
 *
 * @brief Deklariert eigene Datentypen für native C Datentypen, die der einfacheren Zuordnung ihrer Funktion dienen.
 *        Desweiteren ist auf verschiedenen Architekturen die Größe der Datentypen nicht unbedingt gleich.
 *
 * @date 24.11.2020
 * @author Simon
 */

#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>

/* Wird diese Datei mit einem C++ Compiler kompiliert, wird die Datei als C Quellcode gekennzeichnet. */
#ifdef __cplusplus
    extern "C" {
#endif

#ifndef __STDC_FORMAT_MACROS
    /* Wird benötigt für die korrekte Ausgabe von 64-bit Datentypen. */
    #define __STDC_FORMAT_MACROS
#endif
        
#ifndef NULL
    /** Ist NULL nicht definiert in stddef.h, definiere es als NULL Pointer. */
    #define NULL ((void*) 0)
#endif

#ifndef _Bool
    /** Ist _Bool, das für BOOL benötigt wird nicht in stdbool.h definiert, definiere es als Integer mit mindestens 8 bit. */
    #define _Bool int_least8_t
#endif

#ifndef TRUE
    /** Ist TRUE nicht definiert in stdbool.h definiere es als 1. */
    #define TRUE 1
#endif

#ifndef FALSE
    /** Ist FALSE nicht definiert in stdbool.h definiere es als 0. */
    #define FALSE 0
#endif

#ifndef EXIT_FAILURE
    /** Definiert den Rückgabewert der Main Funktion, dient der Veranschaulichung. */
    #define EXIT_FAILURE 1
#endif

#ifndef EXIT_SUCCESS
    /** Definiert den Rückgabewert der Main Funktion, dient der Veranschaulichung. */
    #define EXIT_SUCCESS 0
#endif

/* ******************************************************************/
/*                      Ganzzahl Definitionen                       */
/* ******************************************************************/

typedef signed char        INT8;
typedef signed short       INT16;
typedef signed int         INT32;
typedef int_least64_t      INT64;
typedef long               LONG;
typedef long long          LONGLONG;

typedef unsigned char      UINT8;
typedef unsigned short     UINT16;
typedef unsigned int       UINT32;
typedef uint_least64_t     UINT64;
typedef unsigned long      ULONG;
typedef unsigned long long ULONGLONG;

typedef INT8*              PINT8,      *LPINT8;
typedef INT16*             PINT16,     *LPINT16;
typedef INT32*             PINT32,     *LPINT32;
typedef INT64*             PINT64,     *LPINT64;
typedef LONG*              PLONG,      *LPLONG;
typedef LONGLONG*          PLONGLONG,  *LPLONGLONG;

typedef UINT8*             PUINT8,     *LPUINT8;
typedef UINT16*            PUINT16,    *LPUINT16;
typedef UINT32*            PUINT32,    *LPUINT32;
typedef UINT64*            PUINT64,    *LPUINT64;
typedef ULONG*             PULONG,     *LPULONG;
typedef ULONGLONG*         PULONGLONG, *LPULONGLONG;

/* ******************************************************************/
/*                       Word Definitionen                          */
/* ******************************************************************/

typedef signed short       WORD;
typedef UINT32             DWORD;
typedef UINT64             QWORD;

typedef WORD*              PWORD,      *LPWORD;
typedef DWORD*             PDWORD,     *LPDWORD;
typedef QWORD*             PQWORD,     *LPQWORD;

/* ******************************************************************/
/*               String und Charakter Definitionen                  */
/* ******************************************************************/

typedef char               CHAR;
typedef wchar_t            WCHAR;

typedef unsigned char      UCHAR;
typedef unsigned char      BYTE;

typedef CHAR*              PCHAR,      *LPCHAR;
typedef CHAR*              PSTR,       *LPSTR;
typedef WCHAR*             PWCHAR,     *LPWCHAR;
typedef UCHAR*             PUCHAR,     *LPUCHAR;
typedef BYTE*              PBYTE,      *LPBYTE;
typedef const char*        PCSTR,      *LPCSTR;
typedef const WCHAR*       PCWCHAR,    *LPCWCHAR;

#ifdef UNICODE
    typedef WCHAR          TCHAR;
    typedef WCHAR*         PTCHAR,     *LPTCHAR;
    typedef const WCHAR*   PCTCHAR,    *LPCTCHAR;
#else
    typedef CHAR           TCHAR;
    typedef CHAR*          PTCHAR,     *LPTCHAR;
    typedef const CHAR*    PCTCHAR,    *LPCTCHAR;
#endif

/* ******************************************************************/
/*                     Gleitzahl Deklarationen                      */
/* ******************************************************************/

typedef float              FLOAT;
typedef double             DOUBLE;

typedef FLOAT*             PFLOAT,     *LPFLOAT;
typedef DOUBLE*            PDOUBLE,    *LPDOUBLE;

/* ******************************************************************/
/*                   Booleansche Deklarationen                      */
/* ******************************************************************/

typedef _Bool              BOOL;
typedef BYTE               BOOLEAN;

typedef BOOL*              PBOOL,      *LPBOOL;
typedef BOOLEAN*           PBOOLEAN,   *LPBOOLEAN;

/* ******************************************************************/
/*                Steuerungsdatentypen Deklaration                  */
/* ******************************************************************/

typedef void               VOID;

typedef INT32              SRESULT;
typedef LONG               LRESULT;

typedef VOID*              PVOID,      *LPVOID;

/* Schließt die umgebene Klammer aus der extern "C" Definition oben. */
#ifdef __cplusplus
    }
#endif

#endif /* TYPES_H_INCLUDED */
