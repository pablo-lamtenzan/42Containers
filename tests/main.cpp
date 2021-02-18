
# include <fstream>
# include <sstream>
# include "shared_test_linear.hpp"
# include "shared_test_tree.hpp"
# include "tester.hpp"

int main()
{
	bool status = 0;

	static void (*const tests[])() = {
		&execute_shared_tests_for_linear_containers<int>,
		&execute_shared_tests_for_tree_containers<int, int>,
		&vector_tests,
		&list_tests,
		&map_tests,
		&stack_tests,
		&queue_tests,
		&deque_tests,
		&multimap_tests,
		&set_tests,
		&multiset_tests
	};

	for (size_t i = 0 ; i < sizeof(tests) / sizeof(*tests) ; i++)
		tests[i]();

	// TO DO: Change to the ft filenames the index % 2 == 0 indexes
	static const char*const filenames[] = {
		STD_VECTOR_FILENAME_SHARED,
		STD_VECTOR_FILENAME_SHARED,
		STD_LIST_FILENAME_SHARED,
		STD_LIST_FILENAME_SHARED,
		STD_DEQUE_FILENAME_SHARED,
		STD_DEQUE_FILENAME_SHARED
	};

	for (size_t i = 0 ; i < sizeof(filenames) / sizeof(*filenames) ; i++)
	{
		if (i % 2)
		{
			std::ifstream ifs_ft(filenames[i - 1]);
			std::ifstream ifs_std(filenames[i]);

			if (ifs_ft.bad() || ifs_std.bad())
			{
				std::cerr << "std::ifstream ERROR" << std::endl;
				return (1);
			}

			std::stringstream buff1;
			std::stringstream buff2;

			buff1 << ifs_ft.rdbuf();
			buff2 << ifs_std.rdbuf();

			// TO DO: Add colored log

			std::cout << "Diff between [ " << filenames[i - 1] << " ]"
			<< " and [ " << filenames[i] << " ] : ";

			const std::string& s1 = buff1.str();
			const std::string& s2 = buff2.str();

			std::cout << std::string(s1 != s2 && (status = 1) ? "FAILURE" : "SUCCESS") << std::endl;
		}
	}
	std::cout << std::endl;
	return (status);
}