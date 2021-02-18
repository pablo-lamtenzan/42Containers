
# pragma once

# include "tester.hpp"

# include "random_access_test.hpp"
# include <vector>
# include <string>

template <typename Container, typename T>
inline static void start_vector_tests(const std::string& filename)
{
	std::ofstream fd;

	fd.open(filename);

	static void (*const tests[])(std::ofstream&) = {
		&test_random_access<Container, T>,
	};

	for (size_t i = 0 ; i < sizeof(tests) / sizeof(*tests) ; i++)
		tests[i](fd);

	fd.close();
}

inline void vector_tests()
{
	// constructor
	// at -> template
	// reserve
	// capacity
	// push back -> template
	// pop back -> template
	// resize
	// non mebers -> template

	// WTF linker worsk strangeouslly
	//start_vector_tests<std::vector<int>, int>(std::string(std::string(std::string(TEST_DIR) + std::string(STD_VECTOR_FILENAME))));
	//start_vector_tests<std::vector<int>, int>(std::string(std::string(std::string(TEST_DIR) + std::string(FT_VECTOR_FILENAME))));
	start_vector_tests<std::vector<int>, int>(std::string("__TESTER__/std_vector_test"));
	start_vector_tests<std::vector<int>, int>(std::string("__TESTER__/ft_vector_test"));
}