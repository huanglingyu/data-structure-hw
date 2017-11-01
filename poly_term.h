#include "poly.h"

#ifndef POLY_TERM_H
#define POLY_TERM_H
//多項是的某一項
class poly_term
{
    friend class poly;  //poly可以存取poly_term的東西
  private:
    float coef; //那一項的coefficient
    float exp;  //那一項的exponent
};//end poly_term
#endif