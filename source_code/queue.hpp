
/** @file queue.hpp
 * 
 * 	Contains the implementation of queue container.
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
	struct queue
	{
		// TO DO: possible implementation here of operator== and operator<

		/* Member types */

		typedef Container									container_type;
		typedef typename container_type::value_type			value_type;
		typedef typename container_type::reference			reference;
		typedef typename container_type::const_reference	const_reference;
		typedef typename container_type::size_type			size_type;

		/* Member fucntions */

		explicit queue(const_reference other = container_type());

		// TO DO: operator= & swap

		/* Element access */
		reference 		front();
		const_reference	front() const;
		reference 		back();
		const_reference back() const;

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
	queue<T, Container>::queue(const_reference other = container_type())
	: c(other)
	{ }

	////////////////////
	// Element access //
	////////////////////

	/**
	 * 	@brief front
	 * 
	 * 	@return A reference to the first element in %queue.
	*/
	template <class T, class Container>
	typename queue<T, Container>::reference
	queue<T, Container>::front()
	{ return (c.front()); }

	/**
	 * 	@brief front
	 * 
	 * 	@return A const reference to the first element in %queue.
	*/
	template <class T, class Container>
	typename queue<T, Container>::const_reference
	queue<T, Container>::front() const
	{ return (c.front()); }

	/**
	 * 	@brief back
	 * 
	 * 	@return A reference to the last element in %queue.
	*/
	template <class T, class Container>
	typename queue<T, Container>::reference
	queue<T, Container>::back()
	{ return (c.back()); }

	/**
	 * 	@brief back
	 * 
	 * 	@return A const reference to the last element in %queue.
	*/
	template <class T, class Container>
	typename queue<T, Container>::const_reference
	queue<T, Container>::back() const
	{ return (c.back()); }

	//////////////
	// Capacity //
	//////////////

	/**
	 * 	@brief empty
	 * 
	 * 	@return True if %queue is empty.
	*/
	template <class T, class Container>
	bool
	queue<T, Container>::empty() const
	{ return (c.empty()); }

	/**
	 * 	@brief size
	 * 
	 * 	@return The amount of elements holded by %queue.
	*/
	template <class T, class Container>
	typename queue<T, Container>::size_type
	queue<T, Container>::size() const
	{ return (c.size()); }

	///////////////
	// Modifiers //
	///////////////

	/**
	 * 	@brief push
	 * 
	 * 	Prappend one element in the top of %stack.
	*/
	template <class T, class Container>
	void
	queue<T, Container>::push(const_reference value)
	{ c.push_back(); }

	/**
	 * 	@brief pop
	 * 
	 * 	Removes the element located at the top of %stack.
	*/
	template <class T, class Container>
	void
	queue<T, Container>::pop()
	{ c.pop_front(); }

	/////////////////
	// Non members //
	/////////////////

	/**
	 * 	@brief Queue boolen operators
	 * 
	 * 	@tparam T the type holded by @a Container.
	 * 	@tparam The container type holded by %queue.
	 * 	@return The result of the requested boolean operation.
	*/
	template <class T, class Container>
	inline bool
	operator==(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{ return (lsh.c == rhs.c); }

	template <class T, class Container>
	inline bool
	operator!=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{ return (lsh.c != rhs.c); }

	template <class T, class Container>
	inline bool
	operator<(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{ return (lsh.c < rhs.c); }

	template <class T, class Container>
	inline bool
	operator<=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{ return (lsh.c <= rhs.c); }

	template <class T, class Container>
	inline bool
	operator>(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{ return (lsh.c > rhs.c); }

	template <class T, class Container>
	inline bool
	operator>=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{ return (lsh.c >= rhs.c); }
};
