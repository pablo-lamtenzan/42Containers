
# pragma once

# include "tester.hpp"

# include <iostream>
# include <fstream>
# include <string>

# include <map>
# include <set>

template <typename Container, typename T>
inline static void test_tree_constructor(std::ofstream& fd)
{
	fd << std::endl << "-------------- CONSTRUCTOR ----------------" << std::endl;

	// TEST: default constructor

	// TEST: comparison constructor

	// TEST: range constructor

	// TEST: comparsion range constructor

	// TEST: copy constructor

}

template <typename Container, typename T>
inline static void test_tree_assignation(std::ofstream& fd)
{
	fd << std::endl << "-------------- ASSIGNATION ----------------" << std::endl;

	// TEST: operator=

	// TESTRassign
}

template <typename Container, typename T>
inline static void test_tree_element_access(std::ofstream& fd)
{
	fd << std::endl << "-------------- ELEMENT ACCESS ----------------" << std::endl;

	// call random access

	// TEST: front

	// TEST: back
}

template <typename Container, typename T>
inline static void test_tree_iterators(std::ofstream& fd)
{
	fd << std::endl << "-------------- ITERATORS ----------------" << std::endl;

	// TEST: iterators

	// TEST: const iterators

	// TEST: iterators nom member
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

	// TEST: size

	// TEST: max size
}

template <typename Container, typename T>
inline static void test_tree_modifiers(std::ofstream& fd)
{
	fd << std::endl << "-------------- MODIFIERS ----------------" << std::endl;

	// TEST: insert

	// TEST: erase

	// TEST: swap
}

template <typename Container, typename T>
inline static void test_tree_lookup(std::ofstream& fd)
{
	fd << std::endl << "-------------- LOOKUP ----------------" << std::endl;

	// TEST: count

	// TEST: find

	// TEST: equal range

	// TEST: lower bound

	// TEST: upper bound
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
	shared_tree_tests<std::map<int, int>, int>(std::string(std::string(TEST_DIR) + std::string(FT_MAP_FILENAME_SHARED)));
	shared_tree_tests<std::map<int, int>, int>(std::string(std::string(TEST_DIR) + std::string(STD_MAP_FILENAME_SHARED)));
	shared_tree_tests<std::multimap<int, int>, int>(std::string(std::string(TEST_DIR) + std::string(FT_MULTIMAP_FILENAME_SHARED)));
	shared_tree_tests<std::multimap<int, int>, int>(std::string(std::string(TEST_DIR) + std::string(STD_MULTIMAP_FILENAME_SHARED)));
	shared_tree_tests<std::set<int>, int>(std::string(std::string(TEST_DIR) + std::string(FT_SET_FILENAME_SHARED)));
	shared_tree_tests<std::set<int>, int>(std::string(std::string(TEST_DIR) + std::string(STD_SET_FILENAME_SHARED)));
	shared_tree_tests<std::multiset<int>, int>(std::string(std::string(TEST_DIR) + std::string(FT_MULTISET_FILENAME_SHARED)));
	shared_tree_tests<std::multiset<int>, int>(std::string(std::string(TEST_DIR) + std::string(STD_MULTISET_FILENAME_SHARED)));
}
