// map

////////////////현재 T가 string 일때 작동 안함

#include <string>
template<class _Ty1, class _Ty2> struct pair;
template<class T> class greater;
template <typename value_type>class list_node;

template <class Key, class T, class Compare = greater<T>>
class map
{
public:
	typedef Key key_type;
	typedef T mapped_type;
	typedef pair<Key, T> value_type;
	typedef Compare value_compare;

	typedef int size_type;

	class iterator
	{
	public:
		typedef iterator self_type;
		typedef int difference_type;
		iterator(list_node<value_type>*ptr) : curr_node(ptr) {}
		iterator() : curr_node() {}

		Key& operator*() { return curr_node->data.first; }
		T& operator&() { return curr_node->data.second; }

		iterator& operator=(const iterator& rhs) { this->curr_node = rhs.curr_node; return *this; }
		bool operator==(const iterator& rhs) { return curr_node->data.first == rhs.curr_node->data.first; }
		bool operator!=(const iterator& rhs) { return curr_node->data != rhs.curr_node->data; }
		iterator& operator++() { curr_node = curr_node->next; return *this; }
		iterator operator++(int) { iterator tmp(*this); ++*this; return tmp; }
		iterator& operator--() { curr_node = curr_node->prev; return *this; }
		iterator operator--(int) { iterator tmp(*this); --*this; return tmp; }
		value_type* operator->() { return  &(curr_node->data); }

	private:
		list_node<value_type>* curr_node;
		friend class map<Key, T>;
	};

	class const_iterator
	{
	public:
		typedef iterator self_type;
		typedef int difference_type;
		const_iterator(list_node<value_type>*ptr) : curr_node(ptr) {}
		const_iterator() : curr_node(NULL) {}

		Key& operator*() { return curr_node->data.first; }
		T& operator&() { return curr_node->data.second; }


		iterator& operator=(const iterator& rhs) { this->curr_node = rhs.curr_node; return *this; }
		bool operator==(const iterator& rhs) { return curr_node->data.first == rhs.curr_node->data.first; }
		bool operator!=(const iterator& rhs) { 
			 
			bool a=	curr_node->data != rhs.curr_node->data;
			return a;
		}
		iterator& operator++() { curr_node = curr_node->next; return *this; }
		iterator operator++(int) { iterator tmp(*this); ++*this; return tmp; }
		iterator& operator--() { curr_node = curr_node->prev; return *this; }
		iterator operator--(int) { iterator tmp(*this); --*this; return tmp; }
		value_type* operator->() {
			return  &(curr_node->data);
		}


	private:
		list_node<value_type>* curr_node;
		friend class map<Key, T>;
	};
	//operator

	map& operator= (const map& x)
	{
		size_ = x.size_;
		comp = x.comp;
		node = x.node;
		return  *this;
	}
	T& operator[] (Key k)
	{
		//if (T == std::string ) pair<Key, T> p (k,(T)(" "));
		pair<Key, T> p(k, NULL);

		pair<iterator, bool> flag;
		if (size_ == 0)
		{
			flag = insert(p);
			flag.first++;
			return &flag.first; // if no data
		}
		else
		{
			flag = insert(p);
			if (!flag.second) return &flag.first;
			flag.first++;
			return &flag.first;
		}
	}

	/////////////////////map construct//////////////////////////
	//Constructor
	map() :node(new list_node<value_type>), comp() //empty(1)
	{
		node->next = node;
		node->prev = node;
		size_ = 0;

	} //완료

	template <class InputIterator>
	map(InputIterator first, InputIterator last) :node(new list_node<value_type>), comp() //range(2)
	{
		node->prev = node;
		node->next = node;
		size_ = 0;
		insert(first, last);
	}

	map(const map& x) //copy(3)
	{
		size_ = x.size_;
		comp = x.comp;
		node = x.node;
	}

	//Destructor
	~map() {}

	iterator begin() { return iterator(node->next); }
	iterator end() { return iterator(node); }
	size_type size() { return size_; }
	size_type max_size() const { return pow(2, 32) / sizeof(T)-1; }// char - 1byte, int - 4byte, double - 8byte
	bool empty() const { return size_ == 0; }

	pair<iterator, bool> insert(const value_type& val) //pair<Key,T>
	{
		pair<iterator, bool> p;
		if (size() == 0)
		{
			p.first = map_insert(begin(), val);
			p.second = true;
			return p;
		}
		else
		{
			for (iterator it = begin(); it != end(); it++)
			{
				if (*it == val.first)
				{
					p.first = it;
					p.second = false;
					return p;

				}
				else if (*it > val.first) // input값이 데이터값보다 작을경우 실행
				{
					p.first = map_insert(it, val);
					p.second = true;
					return p;
				}

				if (it == iterator(node->prev)) // input값이 모든 데이터값보다 클경우
				{
					it++;
					p.first = map_insert(it, val);
					p.second = true;
					return p;
				}
			}
			return p;
		}
	}

	iterator map_insert(iterator position, const value_type& val)
	{
		list_node<value_type> *tmp = new list_node<value_type>(val);
		list_node<value_type> *cur = position.curr_node;
		list_node<value_type> *prev = cur->prev;

		tmp->next = cur;
		cur->prev = tmp;
		prev->next = tmp;
		tmp->prev = prev;

		size_++;
		return iterator(prev);
	}

	iterator insert(iterator position, const value_type& val)
	{
		pair<iterator, bool> p = insert(val);
		return p.first;
	}

	template<class inputIterator>
	void insert(inputIterator first, inputIterator last)
	{
		for (inputIterator it = first; it != last; it++)
		{
			pair<Key, T> p(*it, &it);
			pair<iterator, bool> k = insert(p);
		}
	}


	void erase(iterator position) //(1)
	{
		erasing(position);
	}

	iterator erasing(iterator position)
	{
		list_node<value_type> *curr = position.curr_node;
		if (empty())
		{
			return iterator(curr);
		}
		list_node<value_type> *next = curr->next;
		list_node<value_type> *prev = curr->prev;

		next->prev = prev;
		prev->next = next;

		delete curr;

		size_--;

		return iterator(prev);
	}

	size_type erase(const Key& val) //(2)
	{
		for (iterator it = begin(); it != end(); it++)
		{
			if (*it == val)
			{
				erase(it);
				return 1;
			}
		}
	}

	void erase(iterator first, iterator last) //(3)
	{
		for (iterator it = first; it != last; it++)
		{
			it = erasing(it);


		}
	}

	void clear()
	{
		list_node<value_type> *curr = begin().curr_node;
		while (curr->next != curr)
		{
			list_node<value_type> *next = curr->next;
			list_node<value_type> *prev = curr->prev;
			next->prev = prev;
			prev->next = next;

			delete curr;
			curr = next;
		}

		curr->prev = curr;
		curr->next = curr;
		size_ = 0;

	}

	void swap(map& x)
	{
		list_node<value_type> * tmp_node = x.node;
		size_type tmp_size_ = x.size_;
		x.node = node;
		x.size_ = size_;
		node = tmp_node;
		size_ = tmp_size_;
	}

	iterator find(const T& val)
	{
		for (iterator it = begin(); it != end(); it++)
		{
			if (*it == val)   return it;
		}
	}

	size_type count(const T& val)
	{
		for (iterator it = begin(); it != end(); it++)
		{
			if (*it == val)   return 1;
		}
		return 0;
	}

	pair<iterator, iterator> equal_range(const T& val)
	{
		pair<iterator, iterator> p;
		p.first = lower_bound(val);
		p.second = upper_bound(val);
		return p;
	}

	iterator lower_bound(const T& val)
	{
		return find(val);
	}
	iterator upper_bound(const T& val)
	{
		iterator it = find(val);
		it++;
		return it;
	}

private:
	list_node<value_type> *node;
	size_type size_;
	Compare comp;
};

template <typename value_type>
class list_node
{
public:
	list_node() : next(NULL), prev(NULL) {}
	list_node(const value_type& val) : next(NULL), prev(NULL), data(val) {}

public:
	value_type data;
	list_node *prev;
	list_node *next;
	//friend class map<map::key_type, map::mapped_type>;
};


template<class T>
class greater
{
public:
	bool operator()(const T& Left, const T& Right){ return (Left < Right); }
};

template<class _Ty1, class _Ty2>
struct pair
{   // store a pair of values
	typedef pair<_Ty1, _Ty2> _Myt;
	typedef _Ty1 first_type;
	typedef _Ty2 second_type;

	pair() : first(), second()   {  }
	pair(const _Ty1& _Val1, const _Ty2& _Val2) : first(_Val1), second(_Val2){}   // construct from specified values

	_Myt& operator=(const _Myt& _Right)
	{   // assign from copied pair
		first = _Right.first;
		second = _Right.second;
		return (*this);
	}

	bool operator !=(const _Myt& _Right)
	{

		return this != &_Right;
	}

	_Ty1 first;   // the first stored value
	_Ty2 second;   // the second stored value
};