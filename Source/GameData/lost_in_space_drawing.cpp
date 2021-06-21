#include "splashkit.h"
#include "heads_up_display.h"
#include "lost_in_space.h"
#include "./Entities/power_up.h"
#include "./Entities/player.h"
#include "enemies.h"

void draw_next_level_information(const game_data &game) {
    static const string LEVEL_UP_TEXT = "Congratulations, you are on level ";
    static const color TEXT_COLOR = COLOR_BLACK;
    static const font FONT = font_named("hud_font");
    static const int SIZE = 35, BOX_X = 225, BOX_Y = 700;
    drawing_options opts = option_to_screen();

    unsigned int ticks = timer_ticks(game.level_up_timer_cooldown);
    double timer_in_second =  get_ticks_as_seconds(ticks);

    if (timer_in_second > 0 && timer_in_second <= 3.0) 
    {
        fill_rectangle(COLOR_DARK_GRAY, BOX_X, BOX_Y, 385, 50, opts);
        draw_text(LEVEL_UP_TEXT + to_string(game.game_level), TEXT_COLOR, FONT, 
            SIZE, BOX_X + 5, BOX_Y + 5, opts);

        // Display the different level messages 
        if (game.game_level == 2) {
            fill_rectangle(COLOR_DARK_GRAY, BOX_X, BOX_Y + 55, 385, 30, opts);
            draw_text(" Space Fighters will not Spawn! Be Careful...", 
                TEXT_COLOR, FONT, SIZE - 10, BOX_X + 5, BOX_Y + 56, opts);
        }

        if (game.game_level == 3) {
            fill_rectangle(COLOR_DARK_GRAY, BOX_X, BOX_Y + 55, 385, 30, opts);
            draw_text(" Level is Unsupported. Alpha Testing Mode ", TEXT_COLOR, 
                FONT, SIZE - 10, BOX_X + 5, BOX_Y + 56, opts);
        }
    }
}

void draw_power_ups(const vector <power_up_data> &powerups) {
    for (int index = 0; index < powerups.size(); index++)
        draw_power_up(powerups[index]);
}

void draw_game(const game_data &game) {
    draw_heads_up_display(game);
    draw_power_ups(game.power_ups);
    draw_player(game.player);
    draw_next_level_information(game);
    draw_all_enemies(game.enemies);

    refresh_screen(60);
}