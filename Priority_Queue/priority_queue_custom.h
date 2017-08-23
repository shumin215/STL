//FIFO

//pop : pop_back
//front : c.front
//back : c.back

#include <queue>

#include "deque_custom.h"
#include "vector_custom.h" // std::vector
#include "list_custom.h" // std::vector

template<class T>
class less
{
public:
	bool operator()(const T& Left, const T& Right)
	{
		return (Left > Right);
	}
};

template < class T, class _Container = vector<T>, class Comp = less < typename _Container::iterator::value_type >>
class priority_queue
{
public:
	typedef typename priority_queue<T, _Container> _priority_queue;
	typedef _Container container_type;
	typedef typename _Container::iterator::value_type value_type;
	typedef typename _Container::size_type size_type;
	typedef typename _Container::iterator::reference reference;
	priority_queue() : c(), comp(){}
	priority_queue(_priority_queue& _Right) : c(_Right.c), com(_Right.comp){}
	priority_queue(container_type &ctnr) : comp()
	{
		_Container c = new _Container;
		_Container::iterator it = ctnr.begin();
		while (it != c.end())
		{
			push(*it);
			it++;
		}

	}

	explicit priority_queue(_Container&& _Cont) :c(), comp(_Cont){}   // construct by moving specified container
	_priority_queue& operator=(_priority_queue& _Right){ c = _Right.c; comp = _Right.comp; return (*this); }
	size_type size() const   { return (c.size()); }// test length of priority_queue
	void push(const value_type& _Val)
	{
		_Container::iterator it = c.begin();
		_Container::iterator jt = c.end();
		for (it = c.begin(); it <= jt; it++)
		{
			if (comp(*it, _Val)){
				c.insert(it, _Val);
				return;
			}

		}
		c.push_back(_Val);
	}// insert element at end
	void pop()   { c.pop_back(); }   // erase last element
	bool empty(){ return (c.empty()); }// test if priority_queue is empty
	reference top(){ return (c.back()); }// return last element of mutable priority_queue

	void swap(_priority_queue& _Right)
	{   // exchange contents with _Right
		_Container tmp = _Right.c;
		_Right.c = c;
		c = tmp;
	}



	
public:
	_Container c;   // the underlying container
	Comp comp;
	friend class less<T>;
};