# pragma once

/*
** Lexicophical_compare (less-tham comparison): performs a lexical comparison
** between the first range and the second range.
** Used to implement the operator<.
**
** The code is implemented in the documentation: https://cplusplus.com/reference/algorithm/lexicographical_compare/
*/

namespace ft
{
	
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
		if (first2 == last2 || *first2 < *first1)
			return (false);
		else if (*first1 < *first2)
			return (true);
		++first1;
		++first2;
		}
		return (first2 != last2);
	}
};