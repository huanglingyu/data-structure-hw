#ifndef LIST_H
#define LIST_H
//merge sort的list 的class
class list
{
  public:
    list(int a[], int b); //construct
    list merge(list b);   //this和b做merge sort
    void Output();        //print list
  private:
    int *listArray; //list的陣列，這邊是用動態陣列，所以是設指標
    int length;     //list的長度
};                  //end list
#endif