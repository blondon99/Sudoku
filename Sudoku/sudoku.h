//
//  sudoku.h
//  Sudoku
//
//  Created by Brian London on 5/10/15.
//  Copyright (c) 2015 Brian London. All rights reserved.
//
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#ifndef Sudoku_sudoku_h
#define Sudoku_sudoku_h
class sudoku
{
public:
    sudoku(string file);
    int solve();
    void output(string file, bool results);
    void checksolution();
protected:
    vector <string> grid;
    int numTurns;
    int recurse(int r, int c);
    int validRow(int r);
    int validCol(int c);
    int validPanel(int r, int c);
};

#endif
