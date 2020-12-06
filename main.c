/**
 * Created by Simon on 16.11.2020.
 */

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <GL/glew.h>

#include "util.h"
#include "input.h"
#include "hud.h"

int main(int argc, char** argv) {
    /* Initialisiert die Allegro Bibliothek und benötigte Addons. */
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_init_primitives_addon();

    /* Lädt das Tastatur- und Mausmodul */
    al_install_keyboard();
    al_install_mouse();

    al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_WINDOWED);

    /* Erstellt ein Fenster mit der gegebenen Dimension. */
    ALLEGRO_DISPLAY* display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    if (display == NULL) {
        return EXIT_FAILURE;
    }
    LOG_INFO("Allegro Fenster erfolgreich erstellt!");

    glewExperimental = TRUE;
    if (glewInit() != GLEW_OK) {
        return EXIT_FAILURE;
    }

    /* Erstellt eine Event-Queue, die Events des Fensters abfängt, um diese später zu bearbeiten. */
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    if (queue == NULL) {
        return EXIT_FAILURE;
    }
    LOG_INFO("Allegro Event-Queue erfolgreich erstellt!");

    /* Erstellt einen Timer der das Spiel - bei 60FPS - alle 16.66ms neu zeichnet, also 60 mal pro Sekunde. */
    ALLEGRO_TIMER* fps_timer = al_create_timer(1.0 / FPS);
    LOG_INFO("Allegro Synchronisationstimer erfolgreich erstellt!");

    /* Registriere alle Eventausgänge, auf die gelauscht werden soll. */
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(fps_timer));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    ALLEGRO_EVENT event;

    BOOL running = TRUE;
    BOOL redraw = TRUE;

    /* Lade die Standardschriftart für das Spiel. */
    ALLEGRO_FONT* game_font = al_load_ttf_font(GAME_FONT_PATH, 46, 0);

    /* Lade das Hintergrundbild */
    ALLEGRO_BITMAP* background_image = al_load_bitmap("res/background.tga");

    /* Erstelle die MAP Struktur für das Spiel. */
    LPMAP map = NULL;
    if (FAILED(create_map(&map))) {
        return EXIT_FAILURE;
    }

    /* Erstelle eine PLAYER Struktur den Spieler Charakter. */
    LPPLAYER player = NULL;
    if (FAILED(create_player(&player))) {
        return EXIT_FAILURE;
    }

    /* Erstelle eine HUD Struktur die Spielinfos. */
    LPHUD hud = NULL;
    if (FAILED(create_hud(&hud))) {
        return EXIT_FAILURE;
    }

    LOG_INFO("Initialisierungen erfolgreich abgeschlossen!");
    LOG_INFO("Spiel wird gestartet!");

    /* Starte den Timer kurz vor der Spielschleife für maximale Präzision. */
    al_start_timer(fps_timer);
    while (running == TRUE) {
        /*
         * Blockiere die Schleife bis ein Event auftritt.
         * Es wird auf jeden Fall ein Timer Event alle 16.66ms auftreten.
         */
        al_wait_for_event(queue, &event);

        switch (event.type) {
            /* Bei einem Schließen-Event wird running auf FALSE gesetzt und dadurch endet die Spielschleife. */
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running = FALSE;
                break;
            /* Wenn der Timer tickt bewege den Spieler und setzte die Flag zum neuzeichnen des Spiels. */
            case ALLEGRO_EVENT_TIMER:
                redraw = TRUE;
                break;
            /* Liegt irgendein anderes Event for sende es an die Funktionen zum handeln von Tastatur und Maus. */
            default:
                handle_keyboard(&event, &running, player);
                handle_mouse(&event, &running, player);
                break;
        }

        /* Wenn keine Events vorliegen und der Timer 1 mal abgelaufen ist wird neu gezeichnet. */
        if (redraw == TRUE && al_is_event_queue_empty(queue)) {
            al_draw_bitmap(background_image, 0, 0, 0);

            /*
             * Zeichenreihenfolge:
             * HUD =>
             *      MINIMAP
             * MAP =>
             *      ROOM =>
             *           ENEMY
             *           ENEMY
             *           ENEMY
             * PLAYER
             */
            draw_hud(hud, player->_hp);
            draw_minimap(map);
            draw_map(map);
            draw_player(player);

			/* Nur wenn der Spieler noch HP übrig hat, läuft die Logik des Spiels weiter. */
            if (player->_hp > 0) {
                /* Durch das Bewegen wenn der Timer tickt wird eine gleichmäßige Bewegung ermöglicht. */
                move_player(player);
                move_enemies(map->_rooms[map->_minimap->_player_y][map->_minimap->_player_x], player->_x, player->_y);

                /* Prüfe alle Kollisionen, die für den Spielverlauf nötig sind. */
                check_player_reaches_door(map, player);
                check_bullet_hits_enemy(player, map->_rooms[map->_minimap->_player_y][map->_minimap->_player_x]);
                check_bullet_hits_wall(player);
                check_enemy_hits_player(map, player, map->_minimap->_player_x, map->_minimap->_player_y);
            /* Hat der Spieler keine HP mehr, wird das "Verloren" Bild angezeigt. */
            } else {
				al_draw_text(game_font, al_map_rgb(255, 0, 0), GAME_RIGHT / 2.0f - 150.0f, GAME_BOTTOM / 2.0f - 25.0f, 0, "VERLOREN!");
            }

            al_flip_display();
            redraw = FALSE;
        }
    }

    /* Gebe den Speicher der eigenen Strukturen wieder frei. */
    destroy_hud(hud);
    destroy_player(player);
    destroy_map(map);

    /* Gebe den Speicher der benutzten Allegro Strukturen wieder frei. */
    al_destroy_bitmap(background_image);
    al_destroy_font(game_font);
    al_destroy_timer(fps_timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);

    return EXIT_SUCCESS;
}
