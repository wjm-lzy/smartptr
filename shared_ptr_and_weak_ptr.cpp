#include <bits/stdc++.h>

using namespace std;
//    shared_ptr and weak_ptr
//    shared_ptr称为强智能指针
//    weak_ptr称为弱智能指针
//    weak_ptr -> shared_ptr ->资源
//    为什么要存在弱智能指针：避免循环引用（交叉引用）
//class B;
//class A{
//public:
//    A(){cout<<"A"<<endl;}
//    ~A(){cout<<"~A"<<endl;}
//    shared_ptr<B> _ptrb;
//};
//class B{
//public:
//    B(){cout<<"B"<<endl;}
//    ~B(){cout<<"~B"<<endl;}
//    shared_ptr<A> _ptra;
//};
//
//int main(){
//    shared_ptr<A> pa(new A);
//    shared_ptr<B> pb(new B);
//    pa->_ptrb = pb;
//    pb->_ptra = pa;
//    cout<<pa.use_count()<<endl;
//    cout<<pb.use_count()<<endl;
//}

// 上述解决方法：定义的时候使用强智能指针，定义的时候使用弱智能指针
// 弱智能指针只是一个观察者，不能访问资源，知识观察资源是否存在
// 可以进行提升，提升为强智能指针使用，随着程序的运行，可能其资源已经释放了，那么就提升失败，返回空
//class B;
//class A{
//public:
//    A(){cout<<"A"<<endl;}
//    ~A(){cout<<"~A"<<endl;}
//    void testA(){ cout<<"wjm041006"<<endl; }
//    weak_ptr<B> _ptrb;
//};
//class B{
//public:
//    B(){cout<<"B"<<endl;}
//    ~B(){cout<<"~B"<<endl;}
//    weak_ptr<A> _ptra;
//    void func(){
//        shared_ptr<A> ps = _ptra.lock();
//        if(ps!= nullptr){
//            ps->testA();//ps结束：引用计数减少
//        }
//    }
//};
//
//int main(){
//    shared_ptr<A> pa(new A);
//    shared_ptr<B> pb(new B);
//    pa->_ptrb = pb;
//    pb->_ptra = pa;
//
//    pb->func();
//    cout<<pa.use_count()<<endl;
//    cout<<pb.use_count()<<endl;
//}

//接下来就是涉及到多线程访问共享对象的线程安全问题
class A{
public:
    A(){cout<<"A"<<endl;}
    ~A(){cout<<"~A"<<endl;}
    void testA(){ cout<<"wjm041006"<<endl; }

};

//子线程
//void handler01(A *q){
//    std::this_thread::sleep_for(std::chrono::second(2));
//    //q 访问对象的时候，需要观察对象是否存活，那么就需要使用智能指针
//    q->testA();
//}
//
//主线程
//int main(){
//    A *p = new A();
//    thread t1(handler01,p);
//    delete p;
//    t1.join();
//}


void handler01(weak_ptr<A> pw){
    std::this_thread::sleep_for(std::chrono::seconds(2));
    //q 访问对象的时候，需要观察对象是否存活，那么就需要使用智能指针
    shared_ptr<A> sp = pw.lock();
    if(sp!= nullptr){
        sp->testA();
    }
    else{
        cout<<"对象以及析构";
    }
}

int main(){
    {
        shared_ptr<A> p(new A());
        thread t1(handler01,weak_ptr<A>(p));
        t1.detach();

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    std::this_thread::sleep_for(std::chrono::seconds(10));
}
