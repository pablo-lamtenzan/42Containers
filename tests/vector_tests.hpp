
# pragma once

# include "tester.hpp"

# include "random_access_test.hpp"
# include "push_pop_tests.hpp"
# include "non_member_iterators_tests.hpp"

# include <vector>
# include <string>

template <typename Container, typename T>
inline static void test_vec_constructor(std::ofstream& fd)
{
	// Test allocator signature

	// Test size + value signature

	// TO DO those in shared

}

template <typename Container, typename T>
inline static void test_vec_reserve(std::ofstream& fd)
{
	fd << std::endl << "-------------- RESERVE ----------------" << std::endl;
	// reserve > cap

	Container c(size_t(0xff), T(42));

	fd << "\'Reserve\' test 1: " << c.capacity() << " " << c.size() << " ";
	c.reserve(size_t(c.capacity() + size_t(0xff)));
	fd << c.capacity() << " " << c.size() << std::endl;

	// reserve < cap

	fd << "\'Reserve\' test 2: " << c.capacity() << " " << c.size() << " ";
	c.reserve(size_t(c.capacity() / size_t(2)));
	fd << c.capacity() << " " << c.size() << std::endl;

	// reverse == cap

	fd << "\'Reserve\' test 3: " << c.capacity() << " " << c.size() << " ";
	c.reserve(c.capacity());
	fd << c.capacity() << " " << c.size() << std::endl;

	// reserve empty

	Container t;

	fd << "\'Reserve\' test 4: " << t.capacity() << " " << t.size() << " ";
	t.reserve(0xff);
	fd << t.capacity() << " " << t.size() << std::endl;

	// max size (throw std::lenght_error)

	try {
		fd << "\'Reserve\' test 5: " << c.capacity() << " " << c.size() << " ";
		c.reserve(size_t(c.max_size() + size_t(1)));
		fd << "FAILURE" << std::endl;
	} catch (...) { fd << "SUCCESS" << std::endl; }
}

template <typename Container, typename T>
inline static void test_vec_resize(std::ofstream& fd)
{
	fd << std::endl << "-------------- RESIZE ----------------" << std::endl;

	Container c(size_t(0xff));

	// resize < size

	fd << "\'Resize test 1: " << c.capacity() << " " << c.size() << " ";
	c.resize(size_t(c.size() / size_t(2)));
	fd << c.capacity() << " " << c.size() << std::endl;

	// resize > cap

	fd << "\'Resize test 2: " << c.capacity() << " " << c.size() << " ";
	c.resize(size_t(c.capacity() * size_t(2)));
	fd << c.capacity() << " " << c.size() << std::endl;

	// resize < cap && > size

	fd << "\'Resize test 3: " << c.capacity() << " " << c.size() << " ";
	c.resize(size_t(c.size() + size_t(size_t(c.capacity() - c.size()) / size_t(2))));
	fd << c.capacity() << " " << c.size() << std::endl;

	// resize == size

	fd << "\'Resize test 4: " << c.capacity() << " " << c.size() << " ";
	c.resize(c.size());
	fd << c.capacity() << " " << c.size() << std::endl;

	// resize empty

	Container y;

	fd << "\'Resize test 5: " << y.capacity() << " " << y.size() << " ";
	y.resize(size_t(0x42));
	fd << y.capacity() << " " << y.size() << std::endl;

	// resize 0

	Container z;

	fd << "\'Resize test 6: " << z.capacity() << " " << z.size() << " ";
	z.resize(size_t());
	fd << z.capacity() << " " << z.size() << std::endl;

	// resize max size + 1

	Container w;

	try {
		fd << "\'Resize test 1: " << w.capacity() << " " << w.size() << " ";
		c.resize(size_t(c.max_size() + size_t(1)));
		fd << "FAILURE" << std::endl;
	} catch(...) { fd << "SUCCESS" << std::endl; }
}

template <typename Container, typename T>
inline static void start_vector_tests(const std::string& filename)
{
	static void (*const tests[])(std::ofstream&) = {
		&test_vec_constructor<Container, T>,
		&test_random_access<Container, T>,
		&test_vec_reserve<Container, T>,
		&test_push_pop_back<Container, T>,
		&test_vec_resize<Container, T>,
		&test_non_member_iterators<Container, T>
	};

	start_tests(filename, tests, ARRAY_SIZE(tests)); 

}

inline void vector_tests()
{	
	start_vector_tests<std::vector<int>, int>(std::string(std::string(std::string(TEST_DIR) + std::string(STD_VECTOR_FILENAME))));
	start_vector_tests<std::vector<int>, int>(std::string(std::string(std::string(TEST_DIR) + std::string(FT_VECTOR_FILENAME))));
}