/**
 * Created by Simon on 23.11.2020.
 */

#include "enemy.h"

LRESULT CALLBACK create_enemy(_Out_ LPENEMY* pp_enemy) {
    LPENEMY enemy = (LPENEMY) malloc(1 * sizeof(struct _ENEMY));
    if (enemy == NULL) {
        LOG_ERROR("Es konnte kein Speicher für eine _PLAYER Struktur allokiert werden!");
        return LR_POINTER_INIT;
    }

    memset(enemy, 0, sizeof(struct _ENEMY));

    if (FAILED(create_sprite(ENEMY_SPRITE_PATH, &enemy->_sprite))) {
        FREE_MEMORY(enemy);
        return LR_FAILED;
    }

    enemy->_x = inclusive_random(GAME_RIGHT - GAME_LEFT - GAME_TILE_SIZE, GAME_LEFT + GAME_TILE_SIZE);
    enemy->_y = inclusive_random(GAME_BOTTOM - GAME_TOP - GAME_TILE_SIZE, GAME_TOP + GAME_TILE_SIZE);

    CHANGE_OWNER(pp_enemy, enemy);
    return LR_SUCCESS;
}

LRESULT draw_enemy(_In_ LPCENEMY const p_enemy) {
    if (p_enemy != NULL) {
        if (FAILED(draw_sprite(p_enemy->_sprite, p_enemy->_x, p_enemy->_y))) {
            return LR_FAILED;
        }

        if (DEBUG_MODE == TRUE) {
            al_draw_rectangle(p_enemy->_x, p_enemy->_y, p_enemy->_x + p_enemy->_sprite->_width, p_enemy->_y + p_enemy->_sprite->_height, al_map_rgb(255, 0, 0), 2.0f);
        }

        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}

LRESULT move_single_enemy(_InOut_ LPENEMY const p_enemy,
                          _In_    const FLOAT   player_x,
                          _In_    const FLOAT   player_y) {
    if (p_enemy != NULL) {
        if (player_x < p_enemy->_x) {
            p_enemy->_x -= inclusive_random(ENEMY_MIN_MOVE_SPEED, ENEMY_MAX_MOVE_SPEED);
        } else {
            p_enemy->_x += inclusive_random(ENEMY_MIN_MOVE_SPEED, ENEMY_MAX_MOVE_SPEED);
        }

        if (player_y < p_enemy->_y) {
            p_enemy->_y -= inclusive_random(ENEMY_MIN_MOVE_SPEED, ENEMY_MAX_MOVE_SPEED);
        } else {
            p_enemy->_y += inclusive_random(ENEMY_MIN_MOVE_SPEED, ENEMY_MAX_MOVE_SPEED);
        }

        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}

LRESULT check_enemy_hits_player(_In_ LPCMAP const   p_map,
                                _In_ LPPLAYER const p_player,
                                _In_ const UINT8    player_x,
                                _In_ const UINT8    player_y) {
    if (p_map != NULL) {
        UINT8 i;
        for (i = 0; i < MAX_ENEMIES_PER_ROOM; i++) {
            if (p_map->_rooms[player_y][player_x]->_enemies[i] != NULL) {
                if (rect_rect_collision(p_player->_x,
                                        p_player->_y,
                                        p_player->_sprite->_width,
                                        p_player->_sprite->_height,
                                        p_map->_rooms[player_y][player_x]->_enemies[i]->_x,
                                        p_map->_rooms[player_y][player_x]->_enemies[i]->_y,
                                        p_map->_rooms[player_y][player_x]->_enemies[i]->_sprite->_width,
                                        p_map->_rooms[player_y][player_x]->_enemies[i]->_sprite->_height)) {

                    /* Nur wenn die HP größer 0 sind können sie verringert werden, da diese sonst nagativ werden. */
                    if (p_player->_hp > 0) {
                        p_player->_hp--;
                        fprintf(stdout, "Spieler HP: %i\n", p_player->_hp);
                    }
                    
                    destroy_enemy(p_map->_rooms[player_y][player_x]->_enemies[i]);
                    p_map->_rooms[player_y][player_x]->_enemies[i] = NULL;
                    p_map->_rooms[player_y][player_x]->_enemy_count--;

                    return LR_SUCCESS;
                }
            }
        }
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;    
}

LRESULT destroy_enemy(_InOut_opt_ LPENEMY p_enemy) {
    if (p_enemy != NULL) {
        if (p_enemy->_sprite != NULL) {
            destroy_sprite(p_enemy->_sprite);
            p_enemy->_sprite = NULL;
        }
        FREE_MEMORY(p_enemy);
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}
