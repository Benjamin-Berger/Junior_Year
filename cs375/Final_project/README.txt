Java
PlayGame

This program can be run to play once or run through many times with minimal output. (The first prompt, type 0 for 1 game with output or however many games youd like to simulate)

The players are currently, random -1, copy -2, and MCTS 1.
Random is a random player.
Copy copies the last move or random (only different from random in connect four)
MCTS Monte Carlo Tree Search. Parameters: time for each move (in tenths of seconds) and playouts (# of random playouts per simulation phase)

The program will solve Tic-Tac-Toe and its pretty tough to beat in connect four and dots & boxes as a human.

The controls for tic tac toe are the same as a phone dial pad.

The controls for connect for are 0-6 and are printed above the columns.

The controls for dots & boxes are horrible, very tedious to play as a human. The top left horizontal line is 1. Going to the right, each horizontal line is in order up to  4. Then the vertical lines are counted starting with the top left vertical line being 5. The lines contine in this pattern until the bottom right horizontal line at 40.


The changes made in the program had nothing to do with the MCTS logic. The problem in Dots & Boxes occurred when a player went multiple times in a row. The other player didn't get an update on any of the moves except the last, so it was playing on an incorrect version of the board. A  change in MCTSPPLayer class fixed that. We also made changes in the UI and allowed a parameter to be changed without changing the source and re-compiling (which was originally the intended method for testing).We changed the parameter from rounds to time (which makes more sense and makes it easier to get data).

All of the data that is obtainable from this submission is obtainable from the original submission (besides the Dots&Boxes bug). Many changes have been made in the ui to make it easier to obtain the data. We are planning on adding a gui to play each game for the demo in the presentation.