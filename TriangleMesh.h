/* 
 * File:   TriangleMesh.h
 * Author: Rayanne Gonçalves
 *
 * Created on September 22, 2014, 10:44 AM
 */

#ifndef TRIANGLEMESH_H
#define	TRIANGLEMESH_H
#include"Vector.h"

class TriangleMesh
{
private:
    Vector *_vertices;
    Vector *_normalFace;
    Vector *_normalArea;
    Vector *_normalAngle;
    int **_triangles;
    int _numVertice;
    int _numTriangle;
    double _xMin,_xMax,_yMin,_yMax,_zMin,_zMax;    
    
public:
    TriangleMesh( char *file);
    ~TriangleMesh();
    int getNumVertice();
    int getNumTriangle();
    const Vector* getVertice();
    const Vector* getNormalFace();
    const Vector* getNormalArea();
    const Vector* getNormalAngle();
    const int* getTriangles(int indice );
    void normalFace();
    void ponderadaPorArea();
    void ponderadaPorAngulo();
    void atualizaMinMax(double x, double y , double z);
    double getXmin();
    double getYmin();
    double getZmin();
    double getXmax();
    double getYmax();
    double getZmax();
    
    
};



#endif	/* TRIANGLEMESH_H */

