/**
 * Created by Simon on 20.11.2020.
 */

#include "room.h"

LRESULT CALLBACK generate_room(_InOut_ LPMAP      p_map,
                               _In_    const INT8 x,
                               _In_    const INT8 y,
                               _In_    const INT8 depth) {
    /* Ist noch kein Raum vorhanden erstelle einen an der aktuellen Position */
    LPROOM new_room = (LPROOM) malloc(1 * sizeof(struct _ROOM));
    if (new_room == NULL) {
        LOG_ERROR("Es konnte kein Speicher für eine _ROOM Struktur allokiert werden!");
        return LR_POINTER_INIT;
    }

    memset(new_room, 0, sizeof(struct _ROOM));

    new_room->_x = x;
    new_room->_y = y;
    new_room->_enemy_count = (UINT8) (inclusive_random(MIN_ENEMIES_PER_ROOM, MAX_ENEMIES_PER_ROOM));

    /* Generiere eine Zufallszahl zwischen [1, 4| */
    const UINT8 roll = rand() % (4 - depth > 0 ? 4 - depth : 1);

    /* Ist die Zufallszahl 0 und es existiert kein Boss-Raum setzte den Typen des aktuellen Raums auf ROOM_TYPE_BOSS */
    if (!p_map->_minimap->_has_boss_room && roll == 0 && depth > 2) {
        new_room->_type = ROOM_TYPE_BOSS;
        p_map->_minimap->_has_boss_room = TRUE;
    /* Ist die Zufallszahl 1 und es existiert kein Gift-Raum setzte den Typen des aktuellen Raums auf ROOM_TYPE_GIFT */
    } else if (!p_map->_minimap->_has_gift_room && roll == 1 && depth > 2) {
        new_room->_type = ROOM_TYPE_GIFT;
        p_map->_minimap->_has_gift_room = TRUE;
    /* Alle sonstiges Ergebnisse erstellen einen normalen Raum */
    } else {
        new_room->_type = ROOM_TYPE_NORMAL;
    }

    UINT8 i;
    for (i = 0; i < new_room->_enemy_count; i++) {
        if (FAILED(create_enemy(&new_room->_enemies[i]))) {
            return LR_FAILED;
        }
    }

    /* Setze den aktuellen Raum in den Raumplan der Karte ein */
    p_map->_rooms[y][x] = new_room;

    return LR_SUCCESS;
}

LRESULT draw_room(_In_ LPCROOM const p_room) {
    if (p_room != NULL) {
        UINT8 i;
        for (i = 0; i < MAX_ENEMIES_PER_ROOM; i++) {
            draw_enemy(p_room->_enemies[i]);
        }
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}

LRESULT move_enemies(_In_ LPCROOM const p_room,
                     _In_ const FLOAT   player_x,
                     _In_ const FLOAT   player_y) {
    if (p_room != NULL) {
        UINT8 i;
        for (i = 0; i < MAX_ENEMIES_PER_ROOM; i++) {
            move_single_enemy(p_room->_enemies[i], player_x, player_y);
        }
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}

LRESULT destroy_room(_InOut_opt_ LPROOM p_room) {
    if (p_room != NULL) {
        UINT8 i;
        for (i = 0; i < p_room->_enemy_count; i++) {
            destroy_enemy(p_room->_enemies[i]);
            p_room->_enemies[i] = NULL;
        }
        FREE_MEMORY(p_room);
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}
