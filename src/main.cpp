#include <GameState.h>
#include <Application.h>
#include <Agent.h>

using namespace std;

int main(){

    // The logic related to app.run is complicated and hidden to us
    // So we instead just use our own functions for this phase of testing
    Application app;

    app.runTUI(7, 6);

    // return app.run();

    

    // GameState state;
    // state.play(0, 0);
    // state.play(1, 1);
    // state.play(2, 2);
    // state.play(2, 0);

    // Agent::play(state);


    // std::cout << state << endl;


    // cout << Agent::play(state) << endl;

    return 0;
}