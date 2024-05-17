#include <iostream>
#include <string>
#include "property.hpp"

/* This was tested on MSVC only and works for C++14, C++17, C++20 standards (haven't tested for other standards */

int main()
{
	dt0::property<int, int, int&> A { 2, 
		dt0::get<int, int, int&> { 
		[](int& x) -> int { return x * 2; } 
		},
		dt0::set<int>{ 
			[](int& x, const int& y) {x = 2 * y; }, 
			[](int& x, int&& y) noexcept17 {x = std::move(y * 3);
		}} 
	};

	std::cout << A << "\n\n";

	dt0::property<std::string> B { dt0::get<std::string>{}, dt0::set<std::string>{} };

	B = "Hello";

	std::cout << B << "\n\n";

	dt0::const_property<double> C{ dt0::get<double>{} };

	C = 2.71828;

	std::cout << C << "\n\n";
	return 0;
}
