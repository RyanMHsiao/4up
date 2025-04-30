// #include <FL/Enumerations.H>
#include <SettingsInterface.h>

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
}

void SettingsInterface::applyUpdates(){
    int newSize = 0;
    bool shouldEnableAI = false;

}

void SettingsInterface::hide(){
    visible = false;
    pageHeading->hide();
}

void SettingsInterface::show(){
    visible = true;
    pageHeading->show();
}

GameState SettingsInterface::getState() const{
    return state;
}

void SettingsInterface::setState(GameState state){
    this->state = state;
}
