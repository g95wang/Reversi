#include "graphicsdisplay.h"
#include <iostream>

GraphicsDisplay::GraphicsDisplay( size_t size, size_t left, size_t up, size_t n ):
    size{size}, left{left}, up{up}, n{n} {
    display.fillRectangle( 0, 0, WINDOWSIZE, WINDOWSIZE, display.Green );
    for( size_t r = 0; r < n; r++ ){
        for( size_t c = 0; c < n; c++ ){
            display.fillRectangle( left+c*size, up+r*size, 
                    size - INTERVAL, size - INTERVAL, display.Blue );
        }
    }
}

void GraphicsDisplay::notify( Subject<Info, State> &whoFrom ){
    size_t r = whoFrom.getInfo().row;
    size_t c = whoFrom.getInfo().col;
    
    if( r == n && c == n ){
        winMessage( whoFrom.getInfo().colour );
        return;
    }

    switch( whoFrom.getInfo().colour ){
        case Colour::White:
            display.fillRectangle( left+c*size, up+r*size, 
                    size - INTERVAL, size - INTERVAL, display.White );
            break;
        case Colour::Black:
            display.fillRectangle( left+c*size, up+r*size,
                    size - INTERVAL, size - INTERVAL, display.Black );
            break;
        default:
            display.fillRectangle( left+c*size, up+r*size,
                    size - INTERVAL, size - INTERVAL, display.Blue );
            break;
    }
}

void GraphicsDisplay::winMessage( Colour c ){
    
    switch( c ){
        case Colour::White:
            display.drawString(220,470,"White wins!");
            break;
        case Colour::Black:
            display.drawString(220,470,"Black wins!");
            break;
        default:
            display.drawString(240,470,"Tie!");
            break;
    }
    display.drawString(185,490,"Press enter to terminate");
    std::cin.get();
    std::cin.get();
}
