#include "RunSession.h"
#include <ctime>
#include <cstdlib>

int main()
{
    srand(time(0));

    RunSession game;

    game.run();

    return 0;
}