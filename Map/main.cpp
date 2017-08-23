#include <string>
#include <iostream>
#include "map_custom.h"

bool fncomp(char lhs, char rhs) { return lhs<rhs; }

struct classcomp {
	bool operator() (const char& lhs, const char& rhs) const
	{
		return lhs<rhs;
	}
};

//#include <map>
//using namespace std;


void construct();
void insert_clear();
void count();
void size_maxsize();
void equal_range();
void erase_find();
void swap();
int main()
{
	construct();
	insert_clear();
	count();
	size_maxsize();
	equal_range();
	erase_find();
	swap();
	return 0;
}


void construct()
{
	std::cout << "-----------Construct-----------\n";
	map<char, int> first;

	first['a'] = 10;
	first['b'] = 30;
	first['c'] = 50;
	first['d'] = 70;


	map<char, int> second(first.begin(), first.end());
	//map<char, int> third(second);
	map<char, int> third(second);

	map<char, int, classcomp> fourth;                 // class as Compare

	// show content:
	for (map<char, int>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void insert_clear()
{
	std::cout << "-----------Insert-----------\n";
	map<char, int> mymap;

	// first insert function version (single parameter):
	mymap.insert(pair<char, int>('a', 100));
	mymap.insert(pair<char, int>('z', 200));

	pair<map<char, int>::iterator, bool> ret;
	ret = mymap.insert(pair<char, int>('z', 500));
	if (ret.second == false) {
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
	}

	// second insert function version (with hint position):
	map<char, int>::iterator it = mymap.begin();
	mymap.insert(it, pair<char, int>('b', 300));  // max efficiency inserting
	mymap.insert(it, pair<char, int>('c', 400));  // no max efficiency inserting

	// third insert function version (range insertion):
	map<char, int> anothermap;
	anothermap.insert(mymap.begin(), mymap.find('c'));

	// showing contents:
	std::cout << "mymap contains:\n";
	for (it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "anothermap contains:\n";
	for (it = anothermap.begin(); it != anothermap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "-----------Clear-----------\n";
	mymap.clear();
	std::cout << "mymap contains:\n";
	for (it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void count()
{
	std::cout << "-----------Count-----------\n";
	map<char, int> mymap;
	char c;

	mymap['a'] = 101;
	mymap['c'] = 202;
	mymap['f'] = 303;

	for (c = 'a'; c<'h'; c++)
	{
		std::cout << c;
		if (mymap.count(c)>0)
			std::cout << " is an element of mymap.\n";
		else
			std::cout << " is not an element of mymap.\n";
	}
}

void size_maxsize()
{
	std::cout << "-----------Size-----------\n";
	map<char, int> mymap;
	mymap['a'] = 101;
	mymap['b'] = 202;
	mymap['c'] = 302;
	std::cout << "mymap contains:\n";

	map<char, int>::iterator it = mymap.begin();
	for (it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "mymap.size() is " << mymap.size() << '\n';

	std::cout << "-----------Max_size-----------\n";
	int i;
	map<int, int> mymap_2;


	if (mymap_2.max_size()>1000)
	{
		for (i = 0; i<1000; i++) mymap_2[i] = 1;
		std::cout << "The map contains 1000 elements.\n";
	}
	else std::cout << "The map could not hold 1000 elements.\n";
}

void equal_range()
{
	std::cout << "-----------Equal_range-----------\n";
	map<char, int> mymap;

	mymap['a'] = 10;
	mymap['b'] = 20;
	mymap['c'] = 30;
	map<char, int>::iterator it = mymap.begin();
	std::cout << "mymap contains:\n";
	for (it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	pair<map<char, int>::iterator, map<char, int>::iterator> ret;
	ret = mymap.equal_range('b');

	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';

	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';
}

void erase_find()
{
	map<char, int> mymap;
	map<char, int>::iterator it;
	std::cout << "-----------Erase & Find-----------\n";
	// insert some values:
	mymap['a'] = 10;
	mymap['b'] = 20;
	mymap['c'] = 30;
	mymap['d'] = 40;
	mymap['e'] = 50;
	mymap['f'] = 60;

	std::cout << "mymap contains:\n";
	for (it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	it = mymap.find('b');
	mymap.erase(it);                   // erasing by iterator
	std::cout << "mymap contains:\n";
	for (it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	mymap.erase('c');                  // erasing by key

	it = mymap.find('e');
	mymap.erase(it, mymap.end());    // erasing by range
	std::cout << "mymap contains:\n";
	// show content:
	for (it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void swap()
{
	map<char, int> foo, bar;
	std::cout << "-----------Swap-----------\n";
	foo['x'] = 100;
	foo['y'] = 200;

	bar['a'] = 11;
	bar['b'] = 22;
	bar['c'] = 33;

	foo.swap(bar);

	std::cout << "foo contains:\n";
	for (map<char, int>::iterator it = foo.begin(); it != foo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "bar contains:\n";
	for (map<char, int>::iterator it = bar.begin(); it != bar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}
