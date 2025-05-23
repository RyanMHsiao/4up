// #include <FL/Enumerations.H>
#include <FL/Enumerations.H>
#include <SettingsInterface.h>
#include <GameState.h>
#include <bobcat_ui/dropdown.h>
#include <bobcat_ui/textbox.h>
#include <new>

using namespace std;
using namespace bobcat;

SettingsInterface::SettingsInterface(int x, int y, int w, int h, GameState state){
    visible = true;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;

    this->state = state;

    pageHeading = new TextBox(x, y, w, 25, "Settings");
    pageHeading->labelsize(24);
    pageHeading->labelfont(FL_BOLD);

    gridSizeSelector = new Dropdown(x, y + 50, w, 25, "Board Size");
    gridSizeSelector->add("6x7");
    gridSizeSelector->add("7x8");
    gridSizeSelector->add("8x9");

    enableAISelector = new Dropdown(x, y + 100, w, 25, "AI Player");
    enableAISelector->add("Enabled");
    enableAISelector->add("Disabled");
    if (state.getEnabledAI()){
        enableAISelector->value(0);
    }
    else {
        enableAISelector->value(1);
    }
}

void SettingsInterface::applyUpdates(){
    int newSize = 0;

    state.reset();

    if (gridSizeSelector->value() == 0) {
        state.resize(6, 7);
    }
    else if (gridSizeSelector->value() == 1) {
        state.resize(7, 8);
    }
    else if (gridSizeSelector->value() == 2) {
        state.resize(8, 9);
    }

    if (enableAISelector->value() == 0){
        state.enableAI();
    }
    else if (enableAISelector->value() == 1){
        state.disableAI();
    }
    
}

void SettingsInterface::hide(){
    visible = false;
    pageHeading->hide();
    gridSizeSelector->hide();
    enableAISelector->hide();
}

void SettingsInterface::show(){
    visible = true;
    pageHeading->show();
    gridSizeSelector->show();
    enableAISelector->show();
}

GameState SettingsInterface::getState() const{
    return state;
}

void SettingsInterface::setState(GameState state){
    this->state = state;
}
