
# pragma once

/*
** Documentation: https://en.cppreference.com/w/cpp/memory/allocator
*/

# include <iostream>
# include <limits>
# include <new>

namespace ft
{
	template <class T>
	class allocator
	{
		public:

		/* Member types */

		typedef T					value_type;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef std::size_t			size_type;
		typedef std::ptrdiff_t		difference_type;

		template <class U>
		struct rebind { typedef allocator<U> other; };

		/* Member functions */

		allocator() throw() { }
		allocator(const allocator& other) throw() { (void)other; }
		template <class U>
		allocator(const allocator<U>& other) throw() { (void)other; }
		~allocator() { };

		pointer			address(reference x) const { return (&x); }
		const_pointer	address(const_pointer x) const { return (&x); }

		// TO DO: What have i to do with hint ?
		pointer		allocate(size_type n, const void* hint = 0)
		{
			if (std::numeric_limits<size_type>::max() / sizeof(T) < n)
				throw std::bad_array_new_length();

			pointer alloc;

			try {
				alloc = (pointer)(::operator new(n * sizeof(value_type)));
			} catch (const std::bad_alloc& e) { std::cerr << e.what() << std::endl; throw std::bad_alloc(); }

			return (alloc);
		}

		void		deallocate(pointer p, size_type n) { (void)n, ::operator delete(static_cast<void*>(p)); }
		size_type	max_size() const throw() { return (std::numeric_limits<size_type>::max() / sizeof(value_type)); }
		void		contruct(pointer p, const_reference val) { new ((void*)p)value_type(val); }
		void		destroy(pointer p) { ((pointer)p)->~value_type(); };

		/* Non-member functions */

		// TO DO: Use friend here (subject says)
		/*
		template <class T1, class T2>
		bool		operator==(const allocator<T1>& lhs, const allocator<T2>& rhs) throw() { return (&lhs == &rhs); }
		template <class T1, class T2>
		bool		operator!=(const allocator<T1>& lhs, const allocator<T2>& rhs) throw() { return (&lhs != &rhs); }
		*/
	};
};