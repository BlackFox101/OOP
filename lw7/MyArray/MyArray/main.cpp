#include <iostream>
#include "CMyArray.h"

using namespace std;

int main()
{
    CMyArray<string> strings(3, "hello");

	cout << "size = " << strings.GetSize() << endl;
	for (size_t i = 0; i < strings.GetSize(); i++)
	{
		cout << i << ": " << strings[i] << endl;
	}
	strings.Resize(4);
	cout << "size = " << strings.GetSize() << endl;
	for (size_t i = 0; i < strings.GetSize(); i++)
	{
		cout << i << ": " << strings[i] << endl;
	}

	/*CMyArray<double> numbers(3, 3.14);
	for (size_t i = 0; i < numbers.GetSize(); i++)
	{
		cout << i << ": " << numbers[i] << endl;
	}*/
}