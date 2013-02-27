battleships-c
=============

Battleships game in C

A simple command line implementation of the popular game. Includes 1 and 2 player modes.

The display of the game is very simple. It first asks you to play your ships. Once done you are then asked for the coordinates on the board where you would like to move. Once entered it prints the opposing players game board so that you are aware of where you have already been.

In 1 player mode versus the computer AI realises when it has hit a ship and exhausts all possiblites around that particular area. This makes him a serious competitor.

You can use the make command to compile the program. Or you can use: gcc -std=c99 battleships.c battleships_functions.c battleships_structs.h constants.h -o battleships
