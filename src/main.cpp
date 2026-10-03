#include <iostream>
#include "core/app.h"

App app;

// todo: think of what to use arguments for!
int main(int argc, char* argv[])
{
    std::cout << "Starting!\n";
    app.Init();
        
    app.Update();

    return 0;
}