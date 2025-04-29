#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include "ArrayList.h"


class GameState{
    // variables needed for state:
    //Size of the game, board, whose turn is it, is AI enabled

    ArrayList<ArrayList<int>> board; //2d board (6 rows x 7 columns)
    bool currentTurn; //0 = player 0, 1 = player 1
    bool enabledAI;
    int lastRow;
    int lastCol;
    
public:
//Initialize default game state
    GameState();

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


    int getLastRow() const;
    int getLastCol() const;

    void reset();


    friend std::ostream& operator<<(std::ostream& os, const GameState& state);
};

inline std::ostream& operator<<(std::ostream& os, const GameState& state){
    os << "Printing the game state";

    return os;
}

#endif