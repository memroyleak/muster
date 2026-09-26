#include <iostream>
#include <curses.h>
#include "core/app.h"

App app;

// todo: think of what to use arguments for!
int main(int argc, char* argv[])
{
    std::cout << "Starting!\n";

    app.Init();

    while (app.running)
    {
        
    }

    app.Exit(0);
}