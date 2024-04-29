#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER 1

#include <allegro.h>
#include "scene.hpp"

class Application
{

    public:

    BITMAP* canvas;
    BITMAP* title_bm;
    MIDI* battle_mt;
    MIDI* game_over_mt;
    MIDI* victory_mt;
    int signals;
    Scene* scene;
    static const int CANVAS_WIDTH;
    static const int CANVAS_HEIGHT;
    static const int SIGNAL_LEFT;
    static const int SIGNAL_RIGHT;
    static const int SIGNAL_UP;
    static const int SIGNAL_DOWN;
    static const int SIGNAL_START;
    static const int SIGNAL_PAUSE;
    static const int SIGNAL_QUIT;
    Application();
    ~Application();
    void Load_Resources();
    void Run();

    private:

    unsigned int timer;
    bool paused;
    void Display_Canvas();
    void Generate_Signals();

};

#endif
