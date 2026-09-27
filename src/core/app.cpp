#include <cstdlib>
#include <curses.h>
#include "app.h"

void App::Init()
{
    running = true;

    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    // clear terminal before running update
    clear();
    maxLines = LINES - 1;
    maxColumns = COLS - 1;

    mvprintw(maxLines / 2, maxColumns / 2, "pdcurse-YOU");
}

void App::Update()
{
    int ch = 0;
    while ((ch = getch()) != ERR)
    {
        if (ch == 3)
            App::Exit(0);
    }

    // todo: update UI
}

int App::Exit(int exitCode)
{
    // todo: stop playback, cleanup routine...

    endwin();
    exit(exitCode);
}