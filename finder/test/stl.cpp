#include <iostream>
#include <iterator>
using namespace std;

#include <algorithm>
#include <vector>

void print( vector<int> ) ;//utility function outputs a $container

int main()
{

 	vector<int> a;

	print(a);

  	// Place 9,8,7,6,5,4,3,2,1 into the vector

	a.push_back(1);
	a.push_back(3);
	a.push_back(3);
	a.push_back(3);
	a.push_back(2);
	a.push_back(2);
	a.push_back(1);

 	print(a); // elements of a are (9,8,7,6,5,4,3,2,1)

	a.erase(a.begin()+5);
	print(a);

 	sort( a.begin(), a.end() ); //in the STL <algorithm> library

 	print(a); // elements are nor in order.

	vector<int>::iterator new_end = unique( a.begin() , a.end() );

	print(a);

	vector<int>* b = new vector<int> (a.begin(),a.end() - 1);

	(*b)[0] = 4;

	print(*b);
	
	cout << (*b).size() << " " << a.size() << endl;

	vector<int>::iterator pos = find ((*b).begin(),(*b).end(),3);

	cout << *pos << endl;

	int teste = (*b).end() - (*b).begin();

	cout << teste << endl;

}

void print( vector<int> a)
{

 	for(vector<int>::iterator ai=a.begin(); ai!=a.end(); ++ai)

 		cout << *ai << " ";

 	cout << endl;

	cout << '[' << a.size() << ']' << endl;
 	cout << "----------------"<<endl;

}


