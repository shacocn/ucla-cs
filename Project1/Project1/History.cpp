#include "History.h"
#include "globals.h"
#include <iostream>

using namespace std;

// Constructor
History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
            m_grid[i][j] = '.';
    }
}

// Records a zombie's death at location (r, c) where (1, 1) is the upper left most position.
bool History::record(int r, int c)
{
    /* Check for in bounds. */
    if (r < 1 || r > m_rows || c < 1 || c > m_cols)
        return false;
    
    /* Exit if already reached max number of deaths. */;
    if (m_grid[r-1][c-1] == 'Z')
        return true;
    
    /* Check for case of first death. */
    if (m_grid[r-1][c-1] == '.')
    {
        m_grid[r-1][c-1] = 'A';
        return true;
    }
    
    /* Otherwise, simply increase the letter by incrementing by one. */
    m_grid[r-1][c-1]++;
    return true;
}

void History::display() const
{
    clearScreen();
    
    /* Populate the screen with corresponding chars. */
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
            cout << m_grid[i][j];
        cout << endl;
    }
    cout << endl;
}
