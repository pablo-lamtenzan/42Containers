
# include "../vector/vector.hpp"
# include "../stack/stack.hpp"
# include "../queue/queue.hpp"

# include <fstream>

int main()
{
	size_t status = 0;

	static const char*const names[] = {
		"Test vector: ",
		"Test list: ",
		"Test map: ",
		"Test stack: ",
		"Test queue: "
	};

	static const char*const filenames[] = {
		"test_vector_ft",
		"test_vector_std",
		"test_list_ft",
		"test_list_std",
		"test_map_ft",
		"test_map_std",
		"test_stack_ft",
		"test_stack_std",
		"test_queue_ft",
		"test_queue_std"
	};

	template <class Container>
	using type = Container;

	static void				(*const tests[])(const std::string&, type)
	{
		&test_vector,
		&test_list,
		&test_map,
		&test_stack,
		&test_queue
	};

	template <class Container>
	using type = Container;

	static type containers[] = {
		ft::vector,
		std::vector,
		ft::list,
		std::list,
		ft::map,
		std::map,
		ft::stack,
		std::stack,
		ft::queue,
		std::queue
	};

	for (size_t i = 0, y = 0 ; i < sizeof(filenames) / sizeof(*filenames) ; i++)
	{
		tests[y](filenames[i], containers[i]);

		if (i % 2)
		{
			std::ifstream ifs1(filename[i - 2]);
			std::ifstream ifs2(filename[i - 1]);

			if (ifs1.bad() || ifs2.bad())
			{
				std::cerr << "Error: can not open the test files." << std::endl;
				return (1);
			}

			std::stringstream buff1;
			std::stringstream buff2;

			buff1 << ifs1.rdbuf();
			buff2 << ifs2.rdbuf();

			const std::string& s1 = buff1.str();
			const std::string& s2 = buff2.str();

			std::cout << names[i];

			// TO DO: Add color
			if (s1 == s2)
				std::cout << "Passed!" << std::endl;
			else
			{
				std::cout << "Failed!" << std::endl;
				status = 1;
			}
			y++;
		}
	}
	return (status);
}
