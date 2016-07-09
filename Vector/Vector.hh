#ifndef _VECTOR_HH_
#define _VECTOR_HH_

#include <iostream>
#include <math.h>
using namespace std;

template <typename T>
class MyVector
{
private:
    unsigned int sz;
    unsigned int cap;
    unsigned int Log;
    T *v;

public:
    // Member Type
    typedef T* iterator; 
    typedef const T* const_iterator;

    // Constructor
    MyVector();
    explicit MyVector(unsigned int n);
    MyVector(const T &a, unsigned int n);
    MyVector(const T *a, unsigned int n);    // copy data from array to Vector
    MyVector(const MyVector &rhs);  // 복사생성자

    // Operator
    MyVector & operator=(MyVector &rhs);
    MyVector & operator=(const T &a);
    inline T & operator[](const int i);

    // Member Function
    inline size_t size() const;
    inline size_t max_size() const;
    inline size_t capacity() const;
    bool empty() const;
    T& front() const;
    T& back() const;
    T& at(int index) const;
    void pop_back();
    void push_back(const T& value);
    void clear();
    void reserve(unsigned int capacity);
    void resize(size_t size);
    void assign(const T &a, unsigned int number);
    void assign(const T *a, unsigned int number);
    iterator erase(iterator pointer);
    iterator erase(iterator first_pt, iterator last_pt); 

    iterator insert(iterator position, const T& value);
    void insert(iterator position, size_t n, const T& value);
//    void insert(iterator position, iterator first_pt, iterator last_pt);
 
    // Iterator Function
    iterator begin();
    iterator end();
    iterator rbegin();
    iterator rend();
    iterator operator++();
    iterator operator++(int);
    iterator operator--();
    iterator operator--(int);
    iterator operator+=(int& i);
    iterator operator-=(int& i);
    
    // Distructor
    ~MyVector();


    void showVector(MyVector<T> &vector);
};

/*///////////////////////////////////////////////////////////////
 *
 *      Constructor List
 *
 *//////////////////////////////////////////////////////////////

template <typename T>
MyVector<T>::MyVector():sz(0), v(0), cap(0) 
{
}

template <typename T>
MyVector<T>::MyVector(unsigned int n) : sz(0) 
{
    Log = ceil(log((double) n) / log(2.0));
    cap = 1 << Log;
    v = new T[cap];

//    cout << "Log : " << Log << endl;      // For debuging
//    cout << "cap : " << cap << endl;      // For debuging
}

template <typename T>
MyVector<T>::MyVector(const T &a, unsigned int n) : sz(n)
{
    Log = ceil(log((double) sz) / log(2.0));
    cap = 1 << Log;
    v = new T[cap];

    for(int i=0; i<sz; i++)
    {
        v[i] = a;
    }
}

template <typename T>
MyVector<T>::MyVector(const T *a, unsigned int n) : sz(n)
{
    Log = ceil(log((double) sz) / log(2.0));
    cap = 1 << Log;
    v = new T[cap];

    for(int i=0; i<sz; i++)
    {
        v[i] = *a;
        a++;
    }
}

template <typename T>
MyVector<T>::MyVector(const MyVector &rhs) 
: sz(rhs.sz), v(new T[rhs.sz]), cap(rhs.capacity), Log(rhs.Log)
{
    for(int i=0; i<sz; i++)
    {
        v[i] = rhs[i];
    }
}

/*///////////////////////////////////////////////////////////////
 *
 *      Operator List
 *
 *//////////////////////////////////////////////////////////////

template <typename T>
MyVector<T> &MyVector<T>::operator=(MyVector<T> &rhs)
{
    // If it's same with object
    if(this != &rhs)
    {
            // if object is not Null
            if(v != 0)
            {
                // Deallocate object
                delete[] v;
            }
            sz = rhs.sz;
            Log = rhs.Log;
            cap = rhs.cap;
            v = new T[cap];
            for(int i=0; i<sz; i++)
            {
                v[i] = rhs.v[i];
            }
    }
    return *this;
}

template <typename T>
MyVector<T> & MyVector<T>::operator=(const T &a)
{
    for(int i=0; i<sz; i++)
    {
        v[i] = a;
    }
    return *this;
}

template <typename T>
inline T & MyVector<T>::operator[](const int i)
{
    return v[i];
}
/*///////////////////////////////////////////////////////////////
 *
 *      Member Function List
 *
 *//////////////////////////////////////////////////////////////

template <typename T>
inline size_t MyVector<T>::size() const
{
    return sz;
}

template <typename T>
inline size_t MyVector<T>::max_size() const
{
    return -1;
}

template <typename T>
inline size_t MyVector<T>::capacity() const
{
    return cap;
}

template <typename T>
bool MyVector<T>::empty() const 
{
    return (sz == 0);
}

template <typename T>
T& MyVector<T>::front() const
{
    return v[0];
}

template <typename T>
T& MyVector<T>::back() const
{
    return v[sz-1];
}

template <typename T>
T& MyVector<T>::at(int index) const
{
    if(index > sz)
    {
        cout << "The index is out of number" << endl;
        return;
    }

    return v[index];
}

template <typename T>
void MyVector<T>::push_back(const T& value)
{
    if(sz > cap)
    {
        cout << "Store is full" << endl;
        return;
    }

//    cout << "push : " << value << endl;
//    cout << "sz : " << sz << endl;
    
    v[sz] = value;
    sz++;
}

template <typename T>
void MyVector<T>::pop_back()
{
    sz--;
}

template <typename T>
void MyVector<T>::clear()
{
    cap = 0;
    sz = 0;
    v = 0;
    Log = 0;
    //delete[] v;
}

template <typename T>
void MyVector<T>::resize(size_t size)
{
    Log = ceil(log((double) sz) / log(2.0));
//    cap = 1 << Log;
    reserve(1 << Log);
    sz = (unsigned int)size;
}

template <typename T>
void MyVector<T>::reserve(unsigned int capacity)
{
    T* newVector = new T[capacity];

    for(int i=0; i<sz; i++)
    {
        newVector[i] = v[i];
    }
    cap = capacity;
    delete[] v;
    v = newVector;
}

template <typename T>
void MyVector<T>::assign(const T &a, unsigned int number)
{
    delete[] v;

    sz = number;
    Log = ceil(log((double) sz) / log(2.0));
    cap = 1 << Log;
    v = new T[cap];

    for(int i=0; i<sz; i++)
    {
        v[i] = a;
    }
}

template <typename T>
void MyVector<T>::assign(const T *a, unsigned int number)
{
    delete[] v;

    sz = number;
    Log = ceil(log((double) sz) / log(2.0));
    cap = 1 << Log;
    v = new T[cap];

    for(int i=0; i<sz; i++)
    {
        v[i] = *a;
        a++;
    }
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::erase(iterator pointer)
{
    if(pointer < begin() || pointer > end())
    {
        cout << "Error : Its pointer is out of range" << endl;
        return end();
    }

    int index = (pointer - begin())/sizeof(T);
    for(int i=index; i<(sz-1); i++)
    {
        v[i] = v[i+1];
    }

    sz--;
    return pointer;
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::erase(iterator first_pt, iterator last_pt) 
{
    if(first_pt < begin() || last_pt > end())
    {
        cout << "Error : Its pointer is out of range" << endl;
        return end();
    }

    int difference_idx = ((last_pt - first_pt)/sizeof(T)) + 1;
    int first_idx = (first_pt - begin())/sizeof(T);
    int last_idx = (last_pt - begin())/sizeof(T);
    int changed_size = sz - difference_idx;

    for(int i=0; i<first_idx; i++)
    {
        v[i] = v[i+1];
    }

    for(int i=first_idx; i<changed_size; i++)
    {
        v[i] = v[i + difference_idx];
    }

    sz = sz - difference_idx;
    return first_pt;
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::insert(iterator position, const T& value)
{
    int index = position - begin();

    if(begin() + size() >= end())
    {
        cout << "Error : Pointer is out of range" << endl;
        resize(sz+1);
    }

    for(int i = sz-1; i>=index; i--)
    {
        v[i+1] = v[i];
    }
    v[index] = value;

    return position;
}

template <typename T>
void MyVector<T>::insert(iterator position, size_t n, const T& value)
{
    int index = position - begin();

    if(begin() + size() >= end())
    {
        cout << "Error : Pointer is out of range" << endl;
        resize(sz+n);
    }

    for(int i = sz-n-1; i>=index; i--)
    {
        v[i+n] = v[i];
        cout << "v[" << i << "] : " << v[i] << endl;;
    }

    for(int i=index; i<index+n; i++)
    {
        v[i] = value;
    }
}

///////////////// Iterator Function //////////////////

template <typename T>
typename MyVector<T>::iterator MyVector<T>::begin()
{
    return v;
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::end()
{
    return v + this->size();
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::rbegin()
{
    return (v+this->size());
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::rend()
{
    return v;
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::operator++()
{
    if(v == 0)
    {
        cout << "ERR : There is no data" << endl;
        return v;
    }
    else if(v >= (v + this->size()))
    {
        cout << "ERR : It's End of Size" << endl;
        return v;
    }

    v++;
    return v;
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::operator++(int)
{
    if(v == 0)
    {
        cout << "ERR : There is no data" << endl;
        return v;
    }
    else if(v >= (v + this->size()))
    {
        cout << "ERR : It's End of Size" << endl;
        return v;
    }
    
    v++;
    return v;
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::operator--()
{
    if(v == 0)
    {
        cout << "ERR : There is no data" << endl;
        return v;
    }
    else if(v >= (v + this->size()))
    {
        cout << "ERR : It's End of Size" << endl;
        return v;
    }
    v--;
    return v;   
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::operator--(int)
{
    if(v == 0)
    {
        cout << "ERR : There is no data" << endl;
        return v;
    }
    else if(v >= (v + this->size()))
    {
        cout << "ERR : It's End of Size" << endl;
        return v;
    }

    v--;
    return v;   
}
 
template <typename T>
typename MyVector<T>::iterator MyVector<T>::operator+=(int& i)
{
    iterator temp_iter = v;
    temp_iter = temp_iter + i;

    if(temp_iter == 0 || temp_iter > v + this->capacity())
    {
        cout << "ERR : There is no data" << endl;
        return v;
    }
    else if(temp_iter >= (v + this->size()))
    {
        cout << "ERR : It's End of Size" << endl;
        return v;
    }

    v = temp_iter;
    return v;   
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::operator-=(int& i)
{
    iterator temp_iter = v;
    temp_iter = temp_iter - i;

    if(temp_iter == 0 || temp_iter > v + this->capacity())
    {
        cout << "ERR : There is no data" << endl;
        return v;
    }
    else if(temp_iter >= (v + this->size()))
    {
        cout << "ERR : It's End of Size" << endl;
        return v;
    }

    v = temp_iter;
    return v;   
   
}
 
/*///////////////////////////////////////////////////////////////
 *
 *      Destruction List
 *
 *//////////////////////////////////////////////////////////////

template <typename T>
MyVector<T>::~MyVector()
{
    if(v != 0)
        delete[] v;
}

template <typename T>
void MyVector<T>::showVector(MyVector<T> &vector)
{
    if(vector.empty() == true)
    {
        cout << "Vector is empty" << endl;
        return;
    }

    for(int i=0; i<vector.size(); i++)
    {
        cout << vector[i] << ' ';
    }
    cout << endl;
}

#endif
