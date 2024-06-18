//
//  playMove.cpp
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
//  ECE244 Student: write your code for playMove in this file

#include "GameState.h"
#include "globals.h"

// Function prototypes (if you need)

void playMove(GameState &game_state)
{
  // Change turn if move is valid,
  // Change gameOver
  // Change winner
  int col = game_state.get_selectedColumn();
  int row = game_state.get_selectedRow();

  if (game_state.get_turn() == true)
  {
    game_state.set_gameBoard(row, col, R);
  }
  else
  {
    game_state.set_gameBoard(row, col, Y);
  }

  if (col >= 0 && col < boardSize && row >= 0 && row < boardSize)
  {
    game_state.set_moveValid(true);
  }
  else
  {
    game_state.set_moveValid(false);
  }

  game_state.set_gameOver(false);
  game_state.set_winner(Empty);

  int curr = game_state.get_turn() ? R : Y;

  for (int i = 0; i < boardSize; i++)
  {
    for (int j = 0; j < boardSize; j++)
    {
      if (game_state.get_gameBoard(i, j) == curr && game_state.get_gameBoard(i, j + 1) == curr && game_state.get_gameBoard(i, j + 2) == curr && game_state.get_gameBoard(i, j + 3) == curr)
      {
        game_state.set_gameOver(true);
        game_state.set_winner(curr);
      }
      else if (game_state.get_gameBoard(i, j) == curr && game_state.get_gameBoard(i + 1, j) == curr && game_state.get_gameBoard(i + 2, j) == curr && game_state.get_gameBoard(i + 3, j) == curr)
      {
        game_state.set_gameOver(true);
        game_state.set_winner(curr);
      }
      else if (game_state.get_gameBoard(i, j) == curr && game_state.get_gameBoard(i + 1, j + 1) == curr && game_state.get_gameBoard(i + 2, j + 2) == curr && game_state.get_gameBoard(i + 3, j + 3) == curr)
      {
        game_state.set_gameOver(true);
        game_state.set_winner(curr);
      }
      else if (game_state.get_gameBoard(i, j) == curr && game_state.get_gameBoard(i + 1, j - 1) == curr && game_state.get_gameBoard(i + 2, j - 2) == curr && game_state.get_gameBoard(i + 3, j - 3) == curr)
      {
        game_state.set_gameOver(true);
        game_state.set_winner(curr);
      }
    }
  }

  if (game_state.get_moveValid())
  {
    game_state.set_turn(!game_state.get_turn());
  }
}