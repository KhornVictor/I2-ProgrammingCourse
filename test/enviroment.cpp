#include <iostream>
#include <string>
using namespace std;

int main()
{
    cout << "Your C++ environment works!" << endl;
    cout << "--------------------------------" << endl;

    string name = "student";
    cout << "Hello " << name << "!" << endl;

    int *p = new int; 
    *p = 42;
    cout << "Test: the value in the memory is " << *p << endl;
    delete p;

    cout << "--------------------------------" << endl;
    cout << "Now write your own code in this test/ folder." << endl;

    return 0;
}
