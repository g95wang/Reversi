#include "grid.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"

Grid::~Grid(){
    delete td;
    delete ob;
}

bool Grid::isFull() const{
    
    if( num == size * size ) return true;
    return false;
}

Colour Grid::whoWon() const{
    int b=0, w=0;

    for( auto i : theGrid ){
        for ( auto j : i ){
            
            switch( j.getInfo().colour ){
                case Colour::Black:
                    b++;
                    break;
                case Colour::White:
                    w++;
                    break;
                default:
                    break;
            }
        }
    }
   
    //////////////////////////////////////////////////////////////////// 
    //the part below is used for graphical winMessage output
    Cell winMessage{size, size}; //use overflow to indicate game terminating
    
    if( b == w ){
        winMessage.setPiece( Colour::NoColour );
        ob -> notify( winMessage );  
        return Colour::NoColour;
    }
    
    if( b > w ){
        winMessage.setPiece( Colour::Black );
        ob -> notify( winMessage );
        return Colour::White; 
    }

    winMessage.setPiece( Colour::White );
    ob -> notify( winMessage );
    return Colour::Black;
}

//helper, check if (i+k1-1,j+k2-1) is in the grid
//since size_t is unsigned, we shift k1, k2 one unit greater
bool checkValid( size_t i, size_t j, size_t k1, size_t k2, size_t n ){
    
    if( k1 == 1 && k2 == 1 ) return false;
    if( i + k1 == 0 || i + k1 > n ) return false;
    if( j + k2 == 0 || j + k2 > n ) return false;
    return true;
}

void Grid::init( size_t n ){
    ////////////////////////////////////////////////////////////////////
    //initialize the fields
    size = n;
    num = 0;
    
    delete td;
    td = new TextDisplay{n};
    
    delete ob;
    size_t display_size = (500 - 5 - 40) / n;
    size_t trim = (500 - 5 - n * display_size) / 2;
    ob = new GraphicsDisplay{display_size,trim+5,5,n};
    ////////////////////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////////////////////
    //initialize the vector
    theGrid.clear();
    
    for( size_t i = 0; i < n; i++ ){
        std::vector<Cell> row;
        
        for( size_t j = 0; j < n; j++ ){
            row.push_back( Cell{i,j} );
        }
        theGrid.push_back( row );
    }
    ////////////////////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////////////////////
    //initialize the attachment
    for( size_t i = 0; i < n; i++ ){
        for( size_t j = 0; j < n; j++ ){
            for( size_t k1 = 0; k1 <= 2; k1++ ){
                for( size_t k2 = 0; k2 <= 2; k2++ ){
                    
                    if( checkValid(i, j, k1, k2, n) ){
                        theGrid[i][j].attach(&theGrid[i+k1-1][j+k2-1]);
                    }
                }
            }
            theGrid[i][j].attach(td);
            theGrid[i][j].attach(ob);
        }
    }
    ////////////////////////////////////////////////////////////////////
       
    ////////////////////////////////////////////////////////////////////
    //initialize the first four pieces
    setPiece(n/2-1, n/2-1, Colour::Black);  
    setPiece(n/2-1, n/2, Colour::White);
    setPiece(n/2, n/2-1, Colour::White);
    setPiece(n/2, n/2, Colour::Black);
    ////////////////////////////////////////////////////////////////////
}

void Grid::setPiece( size_t r, size_t c, Colour colour ){
    
    if( r >= size || r < 0 || c >= size || c < 0 ) throw InvalidMove{};

    theGrid[r][c].setPiece( colour );
    num++;
}

void Grid::toggle( size_t r, size_t c ){
    theGrid[r][c].toggle();
}

std::ostream &operator<<(std::ostream &out, const Grid &g){
    out << *(g.td);
    return out;
}
