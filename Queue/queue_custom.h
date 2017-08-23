//FIFO

//pop : pop_front
//front : c.front
//back : c.back

#include "deque_custom.h"
#include "vector_custom.h" // std::vector
#include "list_custom.h" // std::vector

template<class T, class _Container = deque<T>>class queue
{
public:
	typedef typename queue<T, _Container> _queue;
	typedef _Container container_type;
	typedef typename _Container::iterator::value_type value_type;
	typedef typename _Container::size_type size_type;
	typedef typename _Container::iterator::reference reference;
	queue() : c(){}
	queue(_queue& _Right) : c(_Right.c){}
	queue(container_type &ctnr) : c(ctnr){}
	explicit queue(_Container&& _Cont) : c(_STD move(_Cont)){}   // construct by moving specified container
	_queue& operator=(_queue& _Right){ c = _Right.c; return (*this); }
	size_type size() const	{ return (c.size()); }// test length of queue
	void push(const value_type& _Val){ c.push_back(_Val); }// insert element at end
	void pop(){ c.pop_front(); }	// erase last element
	bool empty(){ return (c.empty()); }// test if queue is empty
	reference front(){ return (c.front()); }// return last element of mutable queue
	reference back(){ return (c.back()); }// return last element of mutable queue
	void swap(_queue& _Right)
	{	// exchange contents with _Right
		_Container tmp = _Right.c;
		_Right.c = c;
		c = tmp;
	}
protected:
	_Container c;   // the underlying container
};