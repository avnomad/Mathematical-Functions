#include <iostream>
using std::wcout;
using std::wcin;
using std::endl;

#include <iomanip>
using std::setw;
using std::setprecision;

#include <cstdlib>
using std::system;

#include <cmath>

#include <Math/mathematical functions.h>
using namespace Math::MathematicalFunctions;

int main()
{
	wcout << std::fixed << setprecision(12);
	wcout << exp(20,1e-30)<<endl;
	wcout << std::exp(20.0)<<endl;

	system("pause");
	return 0;
} // end function main
