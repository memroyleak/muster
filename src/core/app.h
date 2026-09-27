#pragma once

#include <curses.h>

class App
{
public:
    // note: try and init most values? no undefined behavior pls
    int maxLines, maxColumns = 0;
    bool running;

    void Init();
    void Update();
    int Exit(int exitCode);
};