

template <typename T>
class vector
{
public:

	typedef int size_type;

	class iterator
	{
	public:
		typedef iterator self_type;
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;
		iterator(pointer ptr = 0) : ptr_(ptr) { } //construct null pointer
		reference operator*() { return *ptr_; }
		pointer operator->() { return ptr_; }
		self_type operator+(difference_type integer) { ptr_ = ptr_ + integer; return *this; }
		self_type operator++() { self_type i = *this; ptr_++; return i; }
		self_type operator++(int junk) { ptr_++; return *this; }
		self_type operator-(size_type integer) { ptr_ = ptr_ - integer;   return *this; }
		self_type operator--() { self_type i = *this; ptr_--; return i; }
		self_type operator--(int junk) { ptr_--; return *this; }
		bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
		bool operator<=(self_type& rhs) { return (!(rhs < *this)); }
		bool operator>=(const self_type& rhs) { return (!(*this < rhs)); }
		bool operator<(const self_type& rhs) { return (this->ptr_ < rhs.ptr_); }
		bool operator>(const self_type& rhs) { return (rhs < *this); }
		size_type operator - (const iterator iter) { return ptr_ - iter.ptr_; }

	private:
		pointer ptr_;
	};

	class reverse_iterator
	{
	public:
		typedef reverse_iterator self_type;
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;
		reverse_iterator(pointer ptr = 0) : ptr_(ptr) { } //construct null pointer
		reference operator*() { return *ptr_; }
		pointer operator->() { return ptr_; }
		self_type operator-(difference_type integer) { ptr_ = ptr_ + integer; return *this; }
		self_type operator--() { self_type i = *this; ptr_++; return i; }
		self_type operator--(int junk) { ptr_++; return *this; }
		self_type operator+(size_type integer) { ptr_ = ptr_ - integer;   return *this; }
		self_type operator++() { self_type i = *this; ptr_--; return i; }
		self_type operator++(int junk) { ptr_--; return *this; }
		bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
		bool operator<=(const self_type& rhs) { return (!(rhs < *this)); }
		bool operator>=(const self_type& rhs) { return (!(*this < rhs)); }
		bool operator<(const self_type& rhs) { return (this->ptr_ < rhs.ptr_); }
		bool operator>(const self_type& rhs) { return (rhs < *this); }

	private:
		pointer ptr_;
	};

	class const_iterator
	{
	public:
		typedef const_iterator self_type;
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef int difference_type;
		typedef std::forward_iterator_tag iterator_category;
		const_iterator(pointer ptr = 0) : ptr_(ptr) { }
		self_type operator++() { self_type i = *this; ptr_++; return i; }
		self_type operator++(int junk) { ptr_++; return *this; }
		const reference operator*() { return *ptr_; }
		const pointer operator->() { return ptr_; }
		bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
	private:
		pointer ptr_;
	};

	///////////////Constructor/////////////////

	vector()
	{
		size_ = 0;
		cap = capacity();
		data_ = new T[size_ + 1];
	}

	vector(size_type size, T val)
	{
		data_ = new T[size + 1];
		size_ = size;
		cap = capacity();
		for (int i = 0; i < size; i++)
			data_[i] = val; //init elems to 0
	}

	vector(iterator first, iterator last)
	{
		cap = 0;
		size_ = 0;
		data_ = new T[size_ + 1];
		for (iterator i = last; i != first; i--)
		{
			insert(begin(), *i);
		}
	}

	vector(vector& x)
	{
		cap = 0;
		size_ = 0;
		data_ = new T[size_ + 1];
		for (iterator i = x.end() - 1; i >= x.begin(); i--)
		{
			insert(begin(), *i);
		}
	}
	/////////////////////////////////////////////////////
	~vector()
	{
		if (data_)
		{
			delete[] data_;
		}
	}
	////////////////////////copy//////////////////////////

	vector& operator= (vector& x)
	{
		cap = 0;
		size_ = 0;
		data_ = new T[size_ + 1];
		for (iterator i = x.end() - 1; i >= x.begin(); i--)
		{
			insert(begin(), *i);
		}
		return *this;
	}

	///////////////////////////////////////////////////////

	T& operator[](size_type index) //opoerator
	{
		assert(index < size_);
		return data_[index];
	}

	const T& operator[](size_type index) const
	{
		assert(index < size_);
		return data_[index];
	}

	iterator begin() { return iterator(data_); }
	iterator end() { return iterator(data_ + size_); }
	const_iterator begin() const { return const_iterator(data_); }
	const_iterator end() const { return const_iterator(data_ + size_); }

	void reserve(size_t ncapacity)
	{
		T *temp = new T[ncapacity]; //새로운 저장소를 할당
		if (size_) //보관된 요소가 있다면
		{
			for (size_type n = 0; n < size_; n++)
			{
				temp[n] = data_[n]; //기존 저장소에 보관된 요소를 새로운 저장소로 복사
			}
			delete[] data_; //기존 저장소를 소멸
		}
		data_ = temp; //base에 새로운 저장소를 대입
		cap = ncapacity; //새로운 저장소 용량 대입
	}

	void push_back(T t) { iterator it = insert(end(), t); }
	//////////////////////////////////////////////////////////////////////////////////////////////
	iterator insert(iterator at, T t)
	{
		//at의 상대적 위치를 계산
		size_t index = at - begin();
		//꽉 찼다면 용량을 늘려줌v
		if (size_ == cap)
		{
			reserve(cap + 1); //넣을수 있는 공간 2배로 생성
			//data_가 변하게 된다.
		}
		//보관할 위치 뒤에 있는 요소들 뒤로 한 칸씩 이동
		for (size_t n = size_; n > index; n--)
		{
			data_[n] = data_[n - 1];
		}
		data_[index] = t;
		size_++;

		return &data_[index];
	}
	void insert(iterator at, size_type n, T t) { for (int i = 0; i<n; i++) at = insert(at, t); }
	void insert(iterator position, iterator first, iterator last)
	{
		for (iterator it = last - 1; it >= first; it--)
		{
			position = insert(position, *it);
		}
	}

	void pop_back() { iterator it = erase(end()); }

	iterator erase(iterator at)
	{
		//at의 상대적 위치를 계산
		size_t index = at - data_;

		//보관할 위치 뒤에 있는 요소들 앞으로 한 칸씩 이동
		for (size_t n = index + 1; n < size_; n++)
		{
			data_[n - 1] = data_[n];
		}
		size_--;

		return &data_[index];
	}

	iterator erase(iterator first, iterator last)
	{
		iterator it;
		for (it = last - 1; it >= first; it--)
		{
			it = erase(it);
		}
		return it;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	size_type size() const { return size_; }
	size_type max_size() { return pow(2, 32) / sizeof(size_type)-1; }// char - 1byte, int - 4byte, double - 8byte
	bool empty() { return (size_ == 0) ? true : false; }

	void resize(size_type n, T val = 0)
	{

		if (size_ < n)
		{
			for (size_type i = size_; i < n; i++)
			{
				push_back(val); //기존 저장소에 보관된 요소를 새로운 저장소로 복사
			}
		}
		size_ = n;
	}

	size_type capacity()
	{
		size_type capacity = 1;
		while (capacity < size_) capacity *= 2;
		return capacity;
	}

	T& front() { return *begin(); }
	T& back() { iterator it = end(); it--; return *it; }
	T& at(size_type n) { return data_[n]; }

	void assign(size_type n, T val) { for (int i = 0; i < n; i++){ push_back(val); } }
	void assign(iterator it, iterator last){ for (iterator i = it; i != last; i++){ push_back(*i); } }

	void clear()
	{
		data_ = 0;
		size_ = 0;
	}

	void swap(vector& x)
	{
		T* tmp_data_ = x.data_;
		size_type tmp_size_ = x.size_;
		x.data_ = data_;
		x.size_ = size_;
		data_ = tmp_data_;
		size_ = tmp_size_;
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(data_ + size_ - 1);;
	}
	reverse_iterator rend()
	{
		return reverse_iterator(data_ - 1);
	}
private:
	T* data_;
	size_type size_;
	size_type cap;
};