#include <FL/Enumerations.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>


#include <GameInterface.h>
#include <Agent.h>
#include <bobcat_ui/bobcat_ui.h>
#include <bobcat_ui/button.h>
#include <bobcat_ui/textbox.h>

using namespace std;
using namespace bobcat;

// We must always initialize with max size and just hide unused buttons
// This is a bobcat-ui limitation and a Kyrilov-approved solution
const int MAX_ROWS = 8, MAX_COLS = 9;

GameInterface::GameInterface(int x, int y, int w, int h, GameState initialState){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    
    
    state = initialState;

    boardBackground = new Fl_Box(x, y, w, h);
    boardBackground->box(FL_FLAT_BOX);
    boardBackground->color(fl_rgb_color(0, 0, 255));


    for (int i = 0; i < MAX_ROWS; i++){
        ArrayList<bobcat::Button *> row;
        for (int j = 0; j < MAX_COLS; j++) {
            int x_coord = x + i*50;
            int y_coord = y + j*50;
            Button* temp = new Button(x_coord, y_coord, 40, 40, "");
            temp->box(FL_ROUND_UP_BOX);

            ON_CLICK(temp, GameInterface::handleClick);

            row.append(temp);
        }
        buttons.append(row);
    }

    updateButtons();


    string message = "Player vs Player";
    if (state.getEnabledAI()){
        message = "Player vs AI";
    }

    statusBar = new TextBox(x, h-25 + y, w, 25, message);

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
                        state.play(move.y);
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
    if (result){
        if (state.hasWon(0)){
            showMessage("Player 1 has won.\nClick Close to start a new game.", "Game Over");
        }
        else if (state.hasWon(1)){
            showMessage("Player 2 has won.\nClick Close to start a new game.", "Game Over");
        }
        else{
            showMessage("It is a tie.\nClick Close to start a new game.", "Game Over");
        }
        reset();
    }
    return result;
}

void GameInterface::initButtons(){

    for (int i = 0; i < MAX_ROWS; i++){
        ArrayList<Button*> row;
        for (int j = 0; j < MAX_COLS; j++){
            Button* curr = new Button(0, 0, 1, 1);
            curr->box(FL_ROUND_UP_BOX);

            curr->labelsize(32);
            ON_CLICK(curr, GameInterface::handleClick);
            row.append(curr);
        }
        buttons.append(row); 
    }
}

void GameInterface::resizeButtons() {
    std::cout << "Resizing buttons\n";
}

void GameInterface::showButtons(){


    int btnW = w / state.getCols();
    int btnH = h / state.getRows();
    for (int i = 0; i < state.getRows(); i++){
        int btnY = y + btnH * i;
        for (int j = 0; j < state.getCols(); j++){
            int btnX = x + btnW * j;

            // The cause of the crash is here.
            // The i and j are out of bounds for buttons.
            std::cout << "Showing button " << i << " " << j << "\n";
            std::cout << buttons[i].size() << " is size\n";

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
    }
}

void GameInterface::show() {
    statusBar->show();
    boardBackground->show();
    showButtons();
}

void GameInterface::hide() {
    statusBar->hide();
    boardBackground->hide();
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