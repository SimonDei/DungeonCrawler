# DungeonCrawler 

## Installation
1. Code::Blocks IDE zip-Datei über: https://drive.google.com/file/d/1seUpnlWzO-cbL6Fw3cjoQGaL5Y-qzkLI/view?usp=sharing herunterladen und nach "C:/" entpacken. (Das Entpacken kann bis zu 10 Minuten dauern)  
**Hinweis:** Ist es nicht möglich die zip-Datei unter "C:/" zu entpacken muss nach dem öffnen von Code::Blocks über "Settings -> Compiler -> Global Compiler Settings" unter dem Unterreiter "Toolchain executables" bei "Compiler's installation directory" auf den Knopf "Auto-detect" geklickt werden um den korrekten Pfad zum Compiler zu setzen.
2. Dieses Repository über "Code -> Download ZIP" herunterladen und entpacken.
3. codeblocks.exe öffnen und über "File -> Open" oder Strg+O die .cbp-Datei aus dem entpackten Repository öffnen.
4. Das Projekt kann über "Build -> Build and run" oder F9 gestartet werden.

## C Style-Guide
### Parameter
Jeder Parameter wird in eine eigene Zeile geschrieben mit 4 Leerzeichen vorran. Dabei wird auf korrekten Einzug bei Annotation, Datentyp und Parameternamen geachtet.  
```C
VOID my_function(
    _In_  INT32   x,
    _In_  INT32   y,
    _Out_ LPINT32 p_result);
```
Pointer werden mit einem `p_` vorran deklariert.  
Doppelpointer werden mit `pp_` vorran deklariert.

Die `CALLBACK` Annotation wird für Funktionen verwendet, die einen Doppelpointer entgegennehmen und diesen füllen.

Es gibt 6 verschiedene Annotationen für Parameter
* `_In_` Die Funktion liest aus diesem Parameter, verändert ihn jedoch in keinster Weise. Darf nicht NULL enthalten.
* `_Out_` Die Funktion füllt diesen Pointer, liest jedoch zu keiner Zeit etwas heraus.
* `_InOut_` Die Funktion liest und schreibt am Ende in diesen Pointer. Darf beim Aufruf nicht NULL enthalten.
* `_In_opt_` Die Funktion liest aus diesem Pointer, jedoch darf dieser NULL enthalten.
* `_InOut_opt_` Die Funktion liest und schreibt in diesen Pointer, jedoch darf dieser beim Aufruf NULL enthalten.

Pointer sollten, falls möglich, auf einen Konstanten Wert zeigen.
```C
const struct X*
```  

Desweiteren sollte ein Pointer selbst, falls möglich, immer konstant sein.
```C
struct X* const
```

Optimal wäre ein konstanter Pointer auf einen konstanten Wert.
```C
const struct X* const
```

---
### Datentypen
Es gibt mehrere verschiedene Datentypen, diese sind in **"type.h"** definiert.  
Typendefinitionen haben den Grund, dass man bei Änderung der Anforderungen an Typen, diese zentral ändern kann.  
Desweiteren beschreibt ein `UINT8` eine Zählvariable besser als ein `unsigned char`.  
> Anmerkung:  
> In C steht `char` keinesfalls immer für ein Zeichen sondern lediglich für 1 Byte (-128 bis +127) an Speicher.  

Es sollte in jeder Situation der entsprechend passende Datentyp benutzt werden.  
* In einer "for"-Schleife sollte als Zähler ein `UINT8` benutzt werden.
* Es sollte immer ein `BOOL` für Wahrheitswerte benutzt werden und `TRUE` oder `FALSE` zugeordnet werden.
* Steht fest, dass ein Zahlenwert nie unter 0 fällt sollte immer ein `UINT..` benutzt werden.
* Muss über binäre Operationen auf die Variable zugegriffen werden sollte ein `WORD` oder `DWORD` benutzt werden.

---
### Strukturen
Strukturen selbst werden nicht durch einen `typedef` global redifiniert, sie bleiben im struct space.  
Es wird auf korrekten Einzug geachtet und jede Membervariable beginnt mit einem "_".
```C
struct _MYSTRUCT {
    BOOL   _my_bool;
    INT32  _my_int;
    LPCSTR _my_string;
};
```
Für jede Struktur sollten 4 Pointer-Typendefinitionen erstellt werden:
```C
typedef struct ..* P..
typedef struct ..* LP..
typedef const struct ..* PC..
typedef const struct ..* LPC..  
```
`P` und `LP` sind dabei in der Definition gleich. Beide sind als 32-bit Pointer definiert. Es werden keine 16-bit Pointer definiert.

---
### Makros
In **"util.h"** sind mehrere nützliche Makros definiert, die repetitive Aufgaben vereinfachen, sich um Fehler kümmern oder anhand der Architektur dentsprechend die Richtigen Datentypen auswählen. Diese sollten bevorzugt benutzt werden.  
* `ALLOC_MEMORY(type)` Gibt für den Typen allokierten Speicher zurück.
* `CLEAR_MEMORY(pointer)` Nullt den allokieren Speicher des Pointers.
* `FREE_MEMORY(pointer)` Gibt den allokierten Speicher des Pointers frei und setzt ihn auf NULL.
* `CHANGE_OWNER(new_owner, old_owner)` Übergiebt den Speicher eines Pointers an einen Doppelpointer.
* `TEXT(string)` Gibt einen Text als Wide-String zurück, falls in der aktuellen Implementation Unicode definiert ist.
* `LOG_INFO(string)` Gibt einen Info-Text in der Standardkonsole aus. Falls möglich als UTF-8 String.
* `LOG_ERROR(string)` Gibt einen Error-Text in der Standardkonsole aus. Falls möglich als UTF-8 String.
* `DEG_TO_RAD(degree)` Konvertiert Grad in Radiant um.
* `RAD_TO_DEG(radiant)` Konvertiert Radiant in Grad um.
