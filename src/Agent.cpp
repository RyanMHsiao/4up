#include "Queue.h"
#include "Vertex.h"
#include "Graph.h"
#include <iostream>
#include <Agent.h>
#include "GameState.h"

using namespace std;

struct GameTreeNode{
    Vertex<GameState>* vertex;
    int depth;

    GameTreeNode(Vertex<GameState>* vertex = nullptr, int depth = 0){
        this->vertex = vertex;
        this->depth = depth;
    }
};

Vec findFirstAvailable(GameState state){

    for (int j = 0; j < state.getCols(); j++){
        if (state.hasSpace(j)){
            return Vec(0, j);
        }
    }

    return Vec(0, 0);
}

ArrayList<Vec> openSquares(GameState state){
    ArrayList<Vec> result;
    if (!state.gameOver()){
        for (int j = 0; j < state.getCols(); j++){
            if (state.hasSpace(j)){
                result.append(Vec(0,j));
            }
        }
    }
    return result;
}

int Agent::getReward(Vertex<GameState>* start, int player, int cycles){
    // Evaluate a particular vertex in the state space
    // from the point of view of player
    // std::cout << start->neighbors.size() << std::endl;
    // If it is a terminal state, evaluate it directly
    // if(!start->data.hasWon(!player)){

    // }
        // std::cout << start->neighbors.size() << " and " << i << std::endl;
    //Try looping while adding score, such that you can add when a three in a row occurs, and have the AI try to create those if its theirs, or block if by human.

    if(start->neighbors.size() == 0){
        
        if (start->data.hasWon(player)){
            return 100 * cycles + 100;
        }
        else if (start->data.hasWon(!player)){
            // std::cout << -100 + (-100 * i) << std::endl;
            // std::cout << cycles << " is the cycle" << std::endl;
            return (-100 * cycles);
        }

        if(cycles == 0){
            return 50 * cycles + 1;
        }

    }
    
    // If it is not a terminal state (it has children),
    // we evaluate each child and pick the maximum or the minimum child
    // depending on whose turn it is
    else{
        cycles--;
        int reward = getReward(start->neighbors[0]->location, player, cycles);
        for (int i = 1; i < start->neighbors.size(); i++){
            int curr = getReward(start->neighbors[i]->location, player, cycles);
            if (start->data.getCurrentTurn() == player){
                if (curr > reward){
                    reward = curr;
                }
            }
            else{
                if (curr < reward){
                    reward = curr;
                }
            }
        }
        return reward;
    }

    //Incase no conditions were met
    return 0;
}

Vec Agent::play(GameState state){
    Vertex<GameState>* root = new Vertex<GameState>(state);
    Graph<GameState> gameSpace;
    gameSpace.addVertex(root);
    int zeroColumns = 0;

    Queue<GameTreeNode> frontier;
    frontier.enqueue(GameTreeNode(root, 0));
    int limit = 6;
    while (!frontier.isEmpty()){
        GameTreeNode gtn = frontier.dequeue();
        Vertex<GameState>* node = gtn.vertex;
        int depth = gtn.depth;
        ArrayList<Vec> moves = openSquares(node->data);

        // if (moves.size() < 15){
        //     limit = 5;
        // }
        if (depth < limit){
            for (int i = 0; i < moves.size(); i++){
                GameState currentState = node->data;
                currentState.play(moves[i].y);
                Vertex<GameState>* child = new Vertex<GameState>(currentState);
                gameSpace.addVertex(child);
                gameSpace.addDirectedEdge(node, child, 1);
                frontier.enqueue(GameTreeNode(child, depth + 1));
                
            }
        }
    }
    
    int cycles = limit;
    int reward = getReward(root->neighbors[0]->location, 1, cycles);

    std::cout << reward << std::endl;
    if(reward == 0){
        zeroColumns++;
    }
    int pos = 0;
    for (int i = 1; i < root->neighbors.size(); i++){
        int curr = getReward(root->neighbors[i]->location, 1, cycles);
        std::cout << curr << std::endl;
        if (curr > reward){
            std::cout << "better option at " << i << std::endl;
            reward = curr;
            pos = i;
        }
        else if (curr == reward && root->neighbors[i]->location->data.hasWon(1)){
            //Identified something can be inputted here to prolong the game
            std::cout << "here" << std::endl;
            reward = curr;
            pos = i;
        }
        if(curr == 0){
            zeroColumns++;
        }
    }

    if(reward <= -100){
        std::cout << "Always lose from here" << reward << std::endl;
        // pos = oneOff();
    }

    if(reward == -100 * (limit - 1)){
        //This is to see if there is multiple win scenarios for human, and will try blocking one of them at least to be less stupid
        int possibleWins = 0;
        std::cout << "size: " << root->neighbors.size() << std::endl;
        // Vertex<GameState>* root2 = new Vertex<GameState>(state);
        // root2.play(0);

        for(int count = 0; count < state.getCols(); count++){
            //This will be where I cycle through possible win spots for human when 2 ways to win, such that it will block at least one spot
            GameState root2 = GameState(state);
            
            // Note that using count instead of an actual col value
            if(root2.hasSpace(count)){
                root2.forceOpponentSimulation(count);
                if(root2.hasWon(1) ||  (root2.hasWon(0) && root2.hasSpace(count))){
                    possibleWins++;
                    std::cout << "Poss" << std::endl;
                    pos = count;
                }

            }

        }

        std::cout << "Possible wins: " << possibleWins << std::endl;
    }

    //This is primarily going to be used for the first couple of turns when the AI does not have much to respond to
    //It will choose to play closer towards the center in open columns
    //Will only properly run when 3 or more columns return "0" also
    //In the extremely off chance that this logic will cause the AI to lose, it will just default to what it has been doing

    if(zeroColumns > 2){
            int spotToPlay = state.getLeastFilledRow();
            GameState root2 = GameState(state);
            root2.forceOpponentSimulation(spotToPlay);
            if(root2.hasWon(1) || root2.hasWon(0)){
                //This is intentionally blank, indicating it will cause AI to lose
            } else {
                pos = spotToPlay;
            }
    }

    return root->neighbors[pos]->location->data.getLastMove();
}