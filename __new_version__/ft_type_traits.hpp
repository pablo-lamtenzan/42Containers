
/** @file ft_type_trats.hpp
 *
 * 	This file contains function templates that perform types operations.
 * 
 * 	Functions: enable_if, conditional_type
*/

# pragma once

# include <ft_containers.hpp>

namespace FT_NAMESPACE
{
	/// Nested type, contains the @c type if the bool is true.
	template <bool, typename>
	struct enable_if { };

	template <typename T>
	struct enable_if<true, T> { typedef T type; };

	/// Conditional nested type.
	template <bool Cond, typename Iftrue, typename Iffalse>
	struct conditional_type { typedef Iffalse type; };

	template <bool Cond, typename Iftrue, typename Iffalse>
	struct conditional_type<true, Iftrue, Iffalse> { typedef Iftrue type; };

	struct true_type { };
	struct false_type { };

	/// Compare for equty types
	template <typename, typename>
	struct are_same
	{
		enum { value = 0 };
		typedef false_type type;
	};

	template<typename T>
	struct are_same<T, T>
	{
		enum { value = 1 };
		typedef true_type type;
	};

};