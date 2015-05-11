//
//  sudoku.cpp
//  Sudoku
//
//  Created by Brian London on 5/10/15.
//  Copyright (c) 2015 Brian London. All rights reserved.
//
#include "sudoku.h"


sudoku::sudoku(string file)
{
    //initialize everything, read the sudoku and check validity
    char c;
    int i, j;
    
    numTurns = 0;
    grid.resize(9);
    
    ifstream inputfile(file);
    
    if(inputfile.is_open())
    {
        for(i = 0; i < 9; i++)
        {
            for(j = 0; j < 9; j++)
            {
                if(!(inputfile >> c))
                {
                    cerr << "not enough entries";
                    exit(1);
                }
                if((c == 'x')||(('0' <= c) && (c <= '9')))
                {
                    grid[i].push_back(c);
                }
                else
                {
                    cerr << "invalid character";
                    exit(1);
                }
            }
        }
    }
    else
    {
        cerr << "couldn't open " << file;
        exit(0);
    }
    
    //validate the rows and columns
    for (i = 0; i < 9; i++)
    {
        if(!validCol(i))
        {
            cerr << "column " << i+1 << " is invalid." << endl;
            exit(1);
        }
    
        if(!validRow(i))
        {
            cerr << "row " << i+1 << " is invalid." << endl;
            exit(1);
        }
    }
    
    //validate the panels
    for (i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if(!validPanel(i*3,j*3))
            {
                cerr << "panel invalid at position " << i*3 << j*3 << endl;
                exit(1);
            }
        }
    }
}

void sudoku::output(string file, bool results)
{
    int i, j;
    ofstream outfile;
    
    if(file == "")
    {
        for (i = 0; i < grid.size(); i++)
        {
            for (j = 0; j < grid[i].size(); j++)
            {
                cout << grid[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "---------------------" << endl;
    }
    else
    {
        string heading = "";
        
        if(results)//only append if this is the results.  so we can print both puzzle and results
        {
            outfile.open(file, ofstream::out|ofstream::app);
            heading = "Puzzle Solution: \n";
        }
        else
        {
            outfile.open(file, ofstream::out);
            heading = "Puzzle Input: \n";
        }
        
        if(outfile.is_open())
        {
            outfile << heading;
            
            for (i = 0; i < grid.size(); i++)
            {
                if(!(i % 3))
                {
                    outfile << " --------------------" << endl;
                }
                for (j = 0; j < grid[i].size(); j++)
                {
                    if(!(j % 3))
                    {
                        outfile << "|";
                    }
                    outfile << grid[i][j] << " ";
                }
                outfile << "|\n";
            }
            outfile << " --------------------" << endl;
            if(results)
            {
                outfile << " Solved in " << numTurns << " turns" << endl;
            }
            outfile.close();
        }
        else
        {
            cerr << "unable to open output file: " << file << endl;
        }
    }
}

int sudoku::validRow(int r)
{
    int i;
    int check[10] = {0,0,0,0,0,0,0,0,0,0};
    
    for(i = 0; i < 9; i++)
    {
        if(grid[r][i] != 'x')
        {
            if(check[grid[r][i]-'0'] == 1)
            {
                return 0;
            }
            else
            {
                check[grid[r][i]-'0'] = 1;
            }
        }
    }
    return 1;
}

int sudoku::validCol(int c)
{
    int i;
    int check[10] = {0,0,0,0,0,0,0,0,0,0};
    
    for(i = 0; i < 9; i++)
    {
        if(grid[i][c] != 'x')
        {
            if(check[grid[i][c]-'0'] == 1)
            {
                return 0;
            }
            else
            {
                check[grid[i][c]-'0'] = 1;
            }
        }
    }
    return 1;
}

int sudoku::validPanel(int r, int c)
{
    int i, j;
    int sr,sc;
    int check[10] = {0,0,0,0,0,0,0,0,0,0};
    
    sr = r - r % 3; //find the starting row and column of the current panel
    sc = c - c % 3;
    
    for(i = sr; i < (sr + 3); i++)
    {
        for(j = sc; j < (sc + 3); j++)
        {
            if(grid[i][j] != 'x')
            {
                if(check[grid[i][j]-'0'] == 1)
                {
                    return 0;
                }
                else
                {
                    check[grid[i][j]-'0'] = 1;
                }
            }
        }
    }
    return 1;
}

int sudoku::solve()
{
    return recurse(0,0);
}

int sudoku::recurse(int r, int c)
{
    numTurns ++;
    
    //skip ahead to the next 'x'
    while ((r < 9) && (grid[r][c] != 'x'))
    {
        c++;
        if(c == 9)
        {
            c = 0;
            r++;
        }
    }
    if (r == 9)
    {
        return 1;//if we got this far, we have solved the puzzle
    }
    
    //try every possible number, if this one works, recurse to the next one
    for(int i = '1'; i <= '9'; i++)
    {
        grid[r][c] = i;
        if((validRow(r) &&
            (validCol(c) &&
             (validPanel(r,c) &&
              (recurse(r,c))))))
        {
            return 1;
        }
    }
    
    //if we get here, the solution didn't work.  Reset the cell and exit
    grid[r][c] = 'x';
    return 0;
}

void sudoku::checksolution()
{
    int i,j;
    
    for (i = 0; i < 9; i++)
    {
        if(!validCol(i))
        {
            cerr << "column " << i+1 << " is invalid." << endl;
            exit(1);
        }
    }
    cout << "all columns valid" << endl;
    
    for (i = 0; i < 9; i++)
    {
        if(!validRow(i))
        {
            cerr << "row " << i+1 << " is invalid." << endl;
            exit(1);
        }
    }
    cout << "all rows valid" << endl;
    
    for (i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if(!validPanel(i*3,j*3))
            {
                cerr << "panel invalid at position " << i*3 << j*3 << endl;
                exit(1);
            }
        }
    }
    
    cout << "all panels valid" << endl;
}