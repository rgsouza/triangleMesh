/* 
 * File:   Vector.h
 * Author: Rayanne Gonçalves
 *
 * Created on September 22, 2014, 10:32 AM
 */

#ifndef VECTOR_H
#define	VECTOR_H

class Vector{
    
public:
    Vector(double=0 , double=0, double=0);
    ~Vector();
    double getX() const ;
    double getY() const;
    double getZ() const;
    void setX(double);
    void setY(double);
    void setZ(double);
    Vector crossProd( Vector&);
    void normalize( );
    double getLength();
    void inicialize(int);
    void operator+=( Vector &Q );
    Vector operator*( double scalar );
    Vector operator-( Vector &Q );
    double dotProduct( Vector &Q);
    double getAngle(Vector &Q);
private:
    double _x , _y, _z;
};

#endif	/* VECTOR_H */

