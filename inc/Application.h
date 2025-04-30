#ifndef APPLICATION_H
#define APPLICATION_H

// Include the Bobcat UI component headers that are needed
#include <bobcat_ui/bobcat_ui.h>    // Needed for all apps (always include)
#include <bobcat_ui/window.h>       // Needed for window (always include)
#include <bobcat_ui/textbox.h>      // Needed for displaying text
#include <bobcat_ui/button.h>       // Needed for buttons
#include <bobcat_ui/menu.h>         // Needed for application menu

// Include a Game State object, representing the state of your game
#include "GameState.h"

// Separate file for the game interface
#include "GameInterface.h"

// Separate file for the settings interface
#include "SettingsInterface.h"

class Application: public bobcat::Application_ {
    // Application window
    bobcat::Window *window;
    
    // Application menu
    bobcat::Menu *menu;
    bobcat::MenuItem *newGame;
    bobcat::MenuItem *settings;
    bobcat::MenuItem *quit;
    
    // Application interface
    GameInterface *gameInterface;           // Game interface
    SettingsInterface *settingsInterface;   // Settings interface

    bobcat::Button *applyButton;            // Button to apply settings
    bobcat::Button *cancelButton;           // Cancel button for settings screen

    GameState state;                        // The game state object

    // User interaction event handlers
    void handleNewGameMenuClick(bobcat::Widget *sender);
    void handleSettingsMenuClick(bobcat::Widget *sender);
    void handleCancelBtnClick(bobcat::Widget *sender);
    void handleApplyBtnClick(bobcat::Widget *sender);
    void handleQuitMenuClick(bobcat::Widget *sender);

public:
    Application();
    
    void runTUI(int rows, int cols);
};

#endif