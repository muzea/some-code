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

#include "solve.h"

#define _P_MARK(a,b) std::cout << "Problem "##a##"-"##b << endl
#define P_MARK(a,b) _P_MARK(#a,#b)

int main() {

	P_MARK(1,1);
	cout << P1::recursive(4) << endl;
	//cout << P1::tail_recursive(4) << endl;
	//cout << P1::formula_of_general_term(4) << endl;

	P_MARK(1,2);
	cout << P2::solve(10) << endl;


	int Arr[5] = { 1,3,5,7,8 };
	P_MARK(1,3);
	cout << P3::find(Arr, 5) << endl;

	int i = 0, j = 5;
	P_MARK(1,4);
	P4::find(Arr, sizeof Arr, i, j, 5);
	cout << i << "  " << j << endl;

	P_MARK(1,5);
	P5::solve();

	P_MARK(1,6);
	P6::solve();
	//P6::printNarcissistic<100,999>::print();

	P_MARK(1,7);
	P7::solve();

	P_MARK(1,8);
	P8::solve();

	P_MARK(1,9);
	P9::solve();

	P_MARK(1,10);
	P10::solve();
	

	P_MARK(2, 1);
	P2_1::solve();

	P_MARK(2, 2);
	P2_2::solve();

	P_MARK(2, 3);
	P2_3::solve();
	
	return 0;
}