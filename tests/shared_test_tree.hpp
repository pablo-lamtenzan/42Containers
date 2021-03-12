
# pragma once

# include "tester.hpp"
# include "random_access_test.hpp"

# include <iostream>
# include <fstream>
# include <string>

# include <map>
# include <set>

# include "../source_code/map.hpp"

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::pair<T, T>& pair)
{ return (os << "{ " << pair.first << ", " << pair.second << " }"); }

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& pair)
{ return (os << "{ " << pair.first << ", " << pair.second << " }"); }

// TO DO: Insertion only works for map/multimap

/*
	TO DO for set/multiset
 copy-paste and change std::pair by just a key.
*/

template <typename Container, typename T>
inline static void test_tree_constructor(std::ofstream& fd)
{
	fd << std::endl << "-------------- CONSTRUCTOR ----------------" << std::endl;

	// TEST: default constructor

	Container c;

	fd << "Test \'default constructor\' 1: " << c.empty() << " " << c.size() << std::endl;
	
	// TEST: comparison constructor

	std::less<T> key_compare;
	Container c1(key_compare);

	fd << "Test \'comparison constructor\' 1: " << c.empty() << " " << c.size() << std::endl;

	// TEST: range constructor

	Container c2 /*{ {1, 1}, {2, 2}, {3, 4},}*/;

	// WTF definition of insert not found in any container

	for (size_t i = 15 ; i > size_t() ; i--)
		c2.insert(std::pair<T, T>(T(i), T(i)));

	Container c3(c2.begin(), c2.end());

	fd << "Test \'range constructor\' 1: " << c3.size() << std::endl << "{ ";
	for (typename Container::iterator it = c3.begin() ; it != c3.end() ; it++)
		fd << *it << " ";
	fd << "}" << std::endl;

	// TEST: comparsion range constructor

	Container c4(c3.begin(), c3.end(), key_compare);
	
	fd << "Test \'range constructor\' 1: " << c4.size() << std::endl << "{ ";
	for (typename Container::iterator it = c4.begin() ; it != c4.end() ; it++)
		fd << *it << " ";
	fd << "}" << std::endl;

	// TEST: copy constructor

	Container c5(c4);

	fd << "Test \'range constructor\' 1: " << c5.size() << std::endl << "{ ";
	for (typename Container::iterator it = c5.begin() ; it != c5.end() ; it++)
		fd << *it << " ";
	fd << "}" << std::endl;
}

template <typename Container, typename T>
inline static void test_tree_assignation(std::ofstream& fd)
{
	fd << std::endl << "-------------- ASSIGNATION ----------------" << std::endl;


	// TEST: operator=

	Container c2;

	for (size_t i = 15 ; i > size_t() ; i--)
		c2.insert(std::pair<T, T>(T(i), T(i)));

	Container c = c2;
	fd << "Test \'operator=\' 1: " << c.size() << std::endl << "{ ";
	for (typename Container::iterator it = c.begin() ; it != c.end() ; it++)
		fd << *it << " ";
	fd << "}" << std::endl;

	c.erase(c.begin());
	fd << "Test \'operator=\' 2: " << c2.size() << std::endl << "{ ";
	for (typename Container::iterator it = c2.begin() ; it != c2.end() ; it++)
		fd << *it << " ";
	fd << "}" << std::endl;
}

template <typename Container, typename T>
inline static void test_tree_element_access(std::ofstream& fd)
{
	fd << std::endl << "-------------- ELEMENT ACCESS ----------------" << std::endl;

	// call random access only for map

	// test_random_access<Container, T>(fd);
}

template <typename Container, typename T>
inline static void test_tree_iterators(std::ofstream& fd)
{
	fd << std::endl << "-------------- ITERATORS ----------------" << std::endl;

	// TEST: iterator iteration
	
	Container c;

	for (size_t i = 15 ; i > size_t() ; i--)
		c.insert(std::pair<T, T>(T(i), T(i)));

	typename Container::iterator it = c.begin();
	typename Container::iterator o = c.end();

	size_t y = 0;
	fd << "Test \'iterators\' 1: " << std::endl << "{ ";
	while (it != o)
		fd << *(it++) << std::string(" ");
	fd << "}" << std::endl;

	// TEST: const iterators

	// TEST: non member iterator operators

	typename Container::iterator lhs = c.begin();
	typename Container::iterator rhs = c.end();

	for (size_t i = 0xf ; i > 0 ; i--)
	{
		lhs++;
		rhs--;
	}

	fd << "Test \'iterator\' 4: " << std::endl;
	fd << "[" << bool(lhs == rhs) << "]" << std::endl;
	fd << "[" << bool(lhs != rhs) << "]" << std::endl;
}

template <typename Container, typename T>
inline static void test_tree_reverse_iterators(std::ofstream& fd)
{
	fd << std::endl << "-------------- REVERSE ITERATORS ----------------" << std::endl;

	// TEST: reverse iterators

	// TEST: const reverse iterators

	// TEST: reverse iterarator non member
}

template <typename Container, typename T>
inline static void test_tree_capacity(std::ofstream& fd)
{
	fd << std::endl << "-------------- CAPACITY ----------------" << std::endl;

	// TEST: empty

	Container e;

	fd << "\'Empty\' test 1: " << e.empty() << std::endl;
	e.insert({{T(42), T(42)},});
	fd << "\'Empty\' test 2: " << !e.empty() << std::endl;
	e.erase(e.begin());
	fd << "\'Empty\' test 3: " << e.empty() << std::endl;
	e.insert({{T(42), T(42)},});
	e.clear();
	fd << "\'Empty\' test 4: " << e.empty() << std::endl;

	// TEST: size

	fd << "\'Size\' test 1: " << e.size() << std::endl;
	Container r;
	fd << "\'Size\' test 2: " << r.size() << std::endl;
	e.insert({{T(42), T(42)},});
	fd << "\'Size\' test 3: " << e.size() << std::endl;

	for (size_t i = 15 ; i > size_t() ; i--)
		e.insert(std::pair<T, T>(T(i), T(i)));
	fd << "\'Size\' test 4: " << e.size() << std::endl;

	// TEST: max size

	fd << "\'Max size\' test 1: " << e.max_size() << std::endl;
}

template <typename Container, typename T>
inline static void test_tree_modifiers(std::ofstream& fd)
{
	fd << std::endl << "-------------- MODIFIERS ----------------" << std::endl;

	// TEST: clear

	Container c;

	pid_t pid = fork();
	if (pid == 0)
	{
		c.clear();
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		;
	int wstatus;
	while (waitpid(pid, &wstatus, 0) >= 0);
	fd << "\'Clear\' test 1: " << wstatus << std::endl;

	Container v {{T(42), T(42)},};
	v.clear();
	fd << "\'Clear\' test 2: " << c.size() << " " << c.empty() << std::endl;

	for (size_t i = 15 ; i > size_t() ; i--)
		c.insert(std::pair<T, T>(T(i), T(i)));
	c.clear();
	fd << "\'Clear\' test 3: " << c.size() << " " << c.empty() << std::endl;

	// TEST: insert

	// TO DO: hint insert test

	for (size_t i = 15 ; i > size_t() ; i--)
		c.insert(std::pair<T, T>(T(i), T(i)));
	
	Container r;
	r.insert(++c.begin(), --c.end());

	fd << "\'Insert\' test 2: " << c.size() << std::endl << "{ ";
	for (typename Container::iterator it = r.begin() ; it != r.end() ; it++)
		fd << *it << " "; 
	fd << "}" << std::endl;

	// TEST: erase

	// Note: erase an empty container performs an infinite loop.

	r.erase(++r.begin());
	fd << "\'Erase\' test 1: " << c.size() << std::endl << "{ ";
	for (typename Container::iterator it = r.begin() ; it != r.end() ; it++)
		fd << *it << " ";
	fd << "}" << std::endl;

	while (!r.empty())
		r.erase(r.begin());
	fd << "\'Erase\' test 2: " << *r.begin() << std::endl;

	for (size_t i = 15 ; i > size_t() ; i--)
		r.insert(std::pair<T, T>(T(i), T(i)));
	
	r.erase(++r.begin(), --r.end());
	fd << "\'Erase\' test 3: " << c.size() << std::endl << "{ ";
	for (typename Container::iterator it = r.begin() ; it != r.end() ; it++)
		fd << *it << " ";
	fd << "}" << std::endl;

	// TEST: swap

	Container w;

	for (size_t i = 15 ; i > size_t() ; i--)
		w.insert(std::pair<T, T>(T(i), T(i)));

	w.swap(r);
	fd << "\'Swap\' test 1: " << w.size() << std::endl << "{ ";
	for (typename Container::iterator it = w.begin() ; it != w.end() ; it++)
		fd << *it << " ";
	fd << "}" << std::endl;
	fd << c.size() << std::endl << "{ ";
	for (typename Container::iterator it = r.begin() ; it != r.end() ; it++)
		fd << *it << " ";
	fd << "}" << std::endl;
}

template <typename Container, typename T>
inline static void test_tree_lookup(std::ofstream& fd)
{
	fd << std::endl << "-------------- LOOKUP ----------------" << std::endl;

	// TEST: count

	Container w;

	for (size_t i = 15 ; i > size_t() ; i--)
		w.insert(std::pair<T, T>(T(i % 2 ? 0 : i), T(i)));
	fd << "\'Count\' test 1: " << w.count(T()) << std::endl;

	Container x;
	fd << "\'Count\' test 2: " << x.count(T()) << std::endl;

	fd << "\'Count\' test 3: " << w.count(T(42)) << std::endl;

	// TEST: find

	fd << "\'Find\' test 1: " << *w.find(T(14)) << std::endl;

	fd << "\'Find\' test 2: " << *x.find(T(14)) << std::endl;

	fd << "\'Find\' test 3: " << *w.find(T(42)) << std::endl;

	// TEST: equal range

	fd << "\'Equal range\' test 1: " << *w.equal_range(T(14)).first
	<< *w.equal_range(T(14)).second << std::endl;

	fd << "\'Equal range\' test 2: " << *x.equal_range(T(14)).first
	<< *x.equal_range(T(14)).second << std::endl;

	fd << "\'Equal range\' test 1: " << *w.equal_range(T(42)).first 
	<< *w.equal_range(T(42)).second << std::endl;

	// TEST: lower bound

	fd << "\'Lower bound\' test 1: " << *w.lower_bound(T(14)) << std::endl;

	fd << "\'Lower bound\' test 2: " << *x.lower_bound(T(14)) << std::endl;

	fd << "\'Lower bound\' test 3: " << *w.lower_bound(T(42)) << std::endl;

	// TEST: upper bound

	fd << "\'Upper bound\' test 1: " << *w.upper_bound(T(14)) << std::endl;

	fd << "\'Upper bound\' test 2: " << *x.upper_bound(T(14)) << std::endl;

	fd << "\'Upper bound\' test 3: " << *w.upper_bound(T(42)) << std::endl;
}

template <typename Container, typename T>
inline static void test_tree_observers(std::ofstream& fd)
{
	fd << std::endl << "-------------- OBSERVERS ----------------" << std::endl;

	// TEST: key compare

	// TEST: value compare
}

template <typename Container, typename T>
inline static void test_tree_non_members(std::ofstream& fd)
{
	fd << std::endl << "-------------- NON MEMBERS ----------------" << std::endl;

	Container lhs;

	for (size_t i = 15 ; i > size_t() ; i--)
		lhs.insert(std::pair<T, T>(T(i), T(i)));
	
	Container rhs(lhs);

	fd << "Test \'operator==\' 1: " << bool(lhs == rhs) << std::endl;
	fd << "Test \'operator!=\' 1: " << bool(lhs != rhs) << std::endl;
	fd << "Test \'operator<\' 1: " << bool(lhs < rhs) << std::endl;
	fd << "Test \'operator<=\' 1: " << bool(lhs <= rhs) << std::endl;
	fd << "Test \'operator>\' 1: " << bool(lhs > rhs) << std::endl;
	fd << "Test \'operator>=\' 1: " << bool(lhs >= rhs) << std::endl;

	lhs.insert({T(42), T(42)});
	rhs.insert({T(41), T(41)});

	fd << "Test \'operator==\' 2: " << bool(lhs == rhs) << std::endl;
	fd << "Test \'operator!=\' 2: " << bool(lhs != rhs) << std::endl;
	fd << "Test \'operator<\' 2: " << bool(lhs < rhs) << std::endl;
	fd << "Test \'operator<=\' 2: " << bool(lhs <= rhs) << std::endl;
	fd << "Test \'operator>\' 2: " << bool(lhs > rhs) << std::endl;
	fd << "Test \'operator>=\' 2: " << bool(lhs >= rhs) << std::endl;

	rhs.erase(rhs.begin());
	lhs.erase(lhs.begin());

	fd << "Test \'operator==\' 3: " << bool(lhs == rhs) << std::endl;
	fd << "Test \'operator!=\' 3: " << bool(lhs != rhs) << std::endl;
	fd << "Test \'operator<\' 3: " << bool(lhs < rhs) << std::endl;
	fd << "Test \'operator<=\' 3: " << bool(lhs <= rhs) << std::endl;
	fd << "Test \'operator>\' 3: " << bool(lhs > rhs) << std::endl;
	fd << "Test \'operator>=\' 3: " << bool(lhs >= rhs) << std::endl;

	lhs.swap(rhs);

	fd << "\'Swap\' test 2: " << lhs.size() << std::endl << "{ ";
	for (typename Container::iterator it = lhs.begin() ; it != lhs.end() ; it++)
		fd << *it << " ";
	fd << "}" << std::endl;
	fd << rhs.size() << std::endl << "{ ";
	for (typename Container::iterator it = rhs.begin() ; it != rhs.end() ; it++)
		fd << *it << " ";
	fd << "}" << std::endl;

	lhs.clear();
	rhs.clear();
	fd << "Test \'operator==\' 4: " << bool(lhs == rhs) << std::endl;
	fd << "Test \'operator!=\' 4: " << bool(lhs != rhs) << std::endl;
	fd << "Test \'operator<\' 4: " << bool(lhs < rhs) << std::endl;
	fd << "Test \'operator<=\' 4: " << bool(lhs <= rhs) << std::endl;
	fd << "Test \'operator>\' 4: " << bool(lhs > rhs) << std::endl;
	fd << "Test \'operator>=\' 4: " << bool(lhs >= rhs) << std::endl;
}

template <typename Container, typename T>
inline static void shared_tree_tests(const std::string& filename)
{
	static void (*const tests[])(std::ofstream&) = {
		&test_tree_constructor<Container, T>,
		&test_tree_assignation<Container, T>,
		&test_tree_element_access<Container, T>,
		&test_tree_iterators<Container, T>,
		&test_tree_reverse_iterators<Container, T>,
		&test_tree_capacity<Container, T>,
		&test_tree_modifiers<Container, T>,
		&test_tree_lookup<Container, T>,
		&test_tree_observers<Container, T>,
		&test_tree_non_members<Container, T>
	};

	start_tests(filename, tests, ARRAY_SIZE(tests));
}

template <typename Key, typename Value>
inline static void execute_shared_tests_for_tree_containers()
{
	shared_tree_tests<ft::map<int, int>, int>(std::string(std::string(TEST_DIR) + std::string(FT_MAP_FILENAME_SHARED)));
	shared_tree_tests<std::map<int, int>, int>(std::string(std::string(TEST_DIR) + std::string(STD_MAP_FILENAME_SHARED)));
	shared_tree_tests<std::multimap<int, int>, int>(std::string(std::string(TEST_DIR) + std::string(FT_MULTIMAP_FILENAME_SHARED)));
	shared_tree_tests<std::multimap<int, int>, int>(std::string(std::string(TEST_DIR) + std::string(STD_MULTIMAP_FILENAME_SHARED)));
	//shared_tree_tests<std::set<int>, int>(std::string(std::string(TEST_DIR) + std::string(FT_SET_FILENAME_SHARED)));
	//shared_tree_tests<std::set<int>, int>(std::string(std::string(TEST_DIR) + std::string(STD_SET_FILENAME_SHARED)));
	//shared_tree_tests<std::multiset<int>, int>(std::string(std::string(TEST_DIR) + std::string(FT_MULTISET_FILENAME_SHARED)));
	//shared_tree_tests<std::multiset<int>, int>(std::string(std::string(TEST_DIR) + std::string(STD_MULTISET_FILENAME_SHARED)));
}
