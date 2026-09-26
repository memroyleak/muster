#include <cstdlib> 
#include <curses.h>
#include "app.h"

void App::Init()
{
    running = false;

    initscr();
    cbreak();
    noecho();

    // clear terminal before running update
    clear();
    maxLines = LINES - 1;
    maxColumns = COLS - 1;
}

int App::Exit(int exitCode)
{
    getch();
    endwin();
    return exitCode;
}