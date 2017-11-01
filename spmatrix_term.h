
#ifndef SPMATRIX_TERM_H
#define SPMATRIX_TERM_H
//稀疏矩陣的某一項
class spmatrix_term
{
    friend class spmatrix; //spmatrix可以存取spmatrix_term的東西
  private:
    int row;   //第row列
    int col;   //第col行
    int value; //值是value
};             //end term
#endif