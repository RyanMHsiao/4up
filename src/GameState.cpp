#include "ArrayList.h"
#include <GameState.h>

using namespace std;
GameState::GameState(int numRows, int numCols){
    this->numRows = numRows;
    this->numCols = numCols;
    currentTurn = 0;
    
    enabledAI = false;

    lastMove.set(-1,-1);

    
    for(int i = 0; i<numRows; ++i){
        ArrayList<int> row;
        for (int j = 0; j< numCols; ++j){
            row.append(-1); //fill the row with -1 (empty cells)
        }
        board.append(row); //append the completed row to the board
    }
    cout<<"Initializing Connect 4 state with size"<< numRows <<"x"<<numCols <<endl;
}

//check if a player has won
bool GameState::hasWon(int player) const{
    cout <<"Checking whether player " <<player << " has won" <<endl;

    //horizontal check

    for (int row= 0; row < numRows; ++row){
        for (int col = 0; col <= numCols - 4; ++col){
            if (board[row][col] == player 
            && board[row][col + 1] == player //does the same four positions belong to the same player?
            && board[row][col + 2] == player 
            && board[row][col + 3] == player) {
                return true;
            }
        }
    }

    //Vertical check 
    for (int col = 0; col < numCols; ++col){
        for (int row = 0; row <= numRows - 4; ++row){
            if (board[row][col] == player 
            && board[row + 1][col] == player &&
            board[row + 2][col] == player &&
            board[row + 3][col] == player){
                return true;
                
            }
        }
    }

    //Diagonal (bottom-left to top-right)
    for (int row = 3; row < numRows; ++row){
        for(int col = 0; col <= numCols - 4; ++col){
            if (board[row][col]== player &&
            board[row-1][col+1]== player &&
            board[row-2][col+2]== player &&
            board[row-3][col+3]== player){
            return true;
            }
        }
    }

    //Diagonal (top-left to bottom-right)
    for(int row = 0; row <= numRows - 4; ++row){
        for (int col = 0; col <= numCols - 4; ++col){
            if (board[row][col] == player &&
            board[row+1][col+1] == player &&
            board[row+2][col+2] == player &&
            board[row+3][col+3] == player){
            return true;
            }
        } 
    }
    return false;
}



bool GameState::play(int col){
    cout << "Current player makes move " << col << endl;
    cout << "Must update state, including whose turn it is" << endl; 
    cout << "and the last move, among other things." << endl;

    if( col<0 || col >= numCols){
        return false;
    }

    for(int row = numRows - 1; row >= 0; --row){
        if (board[row][col]== -1){
            board[row][col] = currentTurn;
            lastMove.set(row, col);
            currentTurn = !currentTurn;
            return true;
        }
    }

    return false; //column full
}


int GameState::getCurrentTurn() const {
    cout <<"Whose turn is it?" <<endl;
    return currentTurn;
 }

//tells if no more moves can be made (helps detect a draw)
 bool GameState::isFull() const{
    for (int col = 0; col < numCols; ++col){
        if (board[0][col]== -1){
            return false;
        }
    }
    return true;
 }


 bool GameState::gameOver() const {
    cout << "Checking if the game is over" << endl;
  if(hasWon(0) || hasWon(1)){
    return hasWon(0) || hasWon(1) || isFull();
   }

   
   return true;
 }

 int GameState::getSize() const {
    return numRows * numCols;
 }

 Vec GameState::getBoardDimensions() const{
    return Vec(numRows, numCols);
 }

// string GameState::squareState(int i, int j) const {
//     if (grid[i][j] == 0){
//         return "X";
//     }
//     else if (grid[i][j] == 1){
//         return "O";
//     }
    
//     return "";
// }

Vec GameState::getLastMove() const {
    cout << "Getting the last move that was made" << endl;

    return lastMove;
}


void GameState::reset(){
    currentTurn = 0;
    lastMove.set(-1, -1);
    enabledAI = false;

    //Clear and reinitialize the board with -1 (empty)
    for (int i = 0; i < numRows; i++){
        for (int j = 0; j < numCols; j++){
            board[i][j] = -1;
        }
    }

    cout << "Game state reset to empty" << numRows <<"x" << numCols << "board." <<endl;
}

void GameState::enableAI(){
    enabledAI = true;
}

void GameState::disableAI(){
    enabledAI = false;
}

bool GameState::getEnabledAI() const{
    return enabledAI;
}




