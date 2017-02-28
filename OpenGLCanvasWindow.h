/* 
 * File:   OpenGLCanvasWindow.h
 * Author: Rayanne Gonçalves
 *
 * Created on September 22, 2014, 10:56 AM
 */

#ifndef OPENGLCANVASWINDOW_H
#define	OPENGLCANVASWINDOW_H
#include<iup/iup.h>
#include<iup/iupgl.h>
#include"TriangleMesh.h"

class OpenGLCanvasWindow 
{
public:
    OpenGLCanvasWindow();
    void show();
    void hide();
    virtual ~OpenGLCanvasWindow();
    
private:
    Ihandle *_dialog;
    TriangleMesh *_object;
    double _xMin,_xMax,_yMin,_yMax,_zMin,_zMax;
    int _state;
    void createWindow();
    void initCanvas();
    void drawFace();
    void drawArea();
    void drawAngle();
    
    static int actionCallback(Ihandle* ih );
    static int exitButton( Ihandle *exi );
    static int toogleCallbackI( Ihandle *ih , int state );
    static int toogleCallbackII( Ihandle *ih , int state );
    static int toogleCallbackIII( Ihandle *ih , int state );
    static int openCallback( Ihandle *ih , int state );
    static int resizeCanvasCallback( Ihandle *ih , int w , int h );
    
};



#endif	/* OPENGLCANVASWINDOW_H */

