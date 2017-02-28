#include"Vector.h"
#include<cmath>
#include"divideByZeroException.h"
Vector :: Vector(double x , double y, double z)
{
    _x = x;
    _y = y;
    _z = z;
}



Vector::~Vector( )
{
}



double Vector::getX( ) const 
{
    return _x;
}



double Vector::getY( ) const 
{
    return _y;
}



double Vector::getZ( ) const 
{
    return _z;
}



void Vector::setX( double x )
{
    _x = x;
}



void Vector::setY( double y )
{
    _y = y;
}



void Vector::setZ( double z )
{
     _z = z;
}



Vector Vector::crossProd( Vector &Q)
{
   double x = this ->getX();
   double y = this ->getY();
   double  z = this->getZ();
   
    this->setX( y*Q.getZ() - z*Q.getY());
    this->setY( z*Q.getX() - x*Q.getZ());
    this->setZ( x*Q.getY() - y*Q.getX());
    return *this;
}


double Vector ::getLength()
{
    return   std:: sqrt(std :: pow( getX(),2) + std :: pow(getY(),2) + std:: pow( getZ(),2));
}



void Vector::normalize( )
{
    double x = getX();
    double y = getY();
    double z = getZ();
    double length = getLength();
 
    if( length != 0)
    {
        setX( x / length );
        setY( y / length );
        setZ( z / length );
    }
}

void Vector::inicialize(int size )
{
    for(int i= 0 ; i< size ; i++)
    {
        this->_x = 0;
        this->_y = 0;
        this->_z = 0;
        
    }    
}

void Vector::operator +=(Vector& Q )
{
    double x = this->getX();
    double y = this->getY();
    double z = this->getZ();
 
    this->setX( x + Q.getX() );
    this->setY( y + Q.getY() ); 
    this->setZ( z + Q.getZ() );
}



Vector Vector::operator *(double scalar)
{
    Vector newVector;
    double x = this->getX();
    double y = this->getY();
    double z = this->getZ();
 
    newVector.setX( x*scalar);
    newVector.setY( y*scalar );
    newVector.setZ( z*scalar );
    
    return newVector;
}


Vector Vector::operator -( Vector& Q )
{
    Vector newVector;
 
    newVector.setX( this->getX() - Q.getX());
    newVector.setY( this->getY()  -  Q.getY());
    newVector.setZ( this->getZ()  -  Q.getZ());
 
    return newVector;
}

double Vector::dotProduct( Vector& Q )
{
    return this->getX()*Q.getX() + this->getY()*Q.getY() + this->getZ()*Q.getZ();
}
double Vector::getAngle( Vector& Q )
{
    this->normalize();
    Q.normalize();
    
     if(this->getLength()== 0  ||  Q.getLength()== 0 )
         throw DivideByZeroException();
    
    return acos(dotProduct(Q));
}

