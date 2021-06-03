#include <iostream>
#include "CMyArray.h"

using namespace std;

int main()
{
    CMyArray<int> vector;
	//cout << "size: " << vector.GetSize() << endl;
	//cout << "vector[0]: " << vector[0] << endl;
	vector.PushBack(1);
	vector.PushBack(2);
	vector.PushBack(3);

	CMyArray<int>::iterator it;
	//CMyArray<int>::const_iterator it1;
	/*it = vector.begin();
	cout << *it << endl;
	it = vector.end() - 1;
	cout << *it << endl;*/
	
	for (it = vector.begin(); it != vector.end(); it++)
	{
		cout << *it << endl;
	}
}