/**
 * Created by Simon on 20.11.2020.
 */

#include "minimap.h"

LRESULT CALLBACK generate_minimap(_InOut_ LPMAP p_map,
                                  _In_    INT8  x,
                                  _In_    INT8  y) {
    BOOL tried_directions[4] = {FALSE, FALSE, FALSE, FALSE};
    UINT8 direction;
    UINT8 depth = 0;

/* Sprungadresse, zu der gesprungen wird, wenn in der gewählten Richtung schon ein besetztes Feld ist. */
lbl_NewDirection:

    /* Erhöhe mit jedem Durlauf in der aktuellen Iteration die Tiefe um 1 */
    depth++;

    /* Sind alle Richtungen besetzt, wird in eine zufällige gegangen und die Funktion mit dieser Position rekursiv aufgerufen */
    if (tried_directions[0] == TRUE &&
        tried_directions[1] == TRUE &&
        tried_directions[2] == TRUE &&
        tried_directions[3] == TRUE) {
        switch (rand() % 4) {
            case 0:
                x++;
                break;
            case 1:
                x--;
                break;
            case 2:
                y++;
                break;
            case 3:
                y--;
                break;
            default:
                break;
        }
        generate_minimap(p_map, x, y);
    }

    /* Wähle eine Richtung aus in die geschaut werden soll */
    direction = rand() % 4;
    tried_directions[direction] = TRUE;

    /* Gehe 1 Schritt in die ausgewählte Richtung */
    switch (direction) {
        case 0:
            x++;
            break;
        case 1:
            x--;
            break;
        case 2:
            y++;
            break;
        case 3:
            y--;
            break;
        default:
            break;
    }

    /* Ist das Ende der Karte oben, unten, links oder rechts erricht beende den Durchlauf */
    if (x >= MINIMAP_WIDTH_IN_TILES || x < 0 || y >= MINIMAP_HEIGHT_IN_TILES || y < 0) {
        return LR_OUT_OF_BOUNDS;
    }

    /* Ist das Feld besetzt gehe zurück zum Anfang und wähle dort eine neue Richtung */
    if (p_map->_rooms[y][x] != NULL) {
        tried_directions[0] = FALSE;
        tried_directions[1] = FALSE;
        tried_directions[2] = FALSE;
        tried_directions[3] = FALSE;
        goto lbl_NewDirection;
    }

    generate_room(p_map, x, y, depth);    

    return LR_SUCCESS;
}

LRESULT draw_minimap(_In_ LPCMAP const p_map) {
    UINT8 y, x;
    for (y = 0; y < MINIMAP_HEIGHT_IN_TILES; y++) {
        for (x = 0; x < MINIMAP_WIDTH_IN_TILES; x++) {
            if (p_map->_rooms[y][x] == NULL) {
                al_draw_filled_rectangle(x * MINIMAP_TILE_SIZE,
                                         HUD_TOP + y * MINIMAP_TILE_SIZE,
                                         x * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE,
                                         HUD_TOP + y * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE,
                                         al_map_rgb(0, 0, 0));
            } else {
                switch (p_map->_rooms[y][x]->_type) {
                    case ROOM_TYPE_START:
                        al_draw_filled_rectangle(x * MINIMAP_TILE_SIZE,
                                                 HUD_TOP + y * MINIMAP_TILE_SIZE,
                                                 x * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE,
                                                 HUD_TOP + y * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE,
                                                 al_map_rgb(48, 48, 162));
                        break;
                    case ROOM_TYPE_NORMAL:
                        al_draw_filled_rectangle(x * MINIMAP_TILE_SIZE,
                                                 HUD_TOP + y * MINIMAP_TILE_SIZE,
                                                 x * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE,
                                                 HUD_TOP + y * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE,
                                                 al_map_rgb(164, 164, 164));
                        break;
                    case ROOM_TYPE_BOSS:
                        al_draw_filled_rectangle(x * MINIMAP_TILE_SIZE,
                                                 HUD_TOP + y * MINIMAP_TILE_SIZE,
                                                 x * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE,
                                                 HUD_TOP + y * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE,
                                                 al_map_rgb(200, 40, 40));
                        break;
                    case ROOM_TYPE_GIFT:
                        al_draw_filled_rectangle(x * MINIMAP_TILE_SIZE,
                                                 HUD_TOP + y * MINIMAP_TILE_SIZE,
                                                 x * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE,
                                                 HUD_TOP + y * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE,
                                                 al_map_rgb(192, 192, 0));
                        break;
                    case ROOM_TYPE_NONE:
                        break;
                }
            }
            al_draw_line(MINIMAP_LEFT + x * MINIMAP_TILE_SIZE,
                         MINIMAP_TOP,
                         MINIMAP_LEFT + x * MINIMAP_TILE_SIZE,
                         MINIMAP_BOTTOM,
                         al_map_rgb(180, 180, 180), 1);
        }
        al_draw_line(MINIMAP_LEFT,
                     MINIMAP_TOP + y * MINIMAP_TILE_SIZE,
                     MINIMAP_RIGHT,
                     MINIMAP_TOP + y * MINIMAP_TILE_SIZE,
                     al_map_rgb(180, 180, 180), 1);
    }

    /* Minimap Spielerposition */
    al_draw_filled_circle(MINIMAP_LEFT + p_map->_minimap->_player_x * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE / 2.0f,
                          MINIMAP_TOP + p_map->_minimap->_player_y * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE / 2.0f,
                          MINIMAP_TILE_SIZE / 2.0f - MINIMAP_TILE_SIZE / 6.66f,
                          al_map_rgb(0, 255, 0));

    /* Minimap Rahmen */
    al_draw_rectangle(MINIMAP_LEFT,
                      MINIMAP_TOP,
                      MINIMAP_RIGHT,
                      MINIMAP_BOTTOM,
                      al_map_rgb(180, 180, 180), 1);

    return LR_SUCCESS;
}

LRESULT move_minimap_position(_In_ LPCMAP const p_map,
                              _In_ const INT8   offset_x,
                              _In_ const INT8   offset_y) {
    /* Schaue ob der Spieler auf der X Ache bewegt werden soll und das nächste Feld kein NULL Pointer ist */
    if (offset_x != 0 && p_map->_rooms[p_map->_minimap->_player_y][p_map->_minimap->_player_x + offset_x] != NULL) {
        /* Bewege den Spieler auf der X Achse */
        p_map->_minimap->_player_x += offset_x;
    }
    /* Schaue ob der Spieler auf der Y Ache bewegt werden soll und das nächste Feld kein NULL Pointer ist */
    if (offset_y != 0 && p_map->_rooms[p_map->_minimap->_player_y + offset_y][p_map->_minimap->_player_x] != NULL) {
        /* Bewege den Spieler auf der Y Achse */
        p_map->_minimap->_player_y += offset_y;
    }

    return LR_SUCCESS;
}
