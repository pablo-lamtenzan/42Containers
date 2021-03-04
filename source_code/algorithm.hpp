
/** @file algorithm.hpp
 * 
 * 	This file contains the implementation of lexicographical compare
 * 	and equal
*/

# pragma once

# include "ft_containers.hpp"

namespace FT_NAMESPACE
{
	template <class InputIterator1, class InputIterator2>
  	bool
	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
    InputIterator2 first2, InputIterator2 last2)
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

	template<class InputIt1, class InputIt2>
	bool
	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
    	for (; first1 != last1 ; ++first1, ++first2)
       		if (!(*first1 == *first2))
            	return (false);
    	return (true);
	}

	template<class T> 
	const T&
	min(const T& a, const T& b)
	{ return (b < a ? b : a); }
};