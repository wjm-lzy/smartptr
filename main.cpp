#include <bits/stdc++.h>
using namespace  std;

template<typename T>
class RefCnt{
public:
    RefCnt(T *ptr = nullptr):mptr(ptr){
        if(mptr!=nullptr){
            mcount=1;
        }
    }
    void addRef(){ mcount++; }
    int delRef() { return --mcount; }
private:
    T *mptr;
    int mcount;
};

template<typename T>
class CSmartPtr{
public:
    CSmartPtr(T *ptr = nullptr):mptr(ptr){
        mpRefCNt = new RefCnt<T>(mptr);
    }
    ~CSmartPtr(){
        if(0 == mpRefCNt->delRef()){
            delete mptr;
            mptr = nullptr;
        }

    }

    //利用指针访问指向的对象
    T &operator*() {return *mptr;}

    //利用指针访问函数方法
    T *operator->() {return mptr;}

    //重写拷贝构造
    CSmartPtr(const CSmartPtr<T> &src)
        :mptr(src.mptr),mpRefCNt(src.mpRefCNt){
        if(mptr!= nullptr)
            mpRefCNt->addRef();
    }
    CSmartPtr<T>& operator=(const CSmartPtr<T> &src)
    {
        if(this == &src){
            return *this;
        }
        if(0 == mpRefCNt->delRef()){
            delete mptr;
        }
        mptr = src.mptr;
        mpRefCNt = src.mpRefCNt;
        mpRefCNt->addRef();
        return *this;

    }

private:
    T *mptr;
    RefCnt<int> * mpRefCNt;//指向引用计数对象的指针
};

int main(){
    //利用栈上对象出作用域自动释放构造的
    CSmartPtr<int> ptr1(new int);
    CSmartPtr<int> ptr2(ptr1);
    CSmartPtr<int> ptr3;
    ptr3 = ptr2;
    *ptr1 = 20;
    cout<<*ptr2<<" "<<*ptr3;
    return 0;
}