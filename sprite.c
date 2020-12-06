/**
 * Created by Simon on 23.11.2020.
 */

#include "sprite.h"

LRESULT CALLBACK create_sprite(_In_  LPCSTR const p_file_path,
                               _Out_ LPSPRITE*    pp_sprite) {
    LPSPRITE sprite = (LPSPRITE) malloc(1 * sizeof(struct _SPRITE));
    if (sprite == NULL) {
        LOG_ERROR("Es konnte kein Speicher für eine _SPRITE Struktur allokiert werden!");
        return LR_POINTER_INIT;
    }

    memset(sprite, 0, sizeof(struct _SPRITE));

    sprite->_texture = al_load_bitmap(p_file_path);
    if (sprite->_texture == NULL) {
        fprintf(stderr, "[ERROR]: Textur: %s konnte nicht geladen werden!\n", p_file_path);
        FREE_MEMORY(sprite);
        return LR_POINTER_INIT;
    }

    sprite->_width = (FLOAT) (al_get_bitmap_width(sprite->_texture));
    sprite->_height = (FLOAT) (al_get_bitmap_height(sprite->_texture));

    fprintf(stdout, "[INFO]: Sprite mit Textur: %s erfolgreich erstellt!\n", p_file_path);

    CHANGE_OWNER(pp_sprite, sprite);
    return LR_SUCCESS;
}

LRESULT draw_sprite(_In_ LPCSPRITE const p_sprite,
                    _In_ const FLOAT     x,
                    _In_ const FLOAT     y) {
    if (p_sprite->_texture != NULL) {
        al_draw_bitmap(p_sprite->_texture, x, y, 0);
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}

LRESULT draw_rotated_sprite(_In_ LPCSPRITE const      p_sprite,
                            _In_ const FLOAT          x,
                            _In_ const FLOAT          y,
                            _In_ const enum _ROTATION rotation) {
    if (p_sprite->_texture != NULL) {
        al_draw_rotated_bitmap(p_sprite->_texture,
                               p_sprite->_width / 2.0f,
                               p_sprite->_height / 2.0f,
                               x + p_sprite->_width / 2.0f,
                               y + p_sprite->_height / 2.0f,
                               DEG_TO_RAD((double) rotation * 90.0),
                               0);
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}

LRESULT destroy_sprite(_InOut_opt_ LPSPRITE p_sprite) {
    if (p_sprite != NULL) {
        if (p_sprite->_texture != NULL) {
            al_destroy_bitmap(p_sprite->_texture);
            p_sprite->_texture = NULL;
        }
        FREE_MEMORY(p_sprite);
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}
