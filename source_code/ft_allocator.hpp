
/** @file ft_allocator.hpp
 * 
 * 	This file contains the containers allocator implementation.
*/

// TO DO: std::__addressof

# pragma once

# include "ft_containers.hpp"

namespace FT_NAMESPACE
{
	/**
	 * 	@brief Allocator that uses global new.
	 * 
	 * 	@tparam T the type of the allocated/deallocated object.
	 * 
	 *	All allocations are performed with new, all the deallocation with delete.
	*/
	template <typename T>
	class allocator
	{
		/* Member types */

		public:

		typedef T				value_type;
		typedef std::size_t		size_type;
		typedef std::ptrdiff_t	difference_type;
		typedef T*				pointer;
		typedef const T*		const_pointer;
		typedef T&				reference;
		typedef const T&		const_reference;

		template <typename T1>
		struct rebind { typedef allocator<T1> other; };

		/* Member functions */

		allocator();
		allocator(const allocator&);
		template <typename T1>
		allocator(const allocator<T1>&);
		~allocator();

		pointer			address(reference x) const throw();
		const_pointer	address(const_reference x) const throw();
		pointer			allocate(size_type n, const void* = static_cast<const void*>(0)) throw(std::bad_alloc);
		void			deallocate(pointer p /*, size_type amount*/) throw();
		void			construct(pointer p, const_reference value) throw(std::bad_alloc);
		void			destroy(pointer p) throw();
		size_type		max_size() throw();
		template <typename T1>
		friend bool		operator==(const allocator&, const allocator<T1>&) { return (true); }
		template <typename T1>
		friend bool		operator!=(const allocator&, const allocator<T1>&) { return (false); }
	};

	template <typename T>
	allocator<T>::allocator()
	{ }

	template <typename T>
	allocator<T>::allocator(const allocator&)
	{ }

	template <typename T>
	template <typename T1>
	allocator<T>::allocator(const allocator<T1>&)
	{ }

	template <typename T>
	allocator<T>::~allocator()
	{ }
	
	template <typename T>
	inline typename allocator<T>::pointer
	allocator<T>::address(reference x) const
	throw()
	{ return (std::addressof(x)); }

	template <typename T>
	inline typename allocator<T>::const_pointer
	allocator<T>::address(const_reference x) const
	throw()
	{ return (std::addressof(x)); }
	
	template <typename T>
	inline typename allocator<T>::pointer
	allocator<T>::allocate(size_type n, const void*)
	throw(::std::bad_alloc)
	{
		if (n > max_size())
			throw std::bad_alloc();
		return (static_cast<pointer>(::operator new(n * sizeof(value_type))));
	}

	template <typename T>
	inline void
	allocator<T>::deallocate(pointer p /*, size_type amount*/)
	throw()
	{
		// DO TO: Check what happens here if p in NULL
		::operator delete(p/*, size_type(amount  * sizeof(value_type))*/);
	}

	template <typename T>
	inline void
	allocator<T>::construct(pointer p, const_reference value)
	throw(::std::bad_alloc)
	{ ::new(static_cast<void*>(p)) value_type(value); }

	template <typename T>
	inline void
	allocator<T>::destroy(pointer p)
	throw()
	{ p->~value_type(); }

	template <typename T>
	inline typename allocator<T>::size_type
	allocator<T>::max_size() throw()
	{ return (size_type(-1) / sizeof(value_type)); }

	template <typename T1, typename T2>
	inline bool
	operator==(const allocator<T1>&, const allocator<T2>&)
	{ return(true); }

	template <typename T1, typename T2>
	inline bool
	operator!=(const allocator<T1>&, const allocator<T2>&)
	{ return (false); }
};
