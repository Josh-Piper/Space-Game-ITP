#include "splashkit.h"
#include "heads_up_display.h"
#include "lost_in_space.h"
#include "./Entities/power_up.h"
#include "./Entities/player.h"
#include "enemies.h"

void draw_next_level_information(const game_data &game)
{
    double timer_in_second = (timer_ticks(game.level_up_timer_cooldown) / 1000.0); 
    static const string LEVEL_UP_TEXT = "Congratulations, you are on level ";
    static const color TEXT_COLOR = COLOR_BLACK;
    static const font FONT = font_named("hud_font");
    static const int TEXT_SIZE = 35, LEVEL_UP_BOX_X = 225, LEVEL_UP_BOX_Y = 700;

    if (timer_in_second > 0 && timer_in_second <= 3.0)
    {
        fill_rectangle(COLOR_DARK_GRAY, LEVEL_UP_BOX_X, LEVEL_UP_BOX_Y, 385, 50, option_to_screen());
        draw_text(LEVEL_UP_TEXT + to_string(game.game_level), TEXT_COLOR, FONT, TEXT_SIZE, LEVEL_UP_BOX_X + 5, LEVEL_UP_BOX_Y + 5, option_to_screen());

        // Display the different level messages 
        if (game.game_level == 2)
        {
            fill_rectangle(COLOR_DARK_GRAY, LEVEL_UP_BOX_X, LEVEL_UP_BOX_Y + 55, 385, 30, option_to_screen());
            draw_text(" Space Fighters will not Spawn! Be Careful...", TEXT_COLOR, FONT, TEXT_SIZE - 10, LEVEL_UP_BOX_X + 5, LEVEL_UP_BOX_Y + 56, option_to_screen());
        }

        if (game.game_level == 3)
        {
            fill_rectangle(COLOR_DARK_GRAY, LEVEL_UP_BOX_X, LEVEL_UP_BOX_Y + 55, 385, 30, option_to_screen());
            draw_text(" Level is Unsupported. Alpha Testing Mode ", TEXT_COLOR, FONT, TEXT_SIZE - 10, LEVEL_UP_BOX_X + 5, LEVEL_UP_BOX_Y + 56, option_to_screen());
        }
    }
}

void draw_power_ups(const vector<power_up_data> &powerups)
{
    for (int power_up_index = 0; power_up_index < powerups.size(); power_up_index++)
        draw_power_up(powerups[power_up_index]);
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