#include "spmatrix_term.h"
#ifndef SPMATRIX_H
#define SPMATRIX_H
//稀疏矩陣的class
class spmatrix
{
  public:
    spmatrix(int a, int b, int c); //construct
    void SetValue(int d[]);        //設定初始值
    void FullOutput();             //印出完整矩陣
    spmatrix Transpose();          //轉置矩陣行和列互喚
    spmatrix Multi(spmatrix a);    //matrix 相乘
    void ChangeSize(int size);     //  spmatrix 有值的個數改變
  private:
    int Rows;                 //matrix的列數
    int Cols;                 //matrix的行數
    int NumberOfNonZeroValue; //matrix裡面非零的值的個數
    spmatrix_term *spmArray;  //裝有稀疏矩陣的陣列動態矩陣！
};                            //end spmatrix

#endif