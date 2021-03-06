#include "app.h"

App::App()
{

    debug.errorLog = loggers.getError();
    debug.warnLog = loggers.getWarn();
    debug.infoLog = loggers.getInfo();

    game.setDebug(&debug);

}

void App::run(){

    debug.println("building window");

    window_ptr gameWindow = windowManager.addWindow("game",480,270,"Dev Build",sf::Style::Default);

    srand(time(NULL));

    game.setFrameRate(60);

    game.setGameWindow(gameWindow);

    gameWindow->window.setVerticalSyncEnabled(true);

    game.run();

}

