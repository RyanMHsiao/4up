# 4up documentation
## Rules
Our game has the same rules as the original game of Connect 4. Players take turns choosing columns to put game pieces into. Pieces fall into the lowest unoccupied space in the column, and each column has a limit to the number of pieces it can contain. The first player to have 4 consecutive pieces of their color in a horizontal, vertical, or diagonal line wins. If all the spaces are filled without either player winning, the game ends in a tie.
## Interface description
Upon running our program, you will see a new game with 6 rows and 7 columns playing against the AI. You can start play by clicking on any space. Clicking on a space will drop a piece of your color into that column. When playing against the AI, the AI will think for a few seconds and then respond. If you try to play in a column that is already full, nothing will happen. You can take turns placing pieces until either someone wins or the game ends upon a tie. After the game, a dialog will appear to give you the option to start again.

You can change the settings of the game using the settings menu. To open the settings menu, press the file button in the top left and select settings. Choose the settings you want from the drop-downs, and press apply. This will start a new game with your chosen settings.
## Important implementation details
The GameState itself is mostly original code written by us, representing the board as a 2D array of `int`s. We put a heavy emphasis on using functions to abstract the details from our GameState away and make it easy to change the exact implementation details if needed.

The GameInterface and SettingsInterface code are based on the code from lecture 24, with changes made to reflect the different GameState object that we have implemented. 

The AI works similarly to the original tic-tac-toe AI explained in lecture, but we had to make it more advanced because it is very computationally expensive to test all the possible choices in this game. Our AI tries to make lines of pieces and tries to prevent the human player from winning. It also uses a heuristic in order to try and make moves that take more control of the board, which does not exactly follow mini-max but was approved.
## List of contributions by member
Freysell wrote most of the GameState code, including both the basic methods for changing the state and more complicated methods to help assess the game state.

Alexia adapted the code for the interfaces to work with our project, solving some problems we ran into with the visuals not updating as expected.

Sathya - Worked on implementing the agent such that it correctly tracks the score. Some of the features I implemented to improve the competitiveness of the AI was have it track how many turns ( up to 6 ) it is from either a win or loss, in order to prolong the game when it is close to losing, or take a win instantly. In addition, I implemented getLeastFilledRow() in Gamestate.cpp such that it acts as a heuristic function to break ties whenever the AI returns multiple columns which will result in a draw. The function's purpose it to gravitate towards columns which are less filled and towards the center, such that it does not end up always playing the column with the first free spot when starting on the left.

Ryan organized the project, writing plans for the game features and resolving issues related to git.