/* 
 * File:   divideByZeroException.h
 * Author: treinamento
 *
 * Created on September 25, 2014, 8:56 AM
 */

#ifndef DIVIDEBYZEROEXCEPTION_H
#define	DIVIDEBYZEROEXCEPTION_H
#include<stdexcept>
  
using std :: runtime_error;
 
class DivideByZeroException : public runtime_error
{
    public:
        //Construtor que trata a excecao da tentativa de divisao por zero.
        DivideByZeroException() : runtime_error( " Tentativa de divisao por zero "){};
};

#endif	/* DIVIDEBYZEROEXCEPTION_H */

