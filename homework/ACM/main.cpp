#include <cmath>
#include <queue>
#include <stack>
#include <deque>
#include <string>
#include <vector>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

#define BLOCK_1
#define BLOCK_2

#include "solve.h"

#define _P_MARK(a,b) std::cout << "Problem "##a##"-"##b << endl
#define P_MARK(a,b) _P_MARK(#a,#b)

int main() {
#ifndef BLOCK_1
	P_MARK(1,1);
	cout << P1_1::recursive(4) << endl;
	//cout << P1_1::tail_recursive(4) << endl;
	//cout << P1_1::formula_of_general_term(4) << endl;

	P_MARK(1,2);
	cout << P1_2::solve(10) << endl;


	int Arr[5] = { 1,3,5,7,8 };
	P_MARK(1,3);
	cout << P1_3::find(Arr, 5) << endl;

	int i = 0, j = 5;
	P_MARK(1,4);
	P1_4::find(Arr, sizeof Arr, i, j, 5);
	cout << i << "  " << j << endl;

	P_MARK(1,5);
	P1_5::solve();

	P_MARK(1,6);
	P1_6::solve();
	//P1_6::printNarcissistic<100,999>::print();

	P_MARK(1,7);
	P1_7::solve();

	P_MARK(1,8);
	P1_8::solve();

	P_MARK(1,9);
	P1_9::solve();

	P_MARK(1,10);
	P1_10::solve();
	
#endif
#ifndef BLOCK_2
	P_MARK(2, 1);
	P2_1::solve();

	P_MARK(2, 2);
	P2_2::solve();

	P_MARK(2, 3);
	P2_3::solve();
#endif
	P_MARK(3, 1);
	P3_1::solve();

	P_MARK(3, 2);
	P3_2::solve();

	P_MARK(3, 3);
	int arr[5] = { 1,4,3,5,2 };
	P3_3::qsort(arr, arr + 5);
	cout << P3_3::binary_search(arr, arr + 5, 3) << endl;

	P_MARK(3, 4);
	P3_4::solve();

	P_MARK(3, 5);
	cout<<P3_5::solve(4,5)<<endl;

	P_MARK(3, 6);
	P3_6::solve();

	P_MARK(3, 7);
	P3_7::solve();
	return 0;
}