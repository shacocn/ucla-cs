#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include "SmartZombie.h"
#include "DumbZombie.h"
#include "Penelope.h"
#include "Pit.h"
#include "Wall.h"
#include "Citizen.h"
#include "VaccineGoodie.h"
#include "GasCanGoodie.h"
#include "LandmineGoodie.h"
#include "Exit.h"

#include <string>
#include <sstream>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), numCitizensLeft(0), wonGame(false), finishedLevel(false)
{
}

/*
 level data file:
 1. # - wall
 - perimeter must be a wall
 2. @ - starting location of penelope
 - restart location too
 3. C - citizen
 4. O - pit
 5. V - vaccine goodie
 6. G - gas
 7. L - landmine
 8. X - exits
 9. D - dumb zombie
 10. S - smart zombie
 11. space - places you can walk
 
 16 x 16 layout
 each object is SPRITE_WIDTH wide and SPRITE_HEIGHT tall (16px by 16px)
 measured by bottom left corner
 
 NOTE: LEVEL DATA FILE IS PROVIDED!
 
 Hint: You will likely want to use our Level class to load the current level specification in your StudentWorld class’s init() method. The assetPath() and getLevel() methods that your StudentWorld class inherits from GameWorld might also be useful, along with the Stringstreams writeup on the class web site!
 
 void StudentWorld::someFunc()
 
 1. initialize the data structures used to keep track of game's world
 2. allocate and insert penelope object into game world as specified in the current level's data file
 -    penelope can have an actor pointer not stored in container
 3. allocate and insert all objects in game world as specified in current level's data file
 - must all be stored as pointers in ONE stl container
 
 */




int StudentWorld::init()
{
    /* Set up and try opening the file. */
    Level lev(assetPath());
    ostringstream levelTitle;
    levelTitle << "level0" << getLevel() << ".txt";
    string levelFile = levelTitle.str();
    Level::LoadResult result = lev.loadLevel(levelFile);
    
    /* Check for errors. */
    if (result == Level::load_fail_file_not_found)
        wonGame = true;
    else if (result == Level::load_fail_bad_format)
        exit(1); // error!
    
    /* If no errors, load file. */
    else if (result == Level::load_success)
    {
        /* Iterate through each location in the file. */
        for (int level_x = 0; level_x < SPRITE_WIDTH; level_x++)
        {
            for (int level_y = 0; level_y < SPRITE_HEIGHT; level_y++)
            {
                /* If an object exists, add that object and its location to the data structure. */
                Level::MazeEntry loc = lev.getContentsOf(level_x, level_y);
                addActorToList(level_x, level_y, loc);
            }
        }
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    /*
     1. must ask actors that are currently alive in the game world to doSomething()
            - if actors does something that kills penelope, then return GWSTATUS_PLAYER_DIED immediately
                    - restart the level if more lives left or end the game if she's out of lives
                    - prompt player to continue the game
                    - call cleanup() method
                    - call init() to re-initialize
                    - call move() over and over, once per tick, to play the level again
            - if all citizens and penelope have used exit and time to advance to next level, return GWSTATUS_FINISHED_LEVEL
                    - call cleanup() to destroy level
                    - call init() to prepare for next level (if exists) for play
     2. if that does not happen, then delete actors that died during tick and remove from collection of actors
     3. update status text on screen with latest information
     4. must return GWSTATUS_CONTINUE_GAME if not one of the above
            - tick occurred without penny dying but level not complete; move to next tick and call move)_ again
     */
    
    
    // The term "actors" refers to all zombies, Penelope, goodies, // pits, flames, vomit, landmines, etc.
    // Give each actor a chance to do something, including Penelope for each of the actors in the game world
    // for each of the actors in the game world
//        {
//        if (0/* actor[i] is still alive */ ) {
//            // tell each actor to do something (e.g. move) actor[i]->doSomething();
//            if (0/* Penelope died during this tick */ )
//                return GWSTATUS_PLAYER_DIED;
//            if (0/* Penelope completed the current level*/)
//                return GWSTATUS_FINISHED_LEVEL;
//        }
//        }
    // Remove newly-dead actors after each tick Remove and delete dead game objects
    // Update the game status line
    // Update Display Text // update the score/lives/level text at screen top
    
    // the player hasn’t completed the current level and hasn’t died, so // continue playing the current level
    // return GWSTATUS_CONTINUE_GAME;
    
    /* Go through each of the actors in the GameWorld and have each one doSomething(). */
    list<Actor*>::iterator it = m_actors.begin();
    while (it != m_actors.end())
    {
        if ((*it)->isAlive())
        {
            m_penelope->doSomething();
            (*it)->doSomething();
            if (!m_penelope->isAlive())
                return GWSTATUS_PLAYER_DIED;
            if (finishedLevel)
                return GWSTATUS_FINISHED_LEVEL;
            it++;
        }
        else // dead, so remove
        {
            Actor *temp = *it;
            delete temp;
            it = m_actors.erase(it);
        }
    }
    
    // Update the game status line
    // Update Display Text // update the score/lives/level text at screen top
    
    // the player hasn’t completed the current level and hasn’t died, so // continue playing the current level
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    /*
     
     1. calling this function means that penelope lost a life or completed a level
     2. every actor must be deleted and removed
     3. init() will automatically be recalled
     4. do not call this yourself
     5. NOTE: if the player presses the q key, then make sure your destructor calls cleanUp() to make sure the game shuts down cleanly!
     6. make sure two consecutive calls to cleanup() don't do anything undefined
            - if cleanup() deletes an object and leaves a dangling pointer, don't call cleanup() again in a delete expression! in other words, check this condition
     */
    
    list<Actor*>::iterator it = m_actors.begin();
    while (it != m_actors.end())
    {
        Actor *temp = *it;
        delete temp;
        it = m_actors.erase(it);
    }
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

void StudentWorld::addActorToList(int x, int y, Level::MazeEntry loc)
{
    int gameX = x * SPRITE_HEIGHT; // x coordinate in terms of pixels
    int gameY = y * SPRITE_HEIGHT; // y coordinate in terms of pixels
    switch(loc)
    {
        case Level::player: // found penelope
            m_penelope = new Penelope(gameX, gameY, this);
            break;
        case Level::empty:
            break;
        case Level::smart_zombie:
            m_actors.push_back(new SmartZombie(gameX, gameY, this));
            break;
        case Level::dumb_zombie:
            m_actors.push_back(new DumbZombie(gameX, gameY, this));
            break;
        case Level::exit:
            m_actors.push_back(new Exit(gameX, gameY, this));
            break;
        case Level::wall:
            m_actors.push_back(new Wall(gameX, gameY, this));
            break;
        case Level::pit:
            m_actors.push_back(new Pit(gameX, gameY, this));
            break;
        case Level::citizen:
            m_actors.push_back(new Citizen(gameX, gameY, this));
            break;
        case Level::vaccine_goodie:
            m_actors.push_back(new VaccineGoodie(gameX, gameY, this));
            break;
        case Level::gas_can_goodie:
            m_actors.push_back(new GasCanGoodie(gameX, gameY, this));
            break;
        case Level::landmine_goodie:
            m_actors.push_back(new LandmineGoodie(gameX, gameY, this));
    }
}
