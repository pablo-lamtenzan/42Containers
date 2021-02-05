
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
	class stack
	{
		// TO DO: Probally i have to add the operator== and operator< here too

		public:

		typedef Container									container_type;
		typedef typename container_type::value_type			value_type;
		typedef typename container_type::reference			reference;
		typedef typename container_type::const_reference	const_reference;
		typedef typename container_type::size_type			size_type;

		/* Esp container */

		protected:

		Container			c;

		public:

		/**
		 * 	@brief Default Constructor
		*/
		explicit stack(const_reference other = container_type()) : c(other) { }

		/**
		 * 	@brief empty
		 * 
		 * 	@return True if %stack is empty.
		*/
		bool		empty() const
		{
			return (c.empty());
		}

		/**
		 * 	@brief size
		 * 
		 * 	@return The amount of elements holded by %stack
		*/
		size_type	size() const
		{
			return (c.size());
		}

		/**
		 * 	@brief top
		 * 
		 * 	@return A reference to the first element in %stack.
		*/
		reference 	top()
		{
			return (c.back());
		}

		/**
		 * 	@brief top
		 * 
		 * 	@return A const reference to the first element in %stack.
		*/
		const_reference top() const
		{
			return (c.back());
		}

		/**
		 * 	@brief push
		 * 
		 * 	Prappend one element in the top of %stack.
		*/
		void		push(const_reference value)
		{
			c.push_back();
		}


		/**
		 * 	@brief pop
		 * 
		 * 	Removes the element located at the top of %stack.
		*/
		void		pop()
		{
			c.pop_back();
		}
	};

	/**
	 * 	@brief Stack boolen operators
	 * 
	 * 	@tparam T the type holded by @a Container.
	 * 	@tparam The container type holded by %stack.
	 * 	@return The result of the requested boolean operation.
	*/
	template <class T, class Container>
	inline bool 	operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lsh.c == rhs.c);
	}

	template <class T, class Container>
	inline bool 	operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lsh.c != rhs.c);
	}

	template <class T, class Container>
	inline bool 	operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lsh.c < rhs.c);
	}

	template <class T, class Container>
	inline bool 	operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lsh.c <= rhs.c);
	}

	template <class T, class Container>
	inline bool 	operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lsh.c > rhs.c);
	}

	template <class T, class Container>
	inline bool 	operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lsh.c >= rhs.c);
	}
};