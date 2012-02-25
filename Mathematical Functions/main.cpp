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

#include <limits>
using std::numeric_limits;

int main()
{
	// test factorial
	const auto result_digits = numeric_limits<decltype(factorial(0))>::digits10+1;

	for(int i = 0 ; i <= 20 ; i++)	// should overflow after 20
		wcout << setw(3) << i << "! = " << setw(result_digits) << factorial(i) << '\n';
	wcout << " max = " << setw(result_digits) << numeric_limits<decltype(factorial(0))>::max() << "\n\n" << endl;

	// test exp
	wcout << std::fixed << setprecision(12);
	wcout << exp(20,1e-30)<<endl;
	wcout << std::exp(20.0)<<endl;

	system("pause");
	return 0;
} // end function main
