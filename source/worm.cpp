#include <allegro.h>
#include "worm.hpp"
#include "application.hpp"
#include "scene.hpp"
#include <cstdlib>

using namespace std;

const int Worm::MAX_LENGTH = 8+3;
const int Worm::LEFT = 1;
const int Worm::RIGHT = 2;
const int Worm::UP = 3;
const int Worm::DOWN = 4;

Worm::Worm()
{

    segments = new Point[MAX_LENGTH];
    human_player = false;
    timer = 0;

}

Worm::~Worm()
{

    delete[] segments;

}

void Worm::Process(Application& app,
                   Scene& scene)
{

    if (length > 0)
    {

        int segment = 0;
        int worm = 0;
        int color;
        Point previous;
        Worm* opponent;

        timer++;

        if (human_player)
        {

            color = makecol(0, 255, 0);
            opponent = scene.enemy;

            if (app.signals & Application::SIGNAL_LEFT)
            {

                direction = LEFT;

            }

            if (app.signals & Application::SIGNAL_RIGHT)
            {

                direction = RIGHT;

            }

            if (app.signals & Application::SIGNAL_UP)
            {

                direction = UP;

            }

            if (app.signals & Application::SIGNAL_DOWN)
            {

                direction = DOWN;

            }

        }
        else // computer player
        {

            color = makecol(255, 255, 0); // yellow
            opponent = scene.player;

            if ((rand()%5) == 0)
            {

                // move towards the tail of the player

                if (segments[0].x < scene.player->segments[scene.player->length-1].x)
                {

                    direction = RIGHT;

                }

                if (segments[0].x > scene.player->segments[scene.player->length-1].x)
                {

                direction = LEFT;

                }

                if (segments[0].y < scene.player->segments[scene.player->length-1].y)
                {

                    direction = DOWN;

                }

                if (segments[0].y > scene.player->segments[scene.player->length-1].y)
                {

                    direction = UP;

                }

            }
            else
            {

                if ((timer%15) == 0)
                {

                    direction = LEFT+(rand()%4); // randomly change direction

                }

            }

        }

        previous.x = segments[0].x;
        previous.y = segments[0].y;

        if (direction == LEFT)
        {

            segments[0].x -= 8;

        }

        if (direction == RIGHT)
        {

            segments[0].x += 8;

        }

        if (direction == UP)
        {

            segments[0].y -= 8;

        }

        if (direction == DOWN)
        {

            segments[0].y += 8;

        }

        if (segments[0].x < 0)
        {

            segments[0].x = 0;
            direction = RIGHT;

        }

        if (segments[0].x == Application::CANVAS_WIDTH)
        {

            segments[0].x = Application::CANVAS_WIDTH-8;
            direction = LEFT;

        }

        if (segments[0].y < 8)
        {

            segments[0].y = 8;
            direction = DOWN;

        }

        if (segments[0].y == Application::CANVAS_HEIGHT)
        {

            segments[0].y = Application::CANVAS_HEIGHT-8;
            direction = UP;

        }

        // collision detection stuff

        while (segment < opponent->length)
        {

            if ((segments[0].x == opponent->segments[segment].x) &&
                (segments[0].y == opponent->segments[segment].y))
            {

                if ((length < MAX_LENGTH) && (opponent->length > 0))
                {

                    length++;
                    opponent->length--;
                    break;

                }

            }

            segment++;

        }

        // this repositions the worm

        segment = 1; // skip the head

        while (segment < length)
        {

            Point next;

            next.x = segments[segment].x;
            next.y = segments[segment].y;
            segments[segment].x = previous.x;
            segments[segment].y = previous.y;
            previous.x = next.x;
            previous.y = next.y;
            segment++;

        }

        // draws the worm

        segment = 0;

        while (segment < length)
        {

            rectfill(app.canvas, segments[segment].x, segments[segment].y,
                     (segments[segment].x+7), (segments[segment].y+7), color);
            segment++;

        }

    }

}

void Worm::Build(int x,
                 int y,
                 int length,
                 int direction)
{

    int segment = 0;

    timer = 0;
    this->length = length;
    this->direction = direction;

    while (segment < length)
    {

        segments[segment].x = x;
        segments[segment].y = y;
        segment++;
        x += 8;

    }

}
