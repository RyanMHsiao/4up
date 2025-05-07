#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include <FL/Fl_Box.H>

#include "ArrayList.h"
#include <bobcat_ui/bobcat_ui.h>
#include <bobcat_ui/button.h>
#include <bobcat_ui/textbox.h>

#include <GameState.h>


class GameInterface{
    int x;
    int y;
    int w;
    int h;

    Fl_Box* boardBackground;

    GameState state;

    ArrayList<ArrayList<bobcat::Button*>> buttons;

    bobcat::TextBox *statusBar;

    void updateButtons();

    void handleClick(bobcat::Widget *sender);

    void hideButtons();
    void showButtons();
    bool checkWinningConditions();
    void initButtons();


public:

    GameInterface(int x, int y, int w, int h, GameState initialState);

    void reset();
    void hide();
    void show();

    void resizeButtons();

    GameState getState() const;
    void setState(GameState state);

};

#endif