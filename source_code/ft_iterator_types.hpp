
/** @file ft_iterator_types.hpp
 *
 * 	This file contains the implementation of iterator based on
 * 	STL containers. Such as iterators_trails and struct iterator.
 */

# include "ft_containers.hpp"

# pragma once

namespace FT_NAMESPACE
{
	/**
	 * 	@defgroup iterator_tags Iterator Tags
	 *
	 * 	An iterator_tag is an empty type used to distinguish difderent kinds
	 * 	of iterators. The distinction is made by their behaviour not their
	 * 	content. Different underlying algorithms can then be used based on the
   	 *  different operations supported by different iterator types.
	*/

	//@{
	/// Input iterator tag.
	struct input_iterator_tag { };

	/// Output iterator tag.
	struct output_iterator_tag { };

	/// Forward iterator tag, support a superset of input iterator operations.
	struct forward_iterator_tag : public input_iterator_tag { };

	/// Bidirectional iterator tag, support a superset of forward iterators operations.
	struct bidirectional_iterator_tag : public forward_iterator_tag { };

	/// Random-access iterator tag, support a superset of bidirectional iterator operations.
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };
	//@}

	/**
	 * 	@brief Base-basic %iterator class
	 * 
	 * 	This class does nothing but define nested typedefs, derivated clases
	 *  can inherit from this class to use the typedefs.
	*/
	template <typename It_category, typename It_type, typename It_distance = std::ptrdiff_t,
				typename It_pointer = It_type*, typename It_reference = It_type&>
	struct	iterator
	{
		/// An iterator tag category.
		typedef It_category			iterator_category;

		/// The type pointed by the iterator.
		typedef It_type				value_type;

		/// The type used to represent the distance between iterators.
		typedef It_distance			difference_type;

		/// The type representing a pointer to the type pointed by the iterator.
		typedef It_pointer			pointer;

		/// The type representing a reference to the type pointed by the iterator.
		typedef It_reference		reference;
	};

	/**
	 * 	@brief Traits class for iterators
	 * 
	 * 	This class does nothing but define nestd typedefs, it can be
	 * 	used to define iterator types.
	*/

	template <typename It>
	struct iterator_traits
	{
		typedef typename It::iterator_category	iterator_category;
		typedef typename It::value_type			value_type;
		typedef typename It::difference_type	difference_type;
		typedef typename It::pointer			pointer;
		typedef typename It::reference			reference;
	};

	/// Partial specialization for pointer types.
	template <typename It_type>
	struct iterator_traits<It_type*>
	{
		typedef random_access_iterator_tag		iterator_category;
		typedef It_type							value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef It_type*						pointer;
		typedef It_type&						reference;
	};

	/// Partial specialization for const pointer types.
	template <typename It_type>
	struct iterator_traits<const It_type*>
	{
		typedef random_access_iterator_tag		iterator_category;
		typedef It_type							value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef It_type*						pointer;
		typedef It_type&						reference;
	};

	/**
	 * 	This function are auxiliar function.
	*/
	template <typename It>
	inline const typename iterator_traits<It>::iterator_category
	ft_get_iterator_category(const It&)
	{
		return (typename iterator_traits<It>::iterator_category());
	}

	// TO DO: do it need struct __is_random_access_iter ??
};