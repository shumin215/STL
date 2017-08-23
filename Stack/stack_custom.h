//LIFO

#include "deque_custom.h"
#include "vector_custom.h" // std::vector
#include "list_custom.h" // std::vector

template<class T, class _Container = deque<T>>class stack
{
public:
	typedef typename stack<T, _Container> _Stack;
	typedef _Container container_type;
	typedef typename _Container::iterator::value_type value_type;
	typedef typename _Container::size_type size_type;
	typedef typename _Container::iterator::reference reference;
	stack() : c(){}
	stack(_Stack& _Right): c(_Right.c){}
	stack(container_type &ctnr)	: c(ctnr){}
	explicit stack(_Container&& _Cont) : c(_STD move(_Cont)){}   // construct by moving specified container
	_Stack& operator=(_Stack& _Right){ c = _Right.c; return (*this); }
	size_type size() const	{ return (c.size()); }// test length of stack
	void push(const value_type& _Val){ c.push_back(_Val); }// insert element at end
	void pop(){ c.pop_back(); }	// erase last element
	bool empty(){ return (c.empty()); }// test if stack is empty
	reference top(){ return (c.back()); }// return last element of mutable stack
	void swap(_Stack& _Right)
	{	// exchange contents with _Right
		_Container tmp = _Right.c;
		_Right.c = c;
		c = tmp;
	}
protected:
	_Container c;   // the underlying container
};