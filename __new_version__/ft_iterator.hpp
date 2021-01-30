
/** @file ft_iterator.hpp
 * 
 * 	This file contains the implementation of reverse_iterator.
*/

// TO DO: Complete the previous coment later
// TO DO: std__addressof stack and queue iterators

# pragma once

# include <ft_iterator_base_funct.hpp>

namespace FT_NAMESPACE
{
	/**
   	 *  Bidirectional and random access iterators have corresponding reverse
   	 *  %iterator adaptors that iterate through the data structure in the
   	 *  opposite direction.  They have the same signatures as the corresponding
   	 *  iterators.  The fundamental relation between a reverse %iterator and its
   	 *  corresponding %iterator @c i is established by the identity:
   	 *  @code
   	 *      &*(reverse_iterator(i)) == &*(i - 1)
   	 *  @endcode
   	 *
   	 *  <em>This mapping is dictated by the fact that while there is always a
   	 *  pointer past the end of an array, there might not be a valid pointer
   	 *  before the beginning of an array.</em>
   	 *
   	 *  Reverse iterators can be tricky and surprising at first.  Their
   	 *  semantics make sense, however, and the trickiness is a side effect of
   	 *  the requirement that the iterators must be safe.
  	*/
  	template <typename Iterator>
	class reverse_iterator : public iterator<
			typename iterator_traits<Iterator>::iterator_category,
			typename iterator_traits<Iterator>::value_type,
			typename iterator_traits<Iterator>::difference_type,
			typename iterator_traits<Iterator>::pointer,
            typename iterator_traits<Iterator>::reference>
	{
		/**
		 * 	@brief Convert to pointer
		 * 	
		 * 	Auxliar function used to convert to pointer.
		*/
		template <typename T>
		static T*		convert_to_pointer(T* p) { return (p); }
		
		template <typename T>
		static pointer	convert_to_pointer(T p) { return (p.operator->()); }

		public:

		typedef Iterator						iterator_type;

		protected:

		typedef iterator_traits<iterator_type>	traits_type;

		iterator_type							it;

		public:

		typedef	typename traits_type::difference_type	difference_type;
		typedef typename traits_type::pointer			pointer;
		typedef typename traits_type::reference			reference;

		/**
		 * @brief Default constructor
		 */
		reverse_iterator() : it() { }

		/**
		 * 	@brief Constructor
		 * 
		 * This object %iterator will move to the oposite dirrection that @p x does.
		*/
		explicit reverse_iterator(iterator_type x) : it(x) { }

		/**
		 * 	@brief Copy constructor
		*/
		reverse_iterator(const reverse_iterator& other) : it(other.it) { }

		/**
		 * 	@brief Copy constructor
		 * 
		 * Converts from other types.
		*/
		template <typename Iter>
		reverse_iterator(const reverse_iterator<Iter>& other) : it(other.base()) { }

		/**
		 * 	@brief Base
		 * 
		 * 	@return @c it, the %iterator used for underlying work.
		*/
		iterator_type		base() const
		{
			return (it);
		}

		/**
		 * 	@brief operator*
		 * 
		 * 	@return If the underlying work iterator @c it
		 * 	is deferenceable a reference to @c --it.
		*/
		reference			operator*() const
		{
			iterator_type tmp = it;
			return (*--tmp);
		}

		/**
		 * 	@brief operator->
		 * 
		 * 	@return If the underlying work iterator @c it
		 * 	is deferenceable a pointer to the value at @c --it.
		*/
		pointer				operator->() const
		{
			iterator_type tmp = it;
			return (convert_to_pointer(--tmp));
		}

		/**
		 * 	@brief operator++
		 * 
		 * 	@return @c *this
		 * 
		 * 	Pre-Decrements the underlying work iterator @c it.
		*/
		reverse_iterator&	operator++()
		{
			it--;
			return (*this);
		}

		/**
		 * 	@brief operator++
		 * 
		 * 	@return @c *this
		 * 
		 * 	Post-Decrements the underlying work iterator @c it.
		*/
		reverse_iterator&	operator++(int)
		{
			reverse_iterator tmp = *this;
			operator++();
			return (tmp);
		}

		/**
		 * 	@brief operator--
		 * 
		 * 	@return @c *this
		 * 
		 * 	Pre-Increments the underlying work iterator @c it.
		*/
		reverse_iterator&	operator--()
		{
			it++;
			return (*this);
		}

		/**
		 * 	@brief operator--
		 * 
		 * 	@return @c *this
		 * 
		 * Post-Increments the underlying work iterator @c it.
		*/
		reverse_iterator&	operator--(int)
		{
			reverse_iterator tmp = *this;
			operator--();
			return (tmp);
		}

		/**
		 * 	@brief operator+
		 * 
		 * 	@return A reverse iterator that refrers to @c it - @a n
		 * 
		 * 	Note: Must be a Random Acess Iterator.
		 */
		reverse_iterator	operator+(difference_type n) const
		{
			return (it - n);
		}

		/**
		 * 	@brief operator+=
		 * 
		 * 	@return @c *this
		 * 
		 * 	Moves the inderlying iterator backwards @a n steps.
		 * 	Note: Must be a Random Acess Iterator.
		 */
		reverse_iterator&	operator+=(difference_type n)
		{
			it -= n;
			return (*this);
		}

		/**
		 * 	@brief operator-
		 * 
		 * 	@return A reverse iterator that refrers to @c it + @a n
		 * 
		 * 	Note: Must be a Random Acess Iterator.
		 */
		reverse_iterator	operator-(difference_type n) const
		{
			return (it + n);
		}

		/**
		 *	@brief operator-=
		 * 
		 * 	@return @c *this
		 * 
		 * 	Moves the inderlying iterator forwards @a n steps.
		 * 	Note: Must be a Random Acess Iterator.
		 */
		reverse_iterator&	operator-=(difference_type n)
		{
			it += n;
			return (*this);
		}

		/**
		 * 	@brief operator[]
		 * 
		 * 	@return the value located at @c it - @a n - 1.
		*/
		reference			operator[](difference_type n) const
		{
			return (*(*this + n));
		}
	};

	//@{
	/**
	 * 	@param lhs A %reverse_iterator.
	 *	@param rhs A %reverse_iterator.
	 *	
	 *	@return The result of the boolean operation between both.
	*/
	template <typename Iterator>
	inline bool		operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename Iterator>
	inline bool		operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename Iterator>
	inline bool		operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename Iterator>
	inline bool		operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename Iterator>
	inline bool		operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename Iterator>
	inline bool		operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	/* Const_reverse operator Vs reverse_operator */

	template <typename Iterator1, typename Iterator2>
	inline bool		operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	inline bool		operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	inline bool		operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	inline bool		operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	inline bool		operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	inline bool		operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	//@}

	/**
	 * 	@brief operator-
	 * 	
	 * 	@return the distance between both iterators
	 * 
	 * 	Note: Is espected that @a lhs and @a rhs can have or not the const identifier
	*/
	template <typename Iterator>
	inline typename reverse_iterator<Iterator>::difference_type
	operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	inline typename reverse_iterator<Iterator1>::difference_type
	operator-(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (rhs.base() - lhs.base());
	}

	/**
	 * 	@brief operator+
	 * 	
	 * 	@return A %reverse_iterator result of the incrementation of @a target by @a n.
	*/
	template <typename Iterator>
	inline typename reverse_iterator<Iterator>::difference_type
	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& target)
	{
		return (reverse_iterator(target.base() - n));
	}

	/**
	 * 	@brief Back Insert Iterator
	 * 
	 * 	These are outputs iterators, they are constructed from a T-type-Container.
	*/
	template <class Container>
	class back_insert_iterator : public iterator<output_iterator_tag, void, void, void, void>
	{
		public:

		typedef Container		container_type;

		protected:

		container_type*			container;

		public:

		/**
		 * 	@brief Constructor
		 * 
		 * 	Can only be constructed using a conatiner
		*/
		explicit back_insert_iterator(container_type& c) : container(std::__adressof(c)) { }
		// TO DO: std::__adressof(c)

		/**
		 * 	@brief operator=
		 * 
		 * 	@return @c *this.
		*/
		back_insert_iterator&	operator=(typename container_type::const_reference value)
		{
			container->push_back(value);
			return (*this);
		}

		/**
		 * 	@brief operator++, operator*
		 * 
		 * 	@return @c *this.
		 * 
		 * No operation is performed.
		*/
		back_insert_iterator&	operator*() { return (*this); }
		back_insert_iterator&	operator++() { return (*this); }
		back_insert_iterator	operator++(int) { return (*this); }
	};

	/**
	 * 	@brief Front Insert Iterator
	 * 
	 * 	These are outputs iterators, they are constructed from a T-type-Container.
	*/
	template <class Container>
	class front_insert_iterator : public iterator<output_iterator_tag, void, void, void, void>
	{
		public:

		typedef Container		container_type;

		protected:

		container_type*			container;

		public:

		/**
		 * 	@brief Constructor
		 * 
		 * 	Can only be constructed using a conatiner
		*/
		explicit front_insert_iterator(container_type& c) : container(std::__adressof(c)) { }
		// TO DO: std::__adressof(c)

		/**
		 * 	@brief operator=
		 * 
		 * 	@return @c *this.
		*/
		front_insert_iterator&	operator=(typename container_type::const_reference value)
		{
			container->push_front(value);
			return (*this);
		}

		/**
		 * 	@brief operator++, operator*
		 * 
		 * 	@return @c *this.
		 * 
		 * No operation is performed.
		*/
		front_insert_iterator&	operator*() { return (*this); }
		front_insert_iterator&	operator++() { return (*this); }
		front_insert_iterator	operator++(int) { return (*this); }
	};

	
};