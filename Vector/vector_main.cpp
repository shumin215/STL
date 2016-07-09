#include <iostream>
#include "vector.hh"

int main()
{
    string str[10] = {"One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten"};

    MyVector<string> v1(str, 10);

    v1.showVector(v1);

/*
    MyVector<int> myvector1(5);
    MyVector<int> myvector2(100, 5);
    MyVector<string> myvector3("ABCDEF", 5);

    for(int i=0; i<10; i++)
    {
        myvector1.push_back(i);
    }

    cout << "Vector1 : ";
    showVector(myvector1);

    cout << "Vector2 : ";
    showVector(myvector2);


    cout << "Vector3 : ";
    showVector(myvector3);

    cout << "First data : " << myvector1.front() << endl;
    cout << "Last data : " << myvector1.back() << endl;

    cout << "Max Size : ";
    cout << myvector1.max_size() << endl;

    cout << endl << endl;

    MyVector<int>::iterator iter = myvector1.begin();
    iter++;
    cout << iter << endl;

    showVector(myvector1);
    myvector1.erase(iter);

    showVector(myvector1);


    cout << "---------------After Inserting --------------" << endl;
    myvector1.insert(myvector1.begin()+5,3, 100);
    showVector(myvector1);

*/

    return 0;
}
