#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include "Actor.h"

#include <string>
#include <sstream>
#include <cmath>
using namespace std;

//|||||||||||||||||||||||||||
//     BASIC FUNCTIONS
//|||||||||||||||||||||||||||
GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), m_numCitizensLeft(0), m_wonGame(false), m_finishedLevel(false), m_ticks(0) {
}

int StudentWorld::init()
{
    /* Initialize private variables. */
    m_numCitizensLeft = 0;
    m_wonGame = false;
    m_finishedLevel = false;
    m_ticks = 0;
    increaseScore(getScore() * -1);
    
    /* Set up and try opening the file. */
    Level lev(assetPath());
    ostringstream levelTitle;
    levelTitle << "level0" << getLevel() << ".txt";
    string levelFile = levelTitle.str();
    Level::LoadResult result = lev.loadLevel(levelFile);
    
    /* Check for errors. */
    if (result == Level::load_fail_file_not_found || getLevel() == 99)
        return GWSTATUS_PLAYER_WON;
    else if (result == Level::load_fail_bad_format)
        return GWSTATUS_LEVEL_ERROR; // error!
    
    /* If no errors, load file. */
    else if (result == Level::load_success)
        processFile(lev);
    
    /* Change the status bar and proceed. */
    updateStatusLine();
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    m_ticks++; // increment ticks
    list<Actor*>::iterator it = m_actors.begin();
    while (it != m_actors.end())
    {
        if (m_ticks % 2 == 0 && ((*it)->canTriggerCitizens() || (*it)->canBeInfected()))
            return GWSTATUS_CONTINUE_GAME;
        if ((*it)->alive())
        {
            (*it)->doSomething();
            activateOnAppropriateActors(*it);
            if (!m_penelope->alive())
                return GWSTATUS_PLAYER_DIED;
            if (m_finishedLevel)
            {
                playSound(SOUND_LEVEL_FINISHED);
                return GWSTATUS_FINISHED_LEVEL;
            }
            it++;
        }
        else // dead, so remove
        {
            Actor *temp = *it;
            delete temp;
            it = m_actors.erase(it);
        }
    }
    updateStatusLine();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    list<Actor*>::iterator it = m_actors.begin();
    while (it != m_actors.end())
    {
        if ((*it) != nullptr)
        {
            Actor *temp = *it;
            delete temp;
            it = m_actors.erase(it);
        }
    }
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

//||||||||||||||||||||||||||||||||||||
//     PRIVATE MEMBER FUNCTIONS
//||||||||||||||||||||||||||||||||||||
void StudentWorld::processFile(const Level lev)
{
    /* Iterate through each location in the file. */
    for (int level_x = 0; level_x < SPRITE_WIDTH; level_x++)
    {
        for (int level_y = 0; level_y < SPRITE_WIDTH; level_y++)
        {
            /* If an object exists, add that object and its location to the data structure. */
            Level::MazeEntry loc = lev.getContentsOf(level_x, level_y);
            addActorToList(level_x, level_y, loc);
        }
    }
}

void StudentWorld::addActorToList(int x, int y, Level::MazeEntry loc)
{
    int gameX = x * SPRITE_HEIGHT; // x coordinate in terms of pixels
    int gameY = y * SPRITE_HEIGHT; // y coordinate in terms of pixels
    
    switch(loc)
    {
        case Level::empty:
            break;
        case Level::player: // found penelope
            m_penelope = new Penelope(gameX, gameY, this);
            m_actors.push_back(m_penelope);
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
            m_numCitizensLeft++;
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

void StudentWorld::updateStatusLine()
{
    /* Score: 004500  Level: 27  Lives: 3  Vaccines: 2  Flames: 16  Mines: 1  Infected: 0 */
    ostringstream oss;
    oss << "Score: " << getScore() << "  Level: " << getLevel() << "  Lives: " << getLives() << "  Vaccines: " << m_penelope->numVaccines() << "  Flames: " << m_penelope->numFlameCharges() << "  Mines: " << m_penelope->numLandminesHeld() << "  Infected: " << m_penelope->infectionCount();
    string s = oss.str();
    setGameStatText(s);
}


//|||||||||||||||||||||||||||||
//     MUTATOR FUNCTIONS
//|||||||||||||||||||||||||||||
bool StudentWorld::overlaps(double x1, double y1, double x2, double y2) const
{
    return (distanceBetween(x1, y1, x2, y2) <= 10);
}

double StudentWorld::distanceBetween(double x1, double y1, double x2, double y2) const
{
    double thisCenterX = x1 + (SPRITE_WIDTH / 2.0);
    double thisCenterY = y1 + (SPRITE_WIDTH / 2.0);
    double otherCenterX = x2 + (SPRITE_WIDTH / 2.0);
    double otherCenterY = y2 + (SPRITE_WIDTH / 2.0);
    double deltaX = otherCenterX - thisCenterX;
    double deltaY = otherCenterY - thisCenterY;
    return (sqrt(deltaX*deltaX + deltaY*deltaY));
}

// Add an actor to the world.
void StudentWorld::addActor(Actor* a)
{
    m_actors.push_back(a);
}

// Record that one more citizen on the current level is gone (exited,
// died, or turned into a zombie).
void StudentWorld::recordCitizenGone()
{
    m_numCitizensLeft--;
}

// For each actor overlapping a, activate a if appropriate.
void StudentWorld::activateOnAppropriateActors(Actor* a)
{
    for (list<Actor*>::iterator it = m_actors.begin(); it != m_actors.end(); it++)
    {
        if (*it != a && overlaps((*it)->getX(), (*it)->getY(), a->getX(), a->getY()))
            (*it)->activateIfAppropriate(a);
    }
}

//|||||||||||||||||||||||||
//     CHECK FUNCTIONS
//|||||||||||||||||||||||||
void StudentWorld::recordLevelFinishedIfAllCitizensGone()
{
    if (m_numCitizensLeft == 0)
        m_finishedLevel = true;
}

bool StudentWorld::intersects(double x1, double y1, double x2, double y2) const
{
    if (x1 <= x2 + SPRITE_WIDTH-1 && x2 <= x1 + SPRITE_WIDTH-1 && y1 <= y2 + SPRITE_HEIGHT-1 && y2 <= y1 + SPRITE_HEIGHT-1)
        return true;
    return false;
}

bool StudentWorld::isAgentMovementBlockedAt(double x, double y, double oldX, double oldY) const
{
    bool blocked = false;
    for (list<Actor*>::const_iterator it = m_actors.begin(); it != m_actors.end(); it++)
    {
        if ((*it)->getX() == oldX &&  (*it)->getY() == oldY)
            continue; // old object!
        if (intersects(x, y, (*it)->getX(), (*it)->getY()) && (*it)->blocksMovement())
        {
            blocked = true;
        }
    }
    return blocked;
}

bool StudentWorld::isFlameBlockedAt(double x, double y, double oldX, double oldY) const
{
    for (list<Actor*>::const_iterator it = m_actors.begin(); it != m_actors.end(); it++)
    {
        if ((*it)->getX() == oldX &&  (*it)->getY() == oldY)
            continue; // old object!
        if (intersects(x, y, (*it)->getX(), (*it)->getY()) && (*it)->blocksFlame())
            return true;
    }
    return false;
}

// Returns true if there is something here that causes Zombie to vomit
bool StudentWorld::isZombieVomitTriggerAt(double x, double y, double oldX, double oldY) const
{
    for (list<Actor*>::const_iterator it = m_actors.begin(); it != m_actors.end(); it++)
    {
        if ((*it)->getX() == oldX &&  (*it)->getY() == oldY)
            continue; // old object!
        if ((*it)->getX() <= x && x < ((*it)->getX() + SPRITE_WIDTH) && (*it)->getY() <= y && y < ((*it)->getY() + SPRITE_WIDTH) && (*it)->canBeInfected())
            return true;
    }
    return false;
}

// Return true if there is a living human, otherwise false.  If true,
// otherX, otherY, and distance will be set to the location and distance
// of the human nearest to (x,y).
bool StudentWorld::locateNearestVomitTrigger(double x, double y, double& otherX, double& otherY, double& distance)
{
    double smallestDistance = VIEW_HEIGHT;
    for (list<Actor*>::const_iterator it = m_actors.begin(); it != m_actors.end(); it++)
    {
        double tempDistance = distanceBetween(x, y, (*it)->getX(), (*it)->getY());
        if (isZombieVomitTriggerAt((*it)->getX(), (*it)->getY(), x, y) && tempDistance < smallestDistance)
        {
            smallestDistance = tempDistance;
            distance = smallestDistance;
            otherX = (*it)->getX();
            otherY = (*it)->getY();
        }
    }
    
    /* If smallestDistance remains unchanged, that means no human actors were found. Return false. */
    if (smallestDistance == VIEW_HEIGHT)
        return false;
    
    return true;
}

// Return true if there is a living zombie or Penelope, otherwise false.
// If true, otherX, otherY, and distance will be set to the location and
// distance of the one nearest to (x,y), and isThreat will be set to true
// if it's a zombie, false if a Penelope.
bool StudentWorld::locateNearestCitizenTrigger(double x, double y, double& otherX, double& otherY, double& distance, bool& isThreat) const
{
    double zombieX = x;
    double zombieY = y;
    double zombieDistance = 0;
    
    locateNearestCitizenThreat(x, y, zombieX, zombieY, zombieDistance);
    
    /* If both distances are equal to SPRITE_HEIGHT_GL (not found on screen), then return false. */
    if (distanceToPenelope(x, y) == VIEW_HEIGHT && zombieDistance == VIEW_HEIGHT)
        return false;
    
    /* Otherwise, determine if the distance to Penelope is smaller than the closest zombie. */
    if (distanceToPenelope(x, y) < zombieDistance)
    {
        isThreat = false;
        distance = distanceToPenelope(x, y);
        otherX = penelopeGetX();
        otherY = penelopeGetY();
        return true;
    }
    
    /* If the zombie is closer, then set coordinates to zombie. */
    isThreat = true;
    distance = zombieDistance;
    otherX = zombieX;
    otherY = zombieY;
    return true;
}

// Return true if there is a living zombie, false otherwise.  If true,
// otherX, otherY and distance will be set to the location and distance
// of the one nearest to (x,y).
bool StudentWorld::locateNearestCitizenThreat(double x, double y, double& otherX, double& otherY, double& distance) const
{
    double smallestDistance = VIEW_HEIGHT;
    for (list<Actor*>::const_iterator it = m_actors.begin(); it != m_actors.end(); it++)
    {
        double tempDistance = distanceBetween(x, y, (*it)->getX(), (*it)->getY());
        if ((*it) != m_penelope && (*it)->canMoveAround() && !(*it)->canBeInfected() && tempDistance < smallestDistance)
        {
            smallestDistance = tempDistance;
            distance = smallestDistance;
            otherX = (*it)->getX();
            otherY = (*it)->getY();
        }
    }
    
    /* If smallestDistance remains unchanged, that means no human actors were found. Return false. */
    if (smallestDistance == VIEW_HEIGHT)
        return false;
    return true;
}
