/**
 * Created by Simon on 20.11.2020.
 */

#include "input.h"

static ALLEGRO_KEYBOARD_STATE input_keystate;
static ALLEGRO_MOUSE_STATE input_mousestate;

LRESULT handle_keyboard(_In_    ALLEGRO_EVENT* p_event,
                        _InOut_ LPBOOL         p_running,
                        _In_    LPPLAYER const p_player) {
    al_get_keyboard_state(&input_keystate);

    switch (p_event->type) {
        case ALLEGRO_EVENT_KEY_DOWN:
            switch (p_event->keyboard.keycode) {
                case ALLEGRO_KEY_SPACE:
                    fire_bullet(p_player);
                    break;
                default:
                    break;
            }
            break;
        default: 
            break;
    }
    return LR_SUCCESS;
}

LRESULT handle_mouse(_In_    ALLEGRO_EVENT* p_event,
                     _InOut_ LPBOOL         p_running,
                     _In_    LPPLAYER const p_player) {
    al_get_mouse_state(&input_mousestate);

    switch (p_event->type) {
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:            
            break;
        default: 
            break;
    }
    return LR_SUCCESS;
}
