#include <iostream>

#include "poly_term.h"
#include "poly.h"
#include "spmatrix_term.h"
#include "spmatrix.h"
#include "list.h"

using namespace std;

#define polynomialsize 100  //設定一個裝所有多項式的矩陣的大小


//宣告一個全域變數，用來存所有的poly
poly_term array[polynomialsize];


list::list(int a[],int b){
    listArray = new int[b]; //動態陣列
    length = b;//長度
    for (int i = 0; i < b; i++) //把a的東西都放到b裡面
    {
        listArray[i] = a[i];
    }

}; //end construct

list list::merge(list b){
    int clistsize = this->length + b.length;        //設定list長度
    int *c;             //動態陣列
    c = new int[clistsize];
    int ai = 0;             //a的index
    int bi = 0;             //b的index
    for (int ci = 0; ci < clistsize; ci++)         //以c的index為主，因為是把東西放到c的陣列中
    {
        if (ai < this->length && bi < b.length){        //偵測看有沒有已經讀完的list
            if (this->listArray[ai] < b.listArray[bi])      //a比b小的話放a
            {
                c[ci] = this->listArray[ai];
                ai++; //放完後把a的index加一，所以到最後一個的時候會是a的長度-1，經過這行後變a的長度
            }
            else //b比a小或等於a的時候放b
            {
                c[ci] = b.listArray[bi];
                bi++;// 放完後把b的index加一，所以到最後一個的時候會是b的長度 - 1，經過這行後變b的長度
            }
        }
        else if (bi==b.length){                 //如果是b到最後一個了
            for (; ai < this->length; ai++)     //就把剩下的a放完
            { 
                c[ci] = this->listArray[ai];
                ci++;
            }
        }
        else if (ai == this->length)        //如果是a到最後一個了
        {                                   //就把剩下的b放完
            for (; bi < b.length; bi++)
            {
                c[ci] = b.listArray[bi];
                ci++;
            }
        }
    }
    list d(c, clistsize);       //  把它變成list的形式，才可以回傳
    return d;
}; //end merge

void list::Output(){
    int listsize = this->length;
    for (int i = 0; i < listsize; i++)
    {
        if (i == listsize - 1)      //如果到了最後一個
            cout << this->listArray[i] << endl;
        else
            cout << this->listArray[i] << ",";
    };
}; //end output

spmatrix::spmatrix(int a, int b, int c){
    Rows = b;
    Cols = c;
    NumberOfNonZeroValue = a;
    spmArray = new spmatrix_term [NumberOfNonZeroValue];
    for (int i = 0; i < NumberOfNonZeroValue; i++){
        spmArray[i].row = 0;
        spmArray[i].col = 0;
        spmArray[i].value = 0;
    }
}; // end construct

void spmatrix::FullOutput(){
    int arrayindex = 0;
    int changeline = 0;
    for (int i = 0; i < this->Rows; i++)
    {
        for (int j = 0; j < this->Cols; j++)
        {
            if ( this->spmArray[arrayindex].row == i && this->spmArray[arrayindex].col == j)
            {
                cout << this->spmArray[arrayindex].value;
                arrayindex++;
            }
            else{
                cout << 0;
            }
            changeline++;
            if (changeline % this->Cols == 0){
                cout << endl;
            }
            else{
                cout << ",";
            }
        }
    }

}; //end fulloutput

void spmatrix::SetValue(int d[]){

    //開始把稀疏矩陣放進去
    for (int i = 0; i < this->NumberOfNonZeroValue; i++)
    {
        spmArray[i].row = d[i * 3];
        spmArray[i].col = d[i * 3 + 1];
        spmArray[i].value = d[i * 3 + 2];
    }

}; //end setvalue

spmatrix spmatrix::Transpose(){
    int *position;
    position = new int[this->Cols];
    position[0] = 0;
    for (int i = 0; i < this->NumberOfNonZeroValue; i++)
    {
        for (int j = this->spmArray[i].col + 1; j < this->Rows; j++)
        {
            position[j]++;
        }
    }
    spmatrix a(this->NumberOfNonZeroValue, this->Rows, this->Cols);
    for (int i = 0; i < this->NumberOfNonZeroValue; i++){
        int index = position[this->spmArray[i].col];
        a.spmArray[index].row = this->spmArray[i].col;
        a.spmArray[index].col = this->spmArray[i].row;
        a.spmArray[index].value = this->spmArray[i].value;
        position[this->spmArray[i].col]++;
    }
    return a;
}; //end transpose

spmatrix spmatrix::Multi(spmatrix b){
    spmatrix d(this->Rows * b.Cols, this->Rows, b.Cols);
    if (this->Cols == b.Rows){
        spmatrix c = b.Transpose();
        int dspmArray_index = 0;
        for (int i = 0; i < this->NumberOfNonZeroValue; i++)
        {                                                       //輪過a的所有value
            for (int j = 0; j < c.NumberOfNonZeroValue; j++){   //輪過b的轉置矩陣c的所有value
                if (this->spmArray[i].col == c.spmArray[j].col){
                    d.spmArray[dspmArray_index].row = this->spmArray[i].row;
                    d.spmArray[dspmArray_index].col = c.spmArray[j].row;
                    d.spmArray[dspmArray_index].value = this->spmArray[i].value * c.spmArray[j].value;
                    dspmArray_index++;
                }
            }
        }
        //改spmArray大小
        d.ChangeSize(dspmArray_index + 1);
    }
    else{
        cout << "這兩個矩陣無法相乘" << endl;
    }
    return d;
}; //end multi

void spmatrix::ChangeSize(int size){
    this->NumberOfNonZeroValue = size;
    spmatrix_term *a;
    a = new spmatrix_term[size];
    for (int i = 0; i < size; i++){
        a[i].row = this->spmArray[i].row;
        a[i].col = this->spmArray[i].col;
        a[i].value = this->spmArray[i].value;
    }
    delete[] this->spmArray;
    this->spmArray = a;
}; //end changesize

int poly::Compare(float a,float b){
    if(a==b)
        return 0;       //0代表a＝b
    else if(a<b)
        return 1;       //1代表a<b
    else
        return 2;       //2代表a>b
}; //end Compare

void poly::SetValue(int b,float c[]){
    //b是poly的項數
    //c是要放的多項式的內容

    //基本變數設定
    NumberOfIndex = b;  //多項式的項數
    Start = 0;          //起始的index
    Finish = b-1;       //結束的index
    Free = b;           //開始空的index
    
    //開始把多項式放進去
    int i = Start;
    for (; i <=Finish ; i++)
    {
        ::array[i].coef = c[i * 2];
        ::array[i].exp = c[i * 2 + 1];
    }

}; //end setvalue

poly::poly(){
    this->Start = 0;
    this->Finish = 0;
    this->Free = 0;
    this->NumberOfIndex = 0;
}; //end construct

void poly::AddValue(poly a,int b, float c[]){
    //a是前一個poly
    //b是poly的項數
    //c是要放的多項式的內容

    //基本變數設定
    NumberOfIndex = b;          //多項式的項數
    Start = a.Free;             //起始的index
    Finish = a.Free + b - 1;    //結束的index
    Free = a.Free + b;          //開始空的index

    //開始把多項式放進去
    int i = Start;
    int j = 0;
    for (; i <= Finish; i++)
    {
        ::array[i].coef = c[j * 2];
        ::array[i].exp = c[j * 2 + 1];
        j++;
    }

}; //end setvalue

void poly::Output(){
    int i = this->Start;
    for (; i <= this->Finish; i++)
    {
        if(i==this->Finish)
            cout << ::array[i].coef << "x^" << ::array[i].exp << endl;
        else
            cout << ::array[i].coef << "x^" << ::array[i].exp << "+";
    }
}; //end Output

poly poly::Add(poly b){
    poly c;
    int aIndex = this->Start;
    int bIndex = b.Start;
    c.Start = b.Free;
    int cIndex = c.Start;
    while (aIndex <= this->Finish && bIndex <= b.Finish)
        switch (Compare(::array[aIndex].exp,::array[bIndex].exp))
        {
        case 0:
            ::array[cIndex].coef = ::array[aIndex].coef + ::array[bIndex].coef;
            ::array[cIndex].exp = ::array[aIndex].exp;
            aIndex++;
            bIndex++;
            cIndex++;
            break;
        case 1: //<
            ::array[cIndex].coef = ::array[bIndex].coef;
            ::array[cIndex].exp = ::array[bIndex].exp;
            bIndex++;
            cIndex++;

            break;

        case 2: //>
            ::array[cIndex].coef = ::array[aIndex].coef;
            ::array[cIndex].exp = ::array[aIndex].exp;
            aIndex++;
            cIndex++;
            break;
    }
    c.Finish = cIndex-1;
    c.Free = cIndex;
    c.NumberOfIndex = c.Finish - c.Start + 1;
    return c;
}; //end add

int main()
{
    //merge sort
    cout << "--------merge sort 測試--------" << endl;
    int lista[] = {2, 4, 5, 7};
    list a(lista,4);
    cout << "a:";
    a.Output();
    int listb[] = {1, 2, 3, 6};
    list b(listb,4);
    cout << "b:";
    b.Output();
    list c = a.merge(b);
    cout << "a,b merge sort:";
    c.Output();

    //多項式加法測試
    cout << "--------多項式加法測試--------" << endl;
    poly d;
    float Rawd[] = {2, 1000, 1, 0};
    d.SetValue(2, Rawd);
    cout << "a多項式：" << endl;
    cout<<"A(x) = ";
    d.Output();
    poly e;
    float Rawe[] = {1, 4, 10, 3, 3, 2, 1, 0};
    e.AddValue(d, 4, Rawe);
    cout << "b多項式：" << endl;
    cout<<"B(x) = ";
    e.Output();
    poly f = d.Add(e);
    cout << "c多項式=a多項式+b多項式:" << endl;
    cout<<"C(x) = ";
    f.Output();
    
    //稀疏矩陣乘法測試
    cout << "--------稀疏矩陣乘法測試--------" << endl;
    spmatrix g(8, 6, 6);
    int Rawg[] = {0, 0, 15, 0, 3, 22, 0, 5, -15, 1, 1, 11, 1, 2, 3, 2, 3, -6, 4, 0, 91, 5, 2, 28};
    g.SetValue(Rawg);
    cout << "p27稀疏矩陣" << endl;
    g.FullOutput();
    spmatrix h = g.Transpose();
    cout << "轉至後的p27稀疏矩陣" << endl;
    h.FullOutput();
    cout << "p27稀疏矩陣的平方" << endl;
    spmatrix i = h.Multi(g);
    i.FullOutput();
};
