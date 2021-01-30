
/**	@file ft_containers.hpp
 * 
 * 	This file contain the general shared element used 
 * 	in this reimplementation of STL containers.
 */

# pragma once

# include <cstddef>

# define FT_NAMESPACE ft

namespace FT_NAMESPACE
{

	/**
	 * 	@brief Check type
	 * 
	 * 	Compares 2 value types.
	 * 
	 * 	@tparam Target: the target type.
	 * 	@tparam Required: the required type.
	 * 	@return If Target == Required return true.
	*/
	template <typename Target, typename Required>
	inline bool check_type()
	{
		typename iterator_traits<Target>::iterator_category* t;

		return (dynamic_cast<Required*>(t));
	}
};