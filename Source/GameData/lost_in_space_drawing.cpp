#include "splashkit.h"
#include "heads_up_display.h"
#include "lost_in_space.h"
#include "power_up.h"
#include "enemies.h"
void draw_next_level_information(const game_data &game)
{
    double timer_in_second = (timer_ticks(game.level_up_timer_cooldown) / 1000.0); 
    static const color TEXT_COLOR = COLOR_BLACK;
    static const font FONT = font_named("hud_font");
    static const int TEXT_SIZE = 35, LEVEL_UP_BOX_X = 225, LEVEL_UP_BOX_Y = 700;

    if (timer_in_second > 0 && timer_in_second <= 3.0)
    {
        fill_rectangle(COLOR_DARK_GRAY, LEVEL_UP_BOX_X, LEVEL_UP_BOX_Y, 385, 50, option_to_screen());
        draw_text("Congratulations, you are on level " + to_string(game.game_level), TEXT_COLOR, FONT, TEXT_SIZE, LEVEL_UP_BOX_X + 5, LEVEL_UP_BOX_Y + 5, option_to_screen());
    }
}

void draw_power_ups(const vector<power_up_data> &powerups)
{
    for (int i = 0; i < powerups.size(); i++)
    {
        draw_power_up(powerups[i]);
    }
}

void draw_game(const game_data &game)
{
    draw_heads_up_display(game);

    draw_power_ups(game.power_ups);
    draw_player(game.player);

    draw_next_level_information(game);

    draw_all_enemies(game.enemies);

    refresh_screen(60);
}


