
/** @file vector.hpp
 * 
 * 	This file contains the vector container implementation.
 * 
 *  TO DO: add a description when is done
*/

// TO DO: std::equal
// Types stuff that i saw in correction
// Resise commented
// Range erase return
// Resize set at the end
// Insert signature (multiple signatures modified)
// Range insert operator[] and signature
// operator == and <



# pragma once

# include "ft_allocator.hpp"
# include "ft_iterator.hpp"

# include <limits>

namespace FT_NAMESPACE
{
	////////////////
	// Base class //
	////////////////

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

		/* Member functions */

		/* Constructors */
		vector_algorithm();
		vector_algorithm(const vector_algorithm&);
		vector_algorithm(const allocator_type& alloc);
		vector_algorithm(size_type n);
		vector_algorithm(size_type n, const allocator_type& alloc);
		template <typename T1, typename Alloc1>
		vector_algorithm(const vector_algorithm<T1, Alloc1>&);

		/* Destructor */
		~vector_algorithm();

		/* Fast type basic operations */
		inline void			alg_copy_data(const vector_algorithm& other);
		inline void			alg_swap_data(vector_algorithm& other);
		inline pointer		alg_allocate(size_type n);
		inline void			alg_deallocate(pointer p);

		protected:

		inline void			alg_reserve(size_type n);
	};

	//@{
	/**
	 * 	@brief Constructors
	 * 
	 * 	Construct a %vector_algorithm object.
	 * 	Used to hold vector member and also has
	 * 	basic operations functions.
	*/
	template <class T, class Alloc>
	vector_algorithm<T, Alloc>::vector_algorithm()
	{ }

	template <class T, class Alloc>
	vector_algorithm<T, Alloc>::vector_algorithm(const vector_algorithm&)
	{ }

	template <class T, class Alloc>
	vector_algorithm<T, Alloc>::vector_algorithm(const allocator_type& alloc)
	: memory(alloc)
	{ }

	template <class T, class Alloc>
	vector_algorithm<T, Alloc>::vector_algorithm(size_type n)
	: memory()
	{ alg_reserve(n); }

	template <class T, class Alloc>
	vector_algorithm<T, Alloc>::vector_algorithm(size_type n, const allocator_type& alloc)
	: memory(alloc)
	{ alg_reserve(n); }

	template <class T, class Alloc>
	template <typename T1, typename Alloc1>
	vector_algorithm<T, Alloc>::vector_algorithm(const vector_algorithm<T1, Alloc1>&)
	{ }
	//@}

	/**
	 * 	@brief Destructor
	 * 
	 * 	Destroy a %vector_algorithm object and
	 * 	frees it allocated ressources.
	*/
	template <class T, class Alloc>
	vector_algorithm<T, Alloc>::~vector_algorithm()
	{ alg_deallocate(head); }

	/**
	 * 	@brief alg_copy_data
	 * 
	 * 	@param other A %vector_algorithm object. 
	 * 
	 * 	Auxiliar function who perfrom a pointer copy from
	 * 	@c head, @c tail and @c storage.
	*/
	template <class T, class Alloc>
	void
	vector_algorithm<T, Alloc>::alg_copy_data(const vector_algorithm& other)
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
	template <class T, class Alloc>
	void
	vector_algorithm<T, Alloc>::alg_swap_data(vector_algorithm& other)
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
	template <class T, class Alloc>
	typename vector_algorithm<T, Alloc>::pointer
	vector_algorithm<T, Alloc>::alg_allocate(size_type n)
	{ return (long(n) >= 0 ? memory.allocate(n) : pointer()); }

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
	template <class T, class Alloc>
	void
	vector_algorithm<T, Alloc>::alg_deallocate(pointer p)
	{ memory.deallocate(p); }

	/**
	 * 	@brief alg_reserve
	 * 
	 * 	@param n The new added storage size.
	 * 
	 * 	@return Noting
	 * 
	 * 	Increment the storage by @a n * sizeof(T) bytes.
	*/
	template <class T, class Alloc>
	inline void vector_algorithm<T, Alloc>::alg_reserve(size_type n)
	{
		head = alg_allocate(n);
		tail = head;
		storage = head + n;
	}

	//////////////////
	// Vector class //
	//////////////////

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
		typedef typename Base::size_type				size_type;
      	typedef typename Base::allocator_type			allocator_type;
		typedef typename Base::pointer					pointer;
		typedef const value_type*						const_pointer;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef normal_iterator<pointer, vector>		iterator;
		typedef normal_iterator<const_pointer, vector>	const_iterator;
		typedef reverse_iterator<const_iterator>		const_reverse_iterator;
		typedef reverse_iterator<iterator>				reverse_iterator;
		
		/* Fast type base members */

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

		inline void		vec_cpy(const vector& other, size_type n);
		inline void		vec_array_copy(pointer dest, const_pointer src, size_type n);
		inline void		vec_set(pointer dest, const_reference value, size_type n);
		inline void		vec_clear();

		/* Member functions */

		public:

		vector(const allocator_type& alloc = allocator_type());
		explicit vector(size_type n, const_reference value = value_type(),
		const allocator_type& alloc = allocator_type());
		template <typename InputIterator>
		vector(InputIterator first, InputIterator last,
		const allocator_type& alloc = allocator_type());
		vector(const vector& other);
		~vector();
		vector&			operator=(const vector& other);
		void			assign(size_type count, const_reference value);
		template <typename InputIt>
		void			assign(InputIt first, InputIt last);

		/* Element access */
		reference				operator[](size_type n);
		const_reference			operator[](size_type n) const;
		reference				at(size_type n);
		const_reference			at(size_type n) const;
		reference				front();
		const_reference			front() const;
		reference				back();
		const_reference			back() const;
		pointer					data();
		const_pointer			data() const;

		/* Iterators */
		iterator				begin();
		const_iterator			begin() const;
		iterator				end();
		const_iterator			end() const;
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;

		/* Capacity */
		bool					empty() const;
		size_type				size() const;
		size_type				max_size() const;
		void					reserve(size_type new_cap);
		size_type				capacity() const;
		
		/* Modifiers */
		void					clear();
		void					insert(/*const_*/iterator pos, size_type amount, const_reference value);	
		iterator				insert(const_iterator pos, const_reference value);
		template <typename InputIt>
		iterator				insert(/*const_*/iterator pos, InputIt first, InputIt last);
		iterator				erase(iterator first, iterator last);
		iterator				erase(iterator pos);
		void					push_back(const_reference x);
		void					pop_back();
		void					resize(size_type new_cap, const_reference value = value_type());
		void					swap(vector& other);
	};

	////////////////////////
	// Auxiliar functions //
	////////////////////////

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
	template <class T, class Allocator>
	void
	vector<T, Allocator>::vec_cpy(const vector& other, size_type n)
	{
		for (size_type i = 0 ; i < n ; i++)
			memory.construct(head + i, other.at(i));
	}

	/**
	 * 	@brief Array copy
	 * 
	 * 	@param dest The destination array of elements of an arbitrary type.
	 * 	@param src The source array.
	 * 	@param n The amount of elements to be copied.
	 * 
	 * 	Copies @p n elements from @p src to @p dest.
	*/
	template <class T, class Allocator>
	void
	vector<T, Allocator>::vec_array_copy(pointer dest, const_pointer src, size_type n)
	{
		for (size_type i = 0 ; i < n ; i++)
			dest[i] = src[i];
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
	template <class T, class Allocator>
	void
	vector<T, Allocator>::vec_set(pointer dest, const_reference value, size_type n)
	{
		for (size_type i = 0 ; i < n ; i++)
		{
			memory.destroy(dest + i);
			memory.construct(dest + i, value);
		}
	}

	/**
	 * 	@brief Vector clear
	 * 
	 * 	Destructs the elements of @c *this without deallocating @c head.
	*/
	template <class T, class Allocator>
	void
	vector<T, Allocator>::vec_clear()
	{
		for (; tail != head ; tail--)
			memory.destroy(tail);
	}

	//////////////////////
	// Member functions //
	//////////////////////

	/**
	 * 	@brief Allocator Constructor.
	 * 
	 * 	@param alloc An allocator type;
	*/ 
	template <class T, class Allocator>
	vector<T, Allocator>::vector(const allocator_type& alloc)
	: Base(alloc)
	{ }

	/**
	 *	@brief Assignation Constructor.
	 *	
	 *	@param n The number of element that will be created.
	 *	@param value The value each element will have.
	 *	@param alloc An allocator.
	 *
	 * Creates a %vector with @p n copies of @p value.
	*/
	template <class T, class Allocator>
	vector<T, Allocator>::vector(size_type n, const_reference value, const allocator_type& alloc)
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
	template <class T, class Allocator>
	vector<T, Allocator>::vector(const vector& other)
	: Base(other.size()) // Assuming that others allocators haven't to be handled
	{ vec_cpy(other, other.size()); }

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
	template <class T, class Allocator>
	template <typename InputIterator>
	vector<T, Allocator>::vector(InputIterator first, InputIterator last, const allocator_type& alloc)
	: Base(size_type(last - first), alloc)
	{ assign(first, last); }

	/**
	 * 	@brief Destuctor
	*/
	template <class T, class Allocator>
	vector<T, Allocator>::~vector()
	{
		vec_clear();
		alg_deallocate(head);
	}

	/**
	 * 	@brief operator=
	 * 
	 * 	@param other a vector.
	 * 
	 * 	Copies all the elements in vector to @c *this. 
	*/
	template <class T, class Allocator>
	vector<T, Allocator>&
	vector<T, Allocator>::operator=(const vector& other)
	{
		vec_clear();
		// TO DO: What happends if head is not allocated ?
		alg_deallocate(head, storage);
		alg_reserve(other.capacity());
		vec_copy(other, other.size());
		alg_copy_data(other);
	}

	/**
	 *	@brief assign
	 *
	 * 	@param count A distance.
	 *  @param value The value that will set.
	 *	@return Nothing.
	 *
	 * 	Set @a value to @c *this in a range of @c value.
	*/
	template <class T, class Allocator>
	void
	vector<T, Allocator>::assign(size_type count, const_reference value)
	{
		if (count > size_type(storage - head))
			resize(count, value);
		else
			vec_set(head, value, count);
	}

	/**
	 * 	@brief assign
	 * 	
	 * 	@tparam An input iterator.
	 * 	@param first The first iterator in the range.
	 * 	@param last The last iterator in the range.
	 * 
	 * 	Copies whatever is between @a first and @a last to @c *this.
	*/
	template <class T, class Allocator>
	template <typename InputIt>
	void
	vector<T, Allocator>::assign(InputIt first, InputIt last)
	{
		vec_clear();
		if (size_type(last - first) > size_type(storage))
			reserve(size_type(last - first));
		for (size_type i = 0 ; first != last ; i++, first++)
			memory.construct(head + i, *first);
	}

	////////////////////
	// Element Access //
	////////////////////

	/**
	 * 	@brief operator[]
	 * 
	 * 	@param n The index of the element that will be returned.
	 *	@return A reference to the data at @a n index.
	*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::reference
	vector<T, Allocator>::operator[](size_type n)
	{ return (*(head + n)); }

	/**
	 * 	@brief operator[]
	 * 
	 * 	@param n The index of the element that will be returned.
	 *	@return A const reference to the data at @a n index.
	*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::const_reference
	vector<T, Allocator>::operator[](size_type n) const
	{ return (*(head + n)); }

	/**
	 * 	@brief at
	 * 
	 * 	@param n The index of the element that will be returned.
	 *	@return A reference to the data at @a n index.
	 *
	 * 	@throw std::out_of_range if @c n > @c this->size().
	*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::reference
	vector<T, Allocator>::at(size_type n)
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
	template <class T, class Allocator>
	typename vector<T, Allocator>::const_reference
	vector<T, Allocator>::at(size_type n) const
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
	template <class T, class Allocator>
	typename vector<T, Allocator>::reference
	vector<T, Allocator>::front()
	{ return (*begin()); }

	/**
	 * 	@brief front
	 * 
	 * 	@return A const reference to the first element in %vector.
	 */
	template <class T, class Allocator>
	typename vector<T, Allocator>::const_reference
	vector<T, Allocator>::front() const
	{ return (*begin()); }

	/**
	 * 	@brief back
	 * 
	 * 	@return A reference to the first element in %vector.
	 */
	template <class T, class Allocator>
	typename vector<T, Allocator>::reference
	vector<T, Allocator>::back()
	{ return (*end()); }

	/**
	 * 	@brief back
	 * 
	 * 	@return A const reference to the first element in %vector.
	 */
	template <class T, class Allocator>
	typename vector<T, Allocator>::const_reference
	vector<T, Allocator>::back() const
	{ return (*end()); }

	/**
	 * 	@brief data
	 * 
	 * 	@return a pointer such @c this->data() + @c this->size() is a valid range.
	*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::pointer
	vector<T, Allocator>::data()
	{
		// TO DO: Check what happens if %vector is empty
		return (&front());
	}

	/**
	 * 	@brief data
	 * 
	 * 	@return a const pointer such @c this->data() + @c this->size() is a valid range.
	*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::const_pointer
	vector<T, Allocator>::data() const
	{
		// TO DO: Check what happens if %vector is empty
		return (&front());
	}

	///////////////
	// Iterators //
	///////////////

	/**
	 * 	@brief begin
	 * 
	 * 	Return an iterator to the first element in %vector.
	*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::iterator
	vector<T, Allocator>::begin()
	{ return (iterator(head)); }

	/**
	 * 	@brief begin
	 * 
	 * 	Return a const iterator to the first element in %vector.
	*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::const_iterator
	vector<T, Allocator>::begin() const
	{ return (const_iterator(head)); }

	/**
	 * 	@brief end
	 * 
	 * 	Return an iterator to the last element in %vector.
	*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::iterator
	vector<T, Allocator>::end()
	{ return (iterator(tail)); }

	/**
	 * 	@brief end
	 * 
	 * 	Return a const iterator to the last element in %vector.
	*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::const_iterator
	vector<T, Allocator>::end() const
	{ return (const_iterator(tail)); }

	/**
	 * 	@brief rbegin
	 * 
	 * 	Return a reverse iterator to the first element in %vector.
	*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::reverse_iterator
	vector<T, Allocator>::rbegin()
	{ return (reverse_iterator(head)); }

	/**
	 * 	@brief rbegin
	 * 
	 * 	Return a const reverse iterator to the first element in %vector.
	*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::const_reverse_iterator
	vector<T, Allocator>::rbegin() const
	{ return (const_reverse_iterator(head)); }

	/**
	 * 	@brief rend
	 * 
	 * 	Return a reverse iterator to the last element in %vector.
	*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::reverse_iterator
	vector<T, Allocator>::rend()
	{ return (reverse_iterator(tail)); }

	/**
	 * 	@brief rend
	 * 
	 * 	Return a const reverse iterator to the last element into %vector.
	*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::const_reverse_iterator
	vector<T, Allocator>::rend() const
	{ return (const_reverse_iterator(tail)); }

	//////////////
	// Capacity //
	//////////////

	/*
	 * 	@brief empty
	 * 
	 * 	@return True if the vector is empty.
	*/
	template <class T, class Allocator>
	bool
	vector<T, Allocator>::empty() const
	{ return (begin() == end()); }

		/**
	 * 	@brief size
	 * 
	 * 	@return The number of elements in %vector.
	*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::size_type
	vector<T, Allocator>::size() const
	{ return (size_type(tail - head)); }

	/**
	 * 	@brief max_size
	 * 
	 * 	@return The largest amount of T elements that %vector supports.
	*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::size_type
	vector<T, Allocator>::max_size() const
	{ return (size_type(std::numeric_limits<size_type>::max() / sizeof(value_type))); }

	/**
	 * 	@brief reserve
	*/
	template <class T, class Allocator>
	void
	vector<T, Allocator>::reserve(size_type new_cap)
	{
		if (new_cap > capacity())
		{
			pointer tmp;
			try {
				tmp = alg_allocate(new_cap);
			}
		catch (std::bad_alloc& e) {
				clear();
				alg_deallocate(head);
				std::cerr << e.what() << std::endl;
				throw;
			}
			const size_type s = size();
			vec_array_copy(tmp, head, s);
			vec_clear();
			alg_deallocate(head);
			head = tmp;
			tail = pointer(head + s);
			storage = pointer(head + new_cap);
		}
	}

	/**
	 * 	@brief capacity
	 * 
	 * 	@return The maximun number of element that %vector can hold.
	*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::size_type
	vector<T, Allocator>::capacity() const
	{ return (size_type(storage - head)); }

	///////////////
	// Modifiers //
	///////////////

	/**
	 * 	@brief clear
	 * 
	 * 	Destroys all the elements that %vector hold.
	*/
	template <class T, class Allocator>
	void
	vector<T, Allocator>::clear()
	{ vec_clear(); }

	/**
	 * @brief insert
	 * 
	 * 	@param pos A const iterator into %vector.
	 * 	@param amount The total copies of @a value that will be inserted at @a index.
	 * 	@param value A copy of it will be inserted @a amount times.
	*/
	template <class T, class Allocator>
	void
	vector<T, Allocator>::insert(/*const_*/iterator pos, size_type amount, const_reference value)
	{
		// TO DO: (if i dont have it, i need an operator+ from normal iterator that return a size_type)

		// Handle space

		if (size_type(size() + amount) > capacity())
			resize(size_type(capacity() * 2));
		// Shift elements in range tail-(*this)[pos] by amount
		for (iterator i = end() ; i != pos ; i--)
			*(i + amount) = *i;
		// Insert amount copies of value
		for (size_type i = 0 ; i < amount ; i++)
			memory.construct(&*(pos++), value);
		tail += amount;
	}

	/**
	 * 	@brief insert
	 * 
	 * 	@param index A const interator into %vector.
	 * 	@param value The iserted value.
	 * 	@return An iterator to the inserted data.
	 * 
	 * 	Insert @c value at @c index (before the current element that is holds at @c index before the call)
	*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::iterator
	vector<T, Allocator>::insert(const_iterator pos, const_reference value)
	{
		insert(pos, size_type(1), value);
		return (iterator((*this)[pos]));
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
	template <class T, class Allocator>
	template <typename InputIt>
	typename vector<T, Allocator>::iterator
	vector<T, Allocator>::insert(/*const_*/iterator pos, InputIt first, InputIt last)
	{
		// Handle space
		const size_type amount = distance(first, last);
		if (size_type(size() + amount) > capacity())
			resize(size_type(capacity() * 2));
		// Shift elements in range tail-pos by amount
		iterator insertion_index = pos;
		for (iterator i = end() ; i != pos ; i--)
			*(i + amount) = *i;
		// Insert amount copies of value
		for (size_type i = 0 ; i < amount ; i++)
			memory.construct(&*(pos++), *(first++));
		tail += amount;

		return (insertion_index);
	}

		/**
	 * 	@brief erase
	 * 
	 * 	@param first An iterator that is the first iterator in erase range.
	 * 	@param last An iterator that is the last iterator in erase range.
	 * 	@return An iterator pointing to the iserted data.
	*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::iterator
	vector<T, Allocator>::erase(iterator first, iterator last)
	{
		// Calc the indexes
		const size_type amount = distance(first, last);
		const size_type pos = distance(begin(), first);
		iterator deletion_index = iterator(&(*this)[pos + amount]);
		// Proceed to shift backwards by amount and destroy while overwriting the old element
		for (size_type i = 0 ; i < amount ; i++)
		{
			memory.destroy(&(*this)[pos + i]);
			(*this)[pos + i] = (*this)[pos + i + amount];
		}
		// Shift backwards without destroying the remaining elements
		for (size_type i = pos + amount ; i < size() ; i++)
			(*this)[i] = (*this)[i + amount];
		tail -= amount;
		return (iterator()); // TO DO
	}

	/**
	 * 	@brief erase
	 * 
	 * 	@param pos The target iterator.
	 * 	@return An iterator pointing to the next element.
	 * 
	 * 	Remove an element at the index @a pos.
	*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::iterator
	vector<T, Allocator>::erase(iterator pos)
	{ return (erase(pos, pos + 1)); }


	/**
	 * 	@brief push back
	 * 
	 * 	@param x The data to be appended.
	 * 
	 * 	Append @c x to underliying work array @c head at index @c tail + 1.
	*/
	template <class T, class Allocator>
	void
	vector<T, Allocator>::push_back(const_reference x)
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
	template <class T, class Allocator>
	void
	vector<T, Allocator>::pop_back()
	{
		if (!empty())
			memory.destroy(tail--);
	}

			/**
	 * 	@brief resize
	 * 
	 * 	Change the capacity of %vector.
	 * 	Note: the elements between @c tail and @c storage are uninitialised.
	*/
	template <class T, class Allocator>
	void
	vector<T, Allocator>::resize(size_type new_cap, const_reference value)
	{
		pointer tmp;
		try {
			tmp = alg_allocate(new_cap);
		}
		catch (std::bad_alloc& e) {
			vec_clear();
			alg_deallocate(head);
			std::cerr << e.what() << std::endl;
			throw;
		}
		const size_type s = new_cap < size() ? new_cap : size();
		vec_array_copy(tmp, head, s);
		vec_clear();
		alg_deallocate(head);
		head = tmp;
		tail = pointer(head + s);
		storage = pointer(head + new_cap);
		vec_set(tail, value, size_type(storage - tail));
	}

	/**
	 * 	@brief swap
	 * 
	 *	@param other A %vector.
	 *
	 * 	Swap the underlying work data of @c *this and @a other.
	*/
	template <class T, class Allocator>
	void
	vector<T, Allocator>::swap(vector& other)
	{ alg_swap_data(other); }

	//@{
	/** @brief Boolean operators
	 * 
	 * 	@param lhs A %vector.
	 * 	@param rhs A %vector of the same type of @a lhs.
	 * 
	 * 	@return A boolean that is the result of the requested boolean operation.
	*/
	template <class T, class Allocator>
	inline bool
	operator==(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		// TO DO: Is it worth it to implement std::equal ? 
		return (lhs.size() == rhs.size()/* && std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())*/);
	}

	template <class T, class Allocator>
	inline bool
	operator<(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{ return (1/*std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())*/); }

	template <class T, class Allocator>
	inline bool
	operator!=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{ return (!(lhs == rhs)); }

	template <class T, class Allocator>
	inline bool
	operator<=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{ return (!(rhs < lhs)); }

	template <class T, class Allocator>
	inline bool
	operator>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{ return (rhs < lhs); }

	template <class T, class Allocator>
	inline bool
	operator>=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{ return (!(lhs < rhs)); }
	//@}

	/**
	 * 	@brief swap
	 * 
	 * 	A non member swap spacialisation, built to swap %vectors.
	*/
	template <class T, class Allocator>
	inline void
	swap(vector<T, Allocator>& lhs, vector<T, Allocator>& rhs)
	{ lhs.swap(rhs); }
};
