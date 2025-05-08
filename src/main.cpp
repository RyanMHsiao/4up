#include <GameState.h>
#include <Application.h>
#include <Agent.h>
#include <cassert>

using namespace std;

int main(){



    // The logic related to app.run is complicated and hidden to us
    // So we instead just use our own functions for this phase of testing
    Application app;
    app.prepareGraphics();
    return app.run();



    

//     // GameState state;
//     // state.play(0, 0);
//     // state.play(1, 1);
//     // state.play(2, 2);
//     // state.play(2, 0);

//     // Agent::play(state);


//     // std::cout << state << endl;


//     // cout << Agent::play(state) << endl;

//     testGameStatePrinting();

    


}




// void testConstructors() {
//     cout << "=== Testing Constructors ===" << endl;
    
//     // Default constructor
//     GameState defaultGame;
//     assert(defaultGame.getRows() == 6);
//     assert(defaultGame.getCols() == 7);
//     assert(defaultGame.getCurrentTurn() == 0);
//     cout << "Default constructor test passed." << endl;

//     // Custom size constructor
//     GameState customGame(8, 9);
//     assert(customGame.getRows() == 8);
//     assert(customGame.getCols() == 9);
//     cout << "Custom constructor test passed." << endl;
// }

// void testCopyOperations() {
//     cout << "\n=== Testing Copy Operations ===" << endl;
    
//     GameState original;
//     original.play(3);
//     original.play(2);
    
//     // Copy constructor
//     GameState copyConstructed(original);
//     assert(original == copyConstructed);
//     cout << "Copy constructor test passed." << endl;
    
//     // Assignment operator
//     GameState assigned;
//     assigned = original;
//     assert(original == assigned);
//     cout << "Assignment operator test passed." << endl;
// }

// void testEqualityOperator() {
//     cout << "\n=== Testing Equality Operator ===" << endl;
    
//     GameState game1, game2;
//     assert(game1 == game2);
    
//     game1.play(3);
//     assert(!(game1 == game2));
    
//     game2.play(3);
//     assert(game1 == game2);
    
//     cout << "Equality operator test passed." << endl;
// }

// void testGamePlay() {
//     cout << "\n=== Testing Game Play ===" << endl;
    
//     GameState game;
    
//     // Test invalid moves
//     assert(!game.play(-1));  // Column too low
//     assert(!game.play(7));   // Column too high
//     cout << "Invalid move test passed." << endl;
    
//     // Test valid moves
//     assert(game.play(3));
//     assert(game.getLastMove().x == 5 && game.getLastMove().y == 3);
//     assert(game.getCurrentTurn() == 1);
//     cout << "Valid move test passed." << endl;
    
//     // Test column filling
//     for (int i = 0; i < 5; i++) {  // Fill column 3
//         game.play(3);
//     }
//     assert(!game.play(3));  // Column should be full
//     cout << "Column filling test passed." << endl;
// }

// void testWinConditions() {
//     cout << "\n=== Testing Win Conditions ===" << endl;
    
//     // Test horizontal win
//     GameState horizontal;
//     for (int col = 0; col < 4; col++) {
//         horizontal.play(col);  // Player 0
//         if (col < 3) horizontal.play(col);  // Player 1
//     }
//     assert(horizontal.hasWon(0));
//     cout << "Horizontal win test passed." << endl;
    
//     // Test vertical win
//     GameState vertical;
//     for (int i = 0; i < 4; i++) {
//         vertical.play(0);  // Player 0
//         if (i < 3) vertical.play(1);  // Player 1
//     }
//     assert(vertical.hasWon(0));
//     cout << "Vertical win test passed." << endl;
    
//     // Test diagonal win
//     GameState diagonal;
//     // Setup diagonal pattern
//     diagonal.play(0);  // P0
//     diagonal.play(1);  // P1
//     diagonal.play(1);  // P0
//     diagonal.play(2);  // P1
//     diagonal.play(2);  // P0
//     diagonal.play(3);  // P1
//     diagonal.play(2);  // P0
//     diagonal.play(3);  // P1
//     diagonal.play(3);  // P0
//     diagonal.play(4);  // P1
//     diagonal.play(3);  // P0 (wins)
//     assert(diagonal.hasWon(0));
//     cout << "Diagonal win test passed." << endl;
// }

// void testGameStateFunctions() {
//     cout << "\n=== Testing Game State Functions ===" << endl;
    
//     GameState game;
    
//     // Test squareState
//     assert(game.squareState(5, 3) == "empty");
//     game.play(3);
//     assert(game.squareState(5, 3) == "red");
//     assert(game.squareState(-1, 0) == "invalid");
//     cout << "squareState test passed." << endl;
    
//     // Test squareStateChar
//     assert(game.squareStateChar(5, 3) == 'R');
//     assert(game.squareStateChar(0, 0) == '.');
//     assert(game.squareStateChar(-1, 0) == '?');
//     cout << "squareStateChar test passed." << endl;
    
//     // Test isFull
//     assert(!game.isFull());
//     cout << "isFull (false) test passed." << endl;
    
//     // Test gameOver
//     assert(!game.gameOver());
//     cout << "gameOver (false) test passed." << endl;
// }

// void testReset() {
//     cout << "\n=== Testing Reset ===" << endl;
    
//     GameState game;
//     game.play(0);
//     game.play(1);
//     game.reset();
    
//     assert(game.getCurrentTurn() == 0);
//     assert(game.squareState(5, 0) == "empty");
//     assert(game.squareState(5, 1) == "empty");
//     cout << "Reset test passed." << endl;
// }

// void testFullGame() {
//     cout << "\n=== Testing Full Board ===" << endl;
    
//     GameState game;
//     // Alternate filling columns
//     for (int col = 0; col < game.getCols(); col++) {
//         for (int row = 0; row < game.getRows(); row++) {
//             game.play(col);
//         }
//     }
    
//     assert(game.isFull());
//     assert(game.gameOver());
//     cout << "Full board test passed." << endl;
// }

// void visualizeGame() {
//     cout << "\n=== Visual Game Test ===" << endl;
//     GameState game;
    
//     cout << "Initial board:" << endl;
//     cout << game << endl;
    
//     cout << "Playing moves 3, 3, 4, 4:" << endl;
//     game.play(3);
//     game.play(3);
//     game.play(4);
//     game.play(4);
//     cout << game << endl;
    
//     cout << "Visual verification - should show:" << endl;
//     cout << "- R at (5,3) and (4,3)" << endl;
//     cout << "- Y at (5,4) and (4,4)" << endl;
// }

// int main() {
//     try {
//         testConstructors();
//         testCopyOperations();
//         testEqualityOperator();
//         testGamePlay();
//         testWinConditions();
//         testGameStateFunctions();
//         testReset();
//         testFullGame();
//         visualizeGame();
        
//         cout << "\n=== ALL TESTS PASSED ===" << endl;
//     } catch (const exception& e) {
//         cerr << "Test failed: " << e.what() << endl;
//         return 1;
//     }
    
//     return 0;
// }

/*
int main() {
    try {
        testConstructors();
        testCopyOperations();
        testEqualityOperator();
        testGamePlay();
        testWinConditions();
        testGameStateFunctions();
        testReset();
        testFullGame();
        visualizeGame();
        
        cout << "\n=== ALL TESTS PASSED ===" << endl;
    } catch (const exception& e) {
        cerr << "Test failed: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
*/

