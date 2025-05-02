#include <FL/Enumerations.H>
#include <FL/Fl_Window.H>

#include <GameInterface.h>
#include <Agent.h>
#include <bobcat_ui/bobcat_ui.h>
#include <bobcat_ui/button.h>
#include <bobcat_ui/textbox.h>

using namespace std;
using namespace bobcat;

GameInterface::GameInterface(int x, int y, int w, int h, GameState initialState){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    
    state = initialState;


    for (int i = 0; i < 7; i++){
        int x_coord = x + i*50;
        int y_coord = 100;
        Button* temp = new Button(x_coord, y_coord, 40, 40, "");
        temp->box(FL_ROUND_UP_BOX);

        ON_CLICK(temp, GameInterface::handleClick);

        buttons.append(temp);
    }

    updateButtons();


    string message = "Player vs Player";
    if (state.getEnabledAI()){
        message = "Player vs AI";
    }

    statusBar = new TextBox(x, h-25 + y, w, 25, message);
    statusBar->align(FL_ALIGN_CENTER);

    initButtons(); 
    showButtons();
}

void GameInterface::handleClick(Widget *sender){
    for (int i = 0; i < buttons.size(); i++){
        if (sender == buttons[i]){
            // cout << "Button " << i << " was clicked" << endl;
            state.play(i);
            updateButtons();
            // check winning conditions
            return;
        }
    }
}

bool GameInterface::checkWinningConditions(){
    bool result = state.gameOver();
    if (result){
        if (state.hasWon(0)){
            showMessage("Player 1 has won.\nClick Close to start a new game.", "Game Over");
        }
        else if (state.hasWon(1)){
            showMessage("Player 2 has won.\nClick Close to start a new game.", "Game Over");

void GameInterface::updateButtons(){
    for (int i = 0; i < buttons.size(); i++){
        if (state.squareStateChar(5, i) == 'X'){
            // Make it red
            cout << "Button " << i << " red" << endl;
            buttons[i]->color(fl_rgb_color(255, 0, 0));
            buttons[i]->color2(fl_rgb_color(255, 0, 0));
        }
        else if (state.squareStateChar(5, i) == 'O'){
            // Make it blue
            cout << "Button " << i << " blue" << endl;
            buttons[i]->color(fl_rgb_color(0, 0, 255));
            buttons[i]->color2(fl_rgb_color(0, 0, 255));

        }
        else{
            // Make it gray
            cout << "Button " << i << " gray" << endl;
            buttons[i]->color(49);
            buttons[i]->color2(49);
        }
        buttons[i]->redraw();
    }
}

void GameInterface::initButtons(){

    for (int i = 0; i < state.getRows(); i++){
        ArrayList<Button*> row;
        for (int j = 0; j < state.getCols(); j++){
            Button* curr = new Button(0, 0, 1, 1);
            curr->labelsize(32);
            ON_CLICK(curr, GameInterface::handleClick);
            row.append(curr);
        }
        buttons.append(row);
    }
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
                buttons[i][j]->color(fl_rgb_color(255, 255, 0));
                buttons[i][j]->color2(fl_rgb_color(255, 255, 0));
            }
            //gray
            else {
                buttons[i][j]->color(fl_rgb_color(250, 250, 250));
                buttons[i][j]->color2(fl_rgb_color(250, 250, 250));
            }
        }


void GameInterface::hideButtons(){
    for (int i = 0; i < 7; i++){
        buttons[i]->hide();
    }
}

void GameInterface::showButtons(){
    for (int i = 0; i < 7; i++){
        buttons[i]->show();

    }
}

void GameInterface::show() {
    statusBar->show();
    showButtons();
}

void GameInterface::hide() {
    statusBar->hide();
    hideButtons();
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