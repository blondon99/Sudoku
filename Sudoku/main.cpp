//
//  main.cpp
//  Sudoku
//
//  Created by Brian London on 5/10/15.
//  Copyright (c) 2015 Brian London. All rights reserved.
//

#include "sudoku.h"

int main(int argc, const char * argv[]) {
    sudoku *sud;
    string outfile = "/Users/Brian/Documents/Playground/sud_out.txt";
    string infile = "/Users/Brian/Documents/Playground/worldshardestsudoku.txt";
    
    sud = new sudoku(infile);
    
    sud->output(outfile, false);
    
    if(sud->solve())
    {
        sud->output(outfile, true);
    }
    else
    {
        cout << "Failed!" << endl;
    }
    return 0;
}
