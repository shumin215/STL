#ifndef _LIST_HH_
#define _LIST_HH_

#include <iostream>
#include <memory>
#include <stdlib.h>

using namespace std;

template<typename T, typename Alloc = allocator<T> >
class MyList {
public:

    /*/////////////////////////////////////////////////
     *
     *      Member Typedefine
     *
     */ /////////////////////////////////////////////////
    typedef Alloc allocator_type;
    typedef size_t size_type;
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef ptrdiff_t difference_type;



    /*////////////////////////////////////////////////
     *
     *      Node Definition
     *
     */ //////////////////////////////////////////////
    class Node
    {
    public:

        Node() :
                data(NULL), next(NULL), prev(NULL) {}

        Node(value_type _data, Node* _next, Node* _prev)
        {
            this->data = _data;
            this->next = _next;
            this->prev = _prev;
        }

        // Copy Constructor
        Node(Node *_node):
            next(NULL), prev(NULL)
        {
            // If _node is end node
            if(_node == NULL && _node->getPrev() != _node)
            {
                this->data = _node->getPrev()->getData();
                cout << "Data : " << this->data << endl;

                return;
            }

            this->data = _node->data;
        }

        ~Node()
        {
            cout << "Called by Destructor at Node class" << endl;
        }

        value_type getData()
        {
            return this->data;
        }

        Node* getNext()
        {
            return next;
        }

        Node* getPrev()
        {
            return prev;
        }

        void setData(value_type &_data)
        {
            this->data = _data;
        }

        void setNext(Node* _next)
        {
            this->next = _next;
        }

        void setPrev(Node* _prev)
        {
            this->prev = _prev;
        }

        Node* operator=(Node* _node)
        {
            this->data = _node->data;
            this->next = _node->next;
            this->prev = _node->prev;

            return *this;
        }

    private:
        value_type data;
        Node* next;
        Node* prev;
    };

    /*/////////////////////////////////////////
     *
     *  Iterator Definition
     *
     *//////////////////////////////////////////

    class iterator
    {
    public:

        explicit iterator()
        {
            ptr_node = NULL;
        }

        explicit iterator(Node* _ptr_node)
        {
            this->ptr_node = _ptr_node;
        }

        // Copy Constructor
        iterator(iterator& _iter)
        {
            this->ptr_node = _iter.getPtr();
        }

        ~iterator()
        {
            cout << "Called by Destructor at iterator class" << endl;
        }

        Node* getPtr()
        {
            return this->ptr_node;
        }

        void setPtr(Node* _ptr_node)
        {
            this->ptr_node = _ptr_node;
        }

        // First operations, second ++
        iterator& operator++(int dummy)
        {
            iterator& i = *this;
            this->ptr_node = this->ptr_node->getNext();
            return i;
        }

        // First ++, Second operation
        iterator& operator++()
        {
            this->ptr_node = this->ptr_node->getNext();
            return *this;
        }

//      iterator operator--(int dummy)
//      {
//          cout << "Called --(int dummy)" << endl;
//          if(ptr_node == NULL)
//          {
//              ptr_node = head;
//              for(int i=0; i != size()-1; i++)
//              {
//                  ptr_node = ptr_node->getNext();
//              }
//          }
//          iterator i = *this;
//          cout << "Debug 0" << endl;
//          cout << ptr_node << endl;
//          ptr_node = ptr_node->getPrev();
//          return i;
//      }

        iterator& operator--(int dummy)
        {
            iterator i = *this;
            ptr_node = ptr_node->getPrev();
            return i;
        }

        iterator& operator--()
        {
            ptr_node = ptr_node->getPrev();
            return *this;
        }

        value_type operator*()
        {
            return ptr_node->getData();
        }

        Node* operator->()
        {
            return ptr_node;
        }

        bool operator==(iterator& _rhs)
        {
            return ptr_node == _rhs.getPtr();
        }

        bool operator!=(iterator& _rhs)
        {
            return ptr_node != _rhs.getPtr();
        }

        iterator& operator=(iterator& _rhs)
        {
//          cout << "Before Address : " << getPtr() << endl;
//
//          delete getPtr();
//          // iterator* temp(_rhs);                What is difference?
//          iterator* temp = new iterator(_rhs);    // What is difference?
//
//          cout << "After Address : " << temp->getPtr() << endl;

            iterator* temp = new iterator(_rhs);

            this->ptr_node = temp->getPtr();

            return *this;
        }


/*///////////////////////////////////////////////////
 *
 *  // We need to modify this operator overloading
 *
 *////////////////////////////////////////////////////

        iterator& operator+(const size_type& _value)
        {

            (*this)++;
//          iterator temp = *this;
//          Node* cur = temp.getPtr();
//
//          for(int i=0; i<_value; i++)
//          {
////                cur = cur->getNext();
//              temp++;
//          }

            return *this;
        }

    private:
        Node* ptr_node;
    };

public:
    Node* head;
    Node* tail;

    /*////////////////////////////////////
     *
     *      Constructor
     *
     */ ///////////////////////////////////
    explicit MyList()
    {
        this->head = NULL;
        this->tail = NULL;
    }

    explicit MyList(size_type _n, const value_type& _val) :
            head(NULL), tail(NULL)
    {
        for (int i = 0; i < _n; i++)
        {
            push_back(_val);
        }
    }

// Copy Constructor
    explicit MyList(MyList &_list):
            head(NULL), tail(NULL)
    {
        Node* cur = _list.head;

        while(cur != NULL)
        {
            this->push_back(cur->getData());
            cur = cur->getNext();
        }
    }

    ~MyList()
    {   }

    // Copy Constructor
//    explicit MyList(MyList& _list):
//        head(_list.head), tail(_list.tail)
//    {
//      this->clear();
//
//      iterator iter;
//
//      for(iter = _list.begin(); iter != _list.end(); iter++)
//      {
//          this->push_back()
//      }
//    }

    /*//////////////////////////////////////////
     *
     *      Member functions
     *
     */ /////////////////////////////////////////
    void push_back(const value_type& _val)
    {
        allocator_type alloc;

        Node* new_node = new Node(_val, NULL, NULL);
        tail = new_node;

        // If head is empty
        if (empty())
        {
            head = new_node;

            return;
        }
        // There is node
        else
        {
            Node* cur = head;

            while (cur->getNext() != NULL)
            {
                cur = cur->getNext();
            }

            cur->setNext(new_node);
            new_node->setPrev(cur);

            return;
        }
    }

    void push_front(const value_type& _val)
    {
        Node* new_node = new Node(_val, NULL, NULL);

        if (empty())
        {
            head = new_node;
            tail = new_node;

            return;
        }
        else
        {
            Node* first_node = head;

            new_node->setNext(first_node);
            first_node->setPrev(new_node);

            head = new_node;

            return;
        }
    }

    void pop_front()
    {
        head = head->getNext();

        delete head->getPrev();

        head->setPrev(NULL);
    }

    void pop_back() {
        tail = tail->getPrev();

        delete tail->getNext();

        tail->setNext(NULL);
    }

    bool empty() const {
        if (head == NULL)
            return true;
        else
            return false;
    }

    void assign (size_type _n, const value_type& _val)
    {
        clear();

        for(int i=0; i<_n; i++)
        {
            push_back(_val);
        }
    }

    // ????????????????????????????????????????????????????????????????????????
    //
    //  Is it right?
    //  I allocated a memory for making iterator at begin and end functions...
    //
    // ????????????????????????????????????????????????????????????????????????

    iterator& begin()
    {
        cout << "Begin Function" << endl;
        iterator* temp_iter = new iterator(head);

        return *temp_iter;
    }

    iterator& end()
    {
        cout << "End Function" << endl;
        iterator* temp_iter = new iterator(tail);

        temp_iter->setPtr(temp_iter->getPtr()->getNext());

        return *temp_iter;
    }

    void clear()
    {
        Node* cur = head;

        while(head != NULL)
        {
            head = head->getNext();
            delete cur;
            cur = head;
        }
    }

    size_type size() const
    {
        Node* cur = head;
        size_type count = 0;

        while(cur != NULL)
        {
            count++;
            cur = cur->getNext();
        }

        return count;
    }

    size_type max_size() const
    {
        return -1;
    }

    reference front()
    {
        reference temp = &head->getData();

        return temp;
    }

    const_reference front() const
    {
        const_reference temp = &head->getData();

        return temp;
    }

    reference back()
    {
        reference temp = &tail->getData();

        return temp;
    }

    const_reference back() const
    {
        const_reference temp = &tail->getData();

        return temp;
    }

    iterator insert(iterator &_position, const value_type& _val)
    {
        Node* cur = _position.getPtr();

        Node* new_node = new Node(_val, cur, cur->getPrev());

        if(cur == head)
        {
            cur->setPrev(new_node);
            head = new_node;

            return _position;
        }
        else if(cur == tail->getNext())
        {
            Node* temp = cur->getPrev();
            temp->setNext(new_node);
            tail = new_node;

            return _position;
        }

        Node* temp = cur->getPrev();
        temp->setNext(new_node);
        cur->setPrev(new_node);

        return _position;
    }

    void insert(iterator &_position, size_type _n, const value_type& _val)
    {
        for(int i=0; i<_n; i++)
        {
            insert(_position, _val);
        }
    }

    void insert(iterator &_position, iterator &_first, iterator &_last)
    {

        for(iterator &iter = _first; iter != _last; iter++)
        {
            Node* temp_node = iter.getPtr();
            insert(_position, temp_node->getData());
        }
    }

    bool isEndIterator(iterator &_iterator)
    {
        if(_iterator == this->end())
            return true;
        else
            return false;
    }

    iterator getPrevEndIterator(void)
    {
        iterator* temp_iter = new iterator(tail);

        return *temp_iter;
    }

    iterator erase (iterator &_position)
    {
        if(isEndIterator(_position))
        {
            this->pop_back();
        }
        else if(_position.getPtr() == head)
        {
            this->pop_front();
        }
        else
        {
            Node* cur = _position.getPtr();
            Node* temp = cur->getPrev();
            temp->setNext(cur->getNext());

            temp = cur->getNext();
            temp->setPrev(cur->getPrev());

            delete cur;
        }

        return _position;
    }

    /*???????????????????????????????????????????????????????
     *
     *  Erase function is not complete
     *
     ???????????????????????????????????????????????????????*/

    iterator erase (iterator _first, iterator _last)
    {
        size_type size = getNumberOfIterator(_first, _last);
        iterator iter = _first;
        iterator temp_iter;

        for(size_type i=0; i<size; i++)
        {
            cout << i+1 << "-";
//          cout << iter.getPtr()->getData() << "--->";
//          cout << "Number 2" << endl;
            erase(iter);
            iter++;
//          cout << "Number 1" << endl;
        }
        cout << endl;
//      while(iter != _last)
//      {
//          cout << "Number 1" << endl;
//          iterator temp_iter = iter;
//          iter++;
//          cout << "Number 2" << endl;
//          this->erase(temp_iter);
////            cout << "Erase : " << iter.getPtr()->getData() << endl;
////            cout << "Next Data : " << iter.getPtr()->getNext()->getData() << endl;
//          if(isEndIterator(iter))
//          {
//              break;
//          }
//      }

        cout << "It's finished" << endl;
        return _last;
    }

    void resize(size_type _n, value_type _val = value_type())
    {
        if(this->size() >= _n)
        {
            size_type difference = this->size() - _n;

            for(int i=0; i<difference; i++)
            {
                this->pop_back();
            }
        }
        else
        {
            size_type difference = _n - this->size();

            for(int i=0; i<difference; i++)
            {
                push_back(_val);
            }
        }
    }

    void swapList(MyList& _x)
    {
        swap(*this, _x);
    }

    void splice(iterator& _position, MyList& _x)
    {
        iterator temp_iter = _position;

        // If position is front
        if(temp_iter == this->begin())
        {
            temp_iter.getPtr()->setPrev(_x.tail);
            _x.tail->setNext(temp_iter.getPtr());

            head = _x.head;
        }
        // If position is end
        else if(temp_iter == this->end())
        {
            this->getPrevEndIterator().getPtr()->setNext(_x.head);
            _x.head->setPrev(this->tail);

            tail = _x.tail;
        }
        // The other positions, are middle
        else
        {
            Node* prev_temp_iter_node = temp_iter.getPtr()->getPrev();
            prev_temp_iter_node->setNext(_x.head);
            _x.head->setPrev(prev_temp_iter_node);

            temp_iter.getPtr()->setPrev(_x.tail);
            _x.tail->setNext(temp_iter.getPtr());
        }

    }

    // We make sure eliminate _i in _x List
    void splice(iterator &_position, MyList &_x, iterator &_i)
    {
        if(_i.getPtr() == NULL)
        {
            cout << "It is empty" << endl;
            return;
        }

        iterator temp_iter = _position;
        Node* new_node = new Node(_i.getPtr());

        _x.erase(_i);

        if(temp_iter == this->begin())
        {
            temp_iter.getPtr()->setPrev(new_node);
            new_node->setNext(temp_iter.getPtr());
            new_node->setPrev(NULL);

            head = new_node;
        }

        else if(temp_iter == this->end())
        {
            this->getPrevEndIterator().getPtr()->setNext(new_node);
            new_node->setPrev(this->tail);
            new_node->setNext(NULL);

            this->tail = new_node;
        }

        else
        {
            Node* prev_temp_iter_node = temp_iter.getPtr()->getPrev();
            prev_temp_iter_node->setNext(new_node);
            new_node->setPrev(prev_temp_iter_node);

            temp_iter.getPtr()->setPrev(new_node);
            new_node->setNext(temp_iter.getPtr());
        }
    }

    size_type getNumberOfIterator(iterator& _first, iterator& _last)
    {
        iterator &cur = _first;
        size_type count = 0;

        while(cur != _last)
        {
            count++;
            cur++;
        }

        return count;
    }

    void printList(void) {
        Node* cur = head;

        if(cur == NULL)
        {
            cout << "List is empty" << endl;
        }

        while (cur != NULL)
        {
            cout << cur->getData() << "-->";
            cur = cur->getNext();
        }
        cout << endl;
    }

private:
};

int main()
{
    MyList<string> second, third;


    second.push_back("A");
    second.push_back("B");
    second.push_back("C");
    second.push_back("D");
    second.push_back("E");

    third.push_back("1");
    third.push_back("2");
    third.push_back("3");

    MyList<string> fourth(third);

    second.printList();

    cout << endl << endl;

    second.resize(7, "B");

    second.printList();

    cout << "------- After splicing -------" << endl;

    second.splice(second.begin()++, third, third.begin());

    second.printList();

    third.printList();

//    second.erase(second.begin(),second.end());
//    second.erase(second.begin(), second.end());

//    second.printList();
    return 0;
}
#endif

