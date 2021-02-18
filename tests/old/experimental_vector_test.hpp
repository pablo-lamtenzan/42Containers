
# pragma once

# include "../allocator/allocator.hpp"

# include <deque>
# include <map>
# include <vector>
# include <string>
# include <fstream>

template <typename A, typename B, typename C>
class TYPES
{
	public :

	A	t1;
	B	t2;
	C	t3;

	TYPES() { }
	TYPES(const A& i, const B& f, const C& s) : t1(i), t2(f), t3(s) { }
	~TYPES() { }
};

template <typename A, typename B, typename C>
std::ostream& operator<<(std::ostream& os, const TYPES<A, B, C>& t) { return (os << "{" << t.t1 << "} {" << t.t2 << "} {" << t.t3 << "} "); }



// NOTE: To compile put the boolean operators in comment


void			vector_test_exp()
{

	try {

		std::ofstream fd;

		fd.open("vector_test");

		std::vector<TYPES<int, float, std::string>> vec(64);
		std::vector<TYPES<int, float, std::string>> empty;

		for (int i = 0 ; i < 64 ; i++)
			vec.push_back(TYPES<int, float, std::string>(i, static_cast<float>(i), "VECTOR"));

		/* Test At */
		fd << "Test \'at\' 1: Element in range: " << vec.at(1) << std::endl;
		//fd << "Test \'at\' 2: Element out of range: " << vec.at(420) << std::endl;

		/* Test operator[] */
		fd << "Test \'at\' 1: Element in range: " << vec[1] << std::endl;
		fd << "Test \'at\' 2: Element out of range: " << vec[420] << std::endl;

		/* Test front */
		fd << "Test \'front\' 1: With elem: " << vec.front() << std::endl;
		//fd << "Test \'front\' 2: Without elem: " << empty.front() << std::endl;

		/* Test back */
		fd << "Test \'front\' 1: With elem: " << vec.front() << std::endl;
		fd << "Test \'front\' 2: Without elem: " << vec.front() << std::endl;

		/* Test empty */
		fd << "Test \'empty\' 1: With empty vector: " << empty.empty() << std::endl;
		fd << "Test \'empty\' 2: With filled vector: " << vec.empty() << std::endl;

		/* Test size */
		fd << "Test \'size\' 1: With empty vector: " << empty.size() << std::endl;
		fd << "Test \'size\' 2: With filled vector: " << vec.size() << std::endl;

		/* Test max_size */
		fd << "Test \'max size\' 1: " << vec.max_size() << std::endl;

		/* Test capacity */
		fd << "Test \'capacity\' 1: Filled vector: " << vec.capacity() << std::endl;
		fd << "Test \'capacity\' 2: Empty vector: " << empty.capacity() << std::endl;

		/* Test reserse */
		vec.reserve(42);
		fd << "Test \'reserve\' 1: Filled vector: " << vec.capacity() << std::endl;
		empty.reserve(42);
		fd << "Test \'reserve\' 2: Empty vector: " << vec.capacity() << std::endl;


		/* Test clear */
		fd << "Before \'clear\' 1:" << std::endl;
		fd << "{";
		for (size_t i = 0 ; i < vec.size() ; i++)
			fd << vec.at(i);
		fd << "}" << std::endl << "Size: " << vec.size() << std::endl;
		fd << "Test \'clear\' 1: Filled vector: {";
		for (size_t i = 0 ; i < vec.size() ; i++)
			fd << vec.at(i);
		fd << "}" << std::endl << "Size: " << vec.size() << std::endl;

		fd << "Before \'clear\' 2:" << std::endl;
		fd << "{";
		for (size_t i = 0 ; i < empty.size() ; i++)
			fd << empty.at(i);
		fd << "}" << std::endl << "Size: " << empty.size() << std::endl;
		fd << "Test \'clear\' 2: Empty vector: {";
		for (size_t i = 0 ; i < empty.size() ; i++)
			fd << empty.at(i);
		fd << "}" << std::endl << "Size: " << empty.size() << std::endl;

		/* Test push back */
		for (int i = 0 ; i < 64 ; i++)
			vec.push_back(TYPES<int, float, std::string>(i, static_cast<float>(i), "VECTOR"));
		fd << "Test \'push back\' 1: Filled vector:" << std::endl;
		fd << "Last before: " << vec.at(vec.size() - 1) << std::endl;
		fd << "Size before: " << vec.size() << std::endl;
		vec.push_back(TYPES<int, float, std::string>(65, 65.0f, "VECTOR65"));
		fd << "Last after: " << vec.at(vec.size() - 1) << std::endl;
		fd << "Size after: " << vec.size() << std::endl;

		fd << "Test \'push back\' 1: Empty vector:" << std::endl;
		//fd << "Last before: " << empty.at(empty.size() - 1) << std::endl;
		fd << "Size before: " << empty.size() << std::endl;
		vec.push_back(TYPES<int, float, std::string>(65, 65.0f, "VECTOR65"));
		//fd << "Last after: " << empty.at(empty.size() -	 1) << std::endl;
		fd << "Size after: " << empty.size() << std::endl;

		/* Test pop back */
		fd << "Test \'pop back\' 1: Filled vector:" << std::endl;
		fd << "Last before: " << vec.at(vec.size() - 1) << std::endl;
		fd << "Size before: " << vec.size() << std::endl;
		vec.pop_back();
		fd << "Last after: " << vec.at(vec.size() - 1) << std::endl;
		fd << "Size after: " << vec.size() << std::endl;

		fd << "Test \'pop back\' 1: Empty vector:" << std::endl;
		//fd << "Last before: " << empty.at(empty.size() - 1) << std::endl;
		fd << "Size before: " << empty.size() << std::endl;
		vec.pop_back();
		//fd << "Last after: " << empty.at(empty.size() - 1) << std::endl;
		fd << "Size after: " << empty.size() << std::endl;

		/* Test resize */
		fd << "Test \'resize\' 1: Leasser size:" << std::endl;
		vec.resize(32);
		fd << "{";
		for (size_t i = 0 ; i < vec.size() ; i++)
			fd << vec.at(i);
		fd << "}" << std::endl << "Size: " << vec.size() << std::endl;

		fd << "Test \'resize\' 2: Greather size:" << std::endl;
		vec.resize(64);
		fd << "{";
		for (size_t i = 0 ; i < vec.size() ; i++)
			fd << vec.at(i);
		fd << "}" << std::endl << "Size: " << vec.size() << std::endl;

		/* Test swap */
		empty.clear();
		for (int i = 0 ; i < 64 ; i++)
			empty.push_back(TYPES<int, float, std::string>(i, static_cast<float>(i), "VECTOR"));

		fd << "Test swap:" << std::endl;

		fd << "\'vec\' is:" << std::endl;
		for (size_t i = 0 ; i < vec.size() ; i++)
			fd << vec.at(i);
		fd << "}" << std::endl;
		fd << "Size: " << vec.size() << std::endl;
		fd << "Capacity: " << vec.capacity() << std::endl;

		fd << "\'empty\' is:" << std::endl;
		for (size_t i = 0 ; i < empty.size() ; i++)
			fd << empty.at(i);
		fd << "}" << std::endl;
		fd << "Size: " << empty.size() << std::endl;
		fd << "Capacity: " << empty.capacity() << std::endl;

		fd << "S W A P" << std::endl;
		vec.swap(empty);

		fd << "\'vec\' is:" << std::endl;
		for (size_t i = 0 ; i < vec.size() ; i++)
			fd << vec.at(i);
		fd << "}" << std::endl;
		fd << "Size: " << vec.size() << std::endl;
		fd << "Capacity: " << vec.capacity() << std::endl;

		fd << "\'empty\' is:" << std::endl;
		for (size_t i = 0 ; i < empty.size() ; i++)
			fd << empty.at(i);
		fd << "}" << std::endl;
		fd << "Size: " << empty.size() << std::endl;
		fd << "Capacity: " << empty.capacity() << std::endl;

		/* Test begin */
		empty.clear();

		fd << "Test \'begin\' 1: Empty vector:" << *empty.begin() << std::endl;
		fd << "Test \'begin\' 2: Filled vector: " << *vec.begin() << std::endl;

		/* Test end */
		fd << "Test \'end\' 1: Empty vector:" << *empty.end() << std::endl;
		fd << "Test \'end\' 2: Filled vector: " << *vec.end() << std::endl;

		/* Test rbegin */
		fd << "Test \'rbegin\' 1: Empty vector:" << *empty.rbegin() << std::endl;
		fd << "Test \'rbegin\' 2: Filled vector: " << *vec.rbegin() << std::endl;

		/* Test rend */
		fd << "Test \'rend\' 1: Empty vector:" << *empty.rend() << std::endl;
		fd << "Test \'rend\' 2: Filled vector: " << *vec.rend() << std::endl;


		// TO DO: Iterators does not work and must test all the definitions

	
		/* Test erase */

		typename std::vector<TYPES<int, float, std::string>>::iterator it = vec.begin();
		typename std::vector<TYPES<int, float, std::string>>::iterator end = vec.end();
		
		for (size_t i = 0 ; it != end ; it++)
			if (i++ % 2)
				vec.erase(it);
		fd << "\'vec\' is:" << std::endl;
		for (size_t i = 0 ; i < vec.size() ; i++)
			fd << vec.at(i);
		fd << "}" << std::endl;
		fd << "Size: " << vec.size() << std::endl;
		fd << "Capacity: " << vec.capacity() << std::endl;

		/* Test insert */

		/*
		it = vec.begin();

		for (size_t i = 0 ; it != end ; it++)
			if (i++ % 2)
				vec.insert(it, TYPES<int, float, std::string>(0, 0.0f, "NULL"));
		fd << "\'vec\' is:" << std::endl;
		for (size_t i = 0 ; i < vec.size() ; i++)
			fd << vec.at(i);
		fd << "}" << std::endl;
		fd << "Size: " << vec.size() << std::endl;
		fd << "Capacity: " << vec.capacity() << std::endl;
		*/

		/* Test iterator operators */

		// TO DO

		/* Test constructors */

		std::vector<TYPES<int, float, std::string>> src;
		for (size_t i = 0 ; i < 64 ; i++)
			src.push_back(TYPES<int, float, std::string>(999, 999, "999"));
		
		std::vector<TYPES<int, float, std::string>> dest(src);
		fd << "{ ";
		for (size_t i = 0 ; i < dest.size() ; i++)
			fd << dest.at(i);
		fd << " }";

		std::vector<TYPES<int, float, std::string>> it_dest(dest.begin(), dest.end());
		fd << "{ ";
		for (size_t i = 0 ; i < it_dest.size() ; i++)
			fd << it_dest.at(i);
		fd << " }";

		std::vector<TYPES<int, float, std::string>> counts(64, TYPES<int, float, std::string>(888, 888, "888"));
		fd << "{ ";
		for (size_t i = 0 ; i < counts.size() ; i++)
			fd << counts.at(i);
		fd << " }";

		std::vector<TYPES<int, float, std::string>> assignation = counts;
		counts.clear();
		fd << "{ ";
		for (size_t i = 0 ; i < assignation.size() ; i++)
			fd << assignation.at(i);
		fd << " }";

		/* Test operators */

		std::vector<TYPES<int, float, std::string>> lhs;
		std::vector<TYPES<int, float, std::string>> rhs;

		fd << "Test vector booleans: " << std::endl;

		/* Test operator== */
		fd << "Test \'==\' 1: Equal data and lenght:" << std::endl;
		for (size_t i = 0 ; i < 5 ; i++)
			lhs.push_back(TYPES<int, float, std::string>(static_cast<int>(i), static_cast<float>(i), "ASD"));
		rhs = lhs;
		fd << "> " << static_cast<bool>(lhs == rhs) << std::endl;

		fd << "Test \'==\' 2: Diferent data but same lenght:" << std::endl;
		lhs.clear();
		for (size_t i = 0 ; i < 5 ; i++)
			lhs.push_back(TYPES<int, float, std::string>(static_cast<int>(i + 1), static_cast<float>(i + 1), "ASD1"));
		fd << "> " << static_cast<bool>(lhs == rhs) << std::endl;

		fd << "Test \'==\' 3: Diferent data and lenght:" << std::endl;
		rhs = lhs;
		lhs.push_back(TYPES<int, float, std::string>(0, 0, "0"));
		fd << "> " << static_cast<bool>(lhs == rhs) << std::endl;

		/* Test operator!= */
		fd << "Test \'!=\' 1: Equal data and lenght:" << std::endl;
		for (size_t i = 0 ; i < 5 ; i++)
			lhs.push_back(TYPES<int, float, std::string>(static_cast<int>(i), static_cast<float>(i), "ASD"));
		rhs = lhs;
		fd << "> " << static_cast<bool>(lhs != rhs) << std::endl;

		fd << "Test \'!=\' 2: Diferent data but same lenght:" << std::endl;
		lhs.clear();
		for (size_t i = 0 ; i < 5 ; i++)
			lhs.push_back(TYPES<int, float, std::string>(static_cast<int>(i + 1), static_cast<float>(i + 1), "ASD1"));
		fd << "> " << static_cast<bool>(lhs != rhs) << std::endl;

		fd << "Test \'!=\' 3: Diferent data and lenght:" << std::endl;
		rhs = lhs;
		lhs.push_back(TYPES<int, float, std::string>(0, 0, "0"));
		fd << "> " << static_cast<bool>(lhs != rhs) << std::endl;

		/* Test operator< */
		fd << "Test \'<\' 1: Equal data and lenght:" << std::endl;
		for (size_t i = 0 ; i < 5 ; i++)
			lhs.push_back(TYPES<int, float, std::string>(static_cast<int>(i), static_cast<float>(i), "ASD"));
		rhs = lhs;
		fd << "> " << static_cast<bool>(lhs < rhs) << std::endl;

		fd << "Test \'<\' 2: Diferent data but same lenght:" << std::endl;
		lhs.clear();
		for (size_t i = 0 ; i < 5 ; i++)
			lhs.push_back(TYPES<int, float, std::string>(static_cast<int>(i + 1), static_cast<float>(i + 1), "ASD1"));
		fd << "> " << static_cast<bool>(lhs < rhs) << std::endl;

		fd << "Test \'<\' 3: Diferent data and lenght:" << std::endl;
		rhs = lhs;
		lhs.push_back(TYPES<int, float, std::string>(0, 0, "0"));
		fd << "> " << static_cast<bool>(lhs < rhs) << std::endl;

		/* Test operator <= */
		fd << "Test \'<=\' 1: Equal data and lenght:" << std::endl;
		for (size_t i = 0 ; i < 5 ; i++)
			lhs.push_back(TYPES<int, float, std::string>(static_cast<int>(i), static_cast<float>(i), "ASD"));
		rhs = lhs;
		fd << "> " << static_cast<bool>(lhs <= rhs) << std::endl;

		fd << "Test \'<=\' 2: Diferent data but same lenght:" << std::endl;
		lhs.clear();
		for (size_t i = 0 ; i < 5 ; i++)
			lhs.push_back(TYPES<int, float, std::string>(static_cast<int>(i + 1), static_cast<float>(i + 1), "ASD1"));
		fd << "> " << static_cast<bool>(lhs <= rhs) << std::endl;

		fd << "Test \'<=\' 3: Diferent data and lenght:" << std::endl;
		rhs = lhs;
		lhs.push_back(TYPES<int, float, std::string>(0, 0, "0"));
		fd << "> " << static_cast<bool>(lhs <= rhs) << std::endl;

		/* Test operator > */
		fd << "Test \'>\' 1: Equal data and lenght:" << std::endl;
		for (size_t i = 0 ; i < 5 ; i++)
			lhs.push_back(TYPES<int, float, std::string>(static_cast<int>(i), static_cast<float>(i), "ASD"));
		rhs = lhs;
		fd << "> " << static_cast<bool>(lhs > rhs) << std::endl;

		fd << "Test \'>\' 2: Diferent data but same lenght:" << std::endl;
		lhs.clear();
		for (size_t i = 0 ; i < 5 ; i++)
			lhs.push_back(TYPES<int, float, std::string>(static_cast<int>(i + 1), static_cast<float>(i + 1), "ASD1"));
		fd << "> " << static_cast<bool>(lhs > rhs) << std::endl;

		fd << "Test \'>\' 3: Diferent data and lenght:" << std::endl;
		rhs = lhs;
		lhs.push_back(TYPES<int, float, std::string>(0, 0, "0"));
		fd << "> " << static_cast<bool>(lhs > rhs) << std::endl;

		/* Test operator >= */
		fd << "Test \'>=\' 1: Equal data and lenght:" << std::endl;
		for (size_t i = 0 ; i < 5 ; i++)
			lhs.push_back(TYPES<int, float, std::string>(static_cast<int>(i), static_cast<float>(i), "ASD"));
		rhs = lhs;
		fd << "> " << static_cast<bool>(lhs >= rhs) << std::endl;

		fd << "Test \'>=\' 2: Diferent data but same lenght:" << std::endl;
		lhs.clear();
		for (size_t i = 0 ; i < 5 ; i++)
			lhs.push_back(TYPES<int, float, std::string>(static_cast<int>(i + 1), static_cast<float>(i + 1), "ASD1"));
		fd << "> " << static_cast<bool>(lhs >= rhs) << std::endl;

		fd << "Test \'>=\' 3: Diferent data and lenght:" << std::endl;
		rhs = lhs;
		lhs.push_back(TYPES<int, float, std::string>(0, 0, "0"));
		fd << "> " << static_cast<bool>(lhs >= rhs) << std::endl;

	} catch(std::exception& e) { std::cerr << e.what() << std::endl; }
}
