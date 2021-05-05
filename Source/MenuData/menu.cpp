#include "splashkit.h"
#include "../../Source/Utilities/music_player.h"
#include "menu_drawing.h"
#include "menu.h"
#include "../../Source/Utilities/leaderboard.h"
#include "../../Source/GameData/lost_in_space.h"

// Find what OS the user is using to allow C++ to open the corresponding GitHub repo using the OS's default browser
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(__NT__) 
    #include <windows.h>
    #include <shellapi.h>
    const operating_system OPERATING_SYSTEM = WINDOWS;
#elif __APPLE__
    #include <CoreFoundation/CFBundle.h>
    #include <ApplicationServices/ApplicationServices.h>
    const operating_system OPERATING_SYSTEM = APPLE;
#elif __linux__
    const operating_system OPERATING_SYSTEM = LINUX;
#elif __unix__
    const operating_system OPERATING_SYSTEM = UNIX;
#else
    const operating_system OPERATING_SYSTEM = UNIDENTIFIED;
#endif

menu_handler_data create_menu_handler()
{
    menu_handler_data result;
    result.game_state = HOME_SCREEN;
    result.highlighted_button = NONE;
    result.music_player = create_music_handler();
    result.sorting_method = ALPHA_ASCENDING;
    return result;
}

// Check if the mouse position is between two specific points
bool is_mouse_between_two_points(int first_x, int first_y, int second_x, int second_y) { return ((mouse_x() >= first_x && mouse_x() <= second_x) && (mouse_y() >= first_y && mouse_y() <= second_y)); }

bool is_mouse_in_first_button() { return (is_mouse_between_two_points(100, 165, 350, 415)); }

bool is_mouse_in_second_button() { return (is_mouse_between_two_points(445, 165, 695, 415)); }

bool is_mouse_in_third_button() { return (is_mouse_between_two_points(100, 480, 350, 730)); }

bool is_mouse_in_fourth_button() { return (is_mouse_between_two_points(445, 480, 695, 730 )); }

void handle_all_screnes_button_highlighting(menu_handler_data &global_menu_handler) 
{
    game_state current_state = global_menu_handler.game_state;

    // If the mouse position is in the first button, then signify that it should be highlighted
    if (is_mouse_in_first_button()) 
        global_menu_handler.highlighted_button = FIRST;

    // Check condition for the second button
    else if (is_mouse_in_second_button()) 
        global_menu_handler.highlighted_button = SECOND;

    // Check the condition for the third button, the third button only exists in the home screen and settings screen
    else if (is_mouse_in_third_button() && (current_state == HOME_SCREEN || current_state == SETTINGS_SCREEN )) 
        global_menu_handler.highlighted_button = THIRD;

    // Check the condition for the fourth button, the third button only exists in the home screen and settings screen
    else if (is_mouse_in_fourth_button() && (current_state == HOME_SCREEN || current_state == SETTINGS_SCREEN ))
        global_menu_handler.highlighted_button = FOURTH;

    // If the mouse isn't within the location of any buttons, then signify that there is no button to highlight
    else
        global_menu_handler.highlighted_button = NONE;
}

void handle_settings_screen_actions(menu_handler_data &global_menu_handler) 
{
    static int delay_left_mouse = 0;
    handle_all_screnes_button_highlighting(global_menu_handler);

    // Go back to the home screen
    if (is_mouse_in_first_button() && mouse_clicked(LEFT_BUTTON)) 
    {
        delay_left_mouse = 0; 
        global_menu_handler.game_state = HOME_SCREEN;
    }

     // Pause / Mute the current music
    if (is_mouse_in_second_button() && mouse_clicked(LEFT_BUTTON)) (global_menu_handler.music_player.is_muted) ? global_menu_handler.music_player.is_muted = false : global_menu_handler.music_player.is_muted = true;

     // Decrease the volume of the current music
    if (is_mouse_in_third_button() && mouse_clicked(LEFT_BUTTON)) 
    {   
        delay_left_mouse++;
        // Fix the double mouse click issue from home screen to another screen 
        if (delay_left_mouse > 1) 
        {
            decrease_volume(global_menu_handler.music_player);
            global_menu_handler.music_player.changed_volume_required = true;
        }
    }

     // Increase the volume of the current music
    if (is_mouse_in_fourth_button() && mouse_clicked(LEFT_BUTTON)) 
    {
        increase_volume(global_menu_handler.music_player);
        global_menu_handler.music_player.changed_volume_required = true;
    }
}

void handle_home_screen_actions(menu_handler_data &global_menu_handler) 
{
    handle_all_screnes_button_highlighting(global_menu_handler);

     // Play the Game when the first button is pressed in the home screen
    if (is_mouse_in_first_button() && mouse_down(LEFT_BUTTON)) global_menu_handler.game_state = PLAY_GAME_SCREEN;

     // Goto the leaderboard screen
    if (is_mouse_in_second_button() && mouse_down(LEFT_BUTTON)) global_menu_handler.game_state = LEADERBOARD_SCREEN;
    
     //  Goto the settings screen
    if (is_mouse_in_third_button() && mouse_down(LEFT_BUTTON)) global_menu_handler.game_state = SETTINGS_SCREEN;

    //  Goto the information screen
    if (is_mouse_in_fourth_button() && mouse_down(LEFT_BUTTON)) global_menu_handler.game_state = INFORMATION_SCREEN;
    
}

void handle_information_screen_actions(menu_handler_data &global_menu_handler)
{
    handle_all_screnes_button_highlighting(global_menu_handler);
     
    //  Goto the home screen when the first button is pressed
    if (is_mouse_in_first_button() && mouse_clicked(LEFT_BUTTON)) global_menu_handler.game_state = HOME_SCREEN;

    // If the user clicks the second button, open the GitHub repository
    if (is_mouse_in_second_button() && mouse_clicked(LEFT_BUTTON))
    {
        // Tried concatonating with a constant string, however, issues with conversions with LCPWSTRING and const char[SET_SIZE] due to compiler?
        if (OPERATING_SYSTEM == WINDOWS) ShellExecuteW(0, 0, (L"https://github.com/PandaPlaysAll/Space-Game-ITP"), 0, 0 , SW_SHOWNORMAL ); 
        if (OPERATING_SYSTEM == LINUX) system("xdg-open https://github.com/PandaPlaysAll/Space-Game-ITP");
        if (OPERATING_SYSTEM == UNIX) system("firefox https://github.com/PandaPlaysAll/Space-Game-ITP");
        if (OPERATING_SYSTEM == APPLE)
        {
            // --  TO DO -- 
            // MAJOR ISSUE WITH COMPILING. Important to fix this if wanted cross platform compiling...
            // string url_str = "https://github.com/PandaPlaysAll/Space-Game-ITP";
            // CFURLRef url = CFURLCreateWithBytes (
            //     NULL,                        
            //     (UInt8*)url_str.c_str(),     
            //     url_str.length(),            
            //     kCFStringEncodingASCII,      
            //     NULL                        
            // );
            // LSOpenCFURLRef(url,0);
            // CFRelease(url);
        }
        if (OPERATING_SYSTEM == UNIDENTIFIED) write_line("[WARNING] OS could not be detected!. Please contact leave a issue in https://github.com/PandaPlaysAll/Space-Game-ITP");
    }
}

void handle_leaderboard_screen_actions(menu_handler_data &global_menu_handler)
{
    static int delay_left_click = 0; // Prevent the double bufferring issue of rendering a second click when accessed the button from the home menu

    handle_all_screnes_button_highlighting(global_menu_handler);
    
    //  Goto the home screen when the first button is pressed
    if (is_mouse_in_first_button() && mouse_clicked(LEFT_BUTTON)) 
    {
        delay_left_click = 0;
        global_menu_handler.game_state = HOME_SCREEN;
    }

    if (is_mouse_in_second_button() && mouse_clicked(LEFT_BUTTON))
    {
        delay_left_click+= 1;
        
        if (delay_left_click > 1) 
        {
            reset_leaderboard_file();
        }
    }

    // Changing the sorting if the sorting button is clicked
    if (is_mouse_between_two_points(560, 750, 790, 800)  && mouse_clicked(LEFT_BUTTON)) global_menu_handler.sorting_method = change_type(global_menu_handler.sorting_method);
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
            draw_leader_screen_background(global_menu_handler);
            break;
        default:
            break;
    }
    refresh_screen(60);
}

bool handle_paused_screen_menu(menu_handler_data &global_menu_handler, game_data &game)
{
    // Handle the basic menu flow
    handle_all_screnes_button_highlighting(global_menu_handler);
    draw_settings_paused_screen_background(global_menu_handler);

    // Draw paused screen user information
    draw_text_after_two_buttons(form_paused_menu_information(game));
    refresh_screen();

    // Resume the game, hence return true to end the pause menu
    if (is_mouse_in_first_button() && mouse_clicked(LEFT_BUTTON)) return true;

    // Exit the space game and return to the original menu
    if (is_mouse_in_second_button() && mouse_clicked(LEFT_BUTTON)) 
    {
        global_menu_handler.game_state = HOME_SCREEN;
        return true;
    }

    // Return false, thus, stay in paused menu
    return false;
}

bool handle_end_game_menu(menu_handler_data &global_menu_handler, game_data &game)
{
    static bool has_entered_entry = false;
    static const font default_font = font_named("hud_font");
    static const int rectangle_x = 90;
    static const int rectangle_y = 675;
    static const int game_over_font_size = 25;

    clear_screen();

    // Handle the basics
    handle_all_screnes_button_highlighting(global_menu_handler);
    draw_end_game_screen_background(global_menu_handler, game.player.score);

    // Return the user back to the home menu
    if (is_mouse_in_first_button() && mouse_clicked(LEFT_BUTTON)) 
    {
        // Send the user to the home screen
        global_menu_handler.game_state = HOME_SCREEN;

        // Reset the entry entered when the user returns to the home screen. Allows them to enter their leaderboard entry once per round
        has_entered_entry = false;
        return true;
    }

    // When the user wants to add a leaderboard entry
    if (is_mouse_in_second_button() && mouse_clicked(LEFT_BUTTON))
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
                
                draw_end_game_screen_background(global_menu_handler, game.player.score);
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
    else if ( has_entered_entry )
    {
        draw_text("You have submitted your entry!", COLOR_BROWN, default_font, game_over_font_size + 10, rectangle_x + 5, rectangle_y + 40, option_to_screen() );
    }

    refresh_screen();
    // Iterate again
    return false;
}

void handle_menu()
{
    menu_handler_data global_menu_handler = create_menu_handler();

    while ( ! quit_requested() )
    {
        // Start the game when the menu game item is selected
        if (global_menu_handler.game_state == PLAY_GAME_SCREEN) global_menu_handler.game_state = handle_game();

        // Exit the global menu when the game should end
        if (global_menu_handler.game_state == END_GAME) break;

        // Else deal with the menu actions
        clear_screen();
        handle_music(global_menu_handler.music_player);
        handle_menu_state(global_menu_handler);
        process_events();
        refresh_screen();

    }
}

