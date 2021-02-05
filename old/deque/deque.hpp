
# pragma once

/*
** Deque implementation using a circular array.
** 
** The indexes head and tail are used to control the front and the back.
** When the deque is empty: head == -1 and tail == 0
** When the deque has 1 element: head == 0 and tail == 0
** With more than 1 element, when elements are pushed front head index == size() - 1,
**	then when more elements are pushed front, the head decrements (head == head - 1)
** With more than 1 element, when elements are pushed back tail index == index + 1
** When head - 1 == tail or tail + 1 == head, the deque is full and a realloc is performed.
**
** Documentation: https://en.cppreference.com/w/cpp/container/deque
*/

# include "../allocator/allocator.hpp"
# include "../lexicographical_compare.hpp"
# include "../iterators/reverse_iterator.hpp"

namespace ft
{
	template <class T, class Allocator = allocator<T>>
	class deque
	{
		/* Member types */

		public:

		typedef T				value_type;
		typedef Allocator		allocator_type;
		typedef std::size_t		size_type;
		typedef std::ptrdiff_t	difference_type;
		typedef T&				reference;
		typedef const T&		const_reference;
		typedef T*				pointer;
		typedef const T*		const_pointer;

		// TO DO: Iterators

		/* Core */

		private:

		allocator_type			memory;
		size_type				curr_capacity;
		pointer					array;
		size_type				curr_size;
		int_fast64_t			head;
		int_fast64_t			tail;

		void					realloc()
		{
			if (!empty() && head - 1 == tail && tail + 1 == head)
			{
				const size_t old_capacity = curr_capacity;
				curr_capacity *= 2;
				
				pointer new_array;
				try {
					new_array = memory.allocate(curr_capacity);
				} catch (const std::bad_alloc& e) { if (!empty()) this->~deque(); throw ; }

				for (size_type i = 0 ; i < tail ; i++)
				{
					// check if i m allowed to play God with std::move
					new_array = std::move(operator[](i));
					memory.destroy(operator[](i));
				}

				head += curr_capacity - head;
				for (size_type i = head ; i < curr_capacity ; i++)
				{
					// check if i m allowed to play God with std::move
					new_array = std::move(operator[](i));
					memory.destroy(operator[](i));
				}
				memory.deallocate(array);
				array = new_array;
			}
		}

		/* Member functions */

		public:

			/* Constructors */
		deque() : memory(allocator_type), curr_capacity(0ul), array(NULL), curr_size(0ul), head(-1), tail(0) { }

		explicit deque(const allocator_type& alloc) : memory(alloc), curr_capacity(0ul), array(NULL), curr_size(0ul), head(-1), tail(0) { }

		explicit deque(size_type count, const value_type& value, const allocator_type& alloc = allocator_type())
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

			// TO DO: How i init this ? Where are the elems ? Head ? Tail ?

		}

		template <class InputIt>
		deque(InputIt first, InputIt last, const Allocator& alloc = allocator_type())
		{
			// TO DO: Update the sizes and static init of private members
			assign(first, last);
		}

		deque(const deque& other) { operator=(other); }

			/* Destructor */
		~deque()
		{
			clear();
			memory.deallocate(arrya, curr_capacity);
		}

			/* Operator= */
		deque&		operator=(const deque& other);

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
		// iterator			begin();
		// const_iterator		begin() const;

			/* end */
		// iterator			end();
		// const_iterator		end() const;

			/* rbegin */
		// reverse_iterator	rbegin();
		// const_reverse_iterator	rbegin() const;

			/* rend */
		// reverse_iterator	rend();
		// const_reverse_iterator	rend() const;

		/* Member functions: Capacity */

			/* empty */
		bool				empty() const;

			/* size */
		size_type			size() const;

			/* max size */
		size_type			max_size() const;

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

			/* Push_front */
		void				push_front(const_reference value);

			/* Pop_front */
		void				pop_front();

			/* Resize */
		void				resize(size_type count, value_type value = value_type());

			/* Swap */
		void				swap(deque& other);
	};

	/* Operator= */
	template <class T, class Allocator>
	deque<T, Allocator>&	deque<T, Allocator>::operator=(const deque<T, Allocator>& other)
	{

	}

	/* Assign */
	template <class T, class Allocator>
	void					deque<T, Allocator>::assign(size_type count, const_reference value)
	{

	}

	/* Assign */
	template <class T, class Allocator>
	template <class InputIt>
	void					deque<T, Allocator>::assign(InputIt first, InputIt last)
	{

	}

	/* At */
	template <class T, class Allocator>
	typename deque<T, Allocator>::reference			deque<T, Allocator>::at(size_type pos)
	{

	}

	/* At */
	template <class T, class Allocator>
	typename deque<T, Allocator>::const_reference	deque<T, Allocator>::at(size_type pos) const
	{

	}

	template <class T, class Allocator>
	typename deque<T, Allocator>::reference			deque<T, Allocator>::operator[](size_type pos)
	{
		return (array[pos]);
	}

	/* Operator[] */
	template <class T, class Allocator>
	typename deque<T, Allocator>::const_reference	deque<T, Allocator>::operator[](size_type pos) const
	{
		return (array[pos]);
	}

	/* Front */
	template <class T, class Allocator>
	typename deque<T, Allocator>::reference			deque<T, Allocator>::front()
	{
		
		return (operator[](head));
	}

	/* Front */
	template <class T, class Allocator>
	typename deque<T, Allocator>::const_reference	deque<T, Allocator>::front() const
	{
		return (operator[](head));
	}

	/* Back */
	template <class T, class Allocator>
	typename deque<T, Allocator>::reference			deque<T, Allocator>::back()
	{
		
		return (operator[](tail));
	}

	/* Back */
	template <class T, class Allocator>
	typename deque<T, Allocator>::const_reference	deque<T, Allocator>::back() const
	{
		return (operator[](tail));
	}

	/* Begin */

	/* End */

	/* Rbegin */

	/* Rend */

	/* Empty*/
	template <class T, class Allocator>
	bool										deque<T, Allocator>::empty() const
	{
		return (curr_size == 0);
	}

	/* Size */
	template <class T, class Allocator>
	typename deque<T, Allocator>::size_type		deque<T, Allocator>::size() const
	{
		return (curr_size);
	}

	/* Max size */
	template <class T, class Allocator>
	typename deque<T, Allocator>::size_type		deque<T, Allocator>::max_size() const
	{
		return (std::numeric_limits<size_type>::max() / sizeof(value_type));
	}

	/* Clear */
	template <class T, class Allocator>
	void										deque<T, Allocator>::clear()
	{
		while (tail <= 0)
				memory.destroy(&operator[](tail--));
			if (head != 0 && head != -1)
			{
				while (head < curr_capacity)
					memory.destroy(&operator[](head++));
			}
			tail = 0;
			head = -1;
	}

	/* Insert */

	/* Erase */

	/* Push back */
	template <class T, class Allocator>
	void										deque<T, Allocator>::push_back(const_reference value)
	{

	}

	/* Pop back */
	template <class T, class Allocator>
	void										deque<T, Allocator>::pop_back()
	{

	}

	/* Push front */
	template <class T, class Allocator>
	void										deque<T, Allocator>::push_front(const_reference value)
	{

	}

	/* Pop front */
	template <class T, class Allocator>
	void										deque<T, Allocator>::pop_front()
	{
		
	}

	/* Resize */
	template <class T, class Allocator>
	void										deque<T, Allocator>::resize(size_type count, value_type value)
	{

	}

	/* Swap */
	template <class T, class Allocator>
	void										deque<T, Allocator>::swap(deque& other)
	{

	}

	/* Booleans */

	template <class T, class Alloc>
	bool				operator==(const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs)
	{

	}
	template <class T, class Alloc>
	bool				operator!=(const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs)
	{
		return (!operator==(lhs, rhs));
	}

	template <class T, class Alloc>
	bool				operator<(const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs)
	{
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool				operator<=(const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs)
	{
		return (operator==(lhs, rhs) || operator<(lhs, rhs));
	}

	template <class T, class Alloc>
	bool				operator>(const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs)
	{
		return (!operator<=(lhs, rhs));
	}

	template <class T, class Alloc>
	bool				operator>=(const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs)
	{
		return (!operator<(lhs, rhs));
	}

	template <class T, class Alloc>
	void				swap(deque<T, Alloc>& a, deque<T, Alloc>& b)
	{
		a.swap(b);
	}
};
