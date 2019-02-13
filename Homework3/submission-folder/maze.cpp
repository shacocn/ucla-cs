class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

/* Determines if a solution exists based on recursion. */
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    /* If the start location is equal to ending location, maze is solved, so return true. */
    if (sr == er && sc == ec)
        return true;
    else
    {
        /* Mark the start location as visited. */
        maze[sr][sc] = '*';
        
        /* Check for solution in each direction. */
        if (maze[sr+1][sc] != 'X' && maze[sr+1][sc] != '*')
        {
            if(pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
                return true; // solution found!
        }
        if (maze[sr-1][sc] != 'X' && maze[sr-1][sc] != '*')
        {
            if(pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
                return true; // solution found!
        }
        if (maze[sr][sc-1] != 'X' && maze[sr][sc-1] != '*')
        {
            if(pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
                return true; // solution found!
        }
        if (maze[sr][sc+1] != 'X' && maze[sr][sc+1] != '*')
        {
            if(pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
                return true; // solution found!
        }
    }
    return false; // no solution found.
}
