
/** @file algorithm.hpp
 * 
 * 	This file contains the implementation of lexicographical compare
 * 	and equal
*/

# pragma once

# include "ft_containers.hpp"

namespace FT_NAMESPACE
{
	/* Nested class template designed to hold any fundamental type */
	template <class T>
	struct is_integral
	{ typedef void* type; };

	/* Specilizated versions */
	template <>
	struct is_integral<bool>
	{ typedef int type; };

	template <>
	struct is_integral<char>
	{ typedef int type; };

	template <>
	struct is_integral<signed char>
	{ typedef int type; };
	
	template <>
	struct is_integral<unsigned char>
	{ typedef int type; };

	template <> 
	struct is_integral<wchar_t>
	{ typedef int type; };

/*
	template <>
	struct is_integral<char16_t>
	{ typedef int type; };

	template <>
	struct is_integral<char32_t>
	{ typedef int type; };
*/

	template <>
	struct is_integral<short>
	{ typedef int type; };

	template <>
	struct is_integral<unsigned short>
	{ typedef int type; };

	template <>
	struct is_integral<int>
	{ typedef int type; };

	template <>
	struct is_integral<unsigned int>
	{ typedef int type; };

	template <>
	struct is_integral<long>
	{ typedef int type; };

	template <>
	struct is_integral<unsigned long>
	{ typedef int type; };

	template <>
	struct is_integral<long long>
	{ typedef int type; };

	template <>
	struct is_integral<unsigned long long>
	{ typedef int type; };
/*
	template <>
	struct is_integral<__int128_t>
	{ typedef int type; };

	template <>
	struct is_integral<__uint128_t>
	{ typedef int type; };
*/
	template <class InputIterator1, class InputIterator2>
  	inline bool
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
	inline bool
	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
    	for (; first1 != last1 ; ++first1, ++first2)
       		if (!(*first1 == *first2))
            	return (false);
    	return (true);
	}

	template<class T> 
	inline const T&
	min(const T& a, const T& b)
	{ return (b < a ? b : a); }

	template <typename Arg, typename Result>
	struct unary_function
	{
		/// @c argument_type is the type of the argument.
		typedef Arg		argument_type;
		/// @c result_type is the type of the return
		typedef Result	result_type;
	};

	/// Operator() calls pair.first
	template <typename Pair>
	struct Select_1st
	: public unary_function<Pair, typename Pair::first_type>
	{
		typedef typename Pair::first_type	first_type;

		first_type&			operator()(Pair& x) const;
		const first_type&	operator()(const Pair& x) const;
	};

	template <typename Pair>
	inline typename Select_1st<Pair>::first_type&
	Select_1st<Pair>::operator()(Pair& x) const
	{ return (x.first); }

	template <typename Pair>
	inline const typename Select_1st<Pair>::first_type&
	Select_1st<Pair>::operator()(const Pair& x) const
	{ return (x.first); }
};