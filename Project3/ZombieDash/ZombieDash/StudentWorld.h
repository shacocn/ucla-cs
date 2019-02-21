#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include "Penelope.h"
#include "Level.h"
#include <string>
#include <list>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    /* Accessor functions. */
    int getNumCitizensLeft() const { return numCitizensLeft; };

private:
    /* Private data members. */
    std::list<Actor*> m_actors; // points to all actors on screen
    Penelope* m_penelope; // points to penelope
    int numCitizensLeft; // number of citizens alive
    
    /* Private member functions. */
    void addActorToList(int x, int y, Level::MazeEntry loc); // adds an actor to list at loc(x, y)
};

#endif // STUDENTWORLD_H_
