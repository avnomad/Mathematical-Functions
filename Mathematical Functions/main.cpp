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

#include <array>
using std::array;

#include <vector>
using std::vector;

#include <Math/mathematical functions.h>
using namespace Math::MathematicalFunctions;

#include <limits>
using std::numeric_limits;

#include <crtdbg.h>

#include <StopWatch.h>
#undef min
#undef max


int main()
{
	// enable head checks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_CHECK_ALWAYS_DF|_CRTDBG_LEAK_CHECK_DF/*|_CRTDBG_CHECK_CRT_DF*/);
	_CrtSetReportMode(_CRT_WARN,_CRTDBG_MODE_WNDW);

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
	try
	{
		PascalTriangle pascalTriangle(68);
	}
	catch(const std::domain_error &e)
	{
		wcout << "Correctly throws domain_error: \"" << e.what() << "\"\nwhen trying to instantiate with large n.\n\n" << endl;
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
	const auto max_n = 67u;
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
				wcerr << "error: " << e.what() << " (" << n << "," << k << ")" << endl;
			} // end catch
	wcout << "\nbinomial coefficients computed in 2 different ways match\n(when no overflow occurs).\n\n" << endl;


	// test pi
	const auto Pi = 3.1415926535897932384626433832795;
	wcout << std::scientific;
	wcout << "double precision arithmetic epsilon: " << numeric_limits<double>::epsilon() << endl;
	for(auto acc = 1e-5 ; acc >= 1e-7 ; acc/=10)	// smaller values for accuracy may take a lot of time to compute.
		wcout << "With accuracy " << setprecision(1) <<  acc << " pi is approximated with an error of " << setprecision(3) << fabs(pi(acc)-Pi) << endl;
	wcout << "\n\n";


	// test exp
	for(auto x = -20.0 ; x <= 0.0 ; x += 0.50)
	{
		wcout << "std::exp(" << setprecision(2) << x << ") = " << setprecision(18) << exp(x) << endl;
		wcout << "     exp(" << setprecision(2) << x << ") = " << setprecision(18) << exp(x,1e-20) << endl;
	}
	wcout << "\n\n";

	const double accuracy = 1e-10;
	for(auto x = -15.0 ; x <= 15.0 ; x += 0.20)
	{
		if(fabs(exp(x) - exp(x,accuracy)) > accuracy)
		{
			wcout << "Error exceeds accuracy!!!" << endl;
			wcout << "std::exp(" << setprecision(2) << x << ") = " << setprecision(18) << exp(x) << endl;
			wcout << "     exp(" << setprecision(2) << x << ") = " << setprecision(18) << exp(x,accuracy) << endl;
		} // end if
	}
	wcout << "\n\n";


	// test BernsteinPolynomial
	const auto size = 20+1;
	const auto samples = 11;
	array<array<array<double,samples>,size>,size> formulaBernstein;
	array<array<array<double,samples>,size>,size> recursiveBernstein;
	array<array<array<double,samples>,size>,size> fastRecursiveBernstein;
	vector<double> storage(size);
	StopWatch sw;
	double t;

	sw.push();
	for(auto n = 0 ; n < size ; n++)
		for(auto i = 0 ; i <= n ; i++)
		{
			double x = 0.0;
			for(auto s = 0 ; s < samples ; s++)
			{
				formulaBernstein[n][i][s] = binomialCoefficient(n,i)*pow(x,i)*pow(1-x,n-i);
				x += (1.0-0.0)/(samples-1);
			} // end for
		} // end for
	t = sw.pop();
	std::cout << "formula method's elapsed time: " << t << sw.getUnit() << endl;

	sw.push();
	for(auto n = 0 ; n < size ; n++)
		for(auto i = 0 ; i <= n ; i++)
		{
			double x = 0.0;
			for(auto s = 0 ; s < samples ; s++)
			{
				recursiveBernstein[n][i][s] = BernsteinPolynomial(i,n,x);
				x += (1.0-0.0)/(samples-1);
			} // end for
		} // end for
	t = sw.pop();
	std::cout << "recursive method's elapsed time: " << t << sw.getUnit() << endl;

	sw.push();
	for(auto n = 0 ; n < size ; n++)
		for(auto i = 0 ; i <= n ; i++)
		{
			double x = 0.0;
			for(auto s = 0 ; s < samples ; s++)
			{
				for(auto j = 0 ; j <= n ; j++)
					storage[j] = 0.0;
				fastRecursiveBernstein[n][i][s] = BernsteinPolynomial(i,n,x,storage);
				x += (1.0-0.0)/(samples-1);
			} // end for
		} // end for
	t = sw.pop();
	std::cout << "fast recursive method's elapsed time: " << t << sw.getUnit() << endl;
	std::cout << "\n\n";

	auto mismatches = 0u;
	for(auto n = 0 ; n < size ; n++)
		for(auto i = 0 ; i <= n ; i++)
			for(auto s = 0 ; s < samples ; s++)
			{
				double t = recursiveBernstein[n][i][s];
				double f = formulaBernstein[n][i][s];
				if(2*fabs(t-f)/(t+f) > 1e-15)	// condition is never satisfied with 1e-14
				{
					wcout << "triangle method: " << t << endl;
					wcout << "formula method:  " << f << endl;
					mismatches++;
				} // end if
			} // end for
	wcout << "\nmismatches = " << mismatches << "\n\n" << endl;
	mismatches = 0u;
	for(auto n = 0 ; n < size ; n++)
		for(auto i = 0 ; i <= n ; i++)
			for(auto s = 0 ; s < samples ; s++)
			{
				double t = recursiveBernstein[n][i][s];
				double f = fastRecursiveBernstein[n][i][s];
				if(2*fabs(t-f)/(t+f) > 1e-20)
				{
					wcout << "Error: proxy function returns different result than real function!" << endl;
				} // end if
			} // end for
	wcout << "\nmismatches = " << mismatches << "\n\n" << endl;


	system("pause");
	return 0;
} // end function main
