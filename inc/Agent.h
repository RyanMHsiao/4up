#ifndef AGENT_H
#define AGENT_H

#include "GameState.h"
#include "Vertex.h"

/* 
Things to do:
- make ai check for threats
- how do we look for threats?
- reward for blocking threats
- should check ahead most moves possible (start at 3 and increase from there)
*/

class Agent {
    static int getReward(Vertex<GameState>* start, int player, int cycles);
public:
    static Vec play(GameState state);
};

#endif