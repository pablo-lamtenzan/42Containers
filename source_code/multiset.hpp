/** @file multiset.hpp
 * 
 * 	This file contains the implementation of @c multiset conatiner.
*/

# pragma once

# include <ft_rbtree.hpp>
# include <ft_allocator.hpp>

namespace FT_NAMESPACE
{
	/** @brief multiset
	 * 
	 * 	@tparam Key The type of the key object.
	 * 	@tparam Compare A comparision object.
	 * 	@tparam Alloc An allocator.
	 * 
	 * 	Supports bidirectional iterators.
	*/
	template <typename Key, typename Compare, typename Alloc = allocator<Key>>
	// TO DO Compare is init by default
	class multiset
	{
		/* Member types */

		public:

		typedef Key			key_type;
		typedef Key			value_type;
		typedef Compare		key_compare;
		typedef Compare		value_compare;
		typedef Alloc		allocator_type;

		/* Core */

		private:

		typedef RedBlackTree<key_type, value_type, value_type, key_compare, allocator_type> Tree;
		// TO DO: 3rd tempalte arg is incomplete
		Tree tree;

		/* Imported member types */

		public:

		typedef typename Tree::reference		reference;
		typedef typename Tree::const_reference	const_reference;
		typedef typename Tree::pointer			pointer;
		typedef typename Tree::const_pointer	const_pointer;
		typedef typename Tree::size_type		size_type;
		typedef typename Tree::difference_type	difference_type;

		typedef typename Tree::iterator			iterator;
		typedef typename Tree::const_iterator	const_iterator;

		typedef typename Tree::reverse_iterator			reverse_iterator;
		typedef typename Tree::const_reverse_iterator	const_reverse_iterator;

		/* Member functions */

		multiset();
		multiset(const Compare& cmp, const allocator_type& alloc = allocator_type());
		template <typename InputIt>
		multiset(InputIt first, InputIt last);
		template <typename InputIt>
		multiset(InputIt first, InputIt last, const value_compare& cmp, const allocator_type& alloc = allocator_type());
		multiset(const multiset& other);

		multiset&		operator=(const multiset& other);

		/* Iterators */
		iterator		begin() const;
		iterator 		end() const;
		iterator		rbegin() const;
		iterator 		rend() const;

		/* Capacity */
		bool			empty() const;
		size_type		size() const;
		size_type		max_size() const;

		/* Modifiers */
		void			clear() const;
		::std::pair<iterator, bool>	insert(const_reference& value);
		iterator		insert(const_iterator position, const_reference value);
		template <typename InputIt>
		iterator		insert(InputIt first, InputIt last);
		iterator		erase(iterator position);
		size_type		erase(const key_type& k);
		void			erase(iterator first, iterator last);
		void			swap(const multiset& other);

		/* Lookup */
		size_type		count(const key_type& k) const;
		iterator		find(const key_type& k);
		const_iterator	find(const key_type& k) const;
		::std::pair<iterator, iterator>	equal_range(const key_type& k);
		::std::pair<const_iterator, const_iterator>	equal_range(const key_type& k) const;
		iterator		lower_bound(const key_type& k);
		const_iterator	lower_bound(const key_type& k) const;
		iterator		upper_bound(const key_type& k);
		const_iterator	upper_bound(const key_type& k) const;

		/* Observers */
		key_compare		key_comp() const;
		key_compare		value_comp() const;

		/* Non members */
		template <typename <K1, typename C1, typename A1>
		friend bool operator==(const multiset<K1, C1, A1>& lhs, const multiset<K1, C1, A1>& rhs);
		template <typename <K1, typename C1, typename A1>
		friend bool operator<(const multiset<K1, C1, A1>& lhs, const multiset<K1, C1, A1>& rhs);
	};

	/** 
	 * @brief Default Constructor
	*/
	template <class Key, class Compare, class Alloc>
	multiset<Key, Compare, Alloc>::multiset()
	: tree() 
	{ }

	/**
	 * 	@brief Size Constructor
	 * 
	 * 	@param cmp A comparator.
	 * 	@param alloc An allocator.
	 * 
	 * 	Create a %multiset with no elements.
	*/
	template <class Key, class Compare, class Alloc>
	multiset<Key, Compare, Alloc>::multiset(const Compare& cmp, const allocator_type& alloc)
	: tree(cmp, alloc)
	{ }

	/**
	 * 	@brief Range Constructor
	 * 
	 * 	@tparam InputIt An input iterator.
	 * 	@param first An InputIt.
	 * 	@param last An InputIt.
	 * 
	 * 	Create a %multiset that holds copies of elemets that are in
	 * 	range @p first - @p last.
	*/
	template <class Key, class Compare, class Alloc>
	template <typename InputIt>
	multiset<Key, Compare, Alloc>::multiset(InputIt first, InputIt last)
	: tree()
	{ tree.aux_insert_range_unique(first, last); }

	/**
	 * 	@brief Range Comparison Constructor
	 * 
	 * 	@tparam InputIt An input iterator.
	 * 	@param first An InputIt.
	 * 	@param last An InputIt.
	 * 	@param cmp A comparison object.
	 * 	@param alloc An allocator object.
	 * 
	 * 	Create a %multiset that holds copies of elemets that are in
	 * 	range @p first - @p last.
	*/
	template <class Key, class Compare, class Alloc>
	template <typename InputIt>
	multiset<Key, Compare, Alloc>::multiset(InputIt first, InputIt last, const value_compare& cmp, const allocator_type& alloc)
	: tree(cmp, alloc)
	{ tree.aux_insert_range_unique(first, last); }

	/**
	 * 	@brief Copy Constructor
	 * 
	 * 	@param other A %multiset.
	*/
	template <class Key, class Compare, class Alloc>
	multiset<Key, Compare, Alloc>::multiset(const multiset& other)
	: tree(other.tree)
	{ }

	/**
	 * 	@brief operator=
	 * 
	 * 	@param other A %multiset.
	 * 	@return @c *this.
	 * 
	 * 	Perform a deep copy if @p other into @c *this.
	*/
	template <class Key, class Compare, class Alloc>
	inline multiset<Key, Compare, Alloc>&
	multiset<Key, Compare, Alloc>::operator=(const multiset& other)
	{
		tree = other.tree;
		return (*this);
	}

	///////////////
	// Iterators //
	///////////////

	/**
	 * 	@brief begin
	 * 
	 * 	@return An iterator pointing to the first element of @c *this.
	*/
	template <class Key, class Compare, class Alloc>
	inline typename multiset<Key, Compare, Alloc>::iterator
	multiset<Key, Compare, Alloc>::begin() const 
	{ return (tree.begin()); }

	/**
	 * 	@brief end
	 * 
	 * 	@return An iterator pointing to the last element of @c *this.
	*/
	template <class Key, class Compare, class Alloc>
	inline typename multiset<Key, Compare, Alloc>::iterator
	multiset<Key, Compare, Alloc>::end() const
	{ return (tree.end()); }

	/**
	 * 	@brief rbegin
	 * 
	 * 	@return A revese iterator pointing to the first element of @c *this.
	*/
	template <class Key, class Compare, class Alloc>
	inline typename multiset<Key, Compare, Alloc>::iterator
	multiset<Key, Compare, Alloc>::rbegin() const 
	{ return (tree.rbegin()); }

	/**
	 * 	@brief rend
	 * 
	 * 	@return An iterator pointing to the last element of @c *this.
	*/
	template <class Key, class Compare, class Alloc>
	inline typename multiset<Key, Compare, Alloc>::iterator
	multiset<Key, Compare, Alloc>::rend() const
	{ return (tree.rend()); }

	//////////////
	// Capacity //
	//////////////

	/**
	 * 	@brief empty
	 * 
	 * 	@return True if the %multiset is empty.
	*/
	template <class Key, class Compare, class Alloc>
	inline bool
	multiset<Key, Compare, Alloc>::empty() const
	{ return (tree.empty()); }

	/**
	 * 	@brief size
	 * 
	 * 	@return The size of the %multiset.
	*/
	template <class Key, class Compare, class Alloc>
	inline typename multiset<Key, Compare, Alloc>::size_type
	multiset<Key, Compare, Alloc>::size() const
	{ return (tree.size()); }

	/**
	 * 	@brief max size
	 * 
	 * 	@return The maximum number of element type Key that @c *this can hold.
	*/
	template <class Key, class Compare, class Alloc>
	inline typename multiset<Key, Compare, Alloc>::size_type
	multiset<Key, Compare, Alloc>::max_size() const
	{ return (tree.max_size()); }

	///////////////
	// Modifiers //
	///////////////

	/**
	 * 	@brief clear
	 * 
	 * 	Empty @c *this.
	*/
	template <class Key, class Compare, class Alloc>
	inline void
	multiset<Key, Compare, Alloc>::clear() const
	{ tree.clear(); }

	/**
	 * 	@brief insert
	 * 
	 * 	@param value The key to be inserted.
	 * 
	 * 	Attemps to insert @p value into the %multiset.
	 * 	If the insertion is not possible the bool in the returned pair is false.
	*/
	template <class Key, class Compare, class Alloc>
	inline ::std::pair<typename multiset<Key, Compare, Alloc>::iterator, bool>
	multiset<Key, Compare, Alloc>::insert(const_reference& value)
	{ return (tree.aux_insert_unique(value)); }

	/**
	 * 	@brief insert
	 * 
	 * 	@param position The index of the insertion.
	 * 	@param value The key to be inserted.
	 * 
	 * 	Attemps to insert @p value ussing position as hint.
	 * 	NOTE: position (if is set correctly) is just to increase the speed execution.
	 * 		This function perform the same operation as insert(const_reference) signature.
	*/
	template <class Key, class Compare, class Alloc>
	inline typename multiset<Key, Compare, Alloc>::iterator
	multiset<Key, Compare, Alloc>::insert(const_iterator position, const_reference value)
	{ return (tree.aux_insert_unique(position, value)); }

	/**
	 * 	@brief insert
	 * 
	 * 	@tparam InputIt A input iterator.
	 * 	@param first A InputIt.
	 * 	@param last A InputIt.
	 * 
	 * 	Attemps to insert a range of elements into @c *this.
	*/
	template <class Key, class Compare, class Alloc>
	template <typename InputIt>
	inline typename multiset<Key, Compare, Alloc>::iterator
	multiset<Key, Compare, Alloc>::insert(InputIt first, InputIt last)
	{ return (tree.aux_insert_range_unique(first, last)); }

	/**
	 * 	@brief erase
	 * 
	 * 	@param position An index in the %multiset.
	 * 
	 * 	@return An iterator to the element that is after the deletion
	 * 		at index @p position.
	 * 
	 * 	Erase the element holded at @p position.
	*/
	template <class Key, class Compare, class Alloc>
	inline typename multiset<Key, Compare, Alloc>::iterator
	multiset<Key, Compare, Alloc>::erase(iterator position)
	{ return (tree.erase(position)); }

	/**
	 * 	@brief erase
	 * 
	 * 	@param k A key.
	 * 	
	 *  @return The amount of erased elements.
	 * 
	 * 	Perform an eresion of all the element matching with the key @p k.
	*/
	template <class Key, class Compare, class Alloc>
	inline typename multiset<Key, Compare, Alloc>::size_type
	multiset<Key, Compare, Alloc>::erase(const key_type& k)
	{ return (tree.erase(k)); }

	/**
	 * 	@brief erase
	 * 
	 * 	@param first An iterator.
	 * 	@param last An iterator.
	 * 
	 * 	Perform an erersion in range @p first - @p last.
	*/
	template <class Key, class Compare, class Alloc>
	inline void
	multiset<Key, Compare, Alloc>::erase(iterator first, iterator last)
	{ tree.erase(first, last); }

	/**
	 * 	@brief swap
	 * 
	 * 	@param other A %multiset.
	 * 
	 * 	Perform a swap between @c *this and @p other.
	*/
	template <class Key, class Compare, class Alloc>
	inline void
	multiset<Key, Compare, Alloc>::swap(const multiset& other)
	{ tree.swap(other.tree); }

	////////////
	// Lookup //
	////////////

	/**
	 * 	@brief count
	 * 
	 * 	@param k A key.
	 * 	
	 * 	@return The amount of element matching with the key @p k.
	 * 	NOTE: This function only makes sense on %multiset. On a %set the result
	 * 		will always be 0 or 1.
	*/
	template <class Key, class Compare, class Alloc>
	inline typename multiset<Key, Compare, Alloc>::size_type
	multiset<Key, Compare, Alloc>::count(const key_type& k) const
	{ return (tree.count(k)); }

	/**
	 * 	@brief find
	 * 
	 * 	@param k A key.
	 * 	@return An iterator pointing to the maching key with @p k.
	*/
	template <class Key, class Compare, class Alloc>
	inline typename multiset<Key, Compare, Alloc>::iterator
	multiset<Key, Compare, Alloc>::find(const key_type& k)
	{ return (tree.find(k)); }

	/**
	 * 	@brief find
	 * 
	 * 	@param k A key.
	 * 	@return An iterator pointing to the maching key with @p k.
	*/
	template <class Key, class Compare, class Alloc>
	inline typename multiset<Key, Compare, Alloc>::const_iterator
	multiset<Key, Compare, Alloc>::find(const key_type& k) const
	{ return (tree.find(k)); }

	/**
	 * 	@brief equal range
	 * 
	 * 	@return A pair of iterators that possibly points to the subsequence
	 * 		that match with the given key @p k.
	*/
	template <class Key, class Compare, class Alloc>
	inline ::std::pair<typename multiset<Key, Compare, Alloc>::iterator, typename multiset<Key, Compare, Alloc>::iterator>
	multiset<Key, Compare, Alloc>::equal_range(const key_type& k)
	{ return (tree.equal_range(k)); }

	/**
	 * 	@brief equal range
	 * 
	 * 	@return A pair of const iterators that possibly points to the subsequence
	 * 		that match with the given key @p k.
	*/
	template <class Key, class Compare, class Alloc>
	inline ::std::pair<typename multiset<Key, Compare, Alloc>::const_iterator, typename multiset<Key, Compare, Alloc>::const_iterator>
	multiset<Key, Compare, Alloc>::equal_range(const key_type& k) const
	{ return (tree.equal_range(k)); }

	/**
	 * 	@brief lower bound
	 * 
	 * 	@return An iterator pointing to the end of a subsequence
	 * 		matching with with the key @p k.
	*/
	template <class Key, class Compare, class Alloc>
	inline typename multiset<Key, Compare, Alloc>::iterator
	multiset<Key, Compare, Alloc>::lower_bound(const key_type& k)
	{ return (tree.lower_bound(k)); }

	/**
	 * 	@brief lower bound
	 * 
	 * 	@return A const iterator pointing to the end of a subsequence
	 * 		matching with with the key @p k.
	*/
	template <class Key, class Compare, class Alloc>
	inline typename multiset<Key, Compare, Alloc>::const_iterator
	multiset<Key, Compare, Alloc>::lower_bound(const key_type& k) const
	{ return (tree.lower_bound(k)); }

	/**
	 * 	@brief lower bound
	 * 
	 * 	@return An iterator pointing to the start of a subsequence
	 * 		matching with with the key @p k.
	*/
	template <class Key, class Compare, class Alloc>
	inline typename multiset<Key, Compare, Alloc>::iterator
	multiset<Key, Compare, Alloc>::upper_bound(const key_type& k)
	{ return (tree.upper_bound(k)); }

	/**
	 * 	@brief lower bound
	 * 
	 * 	@return A const iterator pointing to the start of a subsequence
	 * 		matching with with the key @p k.
	*/
	template <class Key, class Compare, class Alloc>
	inline typename multiset<Key, Compare, Alloc>::const_iterator
	multiset<Key, Compare, Alloc>::upper_bound(const key_type& k) const
	{ return (tree.upper_bound(k)); }

	///////////////
	// Observers //
	///////////////

	/**
	 * 	@brief key comp
	 * 
	 * 	@return The comparison objetc which was used to construct @c *this.
	*/
	template <class Key, class Compare, class Alloc>
	inline typename multiset<Key, Compare, Alloc>::key_compare
	multiset<Key, Compare, Alloc>::key_comp() const
	{ return (tree.key_comp()); }

	/**
	 * 	@brief value comp
	 * 
	 * 	@return The comparison object which was used to construct @c *this.
	*/
	template <class Key, class Compare, class Alloc>
	inline typename multiset<Key, Compare, Alloc>::key_compare
	multiset<Key, Compare, Alloc>::value_comp() const
	{ return (tree.key_comp()); }

	/////////////////
	// Non members //
	/////////////////

	//@{
	/**
	 * 	@brief Boolean operators
	 * 
	 * 	@param lsh A %multiset.
	 * 	@param rhs A %multiset with the same type of @p lhs.
	 * 
	 * 	@return The boolean result of the requested operation.
	*/
	template <typename Key, typename Compare, typename Alloc>
	inline bool
	operator==(const multiset<Key, Compare, Alloc>& lhs, const multiset<Key, Compare, Alloc>& rhs)
	{ return (lhs.tree == rhs.tree); }

	template <typename Key, typename Compare, typename Alloc>
	inline bool
	operator<(const multiset<Key, Compare, Alloc>& lhs, const multiset<Key, Compare, Alloc>& rhs)
	{ return (lhs.tree < rhs.tree); }

	template <typename Key, typename Compare, typename Alloc>
	inline bool
	operator!=(const multiset<Key, Compare, Alloc>& lhs, const multiset<Key, Compare, Alloc>& rhs)
	{ return (!(lhs == rhs)); }

	template <typename Key, typename Compare, typename Alloc>
	inline bool
	operator>(const multiset<Key, Compare, Alloc>& lhs, const multiset<Key, Compare, Alloc>& rhs)
	{ return (rhs < lhs); }

	template <typename Key, typename Compare, typename Alloc>
	inline bool
	operator<=(const multiset<Key, Compare, Alloc>& lhs, const multiset<Key, Compare, Alloc>& rhs)
	{ return (!(lhs > rhs)); }

	template <typename Key, typename Compare, typename Alloc>
	inline bool
	operator>=(const multiset<Key, Compare, Alloc>& lhs, const multiset<Key, Compare, Alloc>& rhs)
	{ return (!(lhs < rhs)); }

	/**
	 * 	@brief swap
	 * 
	 * 	A specilisation of swap made for %multiset.
	*/
	template <typename Key, typename Compare, typename Alloc>
	inline void
	swap(const multiset<Key, Compare, Alloc>& lhs, const multiset<Key, Compare, Alloc>& rhs)
	{ lhs.swap(rhs); }
	//@}
};
