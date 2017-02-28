#include "OpenGLCanvasWindow.h"
#include<GL/gl.h>
#include<GL/glu.h>

#include"Vector.h"
#include<cmath>
#include<stdio.h>
#include"Vector.h"
using namespace std;

OpenGLCanvasWindow::OpenGLCanvasWindow( )
{
    _object = 0;
    _state=10;
    createWindow( );

    initCanvas( );
}

OpenGLCanvasWindow::~OpenGLCanvasWindow( )
{
    IupDestroy( _dialog );
}

void OpenGLCanvasWindow::hide( )
{
    IupHide( _dialog );
}

void OpenGLCanvasWindow::show( )
{
    IupShow( _dialog );
}

void OpenGLCanvasWindow::initCanvas( )
{
    GLfloat matSpecular[] = { 1.0 , 1.0  , 1.0 , 1.0 };
    GLfloat matShininess[] = { 36.0 };
    GLfloat lightPosition[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat whiteLight[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lmodelAmbient[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat material[] = { 1.0, 0.0, 0.0, 1.0 };
    glClearColor( 1.0, 1.0, 1.0, 1.0 );


    glShadeModel( GL_SMOOTH );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, matShininess );

    glLightfv( GL_LIGHT0, GL_POSITION, lightPosition );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, whiteLight );
    glLightfv( GL_LIGHT0, GL_SPECULAR, whiteLight );
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lmodelAmbient );
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE );

    glEnable( GL_COLOR_MATERIAL );

    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_DEPTH_TEST );



}

void OpenGLCanvasWindow::createWindow( )
{
    Ihandle *button = IupButton( "Exit  ", NULL );
    Ihandle *button2 = IupButton( "Open", NULL );
    Ihandle *canvas = IupGLCanvas( NULL );

    Ihandle *porFace = IupToggle( "Por face", NULL );
    Ihandle *ponderadaArea = IupToggle( "Por vertice ponderada por area.", NULL );
    Ihandle *ponderadaAngulo = IupToggle( "Por vertice ponderada por angulo", NULL );

    Ihandle *hboxButton = IupHbox( IupFill( ), button2, button, NULL );
    Ihandle *togglesHbox = IupHbox( porFace, ponderadaArea, ponderadaAngulo, IupFill( ), NULL );
    Ihandle *radioOptions = IupRadio( togglesHbox );

    Ihandle *frameNormal = IupFrame( radioOptions );

    Ihandle *hboxCanvas = IupHbox( canvas, NULL );

    Ihandle *vbox = IupVbox( frameNormal, hboxCanvas, hboxButton, NULL );


    _dialog = IupDialog( vbox );

    IupSetAttribute( _dialog, "THIS", (char*) this );
    IupSetAttribute( _dialog, "CANVAS", (char*) canvas );



    
    IupSetAttribute( _dialog, IUP_TITLE, "TriangleMesh" );
    IupSetAttribute( vbox, "MARGIN", "10X10" );
    IupSetAttribute( vbox, "GAP", "10" );
    IupSetAttribute( frameNormal, IUP_TITLE, "Zoom" );
    IupSetAttribute( canvas, "RASTERSIZE", "600x600" );
    IupSetAttribute( canvas, "BUFFER", "DOUBLE" );

    IupSetCallback( button, IUP_ACTION, (Icallback) exitButton );
    IupSetCallback( button2, IUP_ACTION, (Icallback) openCallback );
    IupSetCallback( canvas, IUP_ACTION, (Icallback) actionCallback );
    IupSetCallback( canvas, IUP_RESIZE_CB, (Icallback) resizeCanvasCallback );
    IupSetCallback( porFace, IUP_ACTION, (Icallback) toogleCallbackI );
    IupSetCallback( ponderadaArea, IUP_ACTION, (Icallback) toogleCallbackII );
    IupSetCallback( ponderadaAngulo, IUP_ACTION, (Icallback) toogleCallbackIII );


    IupMap( _dialog );
    IupGLMakeCurrent( canvas );
}

int OpenGLCanvasWindow::exitButton( Ihandle* exi )
{
    return IUP_CLOSE;
}

int OpenGLCanvasWindow::toogleCallbackI( Ihandle* ih, int state )
{
    
    OpenGLCanvasWindow *window = (OpenGLCanvasWindow*) IupGetAttribute( ih, "THIS" );

    if (state)
    {
        window->_state=10;

    }
   // Ihandle *canvas = (Ihandle*) IupGetAttribute( ih, "CANVAS" );
    //IupUpdate( canvas );
    return IUP_DEFAULT;

}

int OpenGLCanvasWindow::toogleCallbackII( Ihandle* ih, int state )
{   
    OpenGLCanvasWindow *window = (OpenGLCanvasWindow*) IupGetAttribute( ih, "THIS" );
    if (state)
    {
        window->_state=20;

    }
    Ihandle *canvas = (Ihandle*) IupGetAttribute( ih, "CANVAS" );
    IupUpdate( canvas );
    return IUP_DEFAULT;
}

int OpenGLCanvasWindow::toogleCallbackIII( Ihandle* ih, int state )
{
    
    OpenGLCanvasWindow *window = (OpenGLCanvasWindow*) IupGetAttribute( ih, "THIS" );
    if (state )
    {
        window->_state=30;

    }
    Ihandle *canvas = (Ihandle*) IupGetAttribute( ih, "CANVAS" );
    IupUpdate( canvas );
    return IUP_DEFAULT;
}

int OpenGLCanvasWindow::openCallback( Ihandle* ih, int state )
{
    IupGLMakeCurrent( ih );
    OpenGLCanvasWindow *window = (OpenGLCanvasWindow*) IupGetAttribute( ih, "THIS" );
    
    Ihandle *dlg = IupFileDlg( );
    IupSetAttribute( dlg, "DIALOGTYPE", "OPEN" );
    IupSetAttribute( dlg, "TITLE", "IupFileDlg OPEN " );
    IupSetAttribute( dlg, "FILTER", "*.off" );
    IupSetAttribute( dlg, "FILTERINFO", " OFF Files" );

    IupPopup( dlg, IUP_CURRENT, IUP_CURRENT );
    
    
    
    if( IupGetInt( dlg, "STATUS" ) != -1)     
    {
            delete window->_object;
            printf("%p\n", window->_object);
            window->_object = new TriangleMesh( IupGetAttribute( dlg, "VALUE" ) );
        
            window->_xMin = window->_object->getXmin( );
            window->_xMax = window->_object->getXmax( );
            window->_yMin = window->_object->getYmin( );
            window->_yMax = window->_object->getYmax( );
            window->_zMin = window->_object->getZmin( );
            window->_zMax = window->_object->getZmax( );
            
            printf(" %s ",IupGetAttribute( dlg, "VALUE" ));

      }    
        
    Ihandle *canvas = (Ihandle*) IupGetAttribute( ih, "CANVAS" );
    IupUpdate( canvas );
        
    IupDestroy(dlg);
    return IUP_DEFAULT;

}

void OpenGLCanvasWindow::drawFace( )
{
   
    const Vector *vertice = _object->getVertice();
    const Vector *normal = _object->getNormalFace(); 
    
    glBegin( GL_TRIANGLES );
    for (int i = 0; i < _object->getNumTriangle( ); i++)
    {
        const int *triangle = _object->getTriangles( i );

           glNormal3f( -normal[i].getX( ), -normal[i].getY( ),-normal[i].getZ( ) );
    
                for (int j = 0; j < 3; j++)
                {

                    glVertex3f( vertice[triangle[j]].getX( ), vertice[triangle[j]].getY( ),
                            vertice[triangle[j]].getZ( ) );

                }
    }
    
    glEnd( );
   
}

void OpenGLCanvasWindow::drawArea( )
{
    const Vector *vertice = _object->getVertice();
    const Vector *normal = _object->getNormalArea();
    
    glBegin( GL_TRIANGLES );
    for (int i = 0; i < _object->getNumTriangle(); i++)
    {
        const int *triangle = _object->getTriangles( i );
        
         for (int j = 0; j < 3; j++)
            {
                glNormal3f( -normal[triangle[j]].getX( ), -normal[triangle[j]].getY( ),-normal[triangle[j]].getZ( ) );
                glVertex3f( vertice[triangle[j]].getX( ), vertice[triangle[j]].getY( ),
                            vertice[triangle[j]].getZ( ) );

            }
    }
    
    glEnd( );
    
}

void OpenGLCanvasWindow::drawAngle( )
{
    const Vector *vertice = _object->getVertice();
    const Vector *normal = _object->getNormalAngle();
    
    glBegin( GL_TRIANGLES );
    for (int i = 0; i < _object->getNumTriangle(); i++)
    {
        const int *triangle = _object->getTriangles( i );
        
         for (int j = 0; j < 3; j++)
            {
                glNormal3f( -normal[triangle[j]].getX( ), -normal[triangle[j]].getY( ),-normal[triangle[j]].getZ( ) );
                glVertex3f( vertice[triangle[j]].getX( ), vertice[triangle[j]].getY( ),
                            vertice[triangle[j]].getZ( ) );

            }
    }
    
    glEnd( );
}



int OpenGLCanvasWindow::actionCallback( Ihandle* ih )
{
    IupGLMakeCurrent( ih );
    OpenGLCanvasWindow *window = (OpenGLCanvasWindow*) IupGetAttribute( ih, "THIS" );
    GLfloat lightPosition[] = { 0.0, 0.0, 0.0, 1.0 };

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glEnable( GL_LIGHTING );
    glColor3f( 1.0f, 0.0f, 0.0f );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
   
    if (window->_object != 0)
    {

        double norma = 0.5*sqrt( pow( window->_xMin - window->_xMax, 2 ) + pow( window->_yMin - window->_yMax, 2 )
                             + pow( window->_zMin - window->_zMax, 2 ) );

        double x = window->_xMin + window->_xMax;
        double y = window->_yMin + window->_yMax;
        double z = window->_zMin + window->_zMax;

        gluLookAt( x / 2 + norma, y / 2 , z / 2 + norma, x / 2, y / 2, z / 2, 0.0, 1.0, 0.0 );
        
        
        if (window->_state == 10 )
        window->drawFace();
        
        else if (window->_state == 20 )
          window->drawArea();
       
        else if ( window->_state == 30 )
            window->drawAngle();
        
        glDisable( GL_LIGHTING );
        
    }
   
    IupGLSwapBuffers( ih );
    return IUP_DEFAULT;
}



int OpenGLCanvasWindow::resizeCanvasCallback( Ihandle* ih, int w, int h )
{
    IupGLMakeCurrent( ih );
    OpenGLCanvasWindow *window = (OpenGLCanvasWindow*) IupGetAttribute( ih, "THIS" );
    
    GLfloat light_position[] = { 0.0, 0.0, 0.0, 0.0 };

    glViewport( 0, 0, (GLsizei) w, (GLsizei) h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    gluPerspective( 60.0, (GLfloat) w / (GLfloat) h, 0.1, 20000.0 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    
    IupUpdate( ih );


    return IUP_DEFAULT;
}

