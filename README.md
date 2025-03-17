Snake and Ladders Game (C++)

Overview

This project is a simple console-based Snake and Ladders game implemented in C++. The game allows two players to compete against each other by rolling dice and moving across a 100-cell board while avoiding snakes and taking advantage of ladders. The game supports two difficulty modes: Easy and Hard.

Features

Two-player mode: Players take turns rolling the dice to advance on the board.

Difficulty settings:

Easy Mode: Standard board with visible positions.

Hard Mode: Board positions are hidden, increasing difficulty.

Randomized Snakes: Snake heads and tails are generated dynamically.

Dice Rolling Simulation: Players roll a 6-sided die with fair or weighted probabilities.

Win Condition: The first player to reach position 100 wins the game.

How to Play

Run the program using a C++ compiler (e.g., g++):

g++ -o snakes_and_ladders game.cpp
./snakes_and_ladders

Choose a difficulty level:

Enter 1 for Hard Mode.

Enter 2 for Easy Mode.

Choose your symbols: Each player selects a unique character to represent their position.

Take turns rolling the dice: Press Enter when prompted to roll the dice.

Move across the board: The program updates player positions after each turn.

Watch out for snakes: If you land on a snake’s head, you will be moved down to its tail.

Win the game: The first player to reach exactly position 100 wins.

Dependencies

Standard C++ libraries (iostream, iomanip, vector, random, string)

Compatible with any C++11 or later compiler

Code Structure

Difficulty class: Handles the board setup and modifies positions based on difficulty.

displayBoard(): Prints the game board in the console.

player1rolling() & player2rolling(): Simulate dice rolling.

SnakeHeads(): Generates random snake positions.

TailDecrease(): Determines snake tails based on heads.

main(): Controls game flow, takes user input, and updates positions.

Future Enhancements

Add ladder functionality.

Improve board visualization.

Implement a graphical user interface (GUI).

Support for more players.

Author

Developed by Mobeen Akhtar. Feel free to contribute or suggest improvements!

License

This project is open-source under the MIT License.
