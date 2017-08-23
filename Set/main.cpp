#include <iostream>
//#include <set>
#include "set_custom.h"
//using namespace std;

void display(set<int>& myset);
void example();
void example1();
int main()
{
	example();
	example1();
	return 0;
}








void display(set<int>& myset)
{
	for (set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void example()
{
	set<int> myset;

	myset.insert(100);
	myset.insert(200);
	myset.insert(300);

	std::cout << "-----------clear-----------\n";
	std::cout << "myset contains: ";
	display(myset);
	std::cout << "clear contains: ";
	myset.clear(); //clear
	display(myset);


	std::cout << "-----------count-----------\n";
	for (int i = 1; i<5; ++i) myset.insert(i * 3);    // set: 3 6 9 12
	std::cout << "myset contains:";
	display(myset);
	for (int i = 0; i<10; ++i)
	{
		std::cout << i;
		if (myset.count(i) != 0)
			std::cout << " is an element of myset.\n";
		else
			std::cout << " is not an element of myset.\n";
	}



	std::cout << "-----------size-----------\n";
	std::cout << "0. size: " << myset.size() << '\n';

	for (int i = 0; i<10; ++i) myset.insert(i);
	std::cout << "1. size: " << myset.size() << '\n';

	myset.insert(100);
	std::cout << "2. size: " << myset.size() << '\n';

	myset.erase(5);
	std::cout << "3. size: " << myset.size() << '\n';


	std::cout << "-----------max_size-----------\n";
	myset.clear();
	int i;

	if (myset.max_size()>1000)
	{
		for (i = 0; i<1000; i++) myset.insert(i);
		std::cout << "The set contains 1000 elements.\n";
	}
	else std::cout << "The set could not hold 1000 elements.\n";


	std::cout << "-----------equal_range-----------\n";
	myset.clear(); //clear
	for (int i = 1; i <= 5; i++) myset.insert(i * 10);
	pair<set<int>::iterator, set<int>::iterator> ret;
	ret = myset.equal_range(30);
	std::cout << "the lower bound points to: " << *ret.first << '\n';
	std::cout << "the upper bound points to: " << *ret.second << '\n';

	std::cout << "-----------erase&find-----------\n";
	set<int>::iterator it;
	for (int i = 1; i<10; i++) myset.insert(i * 10);  // 10 20 30 40 50 60 70 80 90

	it = myset.begin();
	++it;                                         // "it" points now to 20

	myset.erase(it);

	myset.erase(40);

	it = myset.find(60);
	myset.erase(it, myset.end());

	std::cout << "myset contains:";
	for (it = myset.begin(); it != myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void example1()
{
	std::cout << "-----------insert-----------\n";
	set<int> myset;
	set<int>::iterator it;
	pair<set<int>::iterator, bool> ret;

	// set some initial values:
	for (int i = 1; i <= 5; ++i) myset.insert(i * 10);    // set: 10 20 30 40 50

	ret = myset.insert(20);               // no new element inserted

	if (ret.second == false) it = ret.first;  // "it" now points to element 20

	myset.insert(it, 25);                 // max efficiency inserting
	myset.insert(it, 24);                 // max efficiency inserting
	myset.insert(it, 26);                 // no max efficiency inserting

	int myints[] = { 5, 10, 15 };              // 10 already in set, not inserted
	myset.insert(myints, myints + 3);

	std::cout << "myset contains:";
	for (it = myset.begin(); it != myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "-----------swap-----------\n";

	int myints1[] = { 12, 75, 10, 32, 20, 25 };
	set<int> first(myints1, myints1 + 3);     // 10,12,75
	set<int> second(myints1 + 3, myints1 + 6);  // 20,25,32

	first.swap(second);

	std::cout << "first contains:";
	for (set<int>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "second contains:";
	for (set<int>::iterator it = second.begin(); it != second.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "-----------lower_bound&upper_bound-----------\n";

	set<int> mysetb;
	set<int>::iterator itlow, itup;

	for (int i = 1; i<10; i++) mysetb.insert(i * 10); // 10 20 30 40 50 60 70 80 90

	itlow = mysetb.lower_bound(30);                //       ^
	itup = mysetb.upper_bound(60);                 //                   ^

	mysetb.erase(itlow, itup);                     // 10 20 70 80 90

	std::cout << "myset contains:";
	for (set<int>::iterator it = mysetb.begin(); it != mysetb.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';



}