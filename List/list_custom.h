

template <typename T>class list_node;

template <typename T>
class list
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
		iterator() : curr_node(0) {}
		reference operator*() { return curr_node->data; }
		iterator& operator=(const iterator& rhs) { this->curr_node = rhs.curr_node; return *this; }
		//iterator& operator=(iterator& rhs) { this->curr_node = rhs.curr_node; return *this; }
		bool operator==(const iterator& rhs) { return curr_node->data == rhs.curr_node->data; }
		bool operator!=(const iterator& rhs) { return curr_node->data != rhs.curr_node->data; }
		iterator& operator++() { curr_node = curr_node->next; return *this; }
		iterator operator++(int) { iterator tmp(*this); ++*this; return tmp; }
		iterator& operator--() { curr_node = curr_node->prev; return *this; }
		iterator operator--(int) { iterator tmp(*this); --*this; return tmp; }
		pointer* operator->() {
			return  &(curr_node->data);
		}
	private:
		list_node<T>* curr_node;
		friend class list<T>;
	};

	//Constructor
	list() :node(new list_node<T>)
	{
		node->next = node;
		node->prev = node;
		size_ = 0;
		//list_node<T> *temp = new list_node<T>(NULL);
		//first = last = temp;
	} //완료

	list(size_type n, T val) :node(new list_node<T>)
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
	list(InputIterator first, InputIterator last) :node(new list_node<T>)
	{
		node->prev = node;
		node->next = node;
		size_ = 0;
		insert(begin(), first, last);
	}
	/*
	default (1)
	explicit list (const allocator_type& alloc = allocator_type());//완료

	fill (2)
	explicit list (size_type n, const data_type& val = data_type(),
	const allocator_type& alloc = allocator_type());

	range (3)
	template <class InputIterator>
	list (InputIterator first, InputIterator last,
	const allocator_type& alloc = allocator_type());

	copy (4)
	list (const list& x);
	*/

	//Destructor
	~list() {
		//first = 0; last = 0; size_ = 0;
		//나중에 메모리할당해제 구현해야함
	}

	//iterator 관련 함수

	iterator begin() { return iterator(node->next); }
	iterator end() { return iterator(node); }
	//size_type size() { return size_; }
	size_type max_size() const { return pow(2, 32) / sizeof(T)-1; }// char - 1byte, int - 4byte, double - 8byte
	void resize(size_type n, T val = 0)
	{
		if (size_ < n)
		{
			for (size_type i = size_; i < n; i++)
			{
				push_back(val); //기존 저장소에 보관된 요소를 새로운 저장소로 복사
			}
		}
		else if (size_ > n)
		{
			for (size_type j = size_; j > n; j--)
			{
				pop_back(); //기존 저장소에 보관된 요소를 새로운 저장소로 복사
			}
		}
	}

	//리스트 동작함수
	T& front() { return *iterator(node->next); }
	T& back() { return *iterator(node->prev); }
	void push_front(const T& val) { iterator it = insert(begin(), val); }
	void push_back(const T& val) { iterator it = insert(end(), val); }

	void swap(list& x)
	{
		list_node<T> * tmp_node = x.node;
		size_type tmp_size_ = x.size_;
		x.node = node;
		x.size_ = size_;
		node = tmp_node;
		size_ = tmp_size_;
	}
	//capacity

	bool empty() const { return size_ == 0; }
	size_type size() { return size_; }
	//리스트 동작함수

	//assign

	template <class InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
		clear();
		insert(begin(), first, last);
	}

	void assign(size_type n, const T& val)
	{
		clear();
		insert(begin(), n, val);
	}

	/*
	range(1)
	template <class InputIterator>
	void assign(InputIterator first, InputIterator last);
	fill(2)
	void assign(size_type n, const value_type& val);

	*/
	// insert complete //

	iterator insert(iterator at, const T& val)
	{
		list_node<T> *tmp = new list_node<T>(val);
		list_node<T> *cur = at.curr_node;
		list_node<T> *prev = cur->prev;

		tmp->next = cur;
		cur->prev = tmp;
		prev->next = tmp;
		tmp->prev = prev;

		size_++;
		return iterator(prev);

	}

	void insert(iterator position, size_type n, const T& val)
	{
		for (size_type i = 0; i < n; i++)
			insert(position, val);
	}

	template<class inputIterator>
	void insert(iterator position, inputIterator first, inputIterator last)
	{
		for (inputIterator it = first; it != last; it++)
		{
			insert(position, *it);

		}
	}

	iterator erase(iterator position)
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
	iterator erase(iterator first, iterator last)
	{
		for (iterator it = first; it != last; it++)
		{
			it = erase(it);
		}

		return iterator(begin());
	}


	void splice(iterator position, list& x, iterator i = 0)
	{
		if (i == 0)
		{
			iterator x_begin = x.begin();
			iterator x_end = x.end();
			insert(position, x_begin, x_end);
			x.clear();
		}
		else
		{
			//erase 추가할껄
		}
	}
	void pop_front() { iterator it = erase(begin()); }
	void pop_back()
	{
		iterator it = end();
		it--;
		it = erase(it);
	}

	// insert end //

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

	void remove(const T& val)
	{

		for (iterator it = begin(); it != end(); it++)
		{
			if (*it == val)
			{
				it = erase(it);
			}
		}

	}

	template <class Predicate>
	void remove_if(Predicate pred)
	{
		for (iterator it = begin(); it != end(); it++)
		{
			if (pred(*it))
			{
				it = erase(it);
			}
		}
	}
	void reverse()
	{
		size_type pre_size_ = size_;
		for (iterator it = begin(); it != end(); it++) push_front(*it)
		for (size_type i = size_; i > pre_size_; i--) pop_back();
	}

	void unique()
	{
		for (iterator it = begin(); it != end(); it++)
		{
			T tmp_data = *it;
			iterator tmp_it = it;
			tmp_it++;
			for (iterator it_t = tmp_it++; it_t != end(); it_t++)
			{
				if (tmp_data == *it_t) it_t = erase(it_t);
			}
		}
	}
	template <class BinaryPredicate>
	void unique(BinaryPredicate binary_pred)
	{
		for (iterator it = begin(); it != end(); it++)
		{
			T tmp_data = *it;
			iterator tmp_it = it;
			tmp_it++;
			if (binary_pred(tmp_data, *tmp_it++))
			{
				tmp_it = erase(tmp_it);
			}
		}

	}

	void sort()
	{
		if (size_ <= 1)
		{
			return;
		}

		int j = 0;
		for (iterator it = end(); it != begin(); it--)
		{
			int i = 0;
			j++;
			for (iterator jt = begin(); jt != it; jt++)
			{
				if (jt.curr_node->next == it.curr_node) {
					break;
				}
				i++;
				if (*jt > jt.curr_node->next->data)
				{
					list_node<T> *curr = jt.curr_node->next;
					list_node<T> *curprev = curr->prev;
					list_node<T> *next = curr->next;
					list_node<T> *prev = curr->prev->prev;

					curr->prev = prev;
					curr->next = curprev;

					curprev->prev = curr;
					curprev->next = next;
					prev->next = curr;
					next->prev = curprev;
					jt--;

				}
			}
		}
	}

	template <class Compare>
	void sort(Compare comp)
	{
		if (size_ <= 1)
		{
			return;
		}

		int j = 0;
		for (iterator it = end(); it != begin(); it--)
		{
			int i = 0;
			j++;
			for (iterator jt = begin(); jt != it; jt++)
			{
				if (jt.curr_node->next == it.curr_node){
					break;
				}
				i++;
				if (comp(jt.curr_node->next->data, jt.curr_node->data))
				{
					list_node<T> *curr = jt.curr_node->next;
					list_node<T> *curprev = curr->prev;
					list_node<T> *next = curr->next;
					list_node<T> *prev = curr->prev->prev;

					curr->prev = prev;
					curr->next = curprev;

					curprev->prev = curr;
					curprev->next = next;
					prev->next = curr;
					next->prev = curprev;
					jt--;

				}
			}
		}
	}

	void merge(list& x)
	{
		for (iterator it = x.begin(); it != x.end(); it++)
		{
			push_back(*it);
		}
		sort();
		x.clear();
	}
	template <class Compare>

	void merge(list& x, Compare comp)
	{
		for (iterator it = x.begin(); it != x.end(); it++)
		{
			push_back(*it);
		}
		sort(comp);
		x.clear();
	}
private:
	list_node<T> *node;
	//list_node<T> *first;
	//list_node<T> *last;
	size_type size_;

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
	friend class list<T>;
};





