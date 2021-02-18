
# pragma once

# include "tester.hpp"

// C++ style libs
# include <iostream>
# include <fstream>
# include <string>

// C style libs
# include <sys/wait.h>
# include <unistd.h>

// Debug libs
# include <vector>
# include <list>
# include <deque>



// NOTE: Probally stack and queue must be excluded of those tests for practical reasons.
// NOTE: Perhabs is a good idea to use some log dirrectory for the filenames.

// NOTE: Move random access test for list

// TO DO: Constructor and insert does not macth with map, set, multimap, multiset

// Match for vector, deque and list (if RANDOM_ACCESS == 0)


#define RANDOM_ACCESS 0

/**
 * 	@brief cond == true if the template type is random_access
*/

template <typename, typename>
struct are_same
{ enum { cond = false }; };

template <typename T>
struct are_same<T, T>
{ enum { cond = true }; };

template <typename Container, typename T>
inline static void test_constructor(std::ofstream& fd)
{
	fd << std::endl << "-------------- CONSTRUCTOR ----------------" << std::endl;

	// TEST: default constructor
	Container c;

	fd << "Test default constructor 1: " << static_cast<std::string>(c.size() == size_t(0)
	&& c.empty() ? "SUCCESS" : "ERROR") << std::endl;

	// TEST: size constructor
	Container c1(size_t(42));

	fd << "Test size constructor 1: " << static_cast<std::string>(c1.size() == size_t(42)
	&& !c1.empty() ? "SUCCESS" : "ERROR") << std::endl;

	// TEST: range constructor
	typename Container::iterator it = c1.begin();
	for (size_t i = 0; i < c1.size() ; i++)
		*(it++) = T(i);

	Container c2(c1.begin(), c1.end());

	fd << "Test range constructor 1 (part 1/2): " << static_cast<std::string>(c2.size() == c1.size()
	&& c2 == c1 ? "SUCCESS" : "ERROR") << std::endl;

	fd << "Test range constructor 1 (part 2/2): " << std::endl << "{ ";
	it = c2.begin();
	for (size_t i = 0 ; i < c2.size() ; i++)
		fd << *(it++) << static_cast<std::string>(i == c2.size() - 1 ? " }" : " ");
	fd << std::endl;

	// TEST: copy constructor
	Container c3(c2);

	fd << "Test copy constructor 1 (part 1/2): " << static_cast<std::string>(c3.size() == c2.size()
	&& c3 == c2 ? "SUCCESS" : "ERROR") << std::endl;

	fd << "Test copy constructor 1 (part 2/2): " << std::endl << "{ ";
	it = c3.begin();
	for (size_t i = 0 ; i < c3.size() ; i++)
		fd << *(it++) << static_cast<std::string>(i == c3.size() - 1 ? " }" : " ");
	fd << std::endl;

}

template <typename Container, typename T>
inline static void test_assignation(std::ofstream& fd)
{
	// TEST: operator=

	// TEST: assign
}

#if RANDOM_ACCESS

template <typename Container, typename T>
inline static void test_random_access(std::ofstream& fd)
{
	fd << std::endl << "-------------- RANDOM ACCESS ----------------" << std::endl;

	// TEST: at

	Container c(size_t(42));

	for (size_t i = 0 ; i < 42 ; i++)
		c.at(i) = T(i);
	fd << "\'At\' test 1: " << std::endl << "{ ";
	for (size_t i = 0 ; i < 42 ; i++)
	{
		c.at(i) = c.at(i) << T(1 & i);
		fd << c.at(i) << static_cast<std::string>(i == 41 ? "" : " ");
	}
	fd << " }" << std::endl;

	fd << "\'At\' test 2: ";
	try {
		c.at(42) = T();
		fd << "ERROR" << std::endl;
	} catch (...) { fd << "SUCCESS" << std::endl; }
	

	// TEST: operator[]

	c.clear();

	for (size_t i = 0 ; i < 42 ; i++)
		c[i] = T(i);
	fd << "\'operator[]\' test 1: " << std::endl << "{ ";
	for (size_t i = 0 ; i < 42 ; i++)
	{
		c[i] = c[i] << T(1 & i);
		fd << c[i] << static_cast<std::string>(i == 41 ? "" : " ");
	}
	fd << " }" << std::endl;

	fd << "\'operator[]\' test 2: ";
	pid_t pid = fork();
	if (pid == 0)
	{
		c[0xffff] = T();
		exit(EXIT_FAILURE); // Will never execute this line.
	}
	else if (pid < 0)
		std::cerr << "Syscall fork failed for misterious reasons ..."
		<< "[Check the memory avalaible in your device]" << std::endl;

	int wstatus;
	while (waitpid(pid, &wstatus, 0) >= 0);
	if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGSEGV)
		fd << "ALL OK" << std::endl;
	else
		fd << "ERROR" << std::endl;

	// NOTE: Some containers wont segfault if the operator at overflow with this test.
	fd << "\'operator[]\' test 3: ";
	pid_t pid2 = fork();
	if (pid2 == 0)
	{
		c[42] = T();
		exit(EXIT_FAILURE); // Will never execute this line.
	}
	else if (pid2 < 0)
		std::cerr << "Syscall \'fork\' failed for misterious reasons ..."
		<< "[Check the memory avalaible in your device]" << std::endl;

	int wstatus2;
	while (waitpid(pid2, &wstatus2, 0) >= 0);
	if (WIFSIGNALED(wstatus2) && WTERMSIG(wstatus2) == SIGSEGV)
		fd << "SEGFAULT" << std::endl;
	else
		fd << "DON'T SEGFAULT" << std::endl;
}

#endif

template <typename Container, typename T>
inline static void test_element_access(std::ofstream& fd)
{
	fd << std::endl << "-------------- ELEMENT ACCESS ----------------" << std::endl;

	// TEST: back

	Container c(0x42);

	*--c.end() = T(-1);
	fd << "\'back\' test 1: " << c.back() << std::endl;
	c.erase(c.begin());
	fd << "\'back\' test 2: " << c.back() << std::endl;
	c.clear();
	fd << "\'back\' test 3: " << c.back() << std::endl;

	pid_t pid = fork();
	if (pid == 0)
	{
		--c.back() = T(42);
		exit(EXIT_FAILURE); // Will be never executed.
	}
	else if (pid < 0)
		std::cerr << "Syscall \'fork\' failed for misterious reasons ..."
		<< "[Check the memory avalaible in your device]" << std::endl;
	int wstatus;
	while (waitpid(pid, &wstatus, 0) >= 0);
	if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGABRT)
		fd << "ABORT" << std::endl;
	else
		fd << "DON'T ABORT " << wstatus << std::endl;

	// TEST: front

	Container d(0x42);

	*d.begin() = T(-1);
	fd << "\'front\' test 1: " << d.front() << std::endl;
	d.erase(d.begin());
	fd << "\'front\' test 2: " << d.front() << std::endl;
	d.clear();
	fd << "\'front\' test 3: " << d.front() << std::endl;
	d.front() = T(42);
	fd << "\'front\' test 4: " << *d.begin() << std::endl;
}

template <typename Container, typename T>
inline static void test_iterators(std::ofstream& fd)
{
	// TEST: iterator iteration

	// TEST: const iterator iteration

	// TEST: member iterator operators

	// TEST: non member iterator operators
}

template <typename Container, typename T>
inline static void test_capacity(std::ofstream& fd)
{
	fd << std::endl << "-------------- CAPACITY ----------------" << std::endl;

	// TEST empty

	Container c(size_t(1));
	Container e;
	
	fd << "\'Empty\' test 1: " << static_cast<std::string>(e.empty() ? "SUCCESS" : "FAIL") << std::endl;
	*c.begin() = T();
	fd << "\'Empty\' test 2: " << static_cast<std::string>(!c.empty() ? "SUCCESS" : "FAIL") << std::endl;
	c.erase(c.begin());
	fd << "\'Empty\' test 3: " << static_cast<std::string>(c.empty() ? "SUCCESS" : "FAIL") << std::endl;
	*c.begin() = T();
	c.clear();
	fd << "\'Empty\' test 4: " << static_cast<std::string>(c.empty() ? "SUCCESS" : "FAIL") << std::endl;
	Container f(size_t(1));
	fd << "\'Empty\' test 5: " << static_cast<std::string>(!f.empty() ? "SUCCESS" : "FAIL") << std::endl;

	// TEST size

	fd << "\'Size\' test 1: " << c.size() << std::endl;
	*c.begin() = T();
	fd << "\'Size\' test 2: " << c.size() << std::endl;

	Container x(42);
	typename Container::iterator it = x.begin();
	for (size_t i = 0 ; i < 42 ; i++)
		*(it++) = T();
	for (size_t i = 21 ; i > 0 ; i--)
		x.erase(x.begin());
	fd << "\'Size\' test 3: " << x.size() << std::endl;

	// TEST max size

	c.clear();
	fd << "\'Max size\' test 1: " << c.max_size() << std::endl;
	*c.begin() = T();
	fd << "\'Max size\' test 2: " << c.max_size() << std::endl;
	fd << "\'Max size\' test 3: " << x.max_size() << std::endl;
}

template <typename Container, typename T>
inline static void test_modifiers(std::ofstream& fd)
{
	// TEST clear

	// clear changes vector capacity

	// TEST insert

	// TEST erase
}

template <typename Container, typename T>
inline static void test_non_members(std::ofstream& fd)
{
	fd << std::endl << "-------------- NON MEMBERS ----------------" << std::endl;

	// TEST boolean operators

	Container lhs(42);
	typename Container::iterator it = lhs.begin();

	for (size_t i = 0 ; i < 42 ; i++)
		*(it++) = T(i);

	Container rhs(lhs);

	fd << "Test \'operator==\' 1: " << bool(lhs == rhs) << std::endl;
	fd << "Test \'operator!=\' 1: " << bool(lhs != rhs) << std::endl;
	fd << "Test \'operator<\' 1: " << bool(lhs < rhs) << std::endl;
	fd << "Test \'operator<=\' 1: " << bool(lhs <= rhs) << std::endl;
	fd << "Test \'operator>\' 1: " << bool(lhs > rhs) << std::endl;
	fd << "Test \'operator>=\' 1: " << bool(lhs >= rhs) << std::endl;

	it = --lhs.end();
	*it = T(0xff);

	fd << "Test \'operator==\' 2: " << bool(lhs == rhs) << std::endl;
	fd << "Test \'operator!=\' 2: " << bool(lhs != rhs) << std::endl;
	fd << "Test \'operator<\' 2: " << bool(lhs < rhs) << std::endl;
	fd << "Test \'operator<=\' 2: " << bool(lhs <= rhs) << std::endl;
	fd << "Test \'operator>\' 2: " << bool(lhs > rhs) << std::endl;
	fd << "Test \'operator>=\' 2: " << bool(lhs >= rhs) << std::endl;

	rhs.erase(rhs.begin());
	rhs.erase(rhs.begin());

	fd << "Test \'operator==\' 3: " << bool(lhs == rhs) << std::endl;
	fd << "Test \'operator!=\' 3: " << bool(lhs != rhs) << std::endl;
	fd << "Test \'operator<\' 3: " << bool(lhs < rhs) << std::endl;
	fd << "Test \'operator<=\' 3: " << bool(lhs <= rhs) << std::endl;
	fd << "Test \'operator>\' 3: " << bool(lhs > rhs) << std::endl;
	fd << "Test \'operator>=\' 3: " << bool(lhs >= rhs) << std::endl;

	// TEST swap (assuming external swap call local swap, local swap is called)
	lhs.swap(rhs);

	it = lhs.begin();
	fd << "\'Swap\' test 1: " << std::endl << "lhs: { ";
	for (; it != lhs.end() ; it++)
		fd << *it << static_cast<std::string>(it == --lhs.end() ? " }" : " ");
	it = rhs.begin();
	fd << std::endl << "rhs: { ";
	for (; it != rhs.end() ; it++)
		fd << *it << static_cast<std::string>(it == --rhs.end() ? " }" : " ");
	fd << std::endl;

	lhs.clear();
	rhs.clear();
	fd << "Test \'operator==\' 4: " << bool(lhs == rhs) << std::endl;
	fd << "Test \'operator!=\' 4: " << bool(lhs != rhs) << std::endl;
	fd << "Test \'operator<\' 4: " << bool(lhs < rhs) << std::endl;
	fd << "Test \'operator<=\' 4: " << bool(lhs <= rhs) << std::endl;
	fd << "Test \'operator>\' 4: " << bool(lhs > rhs) << std::endl;
	fd << "Test \'operator>=\' 4: " << bool(lhs >= rhs) << std::endl;
}

/**
 * 	@brief Shared tester
 * 
 * 	@tparam Container The target container type.
 * 	@tparam T The value type holded by the target container.
 * 	@param filename The filename used to write the output.
 * 	@return Nothing
 * 
 * 	Perform shared test "cross-containers". Those are the most
 * 	common tests and each container must compile in those tests.
 * 
 * 	NOTE: stack and queue are excluded from those tests.
*/
template <typename Container, typename T>
inline static void shared_tests(const std::string& filename)
{
	std::ofstream fd;

	fd.open(filename);

	static void (*const tests[])(std::ofstream&) = {
		&test_constructor<Container, T>,
		&test_assignation<Container, T>,
		&test_element_access<Container, T>,
		&test_iterators<Container, T>,
		&test_capacity<Container, T>,
		&test_modifiers<Container, T>,
		&test_non_members<Container, T>
	};

	for (size_t i = 0 ; i < sizeof(tests) / sizeof(*tests) ; i++)
		tests[i](fd);

#if RANDOM_ACCESS

	if (are_same<typename Container::iterator::iterator_category,
	std::random_access_iterator_tag>::cond)
		test_random_access<Container, T>(fd);

#endif
	
	fd.close();
}

template <typename T>
inline void execute_shared_tests_for_linear_containers()
{
	shared_tests<std::vector<T>, T>(std::string(std::string(TEST_DIR) + std::string(STD_VECTOR_FILENAME_SHARED)));
	shared_tests<std::list<T>, T>(std::string(std::string(TEST_DIR) + std::string(STD_LIST_FILENAME_SHARED)));
	shared_tests<std::deque<T>, T>(std::string(std::string(TEST_DIR) + std::string(STD_DEQUE_FILENAME_SHARED)));
}
