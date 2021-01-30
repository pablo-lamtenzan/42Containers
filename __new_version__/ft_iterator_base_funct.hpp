
/**
 * 	@file ft_iterator_base_funct.hpp
 * 
 * 	This file contains functions used to implement container
 * 	iterators.
 * 
 * 	Fuctions: distance(), advance()
*/

# pragma once

# include <ft_iterator_types.hpp>

namespace FT_NAMESPACE
{
	/**
	 * 	@brief Distance
	 * 
	 * 	@param first An input iterator.
	 * 	@param last	An input iterator.
	 * 	@return The distance betwenn both.
	*/
	template <typename It>
	inline const typename iterator_traits<It>::difference_type
	distance(It first, It last)
	{
		typename iterator_traits<It>::difference_type dist = 0;

		if (check_type<It, random_access_iterator_tag>())
			dist = last - first;
		else
		{
			while (first++ != last)
				dist++;
		}
		return (dist);
	}

	/**
	 * 	@brief Advance
	 * 
	 *	@param it An iterator
	 *	@param n The delta by wich to change @p it.
	 *	@return Nothing
	 *
	 * 	If @p n is positive, @p it is incremented @p n amount,
	 * 	or decremented if @p n is negative.
	*/
	template <typename It, typename Dist>
	inline const void advance(It& it, Dist n)
	{
		if (check_type<It, random_access_iterator_tag>())
			it += n;
		else if (check_type<It, bidirectional_iterator_tag>())
		{
			if (n > 0)
				while (n--)
					it++;
			else
				while (n++)
					it--;
		}
		else
		{
			while (n--)
				it++;
		}
	}
};
