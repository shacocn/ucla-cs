#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include "Level.h"
#include "GraphObject.h"
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
    virtual ~StudentWorld();
    
    /* Accessor functions. */
    int ticks() const { return m_ticks; };

    /* Mutator functions. */
    bool overlaps(double x1, double y1, double x2, double y2) const;
    void changeLevelStatus(bool newStatus) { m_finishedLevel = newStatus; };
    void addActor(Actor* a);
    void activateOnAppropriateActors(Actor* a);
    
    /* Checks. */
    void recordCitizenGone();
    void recordLevelFinishedIfAllCitizensGone();
    bool isAgentMovementBlockedAt(double x, double y, double oldX, double oldY) const;
    bool isFlameBlockedAt(double x, double y, double oldX, double oldY) const;
    bool isZombieVomitTriggerAt(double x, double y, double oldX, double oldY) const;
    bool locateNearestVomitTrigger(double x, double y, double& otherX, double& otherY, double& distance);
    bool locateNearestCitizenTrigger(double x, double y, double& otherX, double& otherY, double& distance, bool& isThreat) const;
    bool locateNearestCitizenThreat(double x, double y, double& otherX, double& otherY, double& distance) const;
private:
    /* Private data members. */
    std::list<Actor*> m_actors; // points to all actors on screen
    Penelope* m_penelope; // points to penelope
    int m_numCitizensLeft; // number of citizens alive
    bool m_wonGame;
    bool m_finishedLevel;
    int m_ticks;
    std::string statusLine;
    
    /* Loads actors into the m_actor list. */
    void processFile(const Level lev);
    
    /* Adds actors from data file to m_actor list. */
    void addActorToList(int x, int y, Level::MazeEntry loc);
    
    /* Checks for bounding box intersection. */
    bool intersects(double x1, double y1, double x2, double y2) const;
    
    /* Returns distance between two points. */
    double distanceBetween(double x1, double y1, double x2, double y2) const;
    
    /* Updates the status bar. */
    void updateStatusLine();
    
    double penelopeGetX() const { return m_penelope->getX(); };
    double penelopeGetY() const { return m_penelope->getY(); };
    double distanceToPenelope(double x, double y) const { return distanceBetween(penelopeGetX(), penelopeGetY(), x, y); };
    
};

#endif // STUDENTWORLD_H_
