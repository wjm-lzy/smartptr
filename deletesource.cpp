#include <bits/stdc++.h>

using namespace std;

/*
 智能指针中默认的删除器
 class Deletor{
public:
 void operator()(T *ptr){
    deletee ptr;
 }
};

 */

//template <typename T>
//class MyDeletor{
//public:
//    void operator()(T *ptr)const{
//        cout<<"mydeletor"<<endl;
//        delete []ptr;
//    }
//};
int main(){
    //template<_Tp, _Dp = default_delete<_Tp>> class unique_ptr
    //unique_ptr<int,MyDeletor<int>> ptr1(new int[100]);
    //上面虽然可以实现功能，但是对于每个删除器我们都需要定义一个模板，这样很不方便
    //下面使用lambda表达式来实现该功能-》函数对象
    //lambda [捕获外部变量](传入变量)->函数返回类型{函数体}
    unique_ptr<int,function<void (int*)>> ptr1(new int[100],
                                               [](int *p)->void{
        cout<<"wjm041006"<<endl;
        delete[] p;
    });


}