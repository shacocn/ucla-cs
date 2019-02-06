#include <iostream>
#include <string>
#include <stack>
using namespace std;

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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    /* Create a stack and update start position. */
    stack<Coord> coordStack;
    Coord startPos(sr, sc);
    coordStack.push(startPos);
    maze[sr][sc] = 'O';
    /* While stack is not empty... */
    while (coordStack.size() != 0)
    {
        Coord current = coordStack.top(); // set current loc
        coordStack.pop(); // remove it from stack
        int r = current.r();
        int c = current.c();
        
        /* Check to see if you found the ending position. */
        if (r == er && c == ec)
            return true;
        
        /* Check all directions for possible move. */
        if (maze[r+1][c] != 'X' && maze[r+1][c] != 'O')
        { // south
            Coord newCoord(r+1, c);
            coordStack.push(newCoord);
            maze[r+1][c] = 'O';
        }
        if (maze[r][c-1] != 'X' && maze[r][c-1] != 'O')
        { // west
            Coord newCoord(r, c-1);
            coordStack.push(newCoord);
            maze[r][c-1] = 'O';
        }
        if (maze[r-1][c] != 'X' && maze[r-1][c] != 'O')
        { // north
            Coord newCoord(r-1, c);
            coordStack.push(newCoord);
            maze[r-1][c] = 'O';
        }
        if (maze[r][c+1] != 'X' && maze[r][c+1] != 'O')
        { // east
            Coord newCoord(r, c+1);
            coordStack.push(newCoord);
            maze[r][c+1] = 'O';
        }
    }
    return false; // no solution
}

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X....X...X",
        "X.XX.XX..X",
        "XXX....X.X",
        "X.XXX.XXXX",
        "X.X...X..X",
        "X...X.X..X",
        "XXXXX.X.XX",
        "X........X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 3,5, 8,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
