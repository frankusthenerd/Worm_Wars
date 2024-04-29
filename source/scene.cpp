#include <allegro.h>
#include "scene.hpp"
#include "application.hpp"

Scene::Scene()
{

    player = new Worm();
    player->human_player = true;
    player->Build(8, 8, 3, Worm::DOWN);
    enemy = new Worm();
    enemy->Build((Application::CANVAS_WIDTH/2), (Application::CANVAS_HEIGHT-16), 8, Worm::UP);
    game_over = false;
    game_won = false;
    clock = 0;

}

Scene::~Scene()
{

    delete player;
    delete enemy;

}

void Scene::Reset()
{

    game_over = false;
    game_won = false;
    player->Build(8, 8, 3, Worm::DOWN);
    enemy->Build((Application::CANVAS_WIDTH/2), (Application::CANVAS_HEIGHT-16), 8, Worm::UP);

}

void Scene::Process(Application& app)
{

    clock++;
    clear_bitmap(app.canvas);
    player->Process(app, (*this));
    enemy->Process(app, (*this));
    textprintf_ex(app.canvas, font, 1, 1, makecol(255, 255, 255), -1, "%02u:%02u:%02u",
                  ((clock/5)/60), ((clock/5)%60), (clock%5)); // time display
    game_over = (player->length == 0);
    game_won = (enemy->length == 0);

    if (game_won)
    {

        play_midi(app.victory_mt, 1);

    }

    if (game_over)
    {

        play_midi(app.game_over_mt, 0);

    }

}
