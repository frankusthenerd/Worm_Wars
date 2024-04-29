#ifndef WORM_HEADER
#define WORM_HEADER 1

#include "point.hpp"

class Application;
class Scene;

class Worm
{

    public:

    int length;
    bool human_player;
    static const int LEFT;
    static const int RIGHT;
    static const int UP;
    static const int DOWN;
    Worm();
    ~Worm();
    void Process(Application& app,
                 Scene& scene);
    void Build(int x,
               int y,
               int length,
               int direction);

    private:

    static const int MAX_LENGTH;
    unsigned int timer;
    int direction;
    Point* segments;

};

#endif
