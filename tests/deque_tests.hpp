
# pragma once

# include "tester.hpp"
# include "vector_tests.hpp"

# include <deque>

template <typename Container, typename T>
inline static void test_deque_resize(std::ofstream& fd)
{
	fd << std::endl << "-------------- RESIZE ----------------" << std::endl;

	// TO DO:

	fd << "TO DO" << std::endl;
}

template <typename Container, typename T>
inline static void start_deque_tests(const std::string& filename)
{
	static void (*const tests[])(std::ofstream&) = {
		&test_random_access<Container, T>,
		&test_push_pop_back<Container, T>,
		&test_push_pop_front<Container, T>,
		&test_deque_resize<Container, T>,
		&test_non_member_iterators<Container, T>,
	};

	start_tests(filename, tests, ARRAY_SIZE(tests));
}

inline static void deque_tests()
{
	start_deque_tests<std::deque<int>, int>(std::string(std::string(std::string(TEST_DIR) + std::string(STD_DEQUE_FILENAME))));
	start_deque_tests<std::deque<int>, int>(std::string(std::string(std::string(TEST_DIR) + std::string(FT_DEQUE_FILENAME))));
}