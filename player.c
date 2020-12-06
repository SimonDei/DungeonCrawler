/**
 * Created by Simon on 20.11.2020.
 */

#include "player.h"

static ALLEGRO_KEYBOARD_STATE player_keystate;

LRESULT CALLBACK create_player(_Out_ LPPLAYER* pp_player) {
    /* Allokiert Speicher für die Spielerstruktur. */
    LPPLAYER player = (LPPLAYER) malloc(1 * sizeof(struct _PLAYER));
    if (player == NULL) {
        /* Schlägt die Allokation fehl, wird ein Fehler ausgegeben un ein Fehlercode zurückgegeben. */
        LOG_ERROR("Es konnte kein Speicher für eine _PLAYER Struktur allokiert werden!");
        return LR_POINTER_INIT;
    }

    /* Nach erfolgreicher Allokation wird der Speicher genullt. */
    memset(player, 0, sizeof(struct _PLAYER));

    /* Lade das Sprite für den Spieler, das später gezeichnet werden soll. */
    if (FAILED(create_sprite(PLAYER_SPRITE_PATH, &player->_sprite))) {
        /* Schlägt das Laden fehl, wird der allokierte Speicher wieder freigegeben und ein Fehlercode zurückgegeben. */
        FREE_MEMORY(player);
        return LR_POINTER_INIT;
    }

    /* Lade das Sprite für die Explosion, die nach Kollision mit einem Gegner oder einer Wand angezeigt wird. */
    if (FAILED(create_sprite(EXPLOSION_SPRITE_PATH, &player->_explosion))) {
        FREE_MEMORY(player->_sprite);
        FREE_MEMORY(player);
        return LR_POINTER_INIT;
    }

    /* Setzte die Position des Spielers in die Mitte des Spielfelds. */
    player->_x = GAME_RIGHT / 2.0f - GAME_TILE_SIZE;
    player->_y = GAME_BOTTOM / 2.0f - GAME_TILE_SIZE;

    player->_hp = START_PLAYER_HP;

    /* Gebe den erstellen Pointer an den Doppelpointer-Parameter über. */
    CHANGE_OWNER(pp_player, player);
    return LR_SUCCESS;
}

LRESULT draw_player(_In_ LPCPLAYER const p_player) {
    /* Prüfe ob der übergebene Pointer auch einen Wert hat. */
    if (p_player != NULL) {
        /* Zeichnet das Sprite des Spielers an seiner aktuellen Position. */
        draw_sprite(p_player->_sprite, p_player->_x, p_player->_y);

        UINT8 i;
        /* Zeichnet alle aktiven Kugeln des Spielers. */
        for (i = 0; i < PLAYER_MAX_BULLETS; i++) {
            if (p_player->_bullets[i] != NULL) {
                draw_bullet(p_player->_bullets[i]);
            }
        }

        /* Ist in "constants.h" DEBUG_MODE aktiviert, wird eine rote Umrandung um den Spieler gezeichnet. */
        if (DEBUG_MODE == TRUE) {
            al_draw_rectangle(p_player->_x,
                              p_player->_y,
                              p_player->_x + p_player->_sprite->_width,
                              p_player->_y + p_player->_sprite->_height,
                              al_map_rgb(255, 0, 0),
                              2.0f);
        }

        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}

LRESULT move_player(_InOut_ LPPLAYER const p_player) {
    /* Speichere den aktuellen Stand der gedrückten Tasten ab. */
    al_get_keyboard_state(&player_keystate);

    /* Prüfe ob der übergebene Pointer auch einen Wert hat. */
    if (p_player != NULL) {
        /* Schaue ob die Taste "W" gedrückt ist. */
        if (al_key_down(&player_keystate, ALLEGRO_KEY_W)) {
            /* Wenn die Y Position des Spielers unter der oberen Wand ist, darf er sich nach oben bewegen. */
            if (p_player->_y > GAME_TILE_SIZE) {
                p_player->_y -= PLAYER_MOVEMENT_SPEED;
                /* Setze die aktive Guckrichtung nach oben. */
                p_player->_active_direction = DIRECTION_UP;
            }
        }
        
        /* Schaue ob die Taste "A" gedrückt ist. */
        if (al_key_down(&player_keystate, ALLEGRO_KEY_A)) {
            /* Wenn die X Position des Spielers rechts von der linken Wand ist, darf er sich nach links bewegen. */
            if (p_player->_x > GAME_TILE_SIZE) {
                p_player->_x -= PLAYER_MOVEMENT_SPEED;
                p_player->_active_direction = DIRECTION_LEFT;
            }
        }
        
        /* Schaue ob die Taste "S" gedrückt ist. */
        if (al_key_down(&player_keystate, ALLEGRO_KEY_S)) {
            /* Wenn die Y Position des Spielers oberhalb von der unteren Wand ist, darf er sich nach unten bewegen. */
            if (p_player->_y < GAME_BOTTOM - GAME_TILE_SIZE) {
                p_player->_y += PLAYER_MOVEMENT_SPEED;
                p_player->_active_direction = DIRECTION_DOWN;
            }
        }
        
        /* Schaue ob die Taste "D" gedrückt ist. */
        if (al_key_down(&player_keystate, ALLEGRO_KEY_D)) {
            /* Wenn die X Position des Spielers links von der rechten Wand ist, darf er sich nach rechts bewegen. */
            if (p_player->_x < GAME_RIGHT - 2.0f * GAME_TILE_SIZE) {
                p_player->_x += PLAYER_MOVEMENT_SPEED;
                p_player->_active_direction = DIRECTION_RIGHT;
            }
        }
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}

LRESULT reset_player_position(_In_ LPPLAYER const        p_player,
                              _In_ const enum _DIRECTION incoming_direction) {
    /* Schaue, welche Position die Tür hat, durch die der Spieler gekommen ist. */
    switch (incoming_direction) {
        case DIRECTION_LEFT:
            p_player->_x = GAME_RIGHT - GAME_TILE_SIZE * 2.0f;
            p_player->_y = GAME_BOTTOM / 2.0f - GAME_TILE_SIZE;
            break;
        case DIRECTION_RIGHT:
            p_player->_x = GAME_TILE_SIZE + GAME_TILE_SIZE / 2.0f;
            p_player->_y = GAME_BOTTOM / 2.0f - GAME_TILE_SIZE;
            break;
        case DIRECTION_UP:
            p_player->_x = GAME_RIGHT / 2.0f - GAME_TILE_SIZE;
            p_player->_y = GAME_BOTTOM - GAME_TILE_SIZE;
            break;
        case DIRECTION_DOWN:
            p_player->_x = GAME_RIGHT / 2.0f - GAME_TILE_SIZE;
            p_player->_y = GAME_TILE_SIZE;
            break;
    }
    return LR_SUCCESS;
}

BOOL check_player_reaches_door(_In_ LPCMAP const   p_map,
                               _In_ LPPLAYER const p_player) {
    /* Speichere die aktuelle Position des Spielers auf der Minimap ab. */
    const UINT8 player_x = p_map->_minimap->_player_x;
    const UINT8 player_y = p_map->_minimap->_player_y;

    /* fprintf(stdout, "X: %.2f, Y: %.2f\n", p_player->_x, p_player->_y); */

    /* Falls noch Gegner auf der Karte sind, kann der Spieler den Raum nicht verlassen. */
    if (p_map->_rooms[player_y][player_x]->_enemy_count > 0) {
        return FALSE;
    }

    /* Schaue ob der Spieler die Tür am oberen Rand berührt. */
    if (p_map->_rooms[player_y - 1][player_x] != NULL) {
        if (rect_rect_collision(p_player->_x, p_player->_y, p_player->_sprite->_width, p_player->_sprite->_height,
                           ROOM_DOOR_TOP_X, ROOM_DOOR_TOP_Y, GAME_TILE_SIZE, GAME_TILE_SIZE)) {
            /* Bewege den Spieler auf der Minimap um 1 nach oben. (Y - 1) */
            move_minimap_position(p_map, 0, -1);
            /* Setze die Spielerposition zurück und gebe als kommende Richtung oben mit. */
            reset_player_position(p_player, DIRECTION_UP);
            return TRUE;
        }
    }
    
    /* Schaue ob der Spieler die Tür am rechten Rand berührt. */
    if (p_map->_rooms[player_y][player_x + 1] != NULL) {
        if (rect_rect_collision(p_player->_x, p_player->_y, p_player->_sprite->_width, p_player->_sprite->_height,
                           ROOM_DOOR_RIGHT_X, ROOM_DOOR_RIGHT_Y, GAME_TILE_SIZE, GAME_TILE_SIZE)) {
            /* Bewege den Spieler auf der Minimap um 1 nach rechts. (X + 1) */
            move_minimap_position(p_map, 1, 0);
            reset_player_position(p_player, DIRECTION_RIGHT);
            return TRUE;
        }
    }
    
    /* Schaue ob der Spieler die Tür am unteren Rand berührt. */
    if (p_map->_rooms[player_y + 1][player_x] != NULL) {
        if (rect_rect_collision(p_player->_x, p_player->_y, p_player->_sprite->_width, p_player->_sprite->_height,
                           ROOM_DOOR_BOTTOM_X, ROOM_DOOR_BOTTOM_Y, GAME_TILE_SIZE, GAME_TILE_SIZE)) {
            /* Bewege den Spieler auf der Minimap um 1 nach unten. (Y + 1) */
            move_minimap_position(p_map, 0, 1);
            reset_player_position(p_player, DIRECTION_DOWN);
            return TRUE;
        }
    }
    
    /* Schaue ob der Spieler die Tür am linken Rand berührt. */
    if (p_map->_rooms[player_y][player_x - 1] != NULL) {
        if (rect_rect_collision(p_player->_x, p_player->_y, p_player->_sprite->_width, p_player->_sprite->_height,
                           ROOM_DOOR_LEFT_X, ROOM_DOOR_LEFT_Y, GAME_TILE_SIZE, GAME_TILE_SIZE)) {
            /* Bewege den Spieler auf der Minimap um 1 nach links. (X - 1) */
            move_minimap_position(p_map, -1, 0);
            reset_player_position(p_player, DIRECTION_LEFT);
            return TRUE;
        }
    }
    return FALSE;
}

LRESULT fire_bullet(_InOut_ LPPLAYER const p_player) {
    /* Prüfe ob der übergebene Pointer auch einen Wert hat. */
    if (p_player != NULL) {
        UINT8 i;
        /* Schaue alle möglichen Kugeln, die der Spieler abfeuern kann durch. */
        for (i = 0; i < PLAYER_MAX_BULLETS; i++) {
            /* Ist die Kugel an der aktuellen nicht in Benutzung erstelle sie. */
            if (p_player->_bullets[i] == NULL) {
                if (FAILED(create_bullet(&p_player->_bullets[i]))) {
                    return LR_FAILED;
                }
                /* Erstelle die Kugel an der Position des Spielers. */
                p_player->_bullets[i]->_x = p_player->_x + GAME_TILE_SIZE / 2.0f;
                p_player->_bullets[i]->_y = p_player->_y + GAME_TILE_SIZE / 2.0f;
                /* Setze die Flugrichtung der Kugel auf die Blickrichtung des Spielers. */
                p_player->_bullets[i]->_active_direction = p_player->_active_direction;
                break;
            }
        }
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}

LRESULT destroy_player(_InOut_opt_ LPPLAYER p_player) {
    if (p_player != NULL) {
        if (p_player->_sprite != NULL) {
            destroy_sprite(p_player->_sprite);
            p_player->_sprite = NULL;
        }
        if (p_player->_explosion != NULL) {
            destroy_sprite(p_player->_explosion);
            p_player->_explosion = NULL;
        }
        UINT8 i;
        for (i = 0; i < PLAYER_MAX_BULLETS; i++) {
            destroy_bullet(p_player->_bullets[i]);
            p_player->_bullets[i] = NULL;
        }
        FREE_MEMORY(p_player);
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}
