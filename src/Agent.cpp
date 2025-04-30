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

int Agent::getReward(Vertex<GameState>* start, int player){
    // Evaluate a particular vertex in the state space
    // from the point of view of player

    // If it is a terminal state, evaluate it directly
    if (start->neighbors.size() == 0){
            if (start->data.hasWon(player)){
                return 100;
            }
            else if (start->data.hasWon(!player)){
                return -100;
            }
            else{
                return 50;
            }
    }
    // If it is not a terminal state (it has children),
    // we evaluate each child and pick the maximum or the minimum child
    // depending on whose turn it is
    else{
        int reward = getReward(start->neighbors[0]->location, player);
        for (int i = 1; i < start->neighbors.size(); i++){
            int curr = getReward(start->neighbors[i]->location, player);
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
}

Vec Agent::play(GameState state){
    Vertex<GameState>* root = new Vertex<GameState>(state);
    Graph<GameState> gameSpace;
    gameSpace.addVertex(root);

    Queue<GameTreeNode> frontier;
    frontier.enqueue(GameTreeNode(root, 0));

    int limit = 7;
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
    
    int reward = getReward(root->neighbors[0]->location, 1);
    int pos = 0;
    for (int i = 1; i < root->neighbors.size(); i++){
        int curr = getReward(root->neighbors[i]->location, 1);
        if (curr > reward){
            reward = curr;
            pos = i;
        }
        else if (curr == reward && root->neighbors[i]->location->data.hasWon(1)){
            reward = curr;
            pos = i;
        }
    }

    return root->neighbors[pos]->location->data.getLastMove();
}