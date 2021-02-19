
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

// NOTE: Move random access test for list

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
	fd << std::endl << "-------------- ASSIGNATION ----------------" << std::endl;

	// TEST: operator=

	Container c(size_t(42));

	size_t y = 0;
	for (auto i = c.begin() ; i != c.end() ; i++)
		*i = T(y++);

	Container w = c;

	fd << "Test \'operator=\' 1: " << std::endl << "["
	<< w.size() << "]" << std::endl << "{ ";
	for (auto i = w.begin() ; i != w.end() ; i++)
		fd << *i << std::string(" ");
	fd << "}" << std::endl;

	// TEST: assign

	Container r;

	r.assign(42, T(42));
	fd << "Test \'assign\' 1: " << std::endl << "["
	<< r.size() << "]" << std::endl << "{ ";
	for (auto i = r.begin() ; i != r.end() ; i++)
		fd << *i << std::string(" ");
	fd << "}" << std::endl;

	Container rr;

	rr.assign(c.begin(), c.end());
	fd << "Test \'assign\' 2: " << std::endl << "["
	<< rr.size() << "]" << std::endl << "{ ";
	for (auto i = rr.begin() ; i != rr.end() ; i++)
		fd << *i << std::string(" ");
	fd << "}" << std::endl;
}

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
		fd << " ABORT" << std::endl;
	else
		fd << " DON'T ABORT" << wstatus << std::endl;

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
	fd << std::endl << "-------------- ITERATORS ----------------" << std::endl;

	Container c(size_t(42));

	// TEST: iterator iteration

	typename Container::iterator it = c.begin();
	typename Container::iterator o = c.end();

	size_t y = 0;
	for (typename Container::iterator i = c.begin() ; i != c.end() ; i++)
		*i = T(y++);
	fd << "Test \'iterators\' 1: " << std::endl << "{ ";
	while (it != o)
		fd << *(it++) << std::string(" ");
	fd << "}" << std::endl;

	// TEST: const iterator iteration

	// TO DO: Once finished mutable iterator test copy paste

	// TEST: member iterator operators

	// Nothing here ? List has no += / -= / + / -

	// TEST: non member iterator operators

	auto lhs = c.begin();
	auto rhs = c.end();

	for (size_t i = 0xf ; i > 0 ; i--)
	{
		lhs++;
		rhs--;
	}

	fd << "Test \'iterator\' 4: " << std::endl;
	fd << "[" << bool(lhs == rhs) << "]" << std::endl;
	fd << "[" << bool(lhs != rhs) << "]" << std::endl;

	//fd << "[" << bool(lhs < rhs) << "]" << std::endl;
	//fd << "[" << bool(lhs <= rhs) << "]" << std::endl;
	//fd << "[" << bool(lhs > rhs) << "]" << std::endl;
	//fd << "[" << bool(lhs >= rhs) << "]" << std::endl;
	
}

template <typename Container, typename T>
inline static void test_reverse_iterators(std::ofstream& fd)
{
	// Do the same as with iterator with with reverse
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
	fd << std::endl << "-------------- MODIFIERS ----------------" << std::endl;

	// TEST clear

	Container c(size_t(42));

	c.clear();
	fd << "\'Clear\' test 1: " << c.size() << " " << c.empty() << std::endl;

	Container z;
	z.clear();

	size_t y = 0;
	for (auto i = c.begin() ; i != c.end() ; i++)
		*i = T(y++);
	c.insert(c.begin(), 42, T());
	c.clear();
	fd << "\'Clear\' test 2: " << c.size() << " " << c.empty() << std::endl;

	// TEST insert

	Container ww;
	Container www(size_t(42));

	ww.insert(ww.begin(), 41, T(42));
	www.insert(++www.begin(), 41, T(42));
	fd << "\'Insert test 1: " << ww.size() << " " << www.size() << std::endl
	<< "{ ";
	auto ll = ww.begin();
	auto lll = www.begin();
	for (size_t i = 41 ; i > 0 ; i--)
		fd << " { " << *(ll++) << " ; " << *(lll++) << " }";
	fd << " }" << std::endl;

	auto f = ww.begin();
	for (size_t i = 21 ; i > 0 ; i--)
		f++;
	auto ff = f;
	for (size_t i = 13 ; i > 0 ; i--)
		ff++;
	ww.insert(ww.begin(), f, ff);
	fd << "\'Insert\' test 2: " << ww.size() << std::endl << "{ ";
	for (auto i = ww.begin() ; i != ww.end() ; i++)
		fd << *i << std::string(" ");
	fd << "} " << std::endl;

	// TEST erase

	if (!are_same<Container ,std::list<T>>::cond
		/*|| typename are_same<Container, ft::list<T>::cond*/)
	{
		Container q;

		pid_t pid = fork();
		if (pid == 0)
		{
			q.erase(q.begin());
			exit(EXIT_FAILURE); // Will never reach this line.
		}
		else if (pid < 0)
			std::cerr << "Syscall \'fork\' failed for misterious reasons ..."
			<< "[Check the memory avalaible in your device]" << std::endl;
		int wstatus;
		while (waitpid(pid, &wstatus, 0) >= 0);
		if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGSEGV)
			fd << " SEGMENTATION FAULT" << std::endl;
		else
			fd << " " << wstatus << std::endl;
	}

	Container ii;

	ii.insert(ii.begin(), 42, T(42));
	auto xx = ii.begin();
	for (size_t i = 18 ; i > 0 ; i--)
		xx++;
	auto yy = xx;
	for (size_t i = 8 ; i > 0 ; i--)
		yy++;
	ii.erase(xx, yy);
	fd << "\'Erase\' test 1: " << ii.size() << std::endl << " { ";
	for (auto i = ii.begin() ; i != ii.end() ; i++)
		fd << *i << " ";
	fd << " }" << std::endl;

	auto gg = ii.begin();
	gg++;
	ii.erase(gg);
	fd << "\'Erase\' test 2: " << ii.size() << std::endl << " { ";
	for (auto i = ii.begin() ; i != ii.end() ; i++)
		fd << *i << " ";
	fd << " }" << std::endl;

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
		&test_reverse_iterators<Container, T>,
		&test_capacity<Container, T>,
		&test_modifiers<Container, T>,
		&test_non_members<Container, T>
	};

	for (size_t i = 0 ; i < sizeof(tests) / sizeof(*tests) ; i++)
		tests[i](fd);
	
	fd.close();
}

template <typename T>
inline void execute_shared_tests_for_linear_containers()
{
	shared_tests<std::vector<T>, T>(std::string(std::string(TEST_DIR) + std::string(STD_VECTOR_FILENAME_SHARED)));
	shared_tests<std::list<T>, T>(std::string(std::string(TEST_DIR) + std::string(STD_LIST_FILENAME_SHARED)));
	shared_tests<std::deque<T>, T>(std::string(std::string(TEST_DIR) + std::string(STD_DEQUE_FILENAME_SHARED)));
	shared_tests<std::vector<T>, T>(std::string(std::string(TEST_DIR) + std::string(FT_VECTOR_FILENAME_SHARED)));
	shared_tests<std::list<T>, T>(std::string(std::string(TEST_DIR) + std::string(FT_LIST_FILENAME_SHARED)));
	shared_tests<std::deque<T>, T>(std::string(std::string(TEST_DIR) + std::string(FT_DEQUE_FILENAME_SHARED)));
}
