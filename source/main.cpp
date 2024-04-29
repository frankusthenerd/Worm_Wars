#include <allegro.h>
#include "application.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

volatile bool timing_signal = false;
Application* application; // this needs to be global
void Timing_Handler();
void Display_Switch_Handler();

int main(int argc,
         char** argv)
{

    int desktop_w;
    int desktop_h;

    allegro_init();
    set_color_depth(desktop_color_depth());
    get_desktop_resolution(&desktop_w, &desktop_h);
    set_gfx_mode(GFX_AUTODETECT, desktop_w, desktop_h, 0, 0);
    install_keyboard();
    install_timer();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    LOCK_VARIABLE(timing_signal);
    LOCK_FUNCTION(Timing_Handler);
    install_int(Timing_Handler, 200);
    set_volume(255, 128);
    srand(time(NULL));
    set_display_switch_mode(SWITCH_PAUSE);
    set_write_alpha_blender();
    set_display_switch_callback(SWITCH_IN, Display_Switch_Handler);
    application = new Application();
    application->Load_Resources();
    application->Run();    
    remove_display_switch_callback(Display_Switch_Handler);
    delete application;
    cout << "Done." << endl;
    return 0;

}

END_OF_MAIN()

void Timing_Handler()
{

    timing_signal = true;

}

END_OF_FUNCTION(Timing_Handler)

void Display_Switch_Handler()
{

    acquire_screen();
    stretch_blit(application->canvas, screen, 0, 0, Application::CANVAS_WIDTH,
                 Application::CANVAS_HEIGHT, 0, 0, SCREEN_W, SCREEN_H);
    release_screen();

}
