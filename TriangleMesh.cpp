#include"TriangleMesh.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#define PI 3,14159265

using namespace std;


TriangleMesh::TriangleMesh( char *file )
{
    ifstream in( file );
    std::string trash;
    double x, y, z;
    _xMin = 10E20, _xMax = -10E20, _yMin = 10E20, _yMax = -10E20, _zMin = 10E20, _zMax = -10E20;

    if (in.fail( ))
    {
        cout << " Erro na abertura do arquivo : " << file << endl;
        exit( 1 );
    }

    in>>trash;

    in >> _numVertice >> _numTriangle>>trash;

    _vertices = new Vector[ _numVertice ];
    
    for (int i = 0; i < _numVertice; i++)
    {
        in >> x >> y>>z;

        atualizaMinMax( x, y, z );

        _vertices[i].setX( x );
        _vertices[i].setY( y );
        _vertices[i].setZ( z );

    }

    _triangles = new int *[_numTriangle];

    for (int i = 0; i < _numTriangle; i++)
    {
        int num;
        in>>num;
        _triangles[i] = new int [num];


        for (int j = 0; j < num; j++)
            in >> _triangles[i][j];

    }

    normalFace();
    ponderadaPorArea();
    ponderadaPorAngulo();
}

TriangleMesh::~TriangleMesh( )
{
    printf("1\n");
    delete _vertices;
    printf("2\n");
    for (int i = 0; i < _numTriangle; i++)
        delete _triangles[i];
    printf("3\n");
    delete _triangles;
    printf("4\n");
    delete _normalAngle;
    printf("5\n");
    delete _normalFace;
    printf("6\n");
    delete _normalArea;
    printf("7\n");
}

int TriangleMesh::getNumVertice( )
{
    return _numVertice;
}

int TriangleMesh::getNumTriangle( )
{
    return _numTriangle;

}

const Vector* TriangleMesh::getVertice( )
{
    return _vertices;
}

const Vector* TriangleMesh::getNormalFace( )
{
    return _normalFace;
}

const Vector* TriangleMesh::getNormalArea( )
{
    return _normalArea;
}

const Vector* TriangleMesh::getNormalAngle( )
{
    return _normalAngle;
}


const int * TriangleMesh::getTriangles( int indice )
{
   
    
    return _triangles[indice];
}

void TriangleMesh::normalFace( )
{
           
    _normalFace = new Vector[ _numTriangle ];

    
    for( int i=0 ; i< _numTriangle ; i++)
    {
        
            Vector one;
            Vector two;
            
            one = _vertices[_triangles[i][0]] - _vertices[_triangles[i][1]];
            
            two = _vertices[_triangles[i][2]] - _vertices[_triangles[i][1]];
            
            
            one.crossProd(two);
            one.normalize();
            
            _normalFace[i].setX(one.getX());
            _normalFace[i].setY(one.getY());
            _normalFace[i].setZ(one.getZ());
            
             
    }  
}

void TriangleMesh::ponderadaPorAngulo( )
{
    _normalAngle =  new Vector[ _numVertice ];
    
    for (int i = 0 ; i< _numVertice ; i++)
    {
           _normalAngle[i].setX(0);
           _normalAngle[i].setY(0);
           _normalAngle[i].setZ(0);
    }
    
    for(int i=0 ; i< _numTriangle ;  i++)
    {
              
        Vector one = _vertices[_triangles[i][0]] - _vertices[_triangles[i][1]];
        Vector two = _vertices[_triangles[i][2]] - _vertices[_triangles[i][1]];
        
        
        double alpha = one.getAngle(two);
        Vector aux = _normalFace[i]*(alpha);
        _normalAngle[_triangles[i][1]]+=aux; 
         
        
        one =  _vertices[_triangles[i][0]] - _vertices[_triangles[i][2]];   
        two = _vertices[_triangles[i][1]] - _vertices[_triangles[i][2]];
        
        double beta = one.getAngle(two);
        
        aux =  _normalFace[i]*(beta);
        _normalAngle[_triangles[i][2]]+= aux;
            
        aux = _normalFace[i]*(PI - alpha - beta);    
        _normalAngle[_triangles[i][0]]+= aux;
    }
    
    for (int i = 0 ; i< _numVertice ; i++)
    {
        _normalAngle[i].normalize();
    }
}

void TriangleMesh::ponderadaPorArea( )
{
        _normalArea = new Vector[ _numVertice ];
       
       
       for (int i = 0 ; i< _numVertice ; i++)
       {
           _normalArea[i].setX(0);
           _normalArea[i].setY(0);
           _normalArea[i].setZ(0);
       }
       
       for(int i=0 ; i< _numTriangle ;  i++)
       {
              
          _normalArea[_triangles[i][0]]+=_normalFace[i];
          _normalArea[_triangles[i][1]]+=_normalFace[i];
          _normalArea[_triangles[i][2]]+=_normalFace[i];
           
       }
       
       for (int i = 0 ; i< _numVertice ; i++)
       {
           _normalArea[i].normalize();
       }
       
       
}

void TriangleMesh::atualizaMinMax( double x, double y, double z )
{
    if (x < _xMin)
        _xMin = x;

    else if (x > _xMax)
        _xMax = x;

    if (y < _yMin)
        _yMin = y;

    else if (y > _yMax)
        _yMax = y;

    if (z < _zMin)
        _zMin = z;

    else if (z > _zMax)
        _zMax = z;
}

double TriangleMesh::getXmax( )
{
    return _xMax;
}

double TriangleMesh::getXmin( )
{
    return _xMin;
}

double TriangleMesh::getYmax( )
{
    return _yMax;

}

double TriangleMesh::getYmin( )
{
    return _yMin;
}

double TriangleMesh::getZmax( )
{
    return _zMax;
}

double TriangleMesh::getZmin( )
{
    return _zMin;
}

