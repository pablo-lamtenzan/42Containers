
# pragma once

# include "tester.hpp"

# include <iostream>
# include <fstream>
# include <string>

# include <map>
# include <set>

template <typename Container, typename T>
inline static void shared_tree_tests(const std::string& filename)
{
	static void (*const tests[])(std::ofstream&) = {
	};

	start_tests(filename, tests, ARRAY_SIZE(tests));
}

template <typename Key, typename Value>
inline void execute_shared_tests_for_tree_containers()
{
	shared_tree_tests<std::map<int, int>, int>(std::string(std::string(TEST_DIR) + std::string(FT_MAP_FILENAME_SHARED)));
	shared_tree_tests<std::map<int, int>, int>(std::string(std::string(TEST_DIR) + std::string(STD_MAP_FILENAME_SHARED)));
	shared_tree_tests<std::multimap<int, int>, int>(std::string(std::string(TEST_DIR) + std::string(FT_MULTIMAP_FILENAME_SHARED)));
	shared_tree_tests<std::multimap<int, int>, int>(std::string(std::string(TEST_DIR) + std::string(STD_MULTIMAP_FILENAME_SHARED)));
	shared_tree_tests<std::set<int, int>, int>(std::string(std::string(TEST_DIR) + std::string(FT_SET_FILENAME_SHARED)));
	shared_tree_tests<std::set<int, int>, int>(std::string(std::string(TEST_DIR) + std::string(STD_SET_FILENAME_SHARED)));
	shared_tree_tests<std::multiset<int, int>, int>(std::string(std::string(TEST_DIR) + std::string(FT_MULTISET_FILENAME_SHARED)));
	shared_tree_tests<std::multiset<int, int>, int>(std::string(std::string(TEST_DIR) + std::string(STD_MULTISET_FILENAME_SHARED)));
}
