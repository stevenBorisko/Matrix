#include <iostream>
#include "Matrix/Matrix.hpp"

using namespace std;

int main() {
	Matrix a(4);
	a *= 2;
	cout << a << endl;
}
