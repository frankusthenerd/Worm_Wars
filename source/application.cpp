#include "application.hpp"
#include "macros.hpp"

const int Application::CANVAS_WIDTH = 256;
const int Application::CANVAS_HEIGHT = 224;
const int Application::SIGNAL_LEFT = 1;
const int Application::SIGNAL_RIGHT = 2;
const int Application::SIGNAL_UP = 4;
const int Application::SIGNAL_DOWN = 8;
const int Application::SIGNAL_START = 16;
const int Application::SIGNAL_PAUSE = 32;
const int Application::SIGNAL_QUIT = 64;
extern volatile bool timing_signal;

Application::Application()
{

    canvas = create_bitmap(CANVAS_WIDTH, CANVAS_HEIGHT);
    signals = 0;
    scene = new Scene();
    timer = 0;
    paused = false;

}

Application::~Application()
{

    destroy_bitmap(canvas);
    destroy_bitmap(title_bm);
    destroy_midi(battle_mt);
    destroy_midi(game_over_mt);
    destroy_midi(victory_mt);
    delete scene;

}

void Application::Load_Resources()
{

    Load_Bitmap_File("data\\graphics\\misc\\title.bmp", &title_bm);
    Load_Music_Track_File("data\\sounds\\music_tracks\\battle.mid", &battle_mt);
    Load_Music_Track_File("data\\sounds\\music_tracks\\game_over.mid", &game_over_mt);
    Load_Music_Track_File("data\\sounds\\music_tracks\\victory.mid", &victory_mt);

}

void Application::Display_Canvas()
{

    acquire_screen();
    vsync();
    stretch_blit(canvas, screen, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, 0, 0, SCREEN_W, SCREEN_H);
    release_screen();

}

void Application::Generate_Signals()
{

    if (keyboard_needs_poll())
    {

        poll_keyboard();

    }

    if (key[KEY_LEFT])
    {

        signals |= SIGNAL_LEFT;

    }

    if (key[KEY_RIGHT])
    {

        signals |= SIGNAL_RIGHT;

    }

    if (key[KEY_UP])
    {

        signals |= SIGNAL_UP;

    }

    if (key[KEY_DOWN])
    {

        signals |= SIGNAL_DOWN;

    }

    if (key[KEY_P])
    {

        signals |= SIGNAL_PAUSE;

    }

    if (key[KEY_ENTER])
    {

        signals |= SIGNAL_START;

    }

    if (key[KEY_Q])
    {

        signals |= SIGNAL_QUIT;

    }

}

void Application::Run()
{

    bool skip_title = false;
    bool done = false;

    while (!skip_title)
    {

        Generate_Signals();

        if (timing_signal)
        {

            timing_signal = false;

            if (signals & SIGNAL_START)
            {

                skip_title = true;
                signals = 0;
                continue;

            }

            if (signals & SIGNAL_QUIT)
            {

                done = true;
                skip_title = true;
                signals = 0;
                continue;

            }

            blit(title_bm, canvas, 0, 0, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);
            Display_Canvas();
            signals = 0;

        }

    }

    play_midi(battle_mt, 1);

    while (!done)
    {

        Generate_Signals();

        if (timing_signal)
        {

            timing_signal = false;
            timer++;

            if (signals & SIGNAL_QUIT)
            {

                done = true;
                continue;

            }

            if (scene->game_won)
            {

                textout_centre_ex(canvas, font, "You won!", (CANVAS_WIDTH/2), (CANVAS_HEIGHT/2),
                                  makecol(255, 255, 255), -1);

            }
            else // game not won
            {

                if (scene->game_over)
                {

                    if (signals & SIGNAL_START)
                    {

                        scene->Reset();
                        timer = 0;
                        paused = false;
                        scene->clock = 0;
                        play_midi(battle_mt, 1);

                    }

                    textout_centre_ex(canvas, font, "Game Over", (CANVAS_WIDTH/2),
                                      (CANVAS_HEIGHT/2), makecol(255, 255, 255), -1);

                }
                else // game not over
                {

                    if (timer > 6)
                    {

                        if (signals & SIGNAL_PAUSE)
                        {

                            timer = 0;

                            if (paused)
                            {

                                paused = false;
                                midi_resume();

                            }
                            else
                            {

                                paused = true;
                                midi_pause();

                            }

                        }

                    }

                    if (paused)
                    {

                        textout_centre_ex(canvas, font, "- paused -", (CANVAS_WIDTH/2),
                                          (CANVAS_HEIGHT/2), makecol(255, 255, 255), -1);

                    }
                    else
                    {

                        scene->Process((*this));

                    }

                }

            }

            Display_Canvas();
            signals = 0;

        }

    }

}
