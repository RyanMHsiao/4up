#include <FL/Enumerations.H>
#include <FL/Fl_Window.H>
#include <GameInterface.h>
#include <Agent.h>
#include <bobcat_ui/bobcat_ui.h>
#include <bobcat_ui/textbox.h>

using namespace std;
using namespace bobcat;

GameInterface::GameInterface(int x, int y, int w, int h, GameState initialState){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    
    state = initialState;

    string message = "Player vs Player";
    if (state.getEnabledAI()){
        message = "Player vs AI";
    }

    statusBar = new TextBox(0, 375, 400, 25, message);

    initButtons(); 
    showButtons();
}

void GameInterface::handleClick(Widget *sender){
    for (int i = 0; i < state.getRows(); i++){
        for (int j = 0; j < state.getCols(); j++){
            if (sender == buttons[i][j]){
                state.play(j);
                updateButtons();

                bool done = checkWinningConditions();
            
                if (!done){
                    if (state.getEnabledAI()){
                        Vec move = Agent::play(state);
                        state.play(move.x);
                        updateButtons();
                        checkWinningConditions();
                    }
                }

                return;
            }
        }
    }
    
}

bool GameInterface::checkWinningConditions(){
    bool result = state.gameOver();
    if (state.gameOver()){
        if (state.hasWon(0)){
            showMessage("Player X has won.\nClick Close to start a new game.", "Game Over");
        }
        else if (state.hasWon(1)){
            showMessage("Player O has won.\nClick Close to start a new game.", "Game Over");
        }
        else{
            showMessage("It is a tie.\nClick Close to start a new game.", "Game Over");
        }
        reset();
    }
    return result;
}

void GameInterface::initButtons(){

    for (int i = 0; i < state.getRows(); i++){
        ArrayList<Button*> row;
        for (int j = 0; j < state.getCols(); j++){
            Button* curr = new Button(0, 0, 1, 1);
            buttons[i][j]->labelsize(32);
            ON_CLICK(buttons[i][j], GameInterface::handleClick);
            row.append(curr);
        }
        buttons.append(row);
    }

    // for (int i = 0; i < buttons.size(); i++){
    //     for (int j = 0; j < buttons[i].size(); j++){
    //         buttons[i][j]->labelsize(32);
    //         ON_CLICK(buttons[i][j], GameInterface::handleClick);
    //     }
    // }
}

void GameInterface::showButtons(){

    int btnW = w / state.getCols();
    int btnH = h / state.getRows();
    for (int i = 0; i < state.getRows(); i++){
        int btnY = y + btnH * i;
        for (int j = 0; j < state.getCols(); j++){
            int btnX = x + btnW * j;

            buttons[i][j]->resize(btnX, btnY, btnW, btnH);
            // buttons[i][j]->label(state.squareState(i, j));
            buttons[i][j]->show();
        }
    }
}

void GameInterface::hideButtons(){

    for (int i = 0; i < state.getRows(); i++){
        for (int j = 0; j < state.getCols(); j++){
            buttons[i][j]->hide();
        }
    }
}

void GameInterface::updateButtons(){
    //rows
    for(int i = 0; i < state.getRows(); i++){
    //columns
        for (int j = 0; j < state.getCols(); j++){
            std::string stateStr = state.squareState(i,j);
            buttons[i][j]->label(stateStr.c_str());

            if (stateStr == "red"){
                buttons[i][j]->color(fl_rgb_color(255, 0, 0));
                buttons[i][j]->color2(fl_rgb_color(255, 0, 0));
            }

            else if (stateStr == "yellow"){
                buttons[i][j]->color(fl_rgb_color(255, 0, 0));
                buttons[i][j]->color2(fl_rgb_color(255, 255, 0));
            }
            //gray
            else {
                buttons[i][j]->color(fl_rgb_color(250, 250, 250));
                buttons[i][j]->color2(fl_rgb_color(250, 250, 250));
            }
        }
    }
}

void GameInterface::show() {
    showButtons();
    statusBar->show();
}

void GameInterface::hide() {
    hideButtons();
    statusBar->hide();
}

void GameInterface::reset() {
    state.reset();
    updateButtons();
}

GameState GameInterface::getState() const{
    return state;
}

void GameInterface::setState(GameState state){
    this->state = state;
    string message = "Player vs Player";
    if (state.getEnabledAI()){
        message = "Player vs AI";
    }
    statusBar->label(message);
}
