#ifndef __GRAPHICS_DISPLAY_H__
#define __GRAPHICS_DISPLAY_H__

#include "info.h"
#include "state.h"
#include "window.h"
#include "subject.h"
#include "observer.h"

const int INTERVAL = 5;
const int WINDOWSIZE = 500;

class GraphicsDisplay : public Observer<Info, State>{
    Xwindow display; //graphical output object
    size_t size; //size of one piece, including separating space
    size_t left; //space left on the left
    size_t up; //space left on the top
    size_t n; //size of the grid

  public:
    GraphicsDisplay( size_t size, size_t left, size_t up, size_t n );
    void notify( Subject<Info, State> &whoFrom ) override;

    //output win message when game terminates
    //after the message appears, press any key in the terminal 
    //to terminate the program
    void winMessage( Colour c );
};

#endif
