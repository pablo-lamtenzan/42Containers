# pragma once

/*
** LegacyRandomAccessIterator is a LegacyBidirectionalIterator that can be moved
** to point to any element in constant time.
** A pointer to an element of an array satisfies all requeriment of LegacyBidirectionalAccessIterator
**
** Documentation: https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator
*/

# include <cstddef>

namespace ft
{
	template <typename It>
	class LegacyRandomAccessIterator
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
		
		/* Iterator (current address in the array) */
		protected:
		
		pointer									it;

		public:

		/* Member functions */


		LegacyRandomAccessIterator() : it(nullptr) { }
		LegacyRandomAccessIterator(pointer ptr) : it(ptr) { }
		LegacyRandomAccessIterator(const LegacyRandomAccessIterator& other) : it(other.it) { }
		~LegacyRandomAccessIterator() { }

		/* Handle assignation */
		LegacyRandomAccessIterator&			operator=(const LegacyRandomAccessIterator& other) { it = other.it; return (*this); }
		/* Handle address addition */
		LegacyRandomAccessIterator			operator+(difference_type n) { return (LegacyRandomAccessIterator(it + n)); }
		/* Handle integer addition with no const iterator */
		size_type							operator+(LegacyRandomAccessIterator& other) { return ((static_cast<uint64_t>(it) + static_cast<uint64_t>(other.it)) / sizeof (size_type)); }
		/* Handle integer addtion with const iterator */
		size_type							operator+(const LegacyRandomAccessIterator& other) { return ((static_cast<uint64_t>(it) + static_cast<uint64_t>(other.it)) / sizeof (size_type)); }
		/* Handle address substraction */
		LegacyRandomAccessIterator			operator-(difference_type n) { return (LegacyRandomAccessIterator(it - n)); }
		/* Handle integer substraction with no const iterator */
		size_type							operator-(LegacyRandomAccessIterator& other) { return ((static_cast<uint64_t>(it) - static_cast<uint64_t>(other.it)) / sizeof (size_type)); }
		/* Handle integer substraction with const iterator */
		size_type							operator-(const LegacyRandomAccessIterator& other) { return (static_cast<uint64_t>(it) - static_cast<uint64_t>(other.it) / sizeof (size_type)); }
		/* Handle self addition */
		LegacyRandomAccessIterator			operator+=(difference_type n) { it += n; return (*this); }
		/* Handle self substraction */
		LegacyRandomAccessIterator			operator-=(difference_type n) { it -= n; return (*this); }
		/* Handle post-incrementation */
		LegacyRandomAccessIterator			operator++(int) { LegacyRandomAccessIterator aux(it); operator++(); return (aux); }
		/* Handle pre-incrementation */
		LegacyRandomAccessIterator&			operator++() { it++; return (*this); }
		/* Handle post-decrementation */
		LegacyRandomAccessIterator			operator--(int) { LegacyRandomAccessIterator aux(it); operator--(); return (aux); }
		/* Handle pre-decrementation */
		LegacyRandomAccessIterator&			operator--() { it--; return (*this); }
		/* Handle self dereference by pointer */
		reference							operator*() { if (!it) throw::std::out_of_range(std::string("Error: Out of bounds.")); return (*it); }
		const_reference						operator*() const { if (!it) throw::std::out_of_range(std::string("Error: Out of bounds.")); return (*it); }
		/* Handle pointing to self methods */
		pointer								operator->() { return (it); }
		const_pointer						operator->() const { return (it); }
		/* Handle self dereference by squared brackets */
		reference							operator[](difference_type pos) { return (it + pos); }
		const_reference						operator[](difference_type pos) const { return (it + pos); }
		/* Handle boolean equity */
		//template <class It1, class It2>
		//bool								operator==(const LegacyRandomAccessIterator<It1>& lhs, const LegacyRandomAccessIterator<It2>& rhs) { return (lhs.it == rhs.it); }
		/* Handle boolean inequity */
		//template <class It1, class It2>
		//bool								operator!=(const LegacyRandomAccessIterator<It1>& lhs, const LegacyRandomAccessIterator<It2>& rhs) { return (lhs.it != rhs.it); }
		/* Handle boolean leeser */
		//template <class It1, class It2>
		//bool								operator<(const LegacyRandomAccessIterator<It1>& lhs, const LegacyRandomAccessIterator<It2>& rhs) { return (lhs.it < rhs.it); }
		/* Handle boolean leeser equity */
		//template <class It1, class It2>
		//bool								operator<=(const LegacyRandomAccessIterator<It1>& lhs, const LegacyRandomAccessIterator<It2>& rhs) { return (lhs.it <= rhs.it); }
		/* Hanlde boolean greather */
		//template <class It1, class It2>
		//bool								operator>(const LegacyRandomAccessIterator<It1>& lhs, const LegacyRandomAccessIterator<It2>& rhs) { return (lhs.it > rhs.it); }
		/* Handle boolean greather equity */
		//template <class It1, class It2>
		//bool								operator>=(const LegacyRandomAccessIterator<It1>& lhs, const LegacyRandomAccessIterator<It2>& rhs) { return (lhs.it >= rhs.it); }

		bool								operator==(const LegacyRandomAccessIterator& other) { return (it == other.it); }
		/* Handle boolean inequity */
		bool								operator!=( const LegacyRandomAccessIterator& other) { return (it != other.it); }
		/* Handle boolean leeser */
		bool								operator<(const LegacyRandomAccessIterator& other) { return (it < other.it); }
		/* Handle boolean leeser equity */
		bool								operator<=(const LegacyRandomAccessIterator& other) { return (it <= other.it); }
		/* Hanlde boolean greather */
		bool								operator>(const LegacyRandomAccessIterator& other) { return (it > other.it); }
		/* Handle boolean greather equity */
		bool								operator>=(const LegacyRandomAccessIterator& other) { return (it >= other.it); }
	};

};