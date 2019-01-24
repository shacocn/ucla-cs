#ifndef globals_h
#define globals_h

const int MAXROWS = 20;              // max rows in the arena
const int MAXCOLS = 30;              // max columns in the arena
const int MAXZOMBIES = 150;          // max zombies allowed
const int INITIAL_ZOMBIE_HEALTH = 2;

const int UP      = 0;
const int DOWN    = 1;
const int LEFT    = 2;
const int RIGHT   = 3;
const int NUMDIRS = 4;

int randInt(int min, int max);
void clearScreen();

#endif /* globals_h */
