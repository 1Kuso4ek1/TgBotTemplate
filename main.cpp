#include "Application.hpp"

int main()
{
    Application app;
    app.setupCommands();
    app.loadData();
    app.run();
}
