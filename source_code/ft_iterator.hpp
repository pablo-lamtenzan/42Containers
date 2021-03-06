
/** @file ft_iterator.hpp
 * 
 * 	This file contains the implementation of reverse_iterator,
 * 	inserters and normal_iterator.
*/

// TO DO: std__addressof inserter classes (std::_addressod retuen __builtin_addressof() in move.h)


# pragma once

# include "ft_iterator_base_funct.hpp"
# include "ft_type_traits.hpp"

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
		protected:

		typedef iterator_traits<Iterator>				traits_type;
	
		public:

		typedef Iterator								iterator_type;
		typedef	typename traits_type::difference_type	difference_type;
		typedef typename traits_type::pointer			pointer;
		typedef typename traits_type::reference			reference;

		private:
	
		/**
		 * 	@brief Convert to pointer
		 * 	
		 * 	Auxliar function used to convert to pointer.
		*/
		template <typename T>
		static T*		convert_to_pointer(T* p) { return (p); }
		
		template <typename T>
		static pointer	convert_to_pointer(T p) { return (p.operator->()); }

		protected:

		iterator_type							it;

		public:

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
		return (reverse_iterator<Iterator>(target.base() - n));
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
		explicit back_insert_iterator(container_type& c) : container(std::addressof(c)) { }
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
		 *	No operation is performed.
		*/
		back_insert_iterator&	operator*() { return (*this); }
		back_insert_iterator&	operator++() { return (*this); }
		back_insert_iterator&	operator++(int) { return (*this); }
	};

	/**
	 * 	@brief Back inserter
	 * 
	 * 	@param c A container of T type
	 * 
	 * 	Easier way to use back_insert_iterator.
	*/
	template <typename Container>
	inline back_insert_iterator<Container>		back_inserter(Container& c)
	{
		return (back_insert_iterator<Container>(c));
	}

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
		 * 	Can only be constructed using a container
		*/
		explicit front_insert_iterator(container_type& c) : container(std::addressof(c)) { }
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
		 *	No operation is performed.
		*/
		front_insert_iterator&	operator*() { return (*this); }
		front_insert_iterator&	operator++() { return (*this); }
		front_insert_iterator&	operator++(int) { return (*this); }
	};

	/**
	 * 	@brief Front inserter
	 * 
	 * 	@param c A container of T type
	 * 
	 * 	Easier way to use front_insert_iterator.
	*/
	template <typename Container>
	inline front_insert_iterator<Container>		front_inserter(Container& c)
	{
		return (front_insert_iterator<Container>(c));
	}

	/**
	 * 	@brief Insert Iterator
	 * 
	 * 	These are outputs iterators, they are constructed from a T-type-Container.
	 * 
	 * 	Assigning a T to the  iterator inserts it in the container at &iterator position,
	 * 	eather than overwriting the value at that location.
	*/
	template <typename Container>
	class insert_iterator : public iterator<output_iterator_tag, void, void, void, void>
	{
		public:

		typedef Container 							container_type;

		private:

		typedef typename container_type::iterator	Iter;

		protected:

		container_type*		container;
		Iter				iter;

		public:

		/**
		 * 	@brief Constructor
		 * 
		 * 	Only constructable using a container and an index iterator.
		*/
		insert_iterator(container_type& c, Iter index) : container(std::addressof(c)), iter(index) { }
		// TO DO: std::__addressof

		/**
		 * 	@brief operator=
		 * 
		 * 	@return An %insert_iterator
		 * 
		 * 	Perform an insertion at the index given in the constructor,
		 * 	instead of overwriting it.
		 * 
		 * 	Example:
		 * 	@code
		 * 		vector<int> v = { A, Z};
		 * 		insert_iterator it(v, ++v.begin());
		 * 		it = 1;
		 *		it = 2;
		 *		it = 3;
		 *		// Vector now contains { A, 1, 2, 3, Z }
		 *	@endcode
		 */
		insert_iterator&	operator=(typename container_type::const_reference c)
		{
			iter = container->insert(iter, c);
			iter++;
			return (*this);
		}

		/**
		 * 	@brief operator++, operator*
		 * 
		 * 	@return @c *this.
		 * 
		 *	No operation is performed.
		*/
		insert_iterator&	operator*() { return (*this); }
		insert_iterator&	operator++() { return (*this); }
		insert_iterator&	operator++(int) { return (*this); }
	};

	/**
	 * 	@brief inserter
	 * 
	 * 	@param c A container of T type.
	 * 	@param index A interator into the container.
	 * 
	 * 	Easier way to use insert_iterator.
	*/
	template <typename Container, typename Iterator>
	inline insert_iterator<Container>	inserter(Container& c, Iterator index)
	{
		return (insert_iterator<Container>(c, typename Container::iterator(index)));
	}
};