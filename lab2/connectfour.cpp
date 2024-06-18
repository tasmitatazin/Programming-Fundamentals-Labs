//
//  connectfour.cpp
//  Connect Four Game
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Modified by Salma Emara and Ethan Hugh on 2023-09-06
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: Complete the skeletal code of the main function in this file

#include <iostream>
#include <string>
using namespace std;

#include "GameState.h"
#include "globals.h"

// Function prototypes

// The main function
int main()
{
  /**********************************************************************************/
  /* Create three initialized game state objects in an array */
  /**********************************************************************************/
  const int numOfRounds = 3;
  GameState game_state[numOfRounds];

  // Read one integer from the user that represents the column
  // the player would like to place their piece (R or Y) in
  // You can assume there will be no formatting errors in the input

  int col;
  int round = 0;
  int rCount = 0;
  int yCount = 0;
  cout << "Game " << round + 1 << endl;
  while (!game_state[round].get_gameOver())
  {
    cout << "Enter column to place piece: ";
    cin >> col;

    if (cin.eof())
    {
      cerr << endl
           << "Game ended by user." << endl;
      exit(0);
    }
    if (cin.fail())
    {
      cin.clear();
      cin.ignore(1000, '\n');
      col = -1; // giving col invalid value so it will be handled as invalid input below
    }

    // Check validity of input and if not valid, handle accordingly
    if (col < 0 || col >= boardSize)
    {
      cout << "Invalid column! " << endl;
      continue;
    }
    else
    {
      if (game_state[round].get_gameBoard(boardSize - 1, col) != Empty)
      {
        cout << "Invalid column! " << endl;
        continue;
      }
      else
      {
        cout << "column chosen: " << col << endl;
      }
    }
    game_state[round].set_selectedColumn(col);
    int row = 0;
    while (game_state[round].get_gameBoard(row, col) != Empty)
    {
      row++;
    }
    game_state[round].set_selectedRow(row);

    playMove(game_state[round]);

    for (int i = 0; i < boardSize; i++)
    {
      for (int j = 0; j < boardSize; j++)
      {
        if (game_state[round].get_gameBoard(boardSize - i - 1, j) == R)
        {
          cout << "R";
        }
        else if (game_state[round].get_gameBoard(boardSize - i - 1, j) == Y)
        {
          cout << "Y";
        }
        else
        {
          cout << "_";
        }
      }
      cout << endl;
    }
    cout << endl;

    if (game_state[round].get_gameOver())
    {
      if (game_state[round].get_winner() == R)
      {
        cout << "R won this round!\n";
        rCount++;
        if (rCount == 2)
        {
          cout << "R won the match!\n\n";
          exit(0);
        }
      }
      else if (game_state[round].get_winner() == Y)
      {
        cout << "Y won this round!\n";
        yCount++;
        if (yCount == 2)
        {
          cout << "Y won the match!\n";
          exit(0);
        }
      }
      else
      {
        cout << "This round was a draw!\n";
      }
      round++;
      cout << "Game " << round + 1 << endl;
    }

    // The coordinates are valid; set the selectedRow and selectedColumn
    // members of the game state to the read values
    // Note that the corresponding mutators of GameState must be first
    // implemented before this works

    // Call playMove

    // Print the GameState object, as prescribed in the handout

    // Check if a player won this round and if so handle accordingly

    // Check if a player won this match and if so handle accordingly
  }
}
