#include "splashkit.h"
#include "../../Source/Utilities/music_player.h"
#include "menu_drawing.h"
#include "menu_logic.h"
#include "menu_utilities.h"
#include "../../Source/Utilities/leaderboard.h"
#include "../../Source/GameData/lost_in_space.h"

// Find what OS the user is using to allow C++ to open the corresponding GitHub repo using the OS's default browser
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(__NT__) 
    void open_github_repoistory()
    {
        system("explorer \"https://github.com/PandaPlaysAll/Space-Game-ITP\"");
    }
#elif __APPLE__
    void open_github_repoistory()
    {
        system("open https://github.com/PandaPlaysAll/Space-Game-ITP");
    }
#elif __linux__
    void open_github_repoistory()
    {
       system("xdg-open https://github.com/PandaPlaysAll/Space-Game-ITP");
    }
#elif __unix__
    void open_github_repoistory()
    {
        system("firefox https://github.com/PandaPlaysAll/Space-Game-ITP");
    }
    
#else
    void open_github_repoistory()
    {
        write_line("[WARNING] OS could not be detected!. Please leave a issue in https://github.com/PandaPlaysAll/Space-Game-ITP");
    }
#endif

menu_handler_data create_menu_handler()
{
    menu_handler_data menu_handler;
    menu_handler.game_state = HOME_SCREEN;
    menu_handler.highlighted_button = NONE;
    menu_handler.music_player = create_music_handler();
    menu_handler.leaderboard_sorting_method = ALPHA_ASCENDING;
    return menu_handler;
}

void handle_all_screens_button_hover_over_highlighting(menu_handler_data &global_menu_handler) // rename functionn name
{
    game_state current_state = global_menu_handler.game_state;

    // Handling mouse over actions by highlighting the button the mouse is over
    if (is_mouse_in_first_button()) 
        global_menu_handler.highlighted_button = FIRST_BTN;

    else if (is_mouse_in_second_button()) 
        global_menu_handler.highlighted_button = SECOND_BTN;

    else if (is_mouse_in_third_button() && (current_state == HOME_SCREEN || current_state == SETTINGS_SCREEN )) 
        global_menu_handler.highlighted_button = THIRD_BTN;

    else if (is_mouse_in_fourth_button() && (current_state == HOME_SCREEN || current_state == SETTINGS_SCREEN ))
        global_menu_handler.highlighted_button = FOURTH_BTN;

    else
        global_menu_handler.highlighted_button = NONE;
}

void handle_settings_screen_actions(menu_handler_data &global_menu_handler) 
{
    // Double click issue is due to the double bufferring in Splash Kit. Do Not Remove delay_left_mouse code. ONGOING ISSUE
    static int delay_left_mouse = 0;
    static const int delay_click_limitter = 1;

    handle_all_screens_button_hover_over_highlighting(global_menu_handler);

    if (has_mouse_clicked_first_button()) 
    {
        delay_left_mouse = 0; 
        global_menu_handler.game_state = HOME_SCREEN;
    }

    if (has_mouse_clicked_second_button()) 
    {
        handle_music_pausing(global_menu_handler.music_player);
    }

    if (has_mouse_clicked_third_button()) 
    {   
        delay_left_mouse++;

        if (delay_left_mouse > delay_click_limitter) 
        {
            decrease_music_volume(global_menu_handler.music_player);
        }
    }

    if (is_mouse_in_fourth_button() && mouse_clicked(LEFT_BUTTON)) 
    {
        increase_music_volume(global_menu_handler.music_player);
    }
}

void handle_home_screen_actions(menu_handler_data &global_menu_handler) 
{
    handle_all_screens_button_hover_over_highlighting(global_menu_handler);

    if (has_mouse_held_first_button()) global_menu_handler.game_state = PLAY_GAME_SCREEN;

    if (has_mouse_held_second_button()) global_menu_handler.game_state = LEADERBOARD_SCREEN;
    
    if (has_mouse_held_third_button()) global_menu_handler.game_state = SETTINGS_SCREEN;

    if (has_mouse_held_fourth_button()) global_menu_handler.game_state = INFORMATION_SCREEN;
    
}

void handle_information_screen_actions(menu_handler_data &global_menu_handler)
{
    handle_all_screens_button_hover_over_highlighting(global_menu_handler);
     
    if (has_mouse_clicked_first_button()) global_menu_handler.game_state = HOME_SCREEN;

    if (has_mouse_clicked_second_button()) open_github_repoistory(); 
}

void handle_leaderboard_screen_actions(menu_handler_data &global_menu_handler)
{
    static int delay_left_click = 0; // Prevent the double bufferring issue of rendering a second click when accessed the button from the home menu
    static const int delay_click_limitter = 1;
    static const int LEADERBOARD_LOCATION_X = 560, LEADERBOARD_LOCATION_Y = 750, LEADERBOARD_SIZE_X = 790, LEADERBOARD_SIZE_Y = 800;

    handle_all_screens_button_hover_over_highlighting(global_menu_handler);
    
    if (has_mouse_clicked_first_button()) 
    {
        delay_left_click = 0;
        global_menu_handler.game_state = HOME_SCREEN;
    }

    if (has_mouse_clicked_second_button())
    {
        delay_left_click++;
        
        if (delay_left_click > delay_click_limitter) 
        {
            reset_leaderboard_file();
        }
    }

    if (is_mouse_between_two_points(LEADERBOARD_LOCATION_X, LEADERBOARD_LOCATION_Y, LEADERBOARD_SIZE_X, LEADERBOARD_SIZE_Y)  && mouse_clicked(LEFT_BUTTON)) 
    {
        global_menu_handler.leaderboard_sorting_method = change_sorting_type(global_menu_handler.leaderboard_sorting_method);
    }
}

// Handle all menu's
void handle_menu_state(menu_handler_data &global_menu_handler) 
{
    switch (global_menu_handler.game_state) 
    {
        case HOME_SCREEN:
            handle_home_screen_actions(global_menu_handler);
            draw_home_screen_background(global_menu_handler);
            break;
        case SETTINGS_SCREEN:
            handle_settings_screen_actions(global_menu_handler);
            draw_settings_screen_background(global_menu_handler);
            break;
        case INFORMATION_SCREEN:
            handle_information_screen_actions(global_menu_handler);
            draw_information_screen_background(global_menu_handler);
            break;
        case LEADERBOARD_SCREEN:
            handle_leaderboard_screen_actions(global_menu_handler);
            draw_leaderboard_screen_background(global_menu_handler);
            break;
        default:
            break;
    }
    refresh_screen(60);
}

bool handle_paused_screen_menu(menu_handler_data &global_menu_handler, game_data &game)
{
    bool resume_game = false;

    handle_all_screens_button_hover_over_highlighting(global_menu_handler);
    draw_settings_paused_screen_background(global_menu_handler);
    draw_text_after_two_buttons(form_paused_menu_information(game));
    refresh_screen();

    if (has_mouse_clicked_first_button()) resume_game = true;

    if (has_mouse_clicked_second_button()) 
    {
        global_menu_handler.game_state = HOME_SCREEN;
        resume_game = true;
    }

    return resume_game;
}

void check_end_game_add_leaderboard_entry(menu_handler_data &global_menu_handler, game_data &game, bool &has_entered_entry)
{
    static const font default_font = font_named("hud_font");
    static const int rectangle_x = 90, rectangle_y = 675, game_over_font_size = 25;

    if ( has_entered_entry )
        draw_text("You have submitted your entry!", COLOR_BROWN, default_font, game_over_font_size + 10, rectangle_x + 5, rectangle_y + 40, option_to_screen() );

    // When the user wants to add a leaderboard entry
    if (has_mouse_clicked_second_button())
    {
        rectangle rect = rectangle_from(rectangle_x, rectangle_y, 600.0, 80.0);
        start_reading_text(rect);
        static const int max_entry_name_length = 20;
        string name = "";

        if ( ! has_entered_entry)
        {
            // Handle reading text (based on https://www.splashkit.io/articles/guides/tags/starter/reading-text/)
            while ( ! quit_requested() )
            {
                process_events();
                clear_screen();
                
                draw_end_game_screen_background(global_menu_handler, game.player.score, game.game_level);
                draw_text("Enter Your Name & Hit Enter", COLOR_AQUAMARINE, default_font, game_over_font_size, 90, 640, option_to_screen() );
                fill_rectangle(COLOR_BLACK, rect, option_to_screen());
                
                draw_text(name, COLOR_WHITE, default_font, game_over_font_size + 10, (rectangle_x + 5), (rectangle_y + 5), option_to_screen());
            
                if (text_entry_cancelled() ) 
                {
                    break;
                } 
                else
                {
                    name = text_input();
                } 

                if (name.length() >= max_entry_name_length)
                {
                    name = name.substr(0, max_entry_name_length);
                    draw_text("Max name is 20 characters", COLOR_RED, default_font, game_over_font_size - 5, rectangle_x + 5, rectangle_y + 40, option_to_screen());
                }

                // Save the users progress to the leaderboard or exit the adding the entry!
                if (mouse_clicked(LEFT_BUTTON))
                {
                    // Exit the writing leaderboard text 
                    break;
                }
                else if ( key_typed(RETURN_KEY) ) 
                {
                    // Prevent the user from adding another entry in the same session
                    add_new_leaderboard_entry(name, game.player.score);
                    has_entered_entry = true;
                    end_reading_text();
                    break;
                }
                   
                refresh_screen();
            }
        }
    }
}

bool handle_end_game_menu(menu_handler_data &global_menu_handler, game_data &game)
{
    static bool has_entered_entry = false;
    bool end_ending_screen_loop = false;

    clear_screen();
    handle_all_screens_button_hover_over_highlighting(global_menu_handler);
    draw_end_game_screen_background(global_menu_handler, game.player.score, game.game_level);

    if (has_mouse_clicked_first_button()) 
    {
        global_menu_handler.game_state = HOME_SCREEN;
        has_entered_entry = false; // Reset the entry entered when the user returns to the home screen. Allows them to enter their leaderboard entry once per round
        end_ending_screen_loop = true;
    }

    check_end_game_add_leaderboard_entry(global_menu_handler, game, has_entered_entry);
    refresh_screen();
    
    return end_ending_screen_loop;
}

void handle_menu()
{
    menu_handler_data global_menu_handler = create_menu_handler();

    while ( ! quit_requested() )
    {
        if (global_menu_handler.game_state == PLAY_GAME_SCREEN) global_menu_handler.game_state = handle_game();

        if (global_menu_handler.game_state == END_GAME) break;

        clear_screen();
        handle_music(global_menu_handler.music_player);
        handle_menu_state(global_menu_handler);
        process_events();
        refresh_screen();

    }
}

