#include"List.hh"
#include <iostream>

using namespace std;

int main() 
{
	MyList<string> first;

	MyList<string> second(3, "A");

	second.push_back("Lee");
	second.push_back("Kim");
	second.push_back("Park");
	second.push_back("Jo");

	second.push_front("Oh");

	second.printList();

	cout << "After Pop" << endl;

	second.pop_front();
	second.pop_front();

	second.printList();

    cout << "After clearing" << endl;

    second.clear();

    second.printList();

    cout << "After assigning" << endl;

    second.assign(3, "Shumin");

    second.printList();

    MyList<string>::iterator i;
    for(i=second.begin(); i != second.end(); i++)
    {
        cout << ' ' << *i;
    }

    cout << endl;


	return 0;
}
