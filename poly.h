#ifndef POLY_H
#define POLY_H
//多項式的class
class poly
{
  public:
    poly();                                  //construct
    void SetValue(int b, float c[]);         //設定初始值
    void AddValue(poly a, int b, float c[]); //在原本的多項式後面加上其他的多項式
    void Output();                           //輸出值
    poly Add(poly b);                        //加poly B
    int Compare(float a, float b);           //比較a,b大小
  private:
    int Start;         //poly的起始array index
    int Finish;        //poly的結束array index
    int Free;          //空的array的index
    int NumberOfIndex; //多項式有多少項(finish-start+1)
};                     //end poly
#endif