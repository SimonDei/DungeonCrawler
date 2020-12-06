/**
 * Created by Simon on 20.11.2020.
 */

#include "map.h"

LRESULT CALLBACK create_map(_Out_ LPMAP* pp_map) {
    /* Setzte die aktuelle Zeit als Seed für den Zufallszahlengenerator. */
    srand((ULONG) time(NULL));

    /* Erstelle einen Pointer auf eine MAP Struktur. */
    LPMAP game_map = (LPMAP) malloc(1 * sizeof(struct _MAP));
    if (game_map == NULL) {
        LOG_ERROR("Es konnte kein Speicher für eine _SPRITE Struktur allokiert werden!");
        /* Schlägt das reservieren des Speichers fehl, wird ein NULL Pointer zurückgegeben. */
        return LR_POINTER_INIT;
    }

    /* Nach erfolgreicher Allokation wird der Speicher genullt. */
    memset(game_map, 0, sizeof(struct _MAP));

    /* Erstelle einen Pointer auf eine MINIMAP Struktur in der MAP. */
    game_map->_minimap = (LPMINIMAP) malloc(1 * sizeof(struct _MINIMAP));
    if (game_map->_minimap == NULL) {
        LOG_ERROR("Es konnte kein Speicher für eine _MINIMAP Struktur allokiert werden!");
        /* Schlägt das reservieren des Speichers fehl, wird der bereits reservierte Speicher für die MAP Struktur wieder freigegeben. */
        FREE_MEMORY(game_map);
        return LR_POINTER_INIT;
    }

    /* Setzte die Breite und Höhe der Karte, sowie die Startposition des Spielers. */
    game_map->_minimap->_width = MINIMAP_WIDTH_IN_TILES;
    game_map->_minimap->_height = MINIMAP_HEIGHT_IN_TILES;
    game_map->_minimap->_player_x = MINIMAP_MIDDLE_X;
    game_map->_minimap->_player_y = MINIMAP_MIDDLE_Y;

    /* Generiere eine Zufallszahl zwischen [MIN_ROOMS, MAX_ROOMS]. */
    const UINT8 room_count = (UINT8) (inclusive_random(MIN_ROOMS, MAX_ROOMS));
    game_map->_minimap->_room_count = room_count;

    /* Gib die Anzahl der Räume in der Konsole aus. */
    fprintf(stdout, "[INFO]: Anzahl der Raeume: %i\n", room_count);

    if (FAILED(create_sprite(WALL_SPRITE_PATH, &game_map->_wall_sprite))) {
        /* Schlägt das reservieren des Speichers fehl, wird der bereits reservierte Speicher für die MAP Struktur wieder freigegeben. */
        FREE_MEMORY(game_map->_minimap);
        FREE_MEMORY(game_map);
        return LR_FAILED;
    }

    if (FAILED(create_sprite(DOOR_SPRITE_PATH, &game_map->_door_sprite))) {
        FREE_MEMORY(game_map->_wall_sprite);
        FREE_MEMORY(game_map->_minimap);
        FREE_MEMORY(game_map);
        return LR_FAILED;
    }

    if (FAILED(create_sprite(DOOR_OPEN_SPRITE_PATH, &game_map->_door_open_sprite))) {
        FREE_MEMORY(game_map->_door_sprite);
        FREE_MEMORY(game_map->_wall_sprite);
        FREE_MEMORY(game_map->_minimap);
        FREE_MEMORY(game_map);
        return LR_FAILED;
    }

    /*
     * Initialisiere alle Räume mit einen NULL Pointer.
     * Wird durch memset() eigentlich nicht mehr benötigt.
     */
    UINT8 y, x;
    for (y = 0; y < MINIMAP_HEIGHT_IN_TILES; y++) {
        for (x = 0; x < MINIMAP_WIDTH_IN_TILES; x++) {
            game_map->_rooms[y][x] = NULL;
        }
    }

    /* Setzte den Anfangsraum in die Mitte der Karte. */
    LPROOM starting_room = (LPROOM) malloc(1 * sizeof(struct _ROOM));
    if (starting_room == NULL) {
        LOG_ERROR("Es konnte kein Speicher für eine _ROOM Struktur allokiert werden!");
        FREE_MEMORY(game_map->_door_open_sprite);
        FREE_MEMORY(game_map->_door_sprite);
        FREE_MEMORY(game_map->_wall_sprite);
        FREE_MEMORY(game_map->_minimap);
        FREE_MEMORY(game_map);
        return LR_POINTER_INIT;
    }

    /* Nach erfolgreicher Allokation wird der Speicher genullt. */
    memset(starting_room, 0, sizeof(struct _ROOM));

    starting_room->_type = ROOM_TYPE_START;
    starting_room->_x = MINIMAP_MIDDLE_X;
    starting_room->_y = MINIMAP_MIDDLE_Y;
    starting_room->_enemy_count = (UINT8) (inclusive_random(MIN_ENEMIES_PER_ROOM, MAX_ENEMIES_PER_ROOM));

    UINT8 i;
    for (i = 0; i < starting_room->_enemy_count; i++) {
        if (FAILED(create_enemy(&starting_room->_enemies[i]))) {
            return LR_FAILED;
        }
    }

    game_map->_rooms[MINIMAP_MIDDLE_Y][MINIMAP_MIDDLE_X] = starting_room;

    /* Starte das Erstellen von "room_count" Räumen. */
    for (i = 0; i < room_count; i++) {
        generate_minimap(game_map, MINIMAP_MIDDLE_X, MINIMAP_MIDDLE_Y);
    }

    /* Gebe den fertigen Karten Pointer an den Parameter Pointer über. */
    CHANGE_OWNER(pp_map, game_map);

    /* Gebe einen Success-Code zurück. */
    return LR_SUCCESS;
}

LRESULT draw_map(_In_ LPCMAP const p_map) {
    if (p_map != NULL) {
        /* Speichere die aktuelle Position des Spielers auf der Minimap ab. */
        const UINT8 player_x = p_map->_minimap->_player_x;
        const UINT8 player_y = p_map->_minimap->_player_y;

        /* Zeichne die Wände am oberen und unteren Rand. */
        /*
        UINT8 x;
        for (x = 0; x < GAME_RIGHT / GAME_TILE_SIZE; x++) {
            draw_sprite(p_map->_wall_sprite, x * GAME_TILE_SIZE, 0);
            draw_sprite(p_map->_wall_sprite, x * GAME_TILE_SIZE, GAME_BOTTOM);
        }
        */

        /* Zeichne die Wände am linken und rechtem Rand. */
        /*
        UINT8 y;
        for (y = 0; y < GAME_BOTTOM / GAME_TILE_SIZE; y++) {
            draw_sprite(p_map->_wall_sprite, 0, y * GAME_TILE_SIZE);
            draw_sprite(p_map->_wall_sprite, GAME_RIGHT - GAME_TILE_SIZE, y * GAME_TILE_SIZE);
        }
        */

        /* Zeichne die rechte Tür. */
        if (p_map->_rooms[player_y][player_x + 1] != NULL) {
            /* Sind noch Gegner im Raum zeichne die geschlossene Tür. */
            if (p_map->_rooms[player_y][player_x]->_enemy_count > 0) {
                draw_rotated_sprite(p_map->_door_sprite, ROOM_DOOR_RIGHT_X, ROOM_DOOR_RIGHT_Y, ROTATE_90);
            /* Sind keine Gegner mehr im Raum zeichne die offene Tür. */
            } else {
                draw_rotated_sprite(p_map->_door_open_sprite, ROOM_DOOR_RIGHT_X, ROOM_DOOR_RIGHT_Y, ROTATE_90);
            }
        }

        /* Zeichne die linke Tür. */
        if (p_map->_rooms[player_y][player_x - 1] != NULL) {
            if (p_map->_rooms[player_y][player_x]->_enemy_count > 0) {
                draw_rotated_sprite(p_map->_door_sprite, ROOM_DOOR_LEFT_X, ROOM_DOOR_LEFT_Y, ROTATE_270);
            } else {
                draw_rotated_sprite(p_map->_door_open_sprite, ROOM_DOOR_LEFT_X, ROOM_DOOR_LEFT_Y, ROTATE_270);
            }
        }

        /* Zeichne die untere Tür. */
        if (p_map->_rooms[player_y + 1][player_x] != NULL) {
            if (p_map->_rooms[player_y][player_x]->_enemy_count > 0) {
                draw_rotated_sprite(p_map->_door_sprite, ROOM_DOOR_BOTTOM_X, ROOM_DOOR_BOTTOM_Y, ROTATE_180);
            } else {
                draw_rotated_sprite(p_map->_door_open_sprite, ROOM_DOOR_BOTTOM_X, ROOM_DOOR_BOTTOM_Y, ROTATE_180);
            }
        }

        /* Zeichne die obere Tür. */
        if (p_map->_rooms[player_y - 1][player_x] != NULL) {
            if (p_map->_rooms[player_y][player_x]->_enemy_count > 0) {
                draw_sprite(p_map->_door_sprite, ROOM_DOOR_TOP_X, ROOM_DOOR_TOP_Y);
            } else {
                draw_sprite(p_map->_door_open_sprite, ROOM_DOOR_TOP_X, ROOM_DOOR_TOP_Y);
            }
        }

        /* Ist in "constants.h" DEBUG_MODE aktiviert, wird eine rote Umrandung um die Türen gezeichnet. */
        if (DEBUG_MODE == TRUE) {
            al_draw_rectangle(ROOM_DOOR_LEFT_X, ROOM_DOOR_LEFT_Y, ROOM_DOOR_LEFT_X + GAME_TILE_SIZE, ROOM_DOOR_LEFT_Y + GAME_TILE_SIZE, al_map_rgb(255, 0, 0), 2.0f);
            al_draw_rectangle(ROOM_DOOR_RIGHT_X, ROOM_DOOR_RIGHT_Y, ROOM_DOOR_RIGHT_X + GAME_TILE_SIZE, ROOM_DOOR_RIGHT_Y + GAME_TILE_SIZE, al_map_rgb(255, 0, 0), 2.0f);
            al_draw_rectangle(ROOM_DOOR_TOP_X, ROOM_DOOR_TOP_Y, ROOM_DOOR_TOP_X + GAME_TILE_SIZE, ROOM_DOOR_TOP_Y + GAME_TILE_SIZE, al_map_rgb(255, 0, 0), 2.0f);
            al_draw_rectangle(ROOM_DOOR_BOTTOM_X, ROOM_DOOR_BOTTOM_Y, ROOM_DOOR_BOTTOM_X + GAME_TILE_SIZE, ROOM_DOOR_BOTTOM_Y + GAME_TILE_SIZE, al_map_rgb(255, 0, 0), 2.0f);

            /* Rote Grenze oben */
            al_draw_rectangle(0, 0, ROOM_DOOR_TOP_X, ROOM_DOOR_TOP_Y + GAME_TILE_SIZE, al_map_rgb(255, 0, 0), 2.0f);
            al_draw_rectangle(ROOM_DOOR_TOP_X + GAME_TILE_SIZE, 0, GAME_RIGHT, ROOM_DOOR_TOP_Y + GAME_TILE_SIZE, al_map_rgb(255, 0, 0), 2.0f);

            /* Rote Grenze unten */
            al_draw_rectangle(0, ROOM_DOOR_BOTTOM_Y, ROOM_DOOR_BOTTOM_X, ROOM_DOOR_BOTTOM_Y + GAME_TILE_SIZE, al_map_rgb(255, 0, 0), 2.0f);
            al_draw_rectangle(ROOM_DOOR_BOTTOM_X + GAME_TILE_SIZE, ROOM_DOOR_BOTTOM_Y, GAME_RIGHT, ROOM_DOOR_BOTTOM_Y + GAME_TILE_SIZE, al_map_rgb(255, 0, 0), 2.0f);

            /* Rote Grenze links */
            al_draw_rectangle(0, 0, ROOM_DOOR_LEFT_X + GAME_TILE_SIZE, ROOM_DOOR_LEFT_Y, al_map_rgb(255, 0, 0), 2.0f);
            al_draw_rectangle(0, ROOM_DOOR_LEFT_Y + GAME_TILE_SIZE, ROOM_DOOR_LEFT_X + GAME_TILE_SIZE, GAME_BOTTOM + GAME_TILE_SIZE, al_map_rgb(255, 0, 0), 2.0f);

            /* Rote Grenze rechts */
			al_draw_rectangle(ROOM_DOOR_RIGHT_X, 0, ROOM_DOOR_RIGHT_X + GAME_TILE_SIZE, ROOM_DOOR_RIGHT_Y, al_map_rgb(255, 0, 0), 2.0f);
			al_draw_rectangle(ROOM_DOOR_RIGHT_X, ROOM_DOOR_RIGHT_Y + GAME_TILE_SIZE, ROOM_DOOR_RIGHT_X, GAME_BOTTOM + GAME_TILE_SIZE, al_map_rgb(255, 0, 0), 2.0f);
        }

        /* Ruft die Zeichenfunktionen für den aktuellen Raum auf. */
        if (FAILED(draw_room(p_map->_rooms[player_y][player_x]))) {
            return LR_FAILED;
        }

        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}

LRESULT log_map(_In_ LPCMAP const p_map) {
    /* Schleife über den 2D-Array */
    UINT8 y, x;
    for (y = 0; y < MINIMAP_HEIGHT_IN_TILES; y++) {
        for (x = 0; x < MINIMAP_WIDTH_IN_TILES; x++) {
            /* Wenn der Pointer NULL ist wird einfach 0 ausgegeben */
            if (p_map->_rooms[y][x] == NULL) {
                printf("0, ");
                /* Ansonsten wird der Wert des Typen als int ausgegeben */
            } else {
                printf("%i, ", p_map->_rooms[y][x]->_type);
            }
        }
        /* Nach jeder Reihe eine neue Zeile anfangen */
        printf("\n");
    }
    return LR_SUCCESS;
}

LRESULT destroy_map(_InOut_opt_ LPMAP p_map) {
    /* Schaue ob der übergebene Pointer einen Wert enthält */
    if (p_map != NULL) {
        /* Schleife über den 2D-Array */
        UINT8 y, x;
        for (y = 0; y < MINIMAP_HEIGHT_IN_TILES; y++) {
            for (x = 0; x < MINIMAP_WIDTH_IN_TILES; x++) {
                /* Gib den Speicher der Raum-Struktur frei */
                destroy_room(p_map->_rooms[y][x]);
            }
        }
        if (p_map->_wall_sprite != NULL) {
            destroy_sprite(p_map->_wall_sprite);
            p_map->_wall_sprite = NULL;
        }
        if (p_map->_minimap != NULL) {
            FREE_MEMORY(p_map->_minimap);
        }
        /* Sind alle Räume gelöscht gib die Karten-Struktur frei */
        FREE_MEMORY(p_map);
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}
