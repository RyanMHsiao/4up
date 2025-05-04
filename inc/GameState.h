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

inline std::ostream& operator<<(std::ostream& os, const Vec& v){
    os <<"(" << v.x << "," << v.y << ")";
    return os;
}


class GameState{
    // variables needed for state:
    //Size of the game, board, whose turn is it, is AI enabled

    ArrayList<ArrayList<int>> board; //2d board (6 rows x 7 columns)
    int numRows;
    int numCols;
    bool currentTurn; //0 = player 0, 1 = player 1
    int elapsedTurns;
    bool enabledAI;
    bool done;
    Vec lastMove;
    
    
    
public:
//Initialize default game state
    GameState(int numRows = 6, int numCols = 7); //constructor with default 6x7

    GameState(const GameState& other);

    bool operator==(const GameState& other) const;

    GameState& operator=(const GameState& other);

    bool play(int col); //play into a column, update state resulting from players move
    bool hasWon(int player) const; //has a player won?
    bool gameOver() const; //is the game over?
    //is the board completely filled
    //if all columns are occupied and no player has won, we have a tie
    bool isFull() const; 
    bool hasSpace(int col) const;

    void reset();
    void enableAI();
    // turn on the AI
    void disableAI();
    bool getEnabledAI() const;
    // is the AI on?
    void resize(int newRows, int newCols);

    int getCurrentTurn() const; //whose turn?
    int getSize() const; //what is the size of the game
    int getRows() const;
    int getCols() const;

    

    int buttonState(int row, int col) const;
    int getElapsedTurns() const; //don't know if this will be useful

    
    Vec getBoardDimensions() const;
    Vec getLastMove() const;
    // get the last move (row, col)
    std::string squareState(int row, int col) const;
    char squareStateChar(int row, int col) const;


    friend std::ostream& operator<<(std::ostream& os, const GameState& state);
};

inline std::ostream& operator<<(std::ostream& os, const GameState& state){
    

    //Print column headers
    os << "     ";
    for(int col = 0; col < state.numCols; col++){
        os << col << "   ";
    }
    os << "\n";

    //print top border
    os << "    ";
    for(int col = 0; col < state.numCols; col++){
        os << "----";
    }
    os << "-\n";

    //Print each row
    for (int row = 0; row < state.numRows; row++){
        os <<row << "  |";
        for (int col = 0; col < state.numCols; col++){
            char c = state.squareStateChar(row, col);
            os << " "<< c << " |";
        }
        os << "\n";

        //print row border
        os << "  ";
        for (int col = 0; col < state.numCols; col++){
            os << "----";
        }
        os <<"-\n";
    }
 
    return os;
}

#endif