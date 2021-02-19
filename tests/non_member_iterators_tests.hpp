
# pragma once

template <typename Container, typename T>
inline void test_non_member_iterators(std::ofstream& fd)
{
	fd << std::endl << "-------------- NON MERBER ITERATORS ----------------" << std::endl;

	Container c(size_t(42));

	size_t y = 0;
	for (typename Container::iterator i = c.begin() ; i != c.end() ; i++)
		*i = T(y++);

	typename Container::iterator lhs = c.begin();
	typename Container::iterator rhs = c.end();

	for (size_t i = 0xf ; i > 0 ; i--)
	{
		lhs++;
		rhs--;
	}

	fd << "Test \'iterator non member\' 1: " << std::endl;
	fd << "[" << bool(lhs == rhs) << "]" << std::endl;
	fd << "[" << bool(lhs != rhs) << "]" << std::endl;
	fd << "[" << bool(lhs < rhs) << "]" << std::endl;
	fd << "[" << bool(lhs <= rhs) << "]" << std::endl;
	fd << "[" << bool(lhs > rhs) << "]" << std::endl;
	fd << "[" << bool(lhs >= rhs) << "]" << std::endl;
}