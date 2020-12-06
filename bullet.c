/**
 * Created by Simon on 26.11.2020.
 */

#include "bullet.h"

LRESULT CALLBACK create_bullet(_Out_ LPBULLET* pp_bullet) {
    LPBULLET bullet = (LPBULLET) malloc(1 * sizeof(struct _BULLET));
    if (bullet == NULL) {
        LOG_ERROR("Es konnte kein Speicher für eine _SPRITE Struktur allokiert werden!");
        return LR_POINTER_INIT;
    }

    memset(bullet, 0, sizeof(struct _BULLET));

    if(FAILED(create_sprite(BULLET_SPRITE_PATH, &bullet->_sprite))) {
        FREE_MEMORY(bullet);
        return LR_FAILED;
    }

    CHANGE_OWNER(pp_bullet, bullet);
    return LR_SUCCESS;
}

LRESULT draw_bullet(_In_ LPBULLET const p_bullet) {
    if (p_bullet != NULL) {
        if (FAILED(draw_sprite(p_bullet->_sprite, p_bullet->_x, p_bullet->_y))) {
            return LR_FAILED;
        }
        switch (p_bullet->_active_direction) {
            case DIRECTION_UP:
                p_bullet->_y -= BULLET_MOVEMENT_SPEED;
                break;
            case DIRECTION_LEFT:
                p_bullet->_x -= BULLET_MOVEMENT_SPEED;
                break;
            case DIRECTION_DOWN:
                p_bullet->_y += BULLET_MOVEMENT_SPEED;
                break;
            case DIRECTION_RIGHT:
                p_bullet->_x += BULLET_MOVEMENT_SPEED;
                break;
        }
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}

LRESULT check_bullet_hits_enemy(_In_ LPPLAYER const p_player,
                                _In_ LPROOM const   p_room) {
    /* Prüfe ob der übergebene Pointer auch einen Wert hat. */
    if (p_player != NULL) {
        UINT8 i, j;
        /* Schaue alle möglichen Kugeln, die der Spieler abfeuern kann durch. */
        for (i = 0; i < PLAYER_MAX_BULLETS; i++) {
            /* Schaue alle möglichen Gegner im Raum durch. */
            for (j = 0; j < MAX_ENEMIES_PER_ROOM; j++) {
                /* Ist die Kugel aktiv und der Gegner noch am leben, schaue ob eine Kollision vorliegt. */
                if (p_player->_bullets[i] != NULL && p_room->_enemies[j] != NULL) {
                    if (point_rect_collision(p_player->_bullets[i]->_x, p_player->_bullets[i]->_y,
                                             p_room->_enemies[j]->_x, p_room->_enemies[j]->_y, GAME_TILE_SIZE, GAME_TILE_SIZE)) {
                        /* Liegt eine Kollision vor, wird an der akutellen Position der Kugel eine Explosion gezeichnet. */
                        draw_sprite(p_player->_explosion, p_player->_bullets[i]->_x, p_player->_bullets[i]->_y);

                        /* Nach der Kollision wird die Kugel zerstört und auf NULL gesetzt. */
                        destroy_bullet(p_player->_bullets[i]);
                        p_player->_bullets[i] = NULL;

                        /*
                         * Auch der Gegner wird nach einem Treffer mit einer Kugel zerstört, auf NULL gesetzt und
                         * die Anzahl der noch lebenden Gegner wird um 1 reduziert.
                         */
                        destroy_enemy(p_room->_enemies[j]);
                        p_room->_enemies[j] = NULL;
                        p_room->_enemy_count--;

                        return LR_SUCCESS;
                    }
                }
            }
        }
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}

LRESULT check_bullet_hits_wall(_In_ LPPLAYER const p_player) {
    /* Prüfe ob der übergebene Pointer auch einen Wert hat. */
    if (p_player != NULL) {
        UINT8 i;
        /* Schaue alle möglichen Kugeln, die der Spieler abfeuern kann durch. */
        for (i = 0; i < PLAYER_MAX_BULLETS; i++) {
            /* Ist die Kugel aktiv und liegt eine Kollision mit einer Wand vor. */
            if (p_player->_bullets[i] != NULL) {
                if (p_player->_bullets[i]->_x >= GAME_RIGHT - 2.0f * GAME_TILE_SIZE ||
                    p_player->_bullets[i]->_x <= GAME_LEFT + GAME_TILE_SIZE ||
                    p_player->_bullets[i]->_y >= GAME_BOTTOM - GAME_TILE_SIZE ||
                    p_player->_bullets[i]->_y <= GAME_TOP + GAME_TILE_SIZE) {
                    /* Liegt eine Kollision vor, wird an der akutellen Position der Kugel eine Explosion gezeichnet. */
                    draw_sprite(p_player->_explosion, p_player->_bullets[i]->_x, p_player->_bullets[i]->_y);

                    /* Nach der Kollision wird die Kugel zerstört und auf NULL gesetzt. */
                    destroy_bullet(p_player->_bullets[i]);
                    p_player->_bullets[i] = NULL;
                }
            }
        }
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}

LRESULT destroy_bullet(_InOut_opt_ LPBULLET p_bullet) {
    if (p_bullet != NULL) {
        if (p_bullet->_sprite != NULL) {
            destroy_sprite(p_bullet->_sprite);
            p_bullet->_sprite = NULL;
        }
        FREE_MEMORY(p_bullet);
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}
