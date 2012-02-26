#include <iostream>
using std::wcout;
using std::wcin;
using std::wcerr;
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

	for(unsigned int i = 0u ; i <= 20u ; i++)	// should overflow after 20
		wcout << setw(3) << i << "! = " << setw(result_digits) << factorial(i) << '\n';
	wcout << " max = " << setw(result_digits) << numeric_limits<decltype(factorial(0))>::max() << "\n\n" << endl;


	// test PascalTriangle
	try
	{
		const auto max_n = 15u;
		PascalTriangle pascalTriangle(max_n);
		for(auto k = 0u ; k < max_n ; k++)
		{
			for(auto n = 0u ; n < k ; n++)
				wcout << setw(5) << "";
			for(auto n = k ; n < max_n ; n++)
				wcout << setw(5) << pascalTriangle(n,k);
			wcout << '\n';
		} // end for
		wcout << endl;

		//wcout << pascalTriangle(-1,0) << endl; will throw
		//wcout << pascalTriangle(-1,-1) << endl; will throw
		//wcout << pascalTriangle(0,1) << endl; will throw
	}
	catch(const std::out_of_range &e)
	{
		wcerr << "error: " << e.what() << "\n\n" << endl;
	} // end catch
	catch(const std::length_error &e)
	{
		wcerr << "error: " << e.what() << "\n\n" << endl;
	} // end catch
	catch(const std::bad_alloc &e)
	{
		wcerr << "error: " << e.what() << "\n\n" << endl;
	} // end catch


	// test binomialCoefficient
	for(auto k = 0u ; k < 15 ; k++)
	{
		for(auto n = 0u ; n < k ; n++)
			wcout << setw(5) << "";
		for(auto n = k ; n < 15 ; n++)
			wcout << setw(5) << binomialCoefficient(n,k);
		wcout << '\n';
	} // end for


	// test PascalTriangle and binomialCoefficient
	const auto max_n = 68u;
	PascalTriangle pascalTriangle(max_n);
	for(auto n = 0u ; n <= max_n ; ++n)
		for(auto k = 0u ; k <= n ; ++k)
			try{
				if(pascalTriangle(n,k) != binomialCoefficient(n,k))
				{
					wcerr << "error: binomial coefficients computed in 2 different ways do not match." << endl;
				}
			}catch(const std::domain_error &e)
			{
				wcerr << "error: " << e.what() << "(" << n << "," << k << ")" << endl;
			} // end catch
	wcout << "\nbinomial coefficients computed in 2 different ways match\n(when no overflow occurs).\n\n" << endl;


	// test exp
	wcout << std::fixed << setprecision(12);
	wcout << exp(20,1e-30)<< endl;
	wcout << std::exp(20.0)<< endl;

	system("pause");
	return 0;
} // end function main
