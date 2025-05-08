#include "Application.h"
#include "SettingsInterface.h"
#include <bobcat_ui/bobcat_ui.h>
#include <bobcat_ui/button.h>
#include <cstdlib>
// #include <type_traits>
#include "Agent.h"

using namespace bobcat;
using namespace std;

Application::Application(){

    window = new Window(100, 100, 400, 400, "Connect4");

    // state = GameState();
    state.enableAI();

    gameInterface = new GameInterface(30, 35, 340, 340, state);
    settingsInterface = new SettingsInterface(30, 40, 340, 340, state);

    cancelButton = new Button(30, 360, 155, 25, "Cancel");
    applyButton = new Button(215, 360, 155, 25, "Apply");

    settingsInterface->hide();
    cancelButton->hide();
    applyButton->hide();

    menu = new Menu();
    newGame = new MenuItem("File/New Game");
    settings = new MenuItem("File/Settings");
    quit = new MenuItem("File/Exit");
    menu->addItem(newGame);
    menu->addItem(settings);
    menu->addItemSep(quit);

    ON_CLICK(newGame, Application::handleNewGameMenuClick);
    ON_CLICK(settings, Application::handleSettingsMenuClick);
    ON_CLICK(quit, Application::handleQuitMenuClick);
    ON_CLICK(cancelButton, Application::handleCancelBtnClick);
    ON_CLICK(applyButton, Application::handleApplyBtnClick);

    // window->redraw();
    window->show();
    // window->redraw();

    
    twoPlayersButton = new Button(30, 35, 155, 25, "Player vs Player");
    AIButton = new Button(215, 35, 155, 25, "Player vs AI");

    ON_CLICK(twoPlayersButton, Application::handleTwoPlayersClick);
    ON_CLICK(AIButton, Application::handleAIClick);

    twoPlayersButton->show();
    AIButton->show();
}

void Application::prepareGraphics() {
    // handleSettingsMenuClick(nullptr);
    gameInterface->updateButtons();
}

void Application::runTUI(int rows, int cols) {
    state = GameState(rows, cols);
    bool artificial = true;
    bool artificialPlay = false;
    // agent = Agent();

    while (!state.gameOver()) {
        if(artificialPlay && artificial){
            Vec spot = Agent::play(state);
            state.play(spot.y);
            artificialPlay = false;
        } else {
            bool valid = false;
            while(!valid){
                std::cout << state << "\n";
                int choice;
                std::cin >> choice;
                if(state.hasSpace(choice)){
                    state.play(choice);
                    valid = true;
                } else {
                    std::cout << "Invalid Move" << std::endl;
                }
            }
            artificialPlay = true;
        }
    }
    std::cout << state << "\n";
    std::cout << "game over\n";
}


void Application::handleNewGameMenuClick(Widget *sender){
    gameInterface->reset();
}
 
void Application::handleSettingsMenuClick(Widget *sender){
    gameInterface->hide();
    settingsInterface->show();
    applyButton->show();
    cancelButton->show();
}

void Application::handleCancelBtnClick(Widget *sender){
    settingsInterface->hide();
    applyButton->hide();
    cancelButton->hide();
    gameInterface->show();
}

void Application::handleApplyBtnClick(Widget* sender){
    settingsInterface->applyUpdates();

    state = settingsInterface->getState();

    gameInterface->setState(state);

    settingsInterface->hide();
    applyButton->hide();
    cancelButton->hide();

    gameInterface->resizeButtons();
    gameInterface->show();
    gameInterface->updateButtons();
}

void Application::handleTwoPlayersClick(Widget *sender){
    state = GameState();
    state.disableAI();
    gameInterface->setState(state);
    gameInterface->reset();
}

void Application::handleAIClick(Widget *sender){
    state = GameState();
    state.enableAI();
    gameInterface->setState(state);
    gameInterface->reset();
}

void Application::handleQuitMenuClick(Widget *sender){
    exit(0);
}



