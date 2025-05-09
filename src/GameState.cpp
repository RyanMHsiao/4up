#include "ArrayList.h"
#include <GameState.h>

using namespace std;
GameState::GameState(int numRows, int numCols){
    this->numRows = numRows;
    this->numCols = numCols;
    currentTurn = 0;
    elapsedTurns = 0;
    done = false;
    
    enabledAI = false;

    lastMove.set(-1,-1);

    //initialize the board with empty cells (-1)
    for(int i = 0; i < numRows; i++){
        ArrayList<int> row;
        for (int j = 0; j< numCols; j++){
            row.append(-1); //fill the row with -1 (empty cells)
        }
        board.append(row); //append the completed row to the board
    }
}

//copy constructor

GameState::GameState(const GameState& other){
    numRows = other.numRows;
    numCols = other.numCols;
    currentTurn = other.currentTurn;
    elapsedTurns = other.elapsedTurns;
    enabledAI = other.enabledAI;
    done = other.done;
    lastMove = other.lastMove;

    //Deep copy the 2D board

    for(int i = 0; i< other.board.size(); i++){
        ArrayList<int> row;
        for (int j = 0; j < other.board[i].size(); j++){
            row.append(other.board[i][j]);
        }
        board.append(row);
    }
}

//copy assignment operator
GameState& GameState::operator=(const GameState & other){
if(this != &other ){
    //clear current board
    while(board.size() > 0){
        board.removeLast();
    }

    //copy simple members
    numRows = other.numRows;
    numCols = other.numCols;
    currentTurn = other.currentTurn;
    elapsedTurns = other.elapsedTurns;
    enabledAI = other.enabledAI;
    done = other.done;
    lastMove = other.lastMove;

    //deep copying the board using ArrayList
    for (int i = 0; i < other.board.size(); i++){
        ArrayList<int> row;
        for (int j = 0; j < other.board[i].size(); j++){
            row.append(other.board[i][j]);
        }
        board.append(row);
    }
}
return *this;

}

//For the agent, used to see if the person being checked is one off from winning
// bool GameState::closeToWin(int player) const{

// }

bool GameState::operator==(const GameState& other) const {
    //variables
    bool dimensionsMatch = (numRows == other.numRows) && (numCols == other.numCols);
    bool turnMatch = currentTurn == other.currentTurn;
    bool turnsElapsedMatch = elapsedTurns == other.elapsedTurns;
    bool aiStatusMatch = enabledAI == other.enabledAI;
    bool gameStatusMatch = done == other.done;
    bool lastMoveMatch = (lastMove.x == other.lastMove.x) && (lastMove.y == other.lastMove.y);
    
    //do they match, then we can return 
    if(!dimensionsMatch || !turnMatch || !turnsElapsedMatch || !aiStatusMatch || !gameStatusMatch || !lastMoveMatch){
        return false;
    }

    //checking board contents
    for (int row = 0; row < numRows; row++){
        for(int col = 0; col < numCols; col++){
            if (board[row][col] != other.board[row][col]){
                return false;
            }
        }
    }
    return true;
}


//check if a player has won
bool GameState::hasWon(int player) const{
    // cout <<"Checking whether player " <<player << " has won" <<endl;

    //horizontal check

    for (int row= 0; row < numRows; row++){
        for (int col = 0; col <= numCols - 4; col++){
            if (board[row][col] == player 
            && board[row][col + 1] == player //does the same four positions belong to the same player?
            && board[row][col + 2] == player 
            && board[row][col + 3] == player) {
                return true;
            }
        }
    }

    //Vertical check 
    for (int col = 0; col < numCols; col++){
        for (int row = 0; row <= numRows - 4; row++){
            if (board[row][col] == player 
            && board[row + 1][col] == player &&
            board[row + 2][col] == player &&
            board[row + 3][col] == player){
                return true;
                
            }
        }
    }

    //Diagonal (bottom-left to top-right)
    for (int row = 3; row < numRows; row++){
        for(int col = 0; col <= numCols - 4; col++){
            if (board[row][col]== player &&
            board[row-1][col+1]== player &&
            board[row-2][col+2]== player &&
            board[row-3][col+3]== player){
            return true;
            }
        }
    }

    //Diagonal (top-left to bottom-right)
    for(int row = 0; row <= numRows - 4; row++){
        for (int col = 0; col <= numCols - 4; col++){
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
    // cout << "Current player makes move " << col << endl;
    // cout << "Must update state, including whose turn it is" << endl; 
    // cout << "and the last move, among other things." << endl;

    // if( col<0 || col >= numCols || isFull() ||gameOver()){
    //     return false;
    // }
    if(!hasSpace(col)) {
        return false;
    }

    //Find the first empty row in the column
    for(int row = numRows - 1; row >= 0; row--){
        if (board[row][col]== -1){
            board[row][col] = currentTurn;
            lastMove.set(row, col);
            elapsedTurns++;

            if (hasWon(currentTurn)) {
                done = true;
            }
            else if (isFull()){
                done = true;
            }
            currentTurn = !currentTurn;
            return true;
        }
    }

    return false; //column is full
}

//tells if no more moves can be made (helps detect a draw)
 bool GameState::isFull() const{
    for (int col = 0; col < numCols; col++){
        if (board[0][col]== -1){
            return false;
        }
    }
    return true;
 }

 int GameState::getLeastFilledRow() const {
    
    int pos = 0;
    int fill = 0;
    int subtractAmount = 0;

    //Intentional integer division if needed
    int center = numRows / 2;

    for(int i = 0; i < numCols; i++){
        int fillForRow = 0;
        for(int j = 0; j < numRows; j++){
            if(board[j][i] == -1){
                fillForRow++;
            } else {
                j = numRows;
            }
        }
        //std::cout << fillForRow << "in col" << i << std::endl;

        if(fillForRow > fill){
            fill = fillForRow;
            pos = i;
        } else if(fillForRow == fill){
            if(i <= center){
                pos = i;
            } else if(i > center){
                //std::cout << "Greater than center" << std::endl;
                int distanceCurrent = abs(pos - center);
                int distancePotential = abs(i - center);

                //std::cout << "Current distance" << distanceCurrent << std::endl;
                //std::cout << "Potential new distance" << distancePotential << std::endl;

                
                if(distancePotential < distanceCurrent){
                    fill = fillForRow;
                    pos = i - subtractAmount;
                    //std::cout << "Update, removing" << subtractAmount << " from " << i << std::endl;
                }


            }
        } 
        if(fillForRow == 0){
            subtractAmount++;
        }
    }
    //std::cout << "Row which is returned: " << pos << std::endl;
    return pos;
 }


 bool GameState::gameOver() const {
    return hasWon(0) || hasWon(1) || isFull();
 }

 bool GameState::hasSpace(int col) const {
    return board[0][col] == -1;
}


int GameState::getCurrentTurn() const {
    return currentTurn;
 }

 int GameState::getCols() const {
    return numCols;
}


int GameState::getRows() const {
    return numRows;
}


int GameState::getElapsedTurns() const {
    return elapsedTurns;
}


 int GameState::getSize() const {
    return numRows * numCols;
 }

 int GameState::buttonState(int row, int col) const{
    if (row < 0 || row >= numRows || col < 0 || col >= numCols){
        return -1; //out of bounds positions return -1
    }
    return board[row][col]; //returns -1 (empty), 0 (player 0), or 1 (player 1)
 }

 Vec GameState::getBoardDimensions() const{
    return Vec(numRows, numCols);
 }



Vec GameState::getLastMove() const {
    return lastMove;
}


void GameState::enableAI(){
    enabledAI = true;
}

void GameState::disableAI(){
    enabledAI = false;
}

void GameState:: resize(int newRows, int newCols){
    if(newRows == numRows && newCols == numCols) return; //no change needed
    
    //clear current board
    while(board.size() > 0) {
        board.removeLast();
    }

    //update dimensions
    numRows = newRows;
    numCols = newCols;

    //Initialize new board
    for(int i = 0; i < numRows; i++){
        ArrayList<int> row;
        for (int j = 0; j<numCols; j++){
            row.append(-1); //fill with empty cells
        }
        board.append(row);
    }

    //Reset game state
    // reset(); 
    // extra comment
    
}

void GameState::reset(){
    currentTurn = 0;
    elapsedTurns = 0;
    done = false;
    lastMove.set(-1, -1);
    

    //Clear and reinitialize the board with -1 (empty)
    while (board.size() > 0){
        board.removeLast();
    }

    for (int i = 0; i < numRows; i++){
        ArrayList<int> row;
        for (int j = 0; j < numCols; j++){
            row.append(-1);
        }
        board.append(row);
    }
}

bool GameState::getEnabledAI() const{
    return enabledAI;
}

std::string GameState::squareState(int row, int col) const {
     int state = buttonState(row, col); //Reuse buttonState's bounds checking

    if (state == -1){
        if(row < 0 || row >= numRows || col < 0 || col >= numCols){
            return "invalid"; //position is out of bounds
        }
        return "empty"; //position is valid but empty
    }
    return(state == 0) ? "red" : "yellow"; //player 0 is red, player 1 is yellow   
}

char GameState::squareStateChar(int row, int col) const {
    int state = buttonState(row, col);

    if(state == -1){
        if (row < 0 || row >= numRows || col < 0 || col >= numCols){
            return '?'; //invalid position
        }
        return '.'; //empty position
    }
    return (state == 0) ? 'R' : 'Y'; //player 0 is R and, player 1 is y
    
}

void GameState::forceOpponentSimulation(int col) {
    currentTurn = !currentTurn;
    play(col);
}
