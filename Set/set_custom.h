// set



template<class _Ty1, class _Ty2> struct pair;
template<class T> class greater;
template <typename T>class list_node;

template <class T, class Compare = greater<T>>
class set
{
public:
	typedef int size_type;

	class iterator
	{
	public:
		typedef iterator self_type;
		typedef T data_type;
		typedef T& reference;
		typedef T* pointer;
		typedef int difference_type;
		iterator(list_node<T>*ptr) : curr_node(ptr) {}
		iterator() : curr_node(NULL) {}
		reference operator*() { return curr_node->data; }
		iterator& operator=(const iterator& rhs) { this->curr_node = rhs.curr_node; return *this; }
		bool operator==(const iterator& rhs) { return curr_node->data == rhs.curr_node->data; }
		bool operator!=(const iterator& rhs) { return curr_node->data != rhs.curr_node->data; }
		iterator& operator++() { curr_node = curr_node->next; return *this; }
		iterator operator++(int) { iterator tmp(*this); ++*this; return tmp; }
		iterator& operator--() { curr_node = curr_node->prev; return *this; }
		iterator operator--(int) { iterator tmp(*this); --*this; return tmp; }
		pointer* operator->() { return  &(curr_node->data); }
	private:
		list_node<T>* curr_node;
		friend class set<T>;
	};

	class const_iterator
	{
	public:
		typedef const_iterator self_type;
		typedef T data_type;
		typedef T& reference;
		typedef T* pointer;
		typedef int difference_type;
		const_iterator(list_node<T>*ptr) : curr_node(ptr) {}
		const_iterator() : curr_node(NULL) {}
		reference operator*() { return curr_node->data; }
		const_iterator& operator=(const const_iterator& rhs) { this->curr_node = rhs.curr_node; return *this; }
		bool operator==(const const_iterator& rhs) { return curr_node->data == rhs.curr_node->data; }
		bool operator!=(const const_iterator& rhs) { return curr_node->data != rhs.curr_node->data; }
		const_iterator& operator++() { curr_node = curr_node->next; return *this; }
		const_iterator operator++(int) { const_iterator tmp(*this); ++*this; return tmp; }
		const_iterator& operator--() { curr_node = curr_node->prev; return *this; }
		const_iterator operator--(int) { const_iterator tmp(*this); --*this; return tmp; }
		pointer* operator->() { return  &(curr_node); }
	private:
		list_node<T>* curr_node;
		friend class set<T>;
	};


	//Constructor
	set() :node(new list_node<T>), comp()
	{
		node->next = node;
		node->prev = node;
		size_ = 0;

	} //완료

	set(size_type n, T val) :node(new list_node<T>), comp()
	{
		node->prev = node;
		node->next = node;
		size_ = 0;

		for (size_type i = 0; i < n; i++)
		{
			push_back(val);
		}
		//push back()구현해야 구현가능

	}

	template <class InputIterator>
	set(InputIterator first, InputIterator last) :node(new list_node<T>), comp()
	{
		node->prev = node;
		node->next = node;
		size_ = 0;
		insert(first, last);
	}

	//Destructor
	~set() {}

	iterator begin() { return iterator(node->next); }
	iterator end() { return iterator(node); }
	iterator rbegin() { return iterator(node->orev); }
	size_type size() { return size_; }
	size_type max_size() const { return pow(2, 32) / sizeof(T)-1; }// char - 1byte, int - 4byte, double - 8byte
	bool empty() const { return size_ == 0; }

	pair<iterator, bool> insert(const T& val)
	{
		pair<iterator, bool> p;
		//std::cout << "----pair start---- \n" << "size : " << size() << "   begin : " << *begin() << "   end : " << *(end()++) << std::endl;
		if (size() == 0)
		{
			p.first = set_insert(begin(), val);
			p.second = true;

			//std::cout << "IT contain : ";
			//for (iterator it = begin(); it != end(); ++it)
			//	std::cout << ' ' << *it;
			//std::cout << '\n';

			//std::cout << std::endl;
			return p;
		}
		else
		{
			for (iterator it = begin(); it != end(); it++)
			{
			//	std::cout << "val : " << val << " it value : " << *it << std::endl;
				if (*it == val)
				{
					p.first = it;
					p.second = false;


				//	std::cout << "IT contain : ";
				//	for (iterator it = begin(); it != end(); ++it)
				//		std::cout << ' ' << *it;
				//	std::cout << '\n';

				//	std::cout << "bool : " << p.second;
				//	std::cout << std::endl;
					return p;

				}
				else if (*it > val) // input값이 데이터값보다 작을경우 실행
				{
					p.first = set_insert(it, val);
					p.second = true;

				//	std::cout << "IT contain : ";
				//	for (iterator it = begin(); it != end(); ++it)
				//		std::cout << ' ' << *it;
				//	std::cout << '\n';

				//	std::cout << std::endl;
					return p;
				}

				if (it == iterator(node->prev)) // input값이 모든 데이터값보다 클경우
				{
					it++;
					p.first = set_insert(it, val);
					p.second = true;

				//	std::cout << "IT contain : ";
				//	for (iterator it = begin(); it != end(); ++it)
				//		std::cout << ' ' << *it;
				//	std::cout << '\n';

				//	std::cout << std::endl;
					return p;
				}
			}
			return p;
		}
	}

	iterator set_insert(iterator position, const T& val)
	{
		list_node<T> *tmp = new list_node<T>(val);
		list_node<T> *cur = position.curr_node;
		list_node<T> *prev = cur->prev;

		tmp->next = cur;
		cur->prev = tmp;
		prev->next = tmp;
		tmp->prev = prev;

		size_++;
		return iterator(prev);
	}

	iterator insert(iterator position, const T& val)
	{
		pair<iterator, bool> p = insert(val);
		return p.first;
	}

	template<class inputIterator>
	void insert(inputIterator first, inputIterator last)
	{
		for (inputIterator it = first; it != last; it++)
		{
			insert(*it);
		}
	}

	iterator erase(iterator position) //(1)
	{
		list_node<T> *curr = position.curr_node;

		if (empty())
		{
			return iterator(curr);
		}
		list_node<T> *next = curr->next;
		list_node<T> *prev = curr->prev;

		next->prev = prev;
		prev->next = next;

		delete curr;

		size_--;

		return iterator(prev);

	}

	size_type erase(const T& val) //(2)
	{
		for (iterator it = begin(); it != end(); it++)
		{
			if (*it == val)
			{
				it = erase(it);
				return *it;
			}
		}
	}

	iterator erase(iterator first, iterator last) //(3)
	{
		for (iterator it = first; it != last; it++)
		{
			it = erase(it);
		}
		return iterator(begin());
	}

	void clear()
	{
		list_node<T> *curr = begin().curr_node;
		while (curr->next != curr)
		{
			list_node<T> *next = curr->next;
			list_node<T> *prev = curr->prev;
			next->prev = prev;
			prev->next = next;

			delete curr;
			curr = next;
		}

		curr->prev = curr;
		curr->next = curr;
		size_ = 0;

	}

	void swap(set& x)
	{
		list_node<T> * tmp_node = x.node;
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
	list_node<T> *node;
	size_type size_;
	Compare comp;
};

template <typename T>
class list_node
{
public:
	list_node() : next(NULL), prev(NULL) {}
	list_node(const T& val) : next(NULL), prev(NULL), data(val) {}

public:
	T data;
	list_node *prev;
	list_node *next;
	friend class set<T>;
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

	_Ty1 first;   // the first stored value
	_Ty2 second;   // the second stored value
};