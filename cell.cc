#include "cell.h"
#include "info.h"
#include "state.h"
#include "grid.h"

Cell::Cell( size_t r, size_t c ):
    r{r}, c{c}{}

void Cell::setPiece( Colour colour ){
    
    if( this -> colour != Colour::NoColour ){
        throw InvalidMove{};
    }

    this -> colour = colour;
    setState( State{StateType::NewPiece, colour, Direction::NW} );
    notifyObservers();
}

void Cell::toggle(){

    switch( colour ){
        case Colour::Black:
            colour = Colour::White;
            break;
        case Colour::White:
            colour = Colour::Black;
            break;
        default:
            break;
    }
}

//helper, get the direction of the piece (n_r, n_c)
//relavent to current cell (r,c)
Direction getDirection( size_t n_r, size_t n_c, size_t r, size_t c ){
    
    if( n_r == r - 1 ){
        if( n_c == c - 1 ) return Direction::NW;
        if( n_c == c ) return Direction::N;
        if( n_c == c + 1 ) return Direction::NE;
    }
    else if( n_r == r ){
        if( n_c == c - 1 ) return Direction::W;
        if( n_c == c + 1 ) return Direction::E;
    }
    else if( n_r == r + 1 ){
        if( n_c == c - 1 ) return Direction::SW;
        if( n_c == c ) return Direction::S;
        if( n_c == c + 1 ) return Direction::SE;
    }

    return Direction::N;
}

//helper, get the opposite direction of the given direction
//used when hitting reply pieces
Direction reverseDirection( Direction t ){
    
    switch( t ){
        case Direction::NW:
            return Direction::SE;
        case Direction::N:
            return Direction::S;
        case Direction::NE:
            return Direction::SW;
        case Direction::W:
            return Direction::E;
        case Direction::E:
            return Direction::W;
        case Direction::SW:
            return Direction::NE;
        case Direction::S:
            return Direction::N;
        case Direction::SE:
            return Direction::NW;
    }

    return Direction::N;
}

void Cell::notify(Subject<Info, State> &whoFrom){
    
    if( colour == Colour::NoColour ) return;
   
    size_t n_r = whoFrom.getInfo().row;
    size_t n_c = whoFrom.getInfo().col;
    Colour col = whoFrom.getInfo().colour;

    //direction of the observer relavent to the subject
    Direction d1 = getDirection( n_r, n_c, r, c );

    //direction of the subject relavent to the new piece
    Direction d2 = whoFrom.getState().direction;
    
    //use t to update the state of current cell
    StateType t;
    
    switch( whoFrom.getState().type ){
        case StateType::NewPiece:
            t = ( col == colour ? StateType::Reply : StateType::Relay );
            setState( State{t, col, d1} );
            notifyObservers();
            break;
        case StateType::Relay:
            if( d1 != d2 ) break;
            t = ( col == colour ? StateType::Relay : StateType::Reply );
            setState( State{t, col, d2} );
            notifyObservers();
            break;
        case StateType::Reply:
            if( d1 != reverseDirection( d2 ) ) break;
            if( getState().type != StateType::Relay ) break;
            t = StateType::Reply;
            setState( State{t, col, d2} );
            toggle();
            notifyObservers();
            break;
    }
}

Info Cell::getInfo() const{
    return Info{r, c, colour};
}
