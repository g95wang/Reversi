#include "textdisplay.h"
#include "state.h"
#include "subject.h"

TextDisplay::TextDisplay( size_t n ):
    theDisplay{std::vector<std::vector<char>> (n, std::vector<char> (n, '-'))}, gridSize{n}{}

void TextDisplay::notify(Subject<Info, State> &whoNotified){
    size_t r = whoNotified.getInfo().row;
    size_t c = whoNotified.getInfo().col;

    switch( whoNotified.getInfo().colour ){
        case Colour::White:
            theDisplay[r][c] = 'W';
            break;
        case Colour::Black:
            theDisplay[r][c] = 'B';
            break;
        default:
            theDisplay[r][c] = '-';
            break;
    }
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td){
    
    for( size_t i = 0; i < td.gridSize; i++ ){
        for( size_t j = 0; j < td.gridSize; j++ ){
            out << td.theDisplay[i][j];
        }
        out << std::endl;
    }
    return out;
}
