#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include "ArrayList.h"

struct Vec{
    int x;
    int y;

    Vec(){
        x = 0;
        y = 0;
    }

    Vec(int x, int y){
        this->x = x;
        this->y = y;
    }

    void set(int x, int y){
        this->x = x;
        this->y = y;
    }

};


class GameState{
    // variables needed for state:
    //Size of the game, board, whose turn is it, is AI enabled

    ArrayList<ArrayList<int>> board; //2d board (6 rows x 7 columns)
    int numRows;
    int numCols;
    bool currentTurn; //0 = player 0, 1 = player 1
    bool enabledAI;
    Vec lastMove;
    int elapsedTurns;
    
public:
//Initialize default game state
    GameState(int numRows = 6, int numCols = 7); //constructor with default 6x7

    int getRows() const;
    int getCols() const;

    int getCurrentTurn() const; //whose turn?

    int buttonState(int row, int col) const;

    bool play(int col); //play into a column, update state resulting from players move


    
    bool hasWon(int player) const; //has a player won?

    bool gameOver() const; //is the game over?

    int getSize() const; //what is the size of the game

    void enableAI(); //turn on the AI

    void disableAI(); //turn off the AI

    bool getEnabledAI() const; //is the AI on?

    bool hasSpace(int col) const;

    Vec getLastMove() const; //get the last move (row, col)

    void reset();

    Vec getBoardDimensions() const;

    std::string squareState(int row, int col) const;

    char squareStateChar(int row, int col) const;

    int getElapsedTurns() const;


    friend std::ostream& operator<<(std::ostream& os, const GameState& state);
};

inline std::ostream& operator<<(std::ostream& os, const GameState& state){
    os << "Printing the game state";

    for (int y = 0; y < state.getRows(); ++y) {
        for (int x = 0; x < state.getCols(); ++x) {
            os << state.squareStateChar(y, x);
        }
        os << "\n";
    }

    return os;
}

#endif