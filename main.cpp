#include "Vector.h"
using namespace Vector;

int main()
{
	vector<string> v1(20);	// 20 elements, each initialized to 0
	cout << "Size of v1: " << v1.size() << endl;

	vector<string> v2;
	v2.push_back("a");
	v2.push_back("b");
	v2.push_back("c");
	v2.push_back("d");
	v2.push_back("e");
	cout << v2 << endl;

	vector<string> v3 = v2; 	// what happens here?
	vector<string> v4;
	v4 = v2;					// what happens here?
	v2[0] = "Test2";
	v3[0] = "Test3";
	v4[0] = "Test4";
	cout << "Independent copies: " << v2[0] << " " << v3[0] << " " << v4[0] << endl;

	string d;

	vector<string> v5(3);
	string s;
	cout << "Input 3 strings: ";
	for (int i = 0; i < 3; i++)
	{
		cin >> s;
		v5.at(i) = s;
	}
	v5.push_back("Hello");
	v5.resize(100);  //will fill the rest with empty strings ""
	cout << v5 << endl;

	vector<int> v6;
	try {
		for (int i = 0; i < 5; ++i) v6.push_back(i);
		for (size_t i = 0; i <= v6.size(); ++i)
			cout << "v[" << i << "]==" << v6.at(i) << '\n';
	}
	catch (out_of_range_) {		// we’ll get here (why?)
		cout << "out of range error" << endl;
	}
	cout << v6 << endl;

	vector<double> v7;
	v7.push_back(3.14);
	const vector<double> v8 = v7;
	double d1 = v8[7];	// call the const version of [ ]
	double d2 = v7[7];	// call the non-const version of [ ]
	//v8[7] = 9;		// error: call the const version of [ ]
	v7[7] = 9;		// call the non-const version of [ ]: ok 

	cout << "Press any key then enter to exit: ";
	cin >> d;

	return 0;
}//in visual studio put a breakpoint here to see destructors