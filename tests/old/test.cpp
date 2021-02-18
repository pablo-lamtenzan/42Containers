

// NOTE THIS DOES NOT WORK, in dont delete it cause sometimes i get inspired


# include <string>
# include <fstream>

// Standart dependencies
# include <vector>
# include <list>
# include <map>
# include <stack>
# include <queue>
# include <deque>
//# include <multimap>
# include <set>
//# include <multiset>

// ft dependencies
# include <vector.hpp>
//# include <list.hpp>
# include <map.hpp>
# include <stack.hpp>
# include <queue.hpp>
# include <deque.hpp>
# include <multimap.hpp>
# include <set.hpp>
# include <multiset.hpp>

# define VECTOR_TEMPLATE int
# define LIST_TEMPLATE int
# define MAP_TEMPLATE int, int
# define STACK_TEMPLATE int
# define QUEUE_TEMPLATE int
# define DEQUE_TEMPLATE int
# define MULTIMAP_TEMPLATE int, int
# define SET_TEMPLATE int, int
# define MULTISET_TEMPLATE int, int

int main()
{
	bool res = 0;
	
	static const char* const names[] = {
		"vector",
		"list",
		"map",
		"stack",
		"queue",
		"deque",
		"multimap",
		"set",
		"multiset"
	};

	/*	Each container must have 2 kinds of tests:
	*	- Global test: shared by all the containers.
	*	- Unique test: unique for the target container.
	*
	*	For each container both tests are performed and the output
	*	of those tests will be stored in file.
	*	Then, the same tests will be performed with the standart version,
	*	and, in the same way, the result will be stored in a file.
	*
	*	Finally, ft and standart files will be read and stored in a buffer using
	*	a std::string. If both buffers are equal the container has pass the test.
	*/

	/// @param filename @param container
	template <typename Container>
	using container = Container;
	static void (*const unique_test[])(const std::string&, container)
	{
		// TO DO: Perhabs the pointer to function array taking as param a template does not work with that syntax.
		&test_vector,
		&test_list,
		&test_map,
		&test_stack,
		&test_queue,
		&test_deque,
		&test_multimap,
		&test_set,
		&test_multiset
	};

	/// Array of the target containers
	template <typename Container>
	using container = Container;
	static container[] = {
		// TO DO: ABSOLUTLY the syntax is wrong.

		ft::vector<VECTOR_TEMPLATE>,
		std::vector<VECTOR_TEMPLATE>,

		ft::list<LIST_TEMPLATE>,
		std::list<LIST_TEMPLATE>,

		ft::map<MAP_TEMPLATE>,
		std::map<MAP_TEMPLATE>,

		ft::stack<STACK_TEMPLATE>,
		std::stack<STACK_TEMPLATE>,

		ft::queue<QUEUE_TEMPLATE>,
		std::queue<QUEUE_TEMPLATE>,

		ft::deque<DEQUE_TEMPLATE>,
		std::deque<DEQUE_TEMPLATE>,

		ft::multimap<MULTIMAP_TEMPLATE>,
		std::multimamp<MULTIMAP_TEMPLATE>,

		ft::set<SET_TEMPLATE>
		std::set<SET_TEMPLATE>

		ft::multiset<MULTISET_TEMPLATE>
		std::multiset<MULTISET_TEMPLATE>
	};

	static const std::string& _global("global_");
	static const std::string& _unique("unique_")
	static const std::string& _ft("ft_");
	static const std::string& _std("std_");
	static const std::string& _test("_test");

	for (size_t i = 0, y = 0 ; i < sizeof(names) / sizeof(*names) ; i++)
	{
		const std::string& global_filename(_global + name[y] + _test);
		const std::string& unique_filename(_unique + name[y] + _test);

		/// @param filename, @param container
		global_test<container[i]>((i % 2 ? _ft : _std) + global_filename);

		/// @param filename, @param container
		unique_test[y]<container[i]>((i % 2 ? _ft : _std) + unique_filename);

		// If std and ft test has been performed
		if (i % 2)
		{
			// Open the filenames
			std::ifstream ft_global_fd(_ft + global_filename);
			std::ifstream std_global_fd(_std + global_filename);
			std::ifstream ft_unique_fd(_ft + unique_filename);
			std::ifstream std_unique_fd(_std + unique_filename);

			if (ft_global_fd.bad() || std_global_fd.bad()
			|| ft_unique_fd.bad() || std_unique_fd.bad())
			{
				std::cerr << "Error: can not open the test files." << std::endl;
				return (1);
			}

			// Read the filenames
			std::stringstream ft_global_buff;
			std::stringstream std_global_buff;
			std::stringstream ft_unique_buff;
			std::stringstream std_unique_buff;

			ft_global_buff << ft_global_fd.rdbuff();
			std_global_buff << std_global_fd.rdbuff();
			ft_unique_buff << ft_unique_fd.rdbuff();
			std_unique_buff << std_unique_fd.rdbuff();

			// Compare the buffers
			const std::string& ft_test = ft_global_buff.str() + ft_unique_buff.str();
			const std::string& std_test = std_global_buff.str() + std_unique_buff.str();

			const std::string& test_name = names[y] + " test: ";
			// TO DO: Add Color
			if (ft_test == std_test)
				std::cout << test_name << "SUCESS";
			else
			{
				std::cout << test_name << "FAILED";
				res = 1;
			}
			y++;
		}
	}
	return (status);
}