#pragma once

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

class App
{
public:
    // note: try and init most values? no undefined behavior pls
    int maxLines, maxColumns = 0;
    bool running;

    ftxui::Element document;

    void Init();
    void Update();
    int Exit(int exitCode);
};