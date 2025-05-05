# 4up documentation
## Rules
Our game has the same rules as the original game of Connect 4. Players take turns choosing columns to put game pieces into. Pieces fall into the lowest unoccupied space in the column, and each column has a limit to the number of pieces it can contain. The first player to have 4 consecutive pieces of their color in a horizontal, vertical, or diagonal line wins. If all the spaces are filled without either player winning, the game ends in a tie.
## Interface description
The settings interface is not yet implemented.

To play the game, simply click on a space in the column you would like to play in. The AI will automatically respond to your move, and you can play until somebody wins or there are no possible moves remaining. When the game ends, a dialog will show up giving you the option to reset the game.
## Important implementation details
The GameState itself is mostly original code written by us, representing the board as a 2D array of `int`s. We put a heavy emphasis on using functions to abstract the details from our GameState away and make it easy to change the exact implementation details if needed.

The GameInterface and SettingsInterface code are based on the code from lecture 24, with changes made to reflect the different GameState object that we have implemented. 

The AI works similarly to the original tic-tac-toe AI explained in lecture, but we had to make it more advanced because it is very computationally expensive to test all the possible choices in this game. Our AI tries to make lines of pieces and tries to prevent the human player from winning.
## List of contributions by member
Freysell wrote most of the GameState code, including both the basic methods for changing the state and more complicated methods to help assess the game state.
Alexia adapted the code for the interfaces to work with our project, solving some problems we ran into with the visuals not updating as expected.
Sathya wrote the code for the AI, writing code to evaluate the position and respond properly to threats.
Ryan organized the project, writing plans for the game features and resolving issues related to git.