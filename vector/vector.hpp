# pragma once

/*
** Implemtation using a array with a block size who is *= 2
** each time a new performed insertion is out of bounds.
**
** Documentation: https://en.cppreference.com/w/cpp/container/vector
*/

# include <cstring>

# include "../allocator/allocator.hpp"
# include "../iterators/LegacyRandomAccessIterator.hpp"
# include "../iterators/reverse_iterator.hpp"
# include "../lexicographical_compare.hpp"

namespace ft
{
	template <class T, class Allocator = allocator<T>>
	class vector
	{
		public:

		/* Member types */

		typedef T					value_type;
		typedef std::size_t			size_type;
		typedef std::ptrdiff_t		difference_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
	
		typedef LegacyRandomAccessIterator<value_type>			iterator;
		typedef LegacyRandomAccessIterator<const value_type>	const_iterator;
		typedef reverse_iterator<const_iterator>				const_reverse_iterator;
		typedef reverse_iterator<iterator>						reverse_iterator;

		private:
	
		/* Core */

		Allocator				memory;
		size_type				curr_capacity;
		pointer					array;
		size_type				curr_size;

		/*
		** Like a kind of realloc, creates a new array and perform a deep copy
		** of all the current elements stored in the current array (size of curr_capacity).
		**
		** Note: Need to be called each time the max size is updated
		*/
		void					array_reserve()
		{
			pointer	new_array;
			try {
				new_array = memory.allocate(curr_capacity);
			} catch (const std::bad_alloc& e) { if (array) this->~vector(); throw ; }
			for (size_type i = 0 ; i < curr_size ; i++)
			{
				// check if i m allowed to play God with std::move
				new_array = std::move(operator[](i));
				memory.destroy(operator[](i));
			}
			memory.deallocate(array);
			array = new_array;
		}

		/*
		** Duplicates the curr_capacity and call array_reserve to perform the reallocation.
		*/
		void				array_resize()
		{
			if (curr_capacity < curr_size)
			{
				while (curr_capacity < curr_size)
					curr_capacity = curr_capacity << 1ul;
				array_reserve();
			}
		}

		public:

		/* Member functions */

			/* Constructor */
		explicit vector(const Allocator& alloc = Allocator()) : memory(alloc), curr_capacity(0ul), array(NULL), curr_size(0ul) { }

		explicit vector(size_type count, const_reference value = value_type(), const Allocator& alloc = Allocator())
		: memory(alloc), curr_size(count)
		{
			// Define the capacity
			curr_capacity = 1;
			while (curr_capacity < curr_size)
				curr_capacity = curr_capacity << 1ul;

			// Allocate the array
			try {
				array = memory.allocate(curr_capacity);
			} catch (const std::bad_alloc& e) { throw ; }

			// Contruct the array
			for (size_type i = 0 ; i < curr_capacity ; i++)
				memory.construct(operator[](i), value);
		}

		template <class InputIt>
		vector(InputIt first, InputIt last, const Allocator& alloc = Allocator())
		: memory(alloc), curr_capacity(0ul), array(NULL), curr_size(0ul) { assign(first, last); }

			/* Destructor */
		~vector()
		{
			for (size_type i = 0 ; i < curr_size ; i++)
				memory.destroy(&operator[](i));
			memory.deallocate(array, curr_capacity);
		}

			/* Operator= */
		vector&		operator=(const vector& other);

			/* Assign */
		void		assign(size_type count, const_reference value);
		template <class InputIt>
		void		assign(InputIt first, InputIt last);

			/* No implement get_allocator (subject rules) */

		/* Member functions: Element access */

			/* At */
		reference			at(size_type pos);
		const_reference		at(size_type pos) const;

			/* Operator[] */
		reference			operator[](size_type pos);
		const_reference		operator[](size_type pos) const;

			/* Front */
		reference			front();
		const_reference		front() const;

			/* Back */
		reference			back();
		const_reference		back() const;

			/* begin */
		iterator			begin();
		const_iterator		begin() const;

			/* end */
		iterator			end();
		const_iterator		end() const;

			/* rbegin */
		reverse_iterator	rbegin();
		const_reverse_iterator	rbegin() const;

			/* rend */
		reverse_iterator	rend();
		const_reverse_iterator	rend() const;

		/* Member functions: Capacity */

			/* empty */
		bool				empty() const;

			/* size */
		size_type			size() const;

			/* max size */
		size_type			max_size() const;

			/* reserve */
		void				reserve(size_type new_cap);

			/* capacity */
		size_type			capacity() const;

		/* Member functions: Modifiers */

			/* clear */
		void				clear();

			/* insert */
		iterator			insert(iterator pos, const_reference value);
		void				insert(iterator pos, size_type count, const_reference value);
		template <class InputIt>
		void				insert(iterator pos, InputIt first, InputIt last);

			/* erase */
		iterator			erase(iterator pos);
		iterator			erase(iterator first, iterator last);

			/* Push_back */
		void				push_back(const_reference value);

			/* Pop_back */
		void				pop_back();

			/* Resize */
		void				resize(size_type count, value_type value = value_type());

			/* Swap */
		void				swap(vector& other);
	};

	/* Operator= */
	template <class T, class Allocator>
	vector<T, Allocator>&	vector<T, Allocator>::operator=(const vector<T, Allocator>& other)
	{
		if (this != &other)
		{
			curr_capacity = other.capacity();
			array_reserve();
			std::memcpy(static_cast<void*>(array), static_cast<void*>(other.array), curr_capacity * sizeof(value_type));
		}
		return (*this);
	}

	/* Assign */
	template <class T, class Allocator>
	void					vector<T, Allocator>::assign(size_type count, const_reference value)
	{
		if (count > curr_capacity)
		{
			curr_size = count;
			array_resize();
		}
		for (size_type i = 0 ; i < count ; i++)
		{
			memory.destroy(&operator[](i));
			memory.construct(&operator[](i), value);
		}
	}

	/* Assign */
	template <class T, class Allocator>
	template <class InputIt>
	void					vector<T, Allocator>::assign(InputIt first, InputIt last)
	{
		// This doesn't need a out of bounds check ?
		while (first != last)
		{
			memory.destroy(first);
			//memory.construct(first, value);
			first++;
		}
	}

	/* At */
	template <class T, class Allocator>
	typename vector<T, Allocator>::reference		vector<T, Allocator>::at(size_type pos)
	{
		if (!(pos < size()))
			throw std::out_of_range(std::string("Error: Out of bounds."));
		return (operator[](pos));
	}

	/* At */
	template <class T, class Allocator>
	typename vector<T, Allocator>::const_reference	vector<T, Allocator>::at(size_type pos) const
	{
		if (!(pos < size()))
			throw std::out_of_range(std::string("Error: Out of bounds"));
		return (operator[](pos));
	}

	/* Operator[] */
	template <class T, class Allocator>
	typename vector<T, Allocator>::reference		vector<T, Allocator>::operator[](size_type pos)
	{
		return (array[pos]);
	}

	/* Operator[] */
	template <class T, class Allocator>
	typename vector<T, Allocator>::const_reference	vector<T, Allocator>::operator[](size_type pos) const
	{
		return (array[pos]);
	}
	
	/* Front */
	template <class T, class Allocator>
	typename vector<T, Allocator>::reference		vector<T, Allocator>::front()
	{
		
		return (operator[](0));
	}

	/* Front */
	template <class T, class Allocator>
	typename vector<T, Allocator>::const_reference	vector<T, Allocator>::front() const
	{
		return (operator[](0));
	}
	
	/* Back */
	template <class T, class Allocator>
	typename vector<T, Allocator>::reference		vector<T, Allocator>::back()
	{
		
		return (operator[](curr_size - 1));
	}

	/* Back */
	template <class T, class Allocator>
	typename vector<T, Allocator>::const_reference	vector<T, Allocator>::back() const
	{
		return (operator[](curr_size - 1));
	}

	/* Begin */
	template <class T, class Allocator>
	typename vector<T, Allocator>::iterator			vector<T, Allocator>::begin()
	{
		return (iterator(&operator[](0)));
	}

	/* Begin */
	template <class T, class Allocator>
	typename vector<T, Allocator>::const_iterator	vector<T, Allocator>::begin() const
	{
		return (const_iterator(&operator[](0)));
	}

	/* End */
	template <class T, class Allocator>
	typename vector<T, Allocator>::iterator			vector<T, Allocator>::end()
	{
		return (iterator(&operator[](curr_size - 1)));
	}

	/* End */
	template <class T, class Allocator>
	typename vector<T, Allocator>::const_iterator	vector<T, Allocator>::end() const
	{
		return (const_iterator(&operator[](curr_size - 1)));
	}

	/* Rbegin */
	template <class T, class Allocator>
	typename vector<T, Allocator>::reverse_iterator	vector<T, Allocator>::rbegin()
	{
		return(reverse_iterator(end()));
	}

	/* Rbegin */
	template <class T, class Allocator>
	typename vector<T, Allocator>::const_reverse_iterator	vector<T, Allocator>::rbegin() const
	{
		return(const_reverse_iterator(end()));
	}

	/* Rend */
	template <class T, class Allocator>
	typename vector<T, Allocator>::reverse_iterator			vector<T, Allocator>::rend()
	{
		return(reverse_iterator(begin()));
	}

	/* Rend */
	template <class T, class Allocator>
	typename vector<T, Allocator>::const_reverse_iterator	vector<T, Allocator>::rend() const
	{
		return(const_reverse_iterator(begin()));
	}

	/* Empty*/
	template <class T, class Allocator>
	bool										vector<T, Allocator>::empty() const
	{
		return (curr_size == 0);
	}

	/* Size */
	template <class T, class Allocator>
	typename vector<T, Allocator>::size_type	vector<T, Allocator>::size() const
	{
		return (curr_size);
	}

	/* Max size */
	template <class T, class Allocator>
	typename vector<T, Allocator>::size_type	vector<T, Allocator>::max_size() const
	{
		return (std::numeric_limits<size_type>::max() / sizeof(value_type));
	}

	/* Reserve */
	template <class T, class Allocator>
	void										vector<T, Allocator>::reserve(size_type new_cap)
	{
		// TO DO: check if that operation still follow cap = cap ^ n
		if (new_cap > max_size())
			throw std::length_error(std::string("Error: Not enought physical memory in the device to perform this reserve allocation"));
		curr_capacity = new_cap;
		array_reserve();
	}

	/* Capacity */
	template <class T, class Allocator>
	typename vector<T, Allocator>::size_type	vector<T, Allocator>::capacity() const
	{
		return (curr_capacity);
	}

	/* Clear */
	template <class T, class Allocator>
	void										vector<T, Allocator>::clear()
	{
		while (curr_size-- < 0)
			memory.destruct(&operator[](curr_size));
	}

	/* Insert */
	template <class T, class Allocator>
	typename vector<T, Allocator>::iterator		vector<T, Allocator>::insert(iterator pos, const_reference value)
	{
		insert(pos, 1, value);
	}

	/* Insert */
	template <class T, class Allocator>
	void										vector<T, Allocator>::insert(iterator pos, size_type count, const_reference value)
	{
		// Handle space
		curr_size += count;
		array_resize();

		// Calc the insertion index
		iterator i = begin();
		size_type insertion_index = 0;
		while (i != pos)
		{
			i++;
			insertion_index++;
		}

		// Shift all "count" times to the left (starting at the insertion index)
		for (size_type i = curr_size ; i > insertion_index ; i--)
			std::move(operator[](i), operator[](i + count));

		// Insert the value at the insertion index (size of count)
		for (size_type i = insertion_index ; i < insertion_index + count ; i++)
		{
			// TO DO: Check if i have to destroy here
			memory.construct(&operator[](i), value);
		}
	}

	/* Insert */
	template <class T, class Allocator>
	template <class InputIt>
	void										vector<T, Allocator>::insert(iterator pos, InputIt first, InputIt last)
	{
		// Handle space
		curr_size += last - first;
		if (curr_size > curr_capacity)
		{
			curr_capacity = curr_size;
			array_reserve();
		}

		// Calc the insertion index
		iterator i = begin();
		size_type insertion_index = 0;
		while (i != pos)
		{
			i++;
			insertion_index++;
		}

		// Shift all "last - first" times to the left (starting at the insertion index)
		for (size_type i = curr_size ; i > insertion_index ; i--)
			std::move(operator[](i), operator[](i + last - first));

		// Insert the value at the insertion index (size of count)
		for (size_type i = insertion_index ; i < insertion_index + last - first ; i++)
		{
			// TO DO: Check if i have to destroy here
			//memory.construct(&operator[](i), value);
		}
	}

	/* Erase */
	template <class T, class Allocator>
	typename vector<T, Allocator>::iterator		vector<T, Allocator>::erase(iterator pos)
	{
		erase(pos, pos + 1);
	}

	/* Erase */
	template <class T, class Allocator>
	typename vector<T, Allocator>::iterator		vector<T, Allocator>::erase(iterator first, iterator last)
	{
		size_type	_size  = last - first;

		// Calc the deletion index
		iterator i = begin();
		size_type deletion_index = 0;
		while (i != last)
		{
			i++;
			deletion_index++;
		}

		// Perform the deletion starting at the deletion index (size of last - first)
		for (size_type i = deletion_index ; i < deletion_index + _size ; i++)
			memory.deltroy(&operator[](i));
		
		// Shift to the left the existing blocks after the deletion
		for (size_type i = deletion_index + _size ; i < curr_size ; i++)
			std::move(operator[](i), operator[](i - _size));

		curr_size -= _size;
	}

	/* Push back */
	template <class T, class Allocator>
	void										vector<T, Allocator>::push_back(const_reference value)
	{
		curr_size++;
		array_resize();
		operator[](curr_size - 1) = value;
	}

	/* Pop back */
	template <class T, class Allocator>
	void										vector<T, Allocator>::pop_back()
	{
		if (!empty())
			operator[](--curr_size).value_type::~value_type();
	}

	/* Resize */
	template <class T, class Allocator>
	void										vector<T, Allocator>::resize(size_type count, value_type value)
	{
		std::swap(curr_size, count);
		array_resize();
		for (size_type i = count ; i < curr_capacity ; i++)
			operator[](i) = value;
	}

	/* Swap */
	template <class T, class Allocator>
	void										vector<T, Allocator>::swap(vector& other)
	{
		// Implement get or change to protected
		std::swap(memory, other.memory);
		std::swap(curr_capacity, other.curr_capacity);
		std::swap(array, other.array);
		std::swap(curr_size, other.curr_size);
	}

	/* Booleans */

	template <class T, class Alloc>
	bool				operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		if (lhs.size() == rhs.size())
		{
			for (auto i = 0ul ; i < lhs.size() ; i++)
				if (lhs.operator[](i) != rhs.operator[](i))
					return (false);
			return (true);
		}
		return (false);
	}
	
	template <class T, class Alloc>
	bool				operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!operator==(lhs, rhs));
	}

	template <class T, class Alloc>
	bool				operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool				operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (operator==(lhs, rhs) || operator<(lhs, rhs));
	}

	template <class T, class Alloc>
	bool				operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!operator<=(lhs, rhs));
	}

	template <class T, class Alloc>
	bool				operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!operator<(lhs, rhs));
	}

	template <class T, class Alloc>
	void				swap(vector<T, Alloc>& a, vector<T, Alloc>& b)
	{
		a.swap(b);
	}
};