
# pragma once

// Example to how to do it: https://catherine-leung.gitbook.io/data-strutures-and-algorithms/lists/linked-list/implementation-iterators

# include "../vector/vector.hpp"

// Is easiest to inline this into vector like in the example

namespace ft
{

	template <typename It>
	class const_iterator
	{
		public:

		/* Member types */

		typedef It								value_type;
		typedef std::size_t						size_type;
		typedef std::ptrdiff_t					difference_type;
		typedef value_type&						reference;
		typedef const value_type&				const_reference;
		typedef value_type*						pointer;
		typedef const value_type*				const_pointer;
		typedef std::bidirectional_iterator_tag	iterator_category;

		/* vector need access to private its members */

		friend class vector;

		private:

		/* Core */

		pointer									it;

		/* Private constructor */
		const_iterator(pointer curr) : it(curr) { }

		public: 

		/* Public member functions */

		const_iterator() : it(NULL) { }
		const_iterator(const const_iterator& other) : it(other.it) { }
		~const_iterator() { }

		/* Handle operators */

		// TO DO: Out of bounds

		/* Assignation */
		const_iterator&					operator=(const const_iterator& other)
		{
			if (this != &other)
			{
				it = other.it;
				return (*this);
		}

		/* Addrees addition */
		const_iterator					operator+(difference_type n) { return (const_iterator(it + n); }

		/* Address addition to integer form */
		size_type						operator+(const_iterator& other) { return ((static_cast<uint64_t>(it) + static_cast<uint64_t>(other.it)) / sizeof(size_type)); }

		/* Address self addition */
		const_iterator					operator+=(difference_type n)
		{
			it += n;
			return (*this);
		}

		/* Address self prefix incrementation by 1 */
		const_iterator					operator++()
		{
			it++;
			return (*this);
		}

		/* Address self postfix incrementation by 1 */
		const_iterator					operator++(int)
		{
			const_iterator old = *this;
			operator++();
			return (old);
		}

		/* Address substracion */
		const_iterator					operator-(difference_type n) { return (const_iterator(it - n)); }

		/* Address substracion to integer form */
		size_type						operator-(const_iterator& other) { return ((static_cast<uint64_t>(it) - static_cast<uint64_t>(other.it)) / sizeof (size_type)); }

		/* Address self substraction */
		const_iterator					operator-=(difference_type n)
		{
			it -= n;
			return (*this);
		}

		/* Address self prefix decrementation by 1 */
		const_iterator					operator++()
		{
			it--;
			return (*this);
		}

		/* Address self postfix decrementation by 1 */
		const_iterator					operator++(int)
		{
			const_iterator old = *this;
			operator--();
			return (old);
		}

		/* Address dereference */
		const_reference					operator*() const
		{
			if (!it)
				throw::std::out_of_range(std::string("Error: Out of bounds."));
			return (*it);
		}

		const_reference					operator->() const { return (it); }

		/* Address defeference using brackets */
		const_reference					operator[](difference_type pos) const { return (it + pos); }
	};

	template <typename It>
	class iterator : public const_iterator
	{
		/* vector need access to private its members */

		friend class vector;
		iterator(pointer curr) : const_iterator(curr) { }

		/* Handle operators */

		/* Assignation */
		iterator&					operator=(const iterator& other)
		{
			if (this != &other)
			{
				it = other.it;
				return (*this);
		}

		/* Addrees addition */
		iterator						operator+(difference_type n) { return (iterator(it + n); }

		/* Address addition to integer form */
		size_type						operator+(iterator& other) { return ((static_cast<uint64_t>(it) + static_cast<uint64_t>(other.it)) / sizeof(size_type)); }

		/* Address self addition */
		iterator						operator+=(difference_type n)
		{
			it += n;
			return (*this);
		}

		/* Address self prefix incrementation by 1 */
		iterator						operator++()
		{
			it++;
			return (*this);
		}

		/* Address self postfix incrementation by 1 */
		iterator						operator++(int)
		{
			const_iterator old = *this;
			operator++();
			return (old);
		}

		/* Address substracion */
		iterator						operator-(difference_type n) { return (const_iterator(it - n)); }

		/* Address substracion to integer form */
		size_type						operator-(iterator& other) { return ((static_cast<uint64_t>(it) - static_cast<uint64_t>(other.it)) / sizeof (size_type)); }

		/* Address self substraction */
		iterator						operator-=(difference_type n)
		{
			it -= n;
			return (*this);
		}

		/* Address self prefix decrementation by 1 */
		iterator						operator++()
		{
			it--;
			return (*this);
		}

		/* Address self postfix decrementation by 1 */
		iterator						operator++(int)
		{
			const_iterator old = *this;
			operator--();
			return (old);
		}

		/* Address dereference */
		reference						operator*()
		{
			if (!it)
				throw::std::out_of_range(std::string("Error: Out of bounds."));
			return (*it);
		}

		reference						operator->() { return (it); }

		/* Address defeference using brackets */
		reference						operator[](difference_type pos) { return (it + pos); }
	};
};