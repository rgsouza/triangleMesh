#include <cstdlib>
#include "OpenGLCanvasWindow.h"

using namespace std;

int main(int argc, char** argv) {

    IupOpen( &argc , &argv );
    
    IupGLCanvasOpen();
    
    OpenGLCanvasWindow *window = new OpenGLCanvasWindow();
    
    window->show();
    
    
    IupMainLoop( );
    
    delete window;
    
    IupClose();
    
    
    
    return EXIT_SUCCESS;
}
