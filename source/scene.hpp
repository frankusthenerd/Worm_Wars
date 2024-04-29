#ifndef SCENE_HEADER
#define SCENE_HEADER 1

#include "worm.hpp"

class Scene
{

    public:

    Worm* player;
    Worm* enemy;
    bool game_over;
    bool game_won;
    unsigned int clock;
    Scene();
    ~Scene();
    void Reset();
    void Process(Application& app);

};

#endif
