#include <iostream>
#include <string>
#include "property.hpp"

/* This was tested on MSVC only and works for C++14, C++17, C++20 standards (haven't tested for other standards */

class Employee
{
public:
	dt0::property<__int64> Id {0, dt0::get<__int64>{}, dt0::set<__int64>{}};
	dt0::property<std::string> Name {dt0::get<std::string>{}, dt0::set<std::string>{}};
	dt0::property<std::string> Surname {dt0::get<std::string>{}, dt0::set<std::string>{}};
	dt0::property<unsigned short> Age {0, dt0::get<unsigned short >{}, dt0::set<unsigned short>{}};
	dt0::property<unsigned int> Salary {0, dt0::get<unsigned int>{}, dt0::set<unsigned int>{}};

	Employee() noexcept = default;

	Employee(__int64 id, std::string name, std::string surname, unsigned short age, unsigned int salary)
	{
		Id = id;
		Name = name;
		Surname = surname;
		Age = age;
		Salary = salary;
	}

	~Employee() noexcept = default;
};

int main()
{
	dt0::property<int, int, int&> A { 2, 
		dt0::get<int, int, int&> { 
			[](int& x) -> int { return x * 2; } 
		},
		dt0::set<int>{ 
			[](int& x, const int& y) { x = 2 * y; }, 
			[](int& x, int&& y) noexcept17 { x = std::move(y * 3); }
		} 
	};

	std::cout << A << "\n\n";

	dt0::property<std::string> B { dt0::get<std::string>{}, dt0::set<std::string>{} };

	B = "Hello";

	std::cout << B << "\n\n";

	dt0::const_property<double> C{ dt0::get<double>{} };

	C = 2.71828;

	std::cout << C << "\n\n";

	Employee employee(0xDEEDAA, "John", "Doe", 46, 4000);

	std::cout << "Id: " << employee.Id
		  << "\nName: " << employee.Name
		  << "\nSurname: " << employee.Surname
		  << "\nAge: " << employee.Age
		  << "\nSalary: " << employee.Salary << "$\n\n";
	return 0;
}
