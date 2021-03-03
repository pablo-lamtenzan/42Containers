
/** @file stack.hpp
 * 
 * 	This file contain the stack implementatation.
*/

# pragma once

# include <ft_containers.hpp>

namespace FT_NAMESPACE
{
	/**
	 * 	@brief Stack
	 * 
	 * 	@tparam T the type of value holded by the conatiner.
	 * 	@tparam Container the type of value holded by the stack
	*/
	template <class T, class Container> // to do set queue by dft
	struct stack
	{
		// TO DO: Probally i have to add the operator== and operator< here too

		/* Member types */

		typedef Container									container_type;
		typedef typename container_type::value_type			value_type;
		typedef typename container_type::reference			reference;
		typedef typename container_type::const_reference	const_reference;
		typedef typename container_type::size_type			size_type;

		/* Member fucntions */

		explicit stack(const_reference other = container_type());

		// TO DO: operator= & swap
	
		/* Element access */
		reference 		top();
		const_reference top() const;

		/* Capacity */
		bool			empty() const;
		size_type		size() const;

		/* Modifiers */
		void			push(const_reference value);
		void			pop();

		/* Core */

		protected:

		container_type	c;
	};

	/**
	 * 	@brief Default Constructor
	*/
	template <class T, class Container>
	stack<T, Container>::stack(const_reference other = container_type())
	: c(other)
	{ }

	////////////////////
	// Element access //
	////////////////////

	/**
	 * 	@brief top
	 * 
	 * 	@return A reference to the first element in %stack.
	*/
	template <class T, class Container>
	inline typename stack<T, Container>::reference
	stack<T, Container>::top()
	{ return (c.back()); }

	/**
	 * 	@brief top
	 * 
	 * 	@return A const reference to the first element in %stack.
	*/
	template <class T, class Container>
	inline typename stack<T, Container>::const_reference
	stack<T, Container>::top() const
	{ return (c.back()); }

	//////////////
	// Capacity //
	//////////////

	/**
	 * 	@brief empty
	 * 
	 * 	@return True if %stack is empty.
	*/
	template <class T, class Container>
	inline bool
	stack<T, Container>::empty() const
	{ return (c.empty()); }

	/**
	 * 	@brief size
	 * 
	 * 	@return The amount of elements holded by %stack
	*/
	template <class T, class Container>
	inline typename stack<T, Container>::size_type
	stack<T, Container>::size() const
	{ return (c.size()); }

	//////////////
	// Modifier //
	//////////////

	/**
	 * 	@brief push
	 * 
	 * 	Preppend one element in the top of %stack.
	*/
	template <class T, class Container>
	inline void
	stack<T, Container>::push(const_reference value)
	{ c.push_back(value); }

	/**
	 * 	@brief pop
	 * 
	 * 	Removes the element located at the top of %stack.
	*/
	template <class T, class Container>
	inline void
	stack<T, Container>::pop()
	{ c.pop_back(); }

	/////////////////
	// Non members //
	/////////////////

	/**
	 * 	@brief Stack boolen operators
	 * 
	 * 	@tparam T the type holded by @a Container.
	 * 	@tparam The container type holded by %stack.
	 * 	@return The result of the requested boolean operation.
	*/
	template <class T, class Container>
	inline bool
	operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (lsh.c == rhs.c); }

	template <class T, class Container>
	inline bool
	operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (lsh.c != rhs.c); }

	template <class T, class Container>
	inline bool
	operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (lsh.c < rhs.c); }

	template <class T, class Container>
	inline bool
	operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (lsh.c <= rhs.c); }

	template <class T, class Container>
	inline bool
	operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (lsh.c > rhs.c); }

	template <class T, class Container>
	inline bool
	operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return (lsh.c >= rhs.c); }
};