#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/elements.hpp>
#include "app.h"

void App::Init()
{
    using namespace ftxui;
    document = hbox({
        text("left")   | border,
        text("middle") | border | flex,
        text("right")  | border,
    });

    running = true;
}

void App::Update()
{
    auto screen = ftxui::Screen::Create(
        ftxui::Dimension::Full(),
        ftxui::Dimension::Fit(document)
    );
    ftxui::Render(screen, document);
    screen.Print();
}

int App::Exit(int exitCode)
{
    running = false;
    // todo: stop playback, cleanup routine...
    return 0;
}