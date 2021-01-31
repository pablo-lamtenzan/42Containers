
/** @file queue.hpp
 * 
 * 	Contains the implementation of queue conatiner.
*/

# pragma once

# include <ft_containers.hpp>

namespace FT_NAMESPACE
{
	/**
	 * 	@brief Queue
	 * 
	 * 	@tparam T the type of value holded by the conatiner.
	 * 	@tparam Container the type of value holded by the queue.
	*/
	template <class T, class Container> // TO DO: put deque as dtf
	class queue
	{
		// TO DO: possible implementation here of operator== and operator<

		public:

		public:

		typedef Container									container_type;
		typedef typename container_type::value_type			value_type;
		typedef typename container_type::reference			reference;
		typedef typename container_type::const_reference	const_reference;
		typedef typename container_type::size_type			size_type;

		/* Eqp container */

		protected:

		Container			c;

		public:

		/**
		 * 	@brief Default Constructor
		*/
		explicit queue(const_reference other = container_type()) : c(other) { }

		/**
		 * 	@brief empty
		 * 
		 * 	@return True if %queue is empty.
		*/
		bool		empty() const
		{
			return (c.empty());
		}

		/**
		 * 	@brief size
		 * 
		 * 	@return The amount of elements holded by %queue.
		*/
		size_type	size() const
		{
			return (c.size());
		}

		/**
		 * 	@brief front
		 * 
		 * 	@return A reference to the first element in %queue.
		*/
		reference 	front()
		{
			return (c.front());
		}

		/**
		 * 	@brief front
		 * 
		 * 	@return A const reference to the first element in %queue.
		*/
		const_reference front() const
		{
			return (c.front());
		}

		/**
		 * 	@brief back
		 * 
		 * 	@return A reference to the last element in %queue.
		*/
		reference 	back()
		{
			return (c.back());
		}

		/**
		 * 	@brief back
		 * 
		 * 	@return A const reference to the last element in %queue.
		*/
		const_reference back() const
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
			c.pop_front();
		}
	};

	/**
	 * 	@brief Queue boolen operators
	 * 
	 * 	@tparam T the type holded by @a Container.
	 * 	@tparam The container type holded by %queue.
	 * 	@return The result of the requested boolean operation.
	*/
	template <class T, class Container>
	inline bool 	operator==(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{
		return (lsh.c == rhs.c);
	}

	template <class T, class Container>
	inline bool 	operator!=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{
		return (lsh.c != rhs.c);
	}

	template <class T, class Container>
	inline bool 	operator<(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{
		return (lsh.c < rhs.c);
	}

	template <class T, class Container>
	inline bool 	operator<=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{
		return (lsh.c <= rhs.c);
	}

	template <class T, class Container>
	inline bool 	operator>(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{
		return (lsh.c > rhs.c);
	}

	template <class T, class Container>
	inline bool 	operator>=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{
		return (lsh.c >= rhs.c);
	}
};