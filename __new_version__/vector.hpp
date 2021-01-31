
/** @file vector.hpp
 * 
 * 	This file contains the vector container implementation.
 * 
 *  TO DO: add a description when is done
*/

# pragma once

# include <ft_allocator.hpp>
# include <ft_iterator.hpp>

namespace FT_NAMESPACE
{
	/**
	 * 	@brief Vector Algorithm
	 * 
	 * 	The vector base class.
	*/
	template <class T, class Alloc>
	struct vector_algorithm
	{
		/* Member types */

		typedef Alloc		allocator_type;
		typedef T*			pointer;
		typedef std::size_t	size_type;

		/* Core */

		pointer				head;
		pointer				tail;
		pointer				storage;
		allocator_type		memory;

		/**
		 * 	@brief Constructors
		*/
		vector_algorithm() { }
		vector_algorithm(const vector_algorithm&) { }
		vector_algorithm(const allocator_type& alloc) : memory(alloc) { }
		vector_algorithm(size_type n) : memory() { alg_reserve(n); }
		vector_algorithm(size_type n, const allocator_type& alloc) : memory(alloc) { alg_reserve(n); }
		template <typename T1, typename Alloc1>
		vector_algorithm const vector_algorithm<T1, Alloc1>&) { }
	
		/**
		 * 	@brief Destructor
		*/
		~vector_algorithm() { alg_deallocate(head, storage - head); }

		/**
		 * 	@brief alg_copy_data
		 * 
		 * 	@param other A %vector_algorithm object. 
		 * 
		 * 	Auxiliar function who perfrom a pointer copy from
		 * 	@c head, @c tail and @c storage.
		*/
		void				alg_copy_data(const vector_algorithm& other)
		{
			head = other.head;
			tail = other.tail;
			storage = other.storage;
		}

		/**
		 * 	@brief alg_swap_data
		 * 
		 * 	@param other A %vector_algorithm object
		 * 
		 * 	Auxiliar function who perfrom a pointer swap from
		 * 	@c head, @c tail and @c storage.
		*/
		void				alg_swap_data(const vector_algorithm& other)
		{
			vector_algorithm	tmp;
			tmp.alg_copy_data(*this);
			alg_copy_data(other);
			other.alg_copy_data(tmp);
		}

		/**
		 * 	@brief alg_allocate
		 * 
		 * 	@param n The size required on the heap.
		 * 
		 * 	@return A pointer to the allocated heap block.
		 * 
		 * 	A fast-use allocator.
		*/
		pointer			alg_allocate(size_type n)
		{
			return (long(n) >= 0 ? allocator_type::allocate(n) : pointer());
		}

		/**
		 * 	@brief alg_deallocate
		 * 
		 * 	@param p A pointer to the target heap memory block.
		 * 	@param n The size to be removed from the heap.
		 * 
		 * 	@return Noting
		 * 
		 * 	A fast-use deallocator.
		*/
		void			alg_deallocate(pointer p, size_type n)
		{
			allocator_type::deallocate(p, n);
		}

		/* Vector inherit only this function */

		protected:

		/**
		 * 	@brief alg_reserve
		 * 
		 * 	@param n The new added storage size.
		 * 
		 * 	@return Noting
		 * 
		 * 	Increment the storage by @a n * sizeof(T) bytes.
		*/
		void			alg_reserve(size_type n)
		{
			head = alg_allocate(n);
			tail = head;
			storage = head + n;
		}
	};

	/**
	 * 	@brief Vector Container
	 * 
	 * 	@tparam T the type of stored values.
	 * 	@tparam Allocator an allocator class
	 * 
	*/
	template <class T, class Allocator = allocator<T>>
	class vector : protected vector_algorithm<T, Allocator>
	{
		/* Member types */

		public:

		typedef vector_algorithm<T, Allocator>			Base;
		typedef T										value_type;
		typedef std::ptrdiff_t							difference_type;
		typedef typename Base::size_type;				size_type;
      	typedef typename Base::allocator_type			allocator_type;
		typedef typename Base::pointer					pointer;
		typedef const value_type*						const_pointer;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef normal_iterator<pointer, vector>		iterator;
		typedef normal_iterator<const_pointer, vector>	const_iterator;
		typedef reverse_iterator<iterator>				reverse_iterator;
		typedef reverse_iterator<const_iterator>		const_reverse_iterator;

		/* Import algorithm core and fast-use allocator/deallocator */

		protected:

		using Base::head;
		using Base::tail;
		using Base::storage;
		using Base::memory;
		using Base::alg_copy_data;
		using Base::alg_swap_data;
		using Base::alg_allocate;
		using Base::alg_deallocate;

		/* Auxiliar functions */

		private:

		/**
		 * 	@brief Vector copy
		 * 
		 * 	@param other A vector.
		 * 	@param n The amount of element to copy.
		 * 	@return Nothing.
		 * 
		 * 	Copy @a n element from other to @c *this.
		 * 	Note: @a n must be <= @c other.capacity() and @c this->capacity().
		*/
		static void	vec_cpy(const vector& other, size_type n)
		{
			for (size_type i = 0 ; i < n ; i++)
				memory.construct(head + i, other.at(i));
		}

		/**
		 * 	@brief Vector set
		 * 
		 * 	@param dest A pointer.
		 * 	@param value A value_type.
		 * 	@param n The amount of set steps.
		 * 
		 * 	Set @a n elements of @a value into @a dest.
		 * 	Note: The elements in @a dest that will be overwriten are destroyed.
		 * 	Note: @a dest + @a n must be <= @c this->capacity().
		 */
		static void vec_set(pointer dest, const_reference value, size_type n)
		{
			for (size_type i = 0 ; i < n ; i++)
			{
				memory.destroy(dest + i);
				memory.constuct(dest + i, value);
			}
		}

		/**
		 * 	@brief Vector clear
		 * 
		 * 	Destructs the elements of @c *this without deallocating @c head.
		*/
		static vec_clear()
		{
			for (; tail != head ; tail--)
				memory.destroy(tail);
		}


		public:

		/**
		 * 	@brief Default Constructor.
		*/
		vector() { }

		/**
		 * 	@brief Allocator Constructor.
		 * 
		 * 	@param alloc An allocator type;
		*/ 
		vector(const allocator_type& alloc = allocator_type()) : Base(alloc) { }

		/**
		 *	@brief Assignation Constructor.
		 *	
		 *	@param n The number of element that will be created.
		 *	@param value The value each element will have.
		 *	@param alloc An allocator.
		 *
		 * Creates a %vector with @p n copies of @p value.
		*/
		explicit vector(size_type n, const_reference = value_type(), const allocator_type& alloc = allocator_type())
		: Base(n, alloc)
		{
			for (size_type i = 0 ; i < n ; i++)
				memory.construct(head + i, value);
		}

		/**
		 * 	@brief Copy constructor
		 * 
		 * 	@param other A vector
		*/
		vector(const vector& other) : Base(other.size()) // Assuming that others allocators haven't to be handled
		{
			vec_cpy(other, other.size());
		}

		/**
		 * 	@brief Range Iterator Constructor
		 * 
		 * 	@tparam An Input Iterator.
		 * 	@param first The first iterator in the range to be copied.
		 * 	@param last The last iterator in the range to be copied.
		 * 	@param alloc An allocator.
		 * 
		 * 	Creates a vector consisting on copies of element in range first-last.
		*/
		template <typename InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
		: Base(size_type(last - first), alloc)
		{
			assign(first, last);
		}

		/**
		 * 	@brief Destuctor
		*/
		~vector()
		{
			vec_clear();
			alg_deallocate(head, storage);
		}

		/**
		 * 	@brief operator=
		 * 
		 * 	@param other a vector.
		 * 
		 * 	Copies all the elements in vector to @c *this. 
		*/
		vector&				operator=(const vector& other)
		{
			vec_clear();
			// TO DO: What happends if head is not allocated ?
			alg_deallocate(head, storage);
			alg_reserve(other.capacity());
			vec_copy(other, other.size());
			alg_copy_data(other);
		}

		// Resize dependency
		void				resize(size_type count, value_type value = value_type());

		/**
		 *	@brief assign
		 *
		 * 	@param count A distance.
		 *  @param value The value that will set.
		 *	@return Nothing.
		 *
		 * 	Set @a value to @c *this in a range of @c value.
		*/
		void				assign(size_type count, const_reference value)
		{
			if (count > storage)
				resize(count, value);
			else
				vec_set(head, value, count);
		}

		// Reserve dependecy
		void				reserve(size_type new_cap);

		/**
		 * 	@brief assign
		 * 	
		 * 	@tparam An input iterator.
		 * 	@param first The first iterator in the range.
		 * 	@param last The last iterator in the range.
		 * 
		 * 	Copies whatever is between @a first and @a last to @c *this.
		*/
		template <typename InputIt>
		void				assign(InputIt first, InputIt last)
		{
			vec_clear();
			if (size_type(last - first) > size_type(storage))
				reserve(size_type(last - first));
			for (size_type i = 0 ; first != last ; i++, first++)
				memory.construct(head + i, *first);
		}

		/**
		 * 	@brief begin
		 * 
		 * 	Return an iterator to the first element in %vector.
		*/
		iterator			begin()
		{
			return (iterator(head));
		}

		/**
		 * 	@brief begin
		 * 
		 * 	Return a const iterator to the first element in %vector.
		*/
		const_iterator		begin() const
		{
			return (const_iterator(head));
		}

		/**
		 * 	@brief end
		 * 
		 * 	Return an iterator to the last element in %vector.
		*/
		iterator			end()
		{
			return (iterator(tail));
		}

		/**
		 * 	@brief end
		 * 
		 * 	Return a const iterator to the last element in %vector.
		*/
		const_iterator		end() const
		{
			return (const_iterator(tail));
		}

		/**
		 * 	@brief rbegin
		 * 
		 * 	Return a reverse iterator to the first element in %vector.
		*/
		reverse_iterator	rbegin()
		{
			return (reverse_iterator(head));
		}

		/**
		 * 	@brief rbegin
		 * 
		 * 	Return a const reverse iterator to the first element in %vector.
		*/
		const_reverse_iterator	rbegin() const
		{
			return (const_reverse_iterator(head));
		}

		/**
		 * 	@brief rend
		 * 
		 * 	Return a reverse iterator to the last element in %vector.
		*/
		reverse_iterator	rend()
		{
			return (reverse_iterator(tail));
		}

		/**
		 * 	@brief end
		 * 
		 * 	Return a const reverse iterator to the last element into %vector.
		*/
		const_reverse_iterator	rend() const
		{
			return (const_reverse_iterator(tail));
		}

		/**
		 * 	@brief clear
		 * 
		 * 	Destroys all the elements that %vector hold.
		*/
		void					clear()
		{
			vec_clear();
		}

		/**
		 * 	@brief size
		 * 
		 * 	@return The number of elements in %vector.
		*/
		size_type				size() const
		{
			return (size_type(tail - head));
		}

		/**
		 * 	@brief max_size
		 * 
		 * 	@return The largest amount of T elements that %vector supports.
		*/
		size_type				max_size() const
		{
			return (size_type(std::numeric_limits<size_type>::max() / sizeof(value_type)));
		}

		/**
		 * 	@brief resize
		 * 
		 * 	Change the capacity of %vector.
		 * 	Note: the elements between @c tail and @c storage are uninitialised.
		*/
		void					resize(size_type new_cap)
		{
x			try {
				pointer tmp = alg_allocate(new_cap);
			}
			catch (std::bad_alloc& e) {
				clear();
				vec_deallocate(head);
				std::cerr << e.what() << std::endl;
				throw;
			}
			const value_type s = new_cap < size() ? new_cap : size();
			vec_cpy(tmp, *this, const_cast<value_type>(s));
			vec_clear();
			vec_deallocate(head);
			head = tmp;
			tail = pointer(head + s);
			storage = pointer(head + new_cap);
		}

		// Capacity dependecy
		size_type			capacity() const;

		/**
		 * 	@brief resize
		 * 
		 * 	Change the capacity of %vector.
		 *	Note: the elements between @c tail and @c storage are initialised to @a value.
		*/
		void				resize(size_type new_cap, const_reference value)
		{
			const size_type c = capacity();
			resize(new_cap);
			if (new_cap > c)
				vec_set(tail, value, size_type(pointer - tail));
		}

		/**
		 * 	@brief capacity
		 * 
		 * 	@return The maximun number of element that %vector can hold.
		*/
		size_type			capacity() const
		{
			return (size_type(storage - head));
		}

		/**
		 * 	@brief empty
		 * 
		 * 	@return True of the vector is empty.
		*/
		bool				empty() const
		{
			return (begin() == end());
		}

		/**
		 * 	@brief operator[]
		 * 
		 * 	@param n The index of the element that will be returned.
		 *	@return A reference to the data at @a n index.
		*/
		reference			operator[](size_type n)
		{
			return (*pointer(head + n));
		}

		/**
		 * 	@brief operator[]
		 * 
		 * 	@param n The index of the element that will be returned.
		 *	@return A const reference to the data at @a n index.
		*/
		const_reference		operator[](size_type n) const
		{
			return (*pointer(head + n));
		}

		/**
		 * 	@brief at
		 * 
		 * 	@param n The index of the element that will be returned.
		 *	@return A reference to the data at @a n index.
		 *
		 * 	@throw std::out_of_range if @c n > @c this->size().
		*/
		reference			at(size_type n)
		{
			// TO DO: out of range
			if (n > size())
				throw std::out_of_range(std::string("TO DO"));
			return ((*this)[n]);
		}

		/**
		 * 	@brief at
		 * 
		 * 	@param n The index of the element that will be returned.
		 *	@return A const reference to the data at @a n index.
		 *
		 * 	@throw std::out_of_range if @c n > @c this->size().
		*/
		const_reference		at(size_type n) const
		{
			// TO DO: out of range
			if (n > size())
				throw std::out_of_range(std::string("TO DO"));
			return ((*this)[n]);
		}

		/**
		 * 	@brief front
		 * 
		 * 	@return A reference to the first element in %vector.
		 */
		reference			front()
		{
			return (*begin());
		}

		/**
		 * 	@brief front
		 * 
		 * 	@return A const reference to the first element in %vector.
		 */
		const_reference		front() const
		{
			return (*begin());
		}

		/**
		 * 	@brief back
		 * 
		 * 	@return A reference to the first element in %vector.
		 */
		reference			back()
		{
			return (*end());
		}

		/**
		 * 	@brief back
		 * 
		 * 	@return A const reference to the first element in %vector.
		 */
		const_reference		back() const
		{
			return (*end());
		}

		/**
		 * 	@brief data
		 * 
		 * 	@return a pointer such @c this->data() + @c this->size() is a valid range.
		*/
		pointer				data()
		{
			// TO DO: Check what happens if %vector is empty
			return (&front();)
		}

		/**
		 * 	@brief data
		 * 
		 * 	@return a const pointer such @c this->data() + @c this->size() is a valid range.
		*/
		const_pointer		data() const
		{
			// TO DO: Check what happens if %vector is empty
			return (&front();)
		}

		/**
		 * 	@brief push back
		 * 
		 * 	@param x The data to be appended.
		 * 
		 * 	Append @c x to underliying work array @c head at index @c tail + 1.
		*/
		void				push_back(const_reference x)
		{
			if (size_type(++tail) > capacity())
				resize(size_type(capacity() * 2));
			memory.construct(tail, x);
		}

		/**
		 * 	@brief pop back
		 * 
		 * 	Removes the last element of the underliying work array @c head at index @c tail.
		*/
		void				pop_back()
		{
			if (!empty())
				memory.destroy(tail--);
		}

		// Insert dependecy
		void				insert(const_iterator pos, value_type amount, const_reference value)

		/**
		 * 	@brief insert
		 * 
		 * 	@param index A const interator into %vector.
		 * 	@param value The iserted value.
		 * 	@return An iterator to the inserted data.
		 * 
		 * 	Insert @c value at @c index (before the current element that is holds at @c index before the call)
		*/
		iterator			insert(const_iterator pos, const_reference value)
		{
			insert(pos, size_type(1), value);
			return (iterator((*this)[pos]));
		}

		/**
		 * @brief insert
		 * 
		 * 	@param pos A const iterator into %vector.
		 * 	@param amount The total copies of @a value that will be inserted at @a index.
		 * 	@param value A copy of it will be inserted @a amount times.
		*/
		void				insert(const_iterator pos, value_type amount, const_reference value)
		{
			// TO DO: (if i dont have it, i need an operator+ from normal iterator that return a size_type)


			// Handle space
			if (size_type(size() + amount) > capacity())
				resize(size_type(capacity() * 2));
			// Shift elements in range tail-(*this)[pos] by amount
			iterator insertion_index = iterator((*this)[pos]);
			for (iterator i = end() ; i != insertion_index ; i--)
				(*this)[i + amount] = (*this)[i];
			// Insert amount copies of value
			for (size_type i = 0 ; i < amount ; i++)
				memory.construct(&(*this)[pos + i], value);
			tail += amount;
		}

		/**
		 * 	@brief insert
		 * 	
		 * 	@tparam InputIt an input iterator
		 * 	@param pos A const iterator into %vector
		 * 	@param first An input iterator
		 * 	@param last An input interator
		 * 	@return An iterator to the inserted data.
		 * 
		 * 	Insert the values in range @a first - @a last at the index @a pos.
		*/
		template <typename InputIt>
		iterator			insert(const_iterator pos, InputIt first, Inputit last)
		{
			// Handle space
			const size_type amount = distance(first, last);
			if (size_type(size() + amount) > capacity())
				resize(size_type(capacity() * 2));
			// Shift elements in range tail-(*this)[pos] by amount
			iterator insertion_index = iterator((*this)[pos]);
			for (iterator i = end() ; i != insertion_index ; i--)
				(*this)[i + amount] = (*this)[i];
			// Insert amount copies of value
			for (size_type i = 0 ; i < amount ; i++)
				memory.construct(&(*this)[pos + i], *(first++));
			tail += amount;
		}

		// Erase dependecy
		iterator			erase(iterator first, iterator last)

		/**
		 * 	@brief erase
		 * 
		 * 	@param pos The target iterator.
		 * 	@return An iterator pointing to the next element.
		 * 
		 * 	Remove an element at the index @a pos.
		*/
		iterator			erase(iterator pos)
		{
			return (erase(pos, pos + 1));
		}

		/**
		 * 	@brief erase
		 * 
		 * 	@param first An iterator that is the first iterator in erase range.
		 * 	@param last An iterator that is the last iterator in erase range.
		 * 	@return An iterator pointing to the iserted data.
		*/
		iterator		erase(iterator first, iterator last)
		{
			// Calc the indexes
			const size_type amount = distance(first, last);
			const size_type pos = distance(begin(), first)
			iterator deletion_index = iterator((*this)[pos + amount]);
			// Proceed to shift backwards by amount and destroy while overwriting the old element
			for (size_type i = 0 ; i < amount ; i++)
			{
				memory.destroy(&(*this)[pos + i]);
				(*this)[pos + i] = (*this)[pos + i + amount];
			}
			// Shift backward witout destroying the remaining elements
			for (size_type i = pos + amount ; i < size() ; i++)
				(*this)[i] = (*this)[i + amount];
			tail -= amount;
		}

		/**
		 * 	@brief swap
		 * 
		 *	@param other A %vector.
		 *
		 * 	Swap the underlying work data of @c *this and @a other.
		*/
		void			swap(const vector& other)
		{
			alg_swap_data(other);
		}
	};

	//@{
	/** @brief Boolean operators
	 * 
	 * 	@param lhs A %vector.
	 * 	@param rhs A %vector of the same type of @a lhs.
	 * 
	 * 	@return A boolean that is the result of the requested boolean operation.
	*/
	template <class T, class Allocator>
	inline bool		operator==(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		// TO DO: Is it worth it to implement std::equal ? 
		return (lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Allocator>
	inline bool		operator!=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Allocator>
	inline bool		operator<(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())));
	}

	template <class T, class Allocator>
	inline bool		operator<=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return (!(rhs < lhs))
	}

	template <class T, class Allocator>
	inline bool		operator>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Allocator>
	inline bool		operator>=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return (!(lhs < rhs));
	}
	//@}

	/**
	 * 	@brief swap
	 * 
	 * 	A non member swap spacialisation, built to swap %vectors.
	*/
	template <class T, class Allocator>
	inline void swap(vector<T, Allocator>& lhs, vector<T, Allocator>& rhs)
	{
		lhs.swap(rhs);
	}
};

