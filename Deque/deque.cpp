#include <iostream>
#include <math.h>
#include <memory>

using namespace std;
//template <typename T, typename Alloc = allocator<T> >
template <typename T>
class MyDeque
{
 public :   
    // Member Type  
    typedef size_t size_type;

    class iterator
    {
        public:
            typedef iterator self_type;
            typedef T value_type;
            typedef T& reference;
            typedef T* pointer;
            typedef const value_type* const_pointer;
            typedef ptrdiff_t difference_type;

            iterator(pointer _ptr):ptr(_ptr){}
            
            self_type operator++()
            {
                self_type i = *this;
                ptr++;
                return i;
            }
            self_type operator++(int)
            {
                ptr++; 
                return *this;
            }

            pointer operator->()
            {
                return ptr;
            }

            pointer operator*()
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

        public:
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

            reverse_iterator(pointer _ptr):ptr(_ptr){}
            
            self_type operator++()
            {
                self_type i = *this;
                ptr++;
                return i;
            }

            self_type operator++(int)
            {
                ptr++; 
                return *this;
            }

            pointer operator->()
            {
                return ptr;
            }

            pointer operator*()
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

        public:
            pointer ptr;
    };

    class Capacity
    {

    };

    typedef T value_type;
    typedef value_type pointer;
    typedef value_type& reference;

    // Constructor

    MyDeque():data(0), size(0), capacity(0), iter(NULL)
    {
    }
    // Member variable
private :
    T* data;
    size_type size;
    size_type capacity;
    iterator iter;
};


int main()
{
    MyDeque<int> deq1;


    return 0;
}
