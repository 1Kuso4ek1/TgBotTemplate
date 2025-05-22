#include "Application.hpp"

int main()
{
    Application app;

    app.setupCommands();
    app.setupKeyboards();
    app.setupCallbackQueries();
    app.loadData();

    app.run();
}
