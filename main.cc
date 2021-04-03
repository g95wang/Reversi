#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
#include "state.h"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd;
    Grid g;

    // Add code here
    int acc; //keep track of who should play

    try {
        while (true) {
            cin >> cmd;
            
            if (cmd == "new") {
                int n;
                cin >> n;

                // Add code here
                if( n % 2 ) continue;
                if( n <= 2 ) continue;
                g.init(n);
                acc = 0;
                cout << g;
            }
            else if (cmd == "play") {
                int r = 0, c = 0;
                cin >> r >> c;

                // Add code here
                try{
                    Colour colour = acc % 2 ? Colour::White : Colour::Black;
                    g.setPiece( r, c, colour );
                    acc++;
                    cout << g;
                }
                catch( InvalidMove ){}
                
                if( g.isFull() ){
        
                    switch( g.whoWon() ){
                        case Colour::Black:
                            cout << "Black wins!" << endl;
                            break;
                        case Colour::White:
                            cout << "White wins!" << endl;
                            break;
                        default:
                            cout << "Tie!" << endl;
                            break;
                    }
                    return 0;
                }
            }
        }
    }
    catch (ios::failure &) {}  // Any I/O failure quits
}
