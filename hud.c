/**
 * Created by Simon on 20.11.2020.
 */

#include "hud.h"

LRESULT CALLBACK create_hud(_Out_ LPHUD* pp_hud) {
	LPHUD hud = (LPHUD) malloc(1 * sizeof(struct _HUD));
	if (hud == NULL) {
		LOG_ERROR("Es konnte kein Speicher für eine _HUD Struktur allokiert werden!");
	}

	memset(hud, 0, sizeof(struct _HUD));

	if (FAILED(create_sprite(HEART_SPRITE_PATH, &hud->_heart))) {
		FREE_MEMORY(hud);
		return LR_FAILED;
	}

	CHANGE_OWNER(pp_hud, hud);
	return LR_SUCCESS;
}

LRESULT draw_hud(_In_ LPCHUD const p_hud,
				 _In_ const UINT8  player_hp) {
    al_draw_filled_rectangle(HUD_LEFT,
                             HUD_TOP,
                             HUD_RIGHT,
                             HUD_BOOTOM,
                             al_map_rgb(0, 0, 0));

	UINT8 i;
	for (i = 0; i < player_hp; i++) {
		draw_sprite(p_hud->_heart, HUD_FIRST_HEART_X + i * HUD_TILE_SIZE, HUD_FIRST_HEART_Y + HUD_TILE_SIZE / 2.0f);
	}

    return LR_SUCCESS;
}

LRESULT destroy_hud(_InOut_opt_ LPHUD p_hud) {
	if (p_hud != NULL) {
		if (p_hud->_heart != NULL) {
			destroy_sprite(p_hud->_heart);
			p_hud->_heart = NULL;
		}
		FREE_MEMORY(p_hud);
		return LR_SUCCESS;
	}
	return LR_SUCCESS;
}
