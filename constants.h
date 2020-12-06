/**
 * @file constants.h
 *
 * @brief Deklariert Konstanten, die dazu dienen Einstellungen in einer separaten Datei schnell anpassen zu können,
 *        ohne den Quellcode durchsuchen zu müssen.
 *
 * @date 20.11.2020
 * @author Simon
 */

#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

/** Gibt die Gesamtbreite des Fensters an. */
#define WINDOW_WIDTH            1024
/** Gibt die Gesamthöhe des Fensters an. */
#define WINDOW_HEIGHT           768

/** Gibt an, ob der Debugmodus aktiv ist. (1 = TRUE, 0 = FALSE) */
#define DEBUG_MODE              1

/** Gibt die Bilder pro Sekunde an, mit denen das Spiel gezeichnet wird. */
#define FPS                     60.0

/** Der Pfad zur Schriftart, die standardgemäß verwendet wird. */
#define GAME_FONT_PATH          "res/game_font.ttf"

/** Der Pfad zum Bild für den Spielercharakter. */
#define PLAYER_SPRITE_PATH      "res/player.tga"
/** Der Pfad zum Bild für den Gegnercharakter. */
#define ENEMY_SPRITE_PATH       "res/enemy.tga"
/** Der Pfad zum Bild für die Wände. */
#define WALL_SPRITE_PATH        "res/wall.tga"
/** Der Pfad zum Bild für die Seitentüren. */
#define DOOR_SPRITE_PATH        "res/door.tga"
/** Der Pfad zum Bild für die offenen Seitentüren. */
#define DOOR_OPEN_SPRITE_PATH   "res/door_open.tga"
/** Der Pfad zum Bild für die Kugeln. */
#define BULLET_SPRITE_PATH      "res/bullet.tga"
/** Der Pfad zum Bild für die Explosion. */
#define EXPLOSION_SPRITE_PATH   "res/explosion.tga"
/** Der Pfad zum Bild für ein Herz. */
#define HEART_SPRITE_PATH       "res/heart.tga"

/** Die Geschwindigkeit, mit der sich der Spieler bewegt. */
#define PLAYER_MOVEMENT_SPEED   4.0f
/** Die Geschwindigkeit, mit der eine Kugel fliegt. */
#define BULLET_MOVEMENT_SPEED   7.0f
/** Die Geschwindigkeit, mit der sich die Gegner bewegen. */
#define ENEMY_MIN_MOVE_SPEED    1.0f
/** Die Geschwindigkeit, mit der sich die Gegner bewegen. */
#define ENEMY_MAX_MOVE_SPEED    1.5f

/** Die Lebenspunkte, mit denen der Spieler anfängt. */
#define START_PLAYER_HP         5
/** Die maximale Anzahl an Kugeln des Spielers, die gleichzeitig auf dem Spielfeld sein können. */
#define PLAYER_MAX_BULLETS      10

/** Die minimale Anzahl an Räumen, die auf der Minimap generiert werden. */
#define MIN_ROOMS               7
/** Die maximale Anzahl an Räumen, die auf der Minimap generiert werden. */
#define MAX_ROOMS               10
/** Die minimale Anzahl an Gegnern, die in einem Raum auftauchen können. */
#define MIN_ENEMIES_PER_ROOM    5
/** Die maximale Anzahl an Gegnern, die in einem Raum auftauchen können. */
#define MAX_ENEMIES_PER_ROOM    8

/** Die Breite und Höhe, die ein Feld im Spielbereich hat. */
#define GAME_TILE_SIZE          32
/** Die Breite und Höhe, die ein Feld im Infobereich hat. */
#define HUD_TILE_SIZE           32
/** Die Breite und Höhe, die ein Feld der Minimap hat. */
#define MINIMAP_TILE_SIZE       24

/** Die Höhe des Infobereichs in Feldern. Die Höhe wird von der Fensterhöhe abgezogen. */
#define HUD_HEIGHT_IN_TILES     7

/** Die X Position der oberen linken Ecke des Spielfelds. */
#define GAME_TOP                0
/** Die Y Position der oberen linken Ecke des Spielfelds. */
#define GAME_LEFT               0
/** Die X Position der unteren rechten Ecke des Spielfelds. */
#define GAME_BOTTOM             (WINDOW_HEIGHT - (HUD_HEIGHT_IN_TILES * HUD_TILE_SIZE))
/** Die Y Position der unteren rechten Ecke des Spielfelds. */
#define GAME_RIGHT              WINDOW_WIDTH

/** Die X Position der oberen linken Ecke der Tür am oberen Rand. (Die Breite und Höhe entsprechen GAME_TILE_SIZE) */
#define ROOM_DOOR_TOP_X         (GAME_RIGHT / 2 - GAME_TILE_SIZE)
/** Die Y Position der oberen linken Ecke der Tür am oberen Rand. */
#define ROOM_DOOR_TOP_Y         0

/** Die X Position der oberen linken Ecke der Tür am rechten Rand. (Die Breite und Höhe entsprechen GAME_TILE_SIZE) */
#define ROOM_DOOR_RIGHT_X       (GAME_RIGHT - GAME_TILE_SIZE)
/** Die Y Position der oberen linken Ecke der Tür am rechten Rand. */
#define ROOM_DOOR_RIGHT_Y       (GAME_BOTTOM / 2 - GAME_TILE_SIZE)

/** Die X Position der oberen linken Ecke der Tür am unteren Rand. (Die Breite und Höhe entsprechen GAME_TILE_SIZE) */
#define ROOM_DOOR_BOTTOM_X      (GAME_RIGHT / 2 - GAME_TILE_SIZE)
/** Die Y Position der oberen linken Ecke der Tür am unteren Rand. */
#define ROOM_DOOR_BOTTOM_Y      GAME_BOTTOM

/** Die X Position der oberen linken Ecke der Tür am linken Rand. (Die Breite und Höhe entsprechen GAME_TILE_SIZE) */
#define ROOM_DOOR_LEFT_X        0
/** Die Y Position der oberen linken Ecke der Tür am linken Rand. */
#define ROOM_DOOR_LEFT_Y        (GAME_BOTTOM / 2 - GAME_TILE_SIZE)

/** Die X Position der oberen linken Ecke des Infobereichs. */
#define HUD_TOP                 (GAME_BOTTOM + GAME_TILE_SIZE)
/** Die Y Position der oberen linken Ecke des Infobereichs. */
#define HUD_LEFT                0
/** Die X Position der unteren rechten Ecke des Spielfelds. */
#define HUD_BOOTOM              WINDOW_HEIGHT
/** Die Y Position der unteren rechten Ecke des Spielfelds. */
#define HUD_RIGHT               WINDOW_WIDTH

/** Die maximale Anzahl an Feldern der Minimap in der Breite. */
#define MINIMAP_WIDTH_IN_TILES  7
/** Die maximale Anzahl an Feldern der Minimap in der Höhe. */
#define MINIMAP_HEIGHT_IN_TILES 7

/** Die X Position des mittleren Felds der Minimap. (z.B. Bei einer Breite von 7 => abgerundet(7 / 2.0) = 3) */
#define MINIMAP_MIDDLE_X        ((UINT8) (MINIMAP_WIDTH_IN_TILES / 2.0))
/** Die Y Position des mittleren Felds der Minimap. (z.B. Bei einer Höhe von 7 => abgerundet(7 / 2.0) = 3) */
#define MINIMAP_MIDDLE_Y        ((UINT8) (MINIMAP_HEIGHT_IN_TILES / 2.0))

/** Die X Position der oberen linken Ecke der Minimap. */
#define MINIMAP_TOP             HUD_TOP
/** Die Y Position der oberen linken Ecke der Minimap. */
#define MINIMAP_LEFT            0
/** Die X Position der unteren rechten Ecke der Minimap. */
#define MINIMAP_BOTTOM          (HUD_TOP + (MINIMAP_TILE_SIZE * MINIMAP_HEIGHT_IN_TILES))
/** Die Y Position der unteren rechten Ecke der Minimap. */
#define MINIMAP_RIGHT           (MINIMAP_TILE_SIZE * MINIMAP_WIDTH_IN_TILES)

/** Die X Position des ersten Herzes für die Spieler HP. */
#define HUD_FIRST_HEART_X       (MINIMAP_RIGHT + HUD_TILE_SIZE)
/** Die Y Position des ersten Herzes für die Spieler HP. */
#define HUD_FIRST_HEART_Y       MINIMAP_TOP

#endif /* CONSTANTS_H_INCLUDED */
