#ifndef C2048_H
#define C2048_H

#include <time.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <vector>

typedef unsigned int uint;
using namespace std;

enum movDir { UP, DOWN, LEFT, RIGHT };
class tile
{
public:
    tile() : val( 0 ), blocked( false ) {}
    uint val;
    bool blocked;
};

class g2048{

public:
  g2048();
  void loop();
  //Was private past this point

  /** Returns the 2048 board as a vector
  @return vector of integers
  */
  vector<double> toVector();
  /**converts the board vector to values from 0-1 for the neural net to use as inputs
  @return vector of values 0 to 1
  */
  vector<double> toInput();
  /**draws the 2048 game board
  */
  void drawBoard();
  /**randomly moves the board
  */
  void randMove();
  /**moves the board with input from the Neural Net
  @param vector<double> output representing the output of the Neural Net
  */
  void netMove(vector<double> output);
  /** Determines the board move from keyboard input
  */
  void waitKey();
  /**Initializes the 2048 board
  */
  void addTile();
  /**determines if a board tile can move
  */
  bool canMove();
  /**Tests if a move is legal
  @return boolean
  */
  bool testAdd(int,int,uint);
  /**moves the boad tiles vertically
  @param int x
  @param int y
  @param unsigned int d
  */
  void moveVert(int,int,int);
  /**moves the boad tiles horizontally
  @param int x
  @param int y
  @param int d
  */
  void moveHori(int,int,int);
  /**moves the board
  @param movDir d
  */
  void move(movDir);
  tile board[4][4];
  bool win, done, moved;
  uint score;
};

#endif
