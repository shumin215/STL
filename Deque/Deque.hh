#ifndef _DEQUE_HH_
#define _DEQUE_HH_
 
#include <iostream>
#include <memory>
 
using namespace std;
template<typename T, typename Alloc = allocator<T> >
class MyDeque
{
public:
    // Member Type
    typedef size_t size_type;
    typedef Alloc allocator_t;
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
 
    class iterator
    {
    public:
        typedef iterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef const value_type* const_pointer;
        typedef ptrdiff_t difference_type;
 
 
        iterator()
        {
            ptr = NULL;
        }
 
        iterator(pointer _ptr) :ptr(_ptr)    {}
 
        self_type operator++(int dummy)
        {
            self_type i = *this;
            ptr++;
            return i;
        }
        self_type operator++()
        {
            ptr++;
            return *this;
        }
 
        self_type operator--(int dummy)
        {
            self_type i = *this;
            ptr--;
            return i;
        }
        self_type operator--()
        {
            ptr--;
            return *this;
        }
 
        pointer operator->()
        {
            return ptr;
        }
 
        value_type operator*()
        {
            return *ptr;
        }
 
        bool operator==(const self_type& rhs)
        {
            return ptr == rhs.ptr;
        }
        bool operator!=(const self_type& rhs)
        {
            return ptr != rhs.ptr;
        }
 
        pointer operator+(const self_type& rhs)
        {
//            self_type temp(ptr + rhs.ptr);
            return ptr + rhs.ptr;
        }
 
        pointer operator+(const int& rhs)
        {
            return ptr + rhs;
        }
 
        pointer operator+(const pointer& rhs)
        {
            return ptr + rhs;
        }
 
        size_type operator-(const self_type& rhs)
        {
            return ptr - rhs.ptr;
        }
 
        pointer operator-(const pointer& rhs)
        {
            return ptr - rhs;
        }
 
        pointer operator-(const int& rhs)
        {
            return ptr - rhs;
        }
 
        self_type operator=(const self_type& rhs)
        {
            self_type temp(rhs.ptr);
            return temp;
        }
 
        self_type operator=(const pointer& rhs)
        {
            self_type temp(rhs);
            return temp;
        }
 
        pointer getPtr()
        {
            return this->ptr;
        }
 
        void setPtr(pointer _ptr)
        {
            this->ptr = _ptr;
        }
 
    private:
        pointer ptr;
    };
 
    class reverse_iterator
    {
    public:
        typedef reverse_iterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef const value_type* const_pointer;
        typedef ptrdiff_t difference_type;
 
        reverse_iterator()
        {
            ptr = NULL;
        }
 
        reverse_iterator(pointer _ptr) :ptr(_ptr)    {}
 
        self_type operator++(int dummy)
        {
            self_type i = *this;
            ptr--;
            return i;
        }
        self_type operator++()
        {
            ptr--;
            return *this;
        }
 
        self_type operator--(int dummy)
        {
            self_type i = *this;
            ptr++;
            return i;
        }
        self_type operator--()
        {
            ptr++;
            return *this;
        }
 
        pointer operator->()
        {
            return ptr;
        }
 
        value_type operator*()
        {
            return *ptr;
        }
 
        bool operator==(const self_type& rhs)
        {
            return ptr == rhs.ptr;
        }
        bool operator!=(const self_type& rhs)
        {
            return ptr != rhs.ptr;
        }
 
        pointer operator+(const self_type& rhs)
        {
//            self_type temp(ptr + rhs.ptr);
            return ptr + rhs.ptr;
        }
 
        pointer operator+(const int& rhs)
        {
            return ptr + rhs;
        }
 
        pointer operator+(const pointer& rhs)
        {
            return ptr + rhs;
        }
 
        size_type operator-(const self_type& rhs)
        {
            return ptr - rhs.ptr;
        }
 
        pointer operator-(const pointer& rhs)
        {
            return ptr - rhs;
        }
 
        pointer operator-(const int& rhs)
        {
            return ptr - rhs;
        }
 
        self_type operator=(const self_type& rhs)
        {
            self_type temp(rhs.ptr);
            return temp;
        }
 
        self_type operator=(const pointer& rhs)
        {
            self_type temp(rhs);
            return temp;
        }
 
        pointer getPtr()
        {
            return this->ptr;
        }
 
        void setPtr(pointer _ptr)
        {
            this->ptr = _ptr;
        }
 
    private:
        pointer ptr;
    };
/*///////////////////////////////////////////////////////
 *
 *         Operator Overloading
 *
 *////////////////////////////////////////////////////////
 
    MyDeque& operator=(MyDeque& _other)
    {
        swapDeque(*this, _other);
        return *this;
    }
 
    T& operator[](const size_type &_position)
    {
        return data_ptr[_position];
    }
 
/*/////////////////////////////////////////////////////////
 *
 *             Constructor
 *
 */////////////////////////////////////////////////////////
 
    explicit MyDeque():data_ptr(NULL), sz(0), capacity(0), iter(NULL)
    {
        allocator_t alloc;
 
        data_ptr = alloc.allocate(0);
        iter.ptr = data_ptr;
    }
 
    explicit MyDeque(size_type _n, const value_type& _val):sz(_n), capacity(_n), iter(NULL), rIter(NULL)
    {
        allocator_t alloc;
 
        data_ptr = alloc.allocate(_n);
//        iter.ptr = data_ptr;
 
        for(int i=0; i<_n; i++)
        {
            *(data_ptr + i) = _val;
        }
    }
 
    explicit MyDeque(iterator _first, iterator _last):iter(NULL), rIter(NULL)
    {
        sz = (_last-_first+1);
        capacity = sz;
        allocator_t alloc;
 
        data_ptr = alloc.allocate(capacity);
//        iter.ptr = data_ptr;
 
        for(int i=0; i != sz; i++)
        {
            *(data_ptr + i) = *(_first.getPtr() + i);
        }
    }
 
    // Copy Constructor
    explicit MyDeque(const MyDeque& _newDeque):sz(0), capacity(0), iter(NULL)
    {
//        data_ptr = new T[_newDeque.capacity];
        allocator_t alloc;
        data_ptr = alloc.allocate(_newDeque.capacity);
 
        // copy(InputIterator first, InputIterator last, OutputIterator result)
        copy(_newDeque.data_ptr, (_newDeque.data_ptr + (unsigned int)_newDeque.sz), data_ptr);
 
        iter = _newDeque.iter;
        capacity = _newDeque.capacity;
        sz = _newDeque.sz;
    }
 
    // Destructor
    ~MyDeque()
    {
        cout << "Destructor called" << endl;
        allocator_t alloc;
        alloc.deallocate(data_ptr, capacity);
    }
/*///////////////////////////////////////////////////////////////
 *
 *     Member Function
 *
 *////////////////////////////////////////////////////////////////
 
    // swap dequeues
    void swapDeque(MyDeque& _a,MyDeque& _b)
    {
        swap(_a.sz, _b.sz);
        swap(_a.capacity, _b.capacity);
        swap(_a.data_ptr, _b.data_ptr);
        swap(_a.iter, _b.iter);
    }
 
    size_type nearest_power_of_2(size_type _n)     // 1100 = 12
    {
        int count = 0;
        while(_n)
        {
            _n = _n >> 1;                        // 0110, 0011, 0001, 0000
            count++;                            // 1, 2, 3, 4
        }
        return 1ULL<<count;                        // 10000 = 16
    }
 
    void reserve(size_type _newCapacity)
    {
        _newCapacity = nearest_power_of_2(_newCapacity);
        allocator_t alloc;
 
        if(_newCapacity > capacity)
        {
            pointer temp = alloc.allocate(_newCapacity);
            // copy(InputIterator first, InputIterator last, OutputIterator result)
            copy(data_ptr, (data_ptr + capacity), temp);
 
            alloc.deallocate(data_ptr, capacity);
 
            data_ptr = temp;
            capacity = _newCapacity;
        }
    }
 
    // Change the size of the Deque exactly to "_newSize"
    void resize(const size_type &_newSize)
    {
        if(_newSize < sz)
        {
            for(size_type i=0; i<sz; i++)
            {
                data_ptr[i].~T();
            }
        }
        else if(_newSize > capacity)
        {
            reserve(_newSize);
        }
        sz = _newSize;
    }
 
    void push_back(const T& val)
    {
        if(capacity <= sz)
        {
            reserve(capacity);
        }
 
        data_ptr[sz] = val;
        sz++;
    }
 
    void push_front(const T& val)
    {
        if(capacity <= sz)
        {
            reserve(sz+1);
        }
        sz++;
 
        for(size_type i=sz-1; i>0; i--)
        {
            data_ptr[i] = data_ptr[i-1];
        }
        data_ptr[0] = val;
    }
 
    void pop_back()
    {
        if(this->sz > 0)
        {
            data_ptr[sz-1].~T();
            sz--;
        }
        else
        {
            cout << "Deque is empty" << endl;
        }
    }
 
    void pop_front()
    {
        if(this->sz > 0)
        {
            data_ptr[0].~T();
            for(size_type i=1; i<sz; i++)
            {
                data_ptr[i-1] = data_ptr[i];
            }
        }
        else
        {
            cout << "Deque is empty" << endl;;
        }
        sz--;
    }
 
    void insert(iterator _position, const value_type& _val)
    {
        if(capacity <= sz)
        {
            reserve(sz+1);
        }
        sz++;
 
        for(size_type i=sz-1; i>_position; i--)
        {
            data_ptr[i] = data_ptr[i-1];
        }
        data_ptr[_position] = _val;
    }
 
    void insert(iterator _position, size_type _n, const value_type& _val)
    {
        if(capacity < sz + _n)
        {
            reserve(sz+_n);
        }
        sz += _n;
 
        for(size_type i=sz-1; i>=_position+_n; i--)
        {
            data_ptr[i] = data_ptr[i-_n];
        }
 
        for(size_type i=_position; i<(_position+_n); i++)
        {
            data_ptr[i] = _val;
        }
    }
 
    void clear()
    {
        for(size_type i = 0; i<sz; i++)
        {
            data_ptr[i].~T();
        }
        sz = 0;
    }
 
    void assign(size_type _n, const value_type& _val)
    {
        clear();
 
        if(capacity < _n)
        {
            reserve(_n);
        }
 
        for(size_type i=0; i<_n; i++)
        {
            data_ptr[i] = _val;
        }
 
        sz = _n;
    }
 
    void assign(iterator _first, iterator _last)
    {
        clear();
 
        size_type temp_sz = _last - _first + 1;
 
        if(capacity < temp_sz)
        {
            reserve(temp_sz);
        }
 
        for(size_type i = 0; i<temp_sz; i++)
        {
            data_ptr[i] = _first + i;
        }
 
        sz = temp_sz;
    }
 
    reference at(size_type _n)
    {
        if(sz < _n)
        {
            cout << "It's not correct" << endl;
            return -999;
        }
 
        return data_ptr[_n];
    }
 
    reference front()
    {
        if(sz == 0)
        {
            cout << "Deque is empty" << endl;
        }
 
        return data_ptr[0];
    }
 
    reference back()
    {
        if(sz == 0)
        {
            cout << "Deque is empty" << endl;
        }
 
        return data_ptr[sz-1];
    }
 
    size_type getCapacity() const
    {
        return capacity;
    }
 
    size_type size() const
    {
        return sz;
    }
 
    bool empty() const
    {
        return sz == 0;
    }
 
 
    iterator begin()
    {
        iter.setPtr(data_ptr);
 
        return iter;
    }
 
    iterator end()
    {
        iter.setPtr(data_ptr + sz);
 
        return iter;
    }
 
    reverse_iterator rbegin()
    {
        rIter.setPtr(data_ptr + sz-1);
 
        return rIter;
    }
 
    reverse_iterator rend()
    {
        rIter.setPtr(data_ptr - 1);
 
        return rIter;
    }
 
    void printDeque()
    {
        cout << "Front - ";
        for(int i=0; i<sz; i++)
        {
            cout << *(data_ptr + i);
            cout << " ";
        }
        cout << " - End" << endl;;
    }
 
    // Member variable
private:
    T* data_ptr;
    size_type sz;
    size_type capacity;
 
public:
    iterator iter;
    reverse_iterator rIter;
};
 
#endif
