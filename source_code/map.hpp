
/** @file map.hpp
 * 
 * 	This file contains the implementation of @c map container.
*/

# pragma once

# include <ft_rbtree.hpp>
# include <functional>

namespace FT_NAMESPACE
{
	/**
	 * 	@brief map
	 * 
	 * 	TO DO
	*/
	template <typename Key, typename T, typename Compare = std::less<Key>,
	typename Alloc = allocator<std::pair<const Key, T>>>
	class map
	{
		/* Member types */

		public:

		typedef Key							key_type;
		typedef T							mapped_type;
		typedef std::pair<const Key, T>		value_type;
		typedef Compare						key_compare;
		typedef Alloc						allocator_type;

		/* value compare class, used for comparison */
		struct value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map<key_type, value_type, key_compare, allocator_type>;

			protected:

			key_compare comp;

			value_compare(key_compare c) : comp(c) { }

			public:

			value_compare()

			operator()(const_reference lhs, const_reference rhs)
			{ return (comp(lhs.first, rhs.first)); }
		};

		private:

		typedef RedBlackTree<key_type, value_type, value_type, key_compare, allocator_type>	Tree;
		// TO DO: 3rd template arg is wrong

		Tree	tree;

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

		map();
		map(const key_compare& comp, const allocator_type& alloc);
		template <typename InputIt>
		map(InputIt first, InputIt last);
		template <typename InputIt>
		map(InputIt first, InputIt last, const key_compare& comp, const allocator_type& alloc = allocator_type());
		map(const map& other);
		map&					operator=(const map& other);

		/* Element access */
		mapped_type& 			operator[](const key_type& k);
		// TO DO: only 1 operator[] signature ?
		mapped_type& 			at(const key_type& k); // C++11
		const mapped_type& 		at(const key_type& k) const; // C++11

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

		/* Modifiers */
		void					clear() const;
		std::pair<iterator, bool>	insert(const_reference pair);
		iterator				insert(iterator pos, const_reference pair);
		template <typename InputIt>
		void					insert(InputIt first, InputIt last);
		void 					erase(iterator pos);
		size_type				erase(const key_type& k);
		void					erase(iterator first, iterator last);
		void					swap(const map& other);

		/* Lookup */
		iterator				find(const key_type& k);
		// TO DO: add count
		std::pair<iterator, iterator>	equal_range(const key_type& k);
		iterator				lower_bound(const key_type& k);
		const_iterator			lower_bound(const key_type& k) const;
		iterator				upper_bound(const key_type& k);
		const_iterator			upper_bound(const key_type& k) const;

		/* Observers */
		key_compare				key_comp() const;
		value_compare			value_comp() const;

		/* Non-members */
		template <typename K1, typename T1, typename C1, typename A1>
		friend bool	operator==(const map<K1, T1, C1, A1>& lhs, const map>K1, T1, C1, A1>& rhs);
		template <typename K1, typename T1, typename C1, typename A1>
		friend bool	operator<(const map<K1, T1, C1, A1>& lhs, const map>K1, T1, C1, A1>& rhs);
	};

	/**
	 * 	@brief Default Constructor
	*/
	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::map()
	: tree()
	{ }

	/**
	 * 	@brief Constructor
	 * 
	 * 	@param comp A comparison object.
	 *  @param alloc An allocator.
	*/
	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::map(const key_compare& comp, const allocator_type& alloc)
	: tree(comp, alloc) { }

	/**
	 * 	@brief Range Constructor
	 * 
	 * 	@tparam InputIt An input iterator.
	 * 	@param first An InputIt.
	 * 	@param last An InputIt.
	 * 
	 * 	Create a map filled with copies of @p first - @p last range.
	*/
	template <class Key, class T, class Compare, class Alloc>
	template <typename InputIt>
	map<Key, T, Compare, Alloc>::map(InputIt first, InputIt last)
	: tree()
	{ tree.aux_insert_range_unique(first, last); }

	/**
	 * 	@brief Range Comp Constructor.
	 * 
	 * 	@tparam InputIt An input iterator.
	 * 	@param first An InputIt.
	 * 	@param last An InputIt.
	 * 	@param comp A comparison object.
	 * 	@param alloc An allocator.
	 *
	 * 	Create a map filled with copies of @p first - @p last range.
	 * 	NOTE: The map is sorted with @p comp.
	*/
	template <class Key, class T, class Compare, class Alloc>
	template <typename InputIt>
	map<Key, T, Compare, Alloc>::map(InputIt first, InputIt last, const key_compare& comp, const allocator_type& alloc = allocator_type())
	: tree(comp, alloc)
	{ tree.aux_insert_range_unique(first, last); }

	/**
	 * 	@brief Copy Constructor
	 * 
	 * 	@param other A %map of the same type of @c *this.
	*/
	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::map(const map& other)
	: tree(other.tree)
	{ }

	/**
	 * 	@brief operator=
	 * 
	 * 	@param other A %map with the same type of @c *this.
	*/
	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>&
	map<Key, T, Compare, Alloc>::operator=(const map& other)
	{
		tree = other.tree;
		return (*this);
	}

	////////////////////
	// Element access //
	////////////////////

	/**
	 * 	@brief operator[]
	 * 	
	 * 	@param k A key search.
	 * 
	 * 	Return a reference to the pair value in @p k
	 * 	in it exist and can perform an insertion.
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::mapped_type& 
	map<Key, T, Compare, Alloc>::operator[](const key_type& k)
	{
		iterator i = lower_bound(k);

		// If i->first >= k or i is the last insert it and return the inserted data.
		if (i == end() || key_comp()(k, (*i).first))
			i = insert(i, value_type(k, mapped_type()));
		return ((*i).second);
	}

	/**
	 * 	@brief at
	 * 	
	 * 	@param k A key search.
	 * 
	 * 	Return a reference to the value in @p k
	 * 	in it exist and can perform an insertion.
	 *  @throw std::out_of_range
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::mapped_type&
	map<Key, T, Compare, Alloc>::at(const key_type& k)
	{
		iterator i = lower_bound(k);
		if (i == end() || key_comp()(k, (*i).first))
			throw std::out_of_range(std::string("map::at"));
		return ((*i).second);
	}

	/**
	 * 	@brief at
	 * 	
	 * 	@param k A key search.
	 * 
	 * 	Return a const reference to the value in @p k
	 * 	in it exist and can perform an insertion.
	 *  @throw std::out_of_range
	*/
	template <class Key, class T, class Compare, class Alloc>
	const typename map<Key, T, Compare, Alloc>::mapped_type&
	map<Key, T, Compare, Alloc>::at(const key_type& k) const
	{
		iterator i = lower_bound(k);
		if (i == end() || key_comp()(k, (*i).first))
			throw std::out_of_range(std::string("map::at"));
		return ((*i).second);
	}

	///////////////
	// Iterators //
	///////////////

	/**
	 * 	@brief begin
	 * 
	 * 	@return An iterator to the first element holded by %map.
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator
	map<Key, T, Compare, Alloc>::begin()
	{ return (tree.begin()); }

	/**
	 * 	@brief begin
	 * 
	 * 	@return A const iterator to the first element holded by %map.
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator
	map<Key, T, Compare, Alloc>::begin() const
	{ return (tree.begin()); }

	/**
	 * 	@brief end
	 * 
	 * 	@return An iterator to the last element holded by %map.
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator
	map<Key, T, Compare, Alloc>::end()
	{ return (tree.end()); }

	/**
	 * 	@brief end
	 * 
	 * 	@return A const iterator to the last element holded by %map.
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator
	map<Key, T, Compare, Alloc>::end() const
	{ return (tree.end()); }

	/**
	 * 	@brief rbegin
	 * 
	 * 	@return A reverse iterator to the first element holded by %map.
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::reverse_iterator
	map<Key, T, Compare, Alloc>::rbegin()
	{ return (tree.begin()); }

	/**
	 * 	@brief rbegin
	 * 
	 * 	@return A const reverse iterator to the first element holded by %map.
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_reverse_iterator
	map<Key, T, Compare, Alloc>::rbegin() const
	{ return (tree.rbegin()); }

	/**
	 * 	@brief rend
	 * 
	 * 	@return A reverse iterator to the last element holded by %map.
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::reverse_iterator
	map<Key, T, Compare, Alloc>::rend()
	{ return (tree.rend()); }

	/**
	 * 	@brief rend
	 * 
	 * 	@return A const reverse iterator to the last element holded by %map.
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_reverse_iterator
	map<Key, T, Compare, Alloc>::rend() const
	{ return (tree.rend()); }

	//////////////
	// Capacity //
	//////////////

	/**
	 * 	@brief empty
	 * 
	 * 	@return True if the %map is empty.
	*/
	template <class Key, class T, class Compare, class Alloc>
	bool
	map<Key, T, Compare, Alloc>::empty() const
	{ return (tree.empty()); }

	/**
	 * 	@brief size
	 * 
	 * 	@return The size of %map.
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type
	map<Key, T, Compare, Alloc>::size() const
	{ return (tree.size()); }

	/**
	 * 	@brief max size
	 * 
	 * 	@return The maximum amount of T elements %map can hold.
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type
	map<Key, T, Compare, Alloc>::max_size() const
	{ return (tree.max_size()); }

	///////////////
	// Modifiers //
	///////////////

	/**
	 * 	@brief clear
	 * 
	 * 	Empty the %map.
	*/
	template <class Key, class T, class Compare, class Alloc>
	void
	map<Key, T, Compare, Alloc>::clear() const
	{ tree.clear(); }

	/**
	 * 	@brief insert
	 * 
	 * 	@param pair A value pair.
	 * 
	 * 	Attemps to insert @p pair into the %map.
	*/
	template <class Key, class T, class Compare, class Alloc>
	std::pair<typename map<Key, T, Compare, Alloc>::iterator, bool>
	map<Key, T, Compare, Alloc>::insert(const_reference pair)
	{ return (tree.aux_insert_unique(pair)); }

	/**
	 * 	@brief insert
	 * 
	 * 	@param pos An iterator.
	 * 	@param pair A value pair.
	 * 	@return An iterator to the inserted value.
	 * 
	 * 	Attemps to insert @p pair into %map at @p pos index.
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator
	map<Key, T, Compare, Alloc>::insert(iterator pos, const_reference pair)
	{ return (tree.aux_insert_unique(pos, pair)); }

	/**
	 * 	@brief insert
	 * 
	 * 	@tparam A InputIt an input iterator.
	 * 	@param first An InputIt.
	 * 	@param last An InputIt.
	 * 
	 * 	Attemps to insert data in range @p first - @p last data into @c *this.
	*/
	template <class Key, class T, class Compare, class Alloc>
	template <typename InputIt>
	void
	map<Key, T, Compare, Alloc>::insert(InputIt first, InputIt last)
	{ tree.aux_insert_range_unique(first, last); }

	/**
	 * 	@brief erase
	 * 
	 * 	@param pos The index.
	 * 
	 * 	Removes the node at @p pos index.
	*/
	template <class Key, class T, class Compare, class Alloc>
	void
	map<Key, T, Compare, Alloc>::erase(iterator pos)
	{ tree.erase(pos); }

	/**
	 * 	@brief erase
	 * 
	 * 	@param k The key to the element to be erased.
	 * 
	 * 	@return The index of the erased element.
	 * 
	 * 	Removes to element maching with @p k key.
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type
	map<Key, T, Compare, Alloc>::erase(const key_type& k)
	{ return (tree.erase(k)); }

	/**
	 * 	@brief erase
	 * 
	 * 	@param first An iterator.
	 * 	@param last An iterator.
	 * 
	 * 	Removes the nodes in range @p first - @p last.
	*/
	template <class Key, class T, class Compare, class Alloc>
	void
	map<Key, T, Compare, Alloc>::erase(iterator first, iterator last)
	{ return (tree.erase(first, last)); }

	/**
	 * 	@brief swap
	 * 
	 * 	@param other A %map with the same type of @c *this.
	*/
	template <class Key, class T, class Compare, class Alloc>
	void
	map<Key, T, Compare, Alloc>::swap(const map& other)
	{ tree.swap(other.tree); }

	////////////
	// Lookup //
	////////////

	/**
	 * 	@brief find
	 * 
	 * 	@param k The key of the pair to find.
	 * 
	 * 	@return An iterator pointing to the pair maching with @p k key.
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator
	map<Key, T, Compare, Alloc>::find(const key_type& k)
	{ return (tree.find(k)); }

	/**
	 * 	@brief equal_range
	 * 
	 * 	@param k A key.
	 * 
	 * 	@return A pair of iterators pointing to the maching @p k value.
	*/
	template <class Key, class T, class Compare, class Alloc>
	std::pair<typename map<Key, T, Compare, Alloc>::iterator, typename map<Key, T, Compare, Alloc>::iterator>
	map<Key, T, Compare, Alloc>::equal_range(const key_type& k)
	{ return (tree.equal_range(k)); }

	/**
	 * 	@brief lower_bound
	 * 
	 * 	@param k A key.
	 * 
	 * 	@return An iterator pointing to the first element of the subsequece
	 * 	maching with the @p k key.
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator
	map<Key, T, Compare, Alloc>::lower_bound(const key_type& k)
	{ return (tree.lower_bound(k)); }

	/**
	 * 	@brief lower_bound
	 * 
	 * 	@param k A key.
	 * 
	 * 	@return A const iterator pointing to the first element of the subsequece
	 * 	maching with the @p k key.
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator
	map<Key, T, Compare, Alloc>::lower_bound(const key_type& k) const
	{ return (tree.lower_bound(k)); }

	/**
	 * 	@brief upper_bound
	 * 
	 * 	@param k A key.
	 * 
	 * 	@return An iterator pointing to the last element of the subsequece
	 * 	maching with the @p k key.
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator
	map<Key, T, Compare, Alloc>::upper_bound(const key_type& k)
	{ return (tree.upper_bound(k)); }

	/**
	 * 	@brief upper_bound
	 * 
	 * 	@param k A key.
	 * 
	 * 	@return A const iterator pointing to the last element of the subsequece
	 * 	maching with the @p k key.
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator
	map<Key, T, Compare, Alloc>::upper_bound(const key_type& k) const
	{ return (tree.upper_bound(k)); }

	///////////////
	// Observers //
	///////////////

	/**
	 * 	@brief key comp
	 * 
	 * 	@return The comparison key object holded by @c *this.
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::key_compare
	map<Key, T, Compare, Alloc>::key_comp() const
	{ return (tree.key_comp()); }

	/**
	 * 	@brief value_comp
	 * 
	 * 	@return The value comparison object.
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::value_compare
	map<Key, T, Compare, Alloc>::value_comp() const
	{ return (value_compare(tree.key_comp())); }

	/////////////////
	// Non members //
	/////////////////

	//@{
	/**
	 * 	@brief Boolean comparison
	 * 
	 * 	@param lhs A %map
	 * 	@param rhs A %map of the same type of @p lhs.
	 * 	@return The boolean result of the requiested operation.
	*/
	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool
	operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return (lhs.tree == rhs.tree); }

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool
	operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return (lhs.tree < rhs.tree); }

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool
	operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return (lhs.tree != rhs.tree); }

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool
	operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return (lhs.tree > rhs.tree); }

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool
	operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return (lhs.tree <= rhs.tree); }

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool
	operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return (lhs.tree >= rhs.tree); }
	//@}

	/**
	 * 	@brief swap
	 * 
	 * 	@param lhs A map.
	 * 	@param rhs A map.
	 * 
	 * 	Specilisated version of swap made for %map objects.
	*/
	template <typename Key, typename T, typename Compare, typename Alloc>
	void
	swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs)
	{ lhs.swap(rhs); }
};
