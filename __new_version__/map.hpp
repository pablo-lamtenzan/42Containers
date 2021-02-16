
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
	typename Alloc = allocator<std::pair<const Key, T>>
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

		/**
		 * 	@brief Default Constructor
		*/
		map() : tree() { }

		/**
		 * 	@brief Constructor
		 * 
		 * 	@param comp A comparison object.
		 *  @param alloc An allocator.
		*/
		map(const key_compare& comp, const allocator_type& alloc)
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
		template <typename InputIt>
		map(InputIt first, InputIt last) : tree()
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
		template <typename InputIt>
		map(InputIt first, InputIt last, const key_compare& comp, const allocator_type& alloc = allocator_type())
		: tree(comp, alloc)
		{ tree.aux_insert_range_unique(first, last); }

		/**
		 * 	@brief Copy Constructor
		 * 
		 * 	@param other A %map of the same type of @c *this.
		*/
		map(const map& other) : tree(other.tree) { }

		/**
		 * 	@brief operator=
		 * 
		 * 	@param other A %map with the same type of @c *this.
		*/
		map&			operator=(const map& other)
		{
			tree = other.tree;
			return (*this);
		}

		/**
		 * 	@brief begin
		 * 
		 * 	@return An iterator to the first element holded by %map.
		*/
		iterator		begin()
		{
			return (tree.begin());
		}

		/**
		 * 	@brief begin
		 * 
		 * 	@return A const iterator to the first element holded by %map.
		*/
		const_iterator	begin() const
		{
			return (tree.begin());
		}

		/**
		 * 	@brief end
		 * 
		 * 	@return An iterator to the last element holded by %map.
		*/
		iterator		end()
		{
			return (tree.end());
		}

		/**
		 * 	@brief end
		 * 
		 * 	@return A const iterator to the last element holded by %map.
		*/
		const_iterator	end() const
		{
			return (tree.end());
		}

		/**
		 * 	@brief rbegin
		 * 
		 * 	@return A reverse iterator to the first element holded by %map.
		*/
		iterator		rbegin()
		{
			return (tree.begin());
		}

		/**
		 * 	@brief bregin
		 * 
		 * 	@return A const reverse iterator to the first element holded by %map.
		*/
		const_iterator	rbegin() const
		{
			return (tree.rbegin());
		}

		/**
		 * 	@brief rend
		 * 
		 * 	@return A reverse iterator to the last element holded by %map.
		*/
		iterator		rend()
		{
			return (tree.rend());
		}

		/**
		 * 	@brief end
		 * 
		 * 	@return A const reverse iterator to the last element holded by %map.
		*/
		const_iterator	rend() const
		{
			return (tree.rend());
		}

		/**
		 * 	@brief empty
		 * 
		 * 	@return True if the %map is empty.
		*/
		bool			empty() const
		{
			return (tree.empty());
		}

		/**
		 * 	@brief size
		 * 
		 * 	@return The size of %map.
		*/
		size_type		size() const
		{
			return (tree.size());
		}

		/**
		 * 	@brief max size
		 * 
		 * 	@return The maximum amount of T elements %map can hold.
		*/
		size_type		max_size() const
		{
			return (tree.max_size());
		}

		/**
		 * 	@brief operator[]
		 * 	
		 * 	@param k A key search.
		 * 
		 * 	Return a reference to the pair value in @p k
		 * 	in it exist and can perform an insertion.
		*/
		mapped_type& 	operator[](const key_type& k)
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
		mapped_type& 	at(const key_type& k)
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
		const mapped_type& 	at(const key_type& k)
		{
			iterator i = lower_bound(k);
			if (i == end() || key_comp()(k, (*i).first))
				throw std::out_of_range(std::string("map::at"));
			return ((*i).second);
		}

		/**
		 * 	@brief insert
		 * 
		 * 	@param pair A value pair.
		 * 
		 * 	Attemps to insert @p pair into the %map.
		*/
		std::pair<iterator, bool>	insert(const_reference pair)
		{
			return (tree.aux_insert_unique(pair));
		}

		/**
		 * 	@brief insert
		 * 
		 * 	@param pos An iterator.
		 * 	@param pair A value pair.
		 * 	@return An iterator to the inserted value.
		 * 
		 * 	Attemps to insert @p pair into %map at @p pos index.
		*/
		iterator		insert(iterator pos, const_reference pair)
		{
			return (tree.aux_insert_unique(pos, pair));
		}

		/**
		 * 	@brief insert
		 * 
		 * 	@tparam A InputIt an input iterator.
		 * 	@param first An InputIt.
		 * 	@param last An InputIt.
		 * 
		 * 	Attemps to insert data in range @p first - @p last data into @c *this.
		*/
		template <typename InputIt>
		void			insert(InputIt first, InputIt last)
		{
			tree.aux_insert_range_unique(first, last);
		}

		/**
		 * 	@brief erase
		 * 
		 * 	@param pos The index.
		 * 
		 * 	Removes the node at @p pos index.
		*/
		void 			erase(iterator pos)
		{
			tree.erase(pos);
		}

		/**
		 * 	@brief erase
		 * 
		 * 	@param k The key to the element to be erased.
		 * 
		 * 	@return The index of the erased element.
		 * 
		 * 	Removes to element maching with @p k key.
		*/
		size_type		erase(const key_type& k)
		{
			return (tree.erase(k));
		}

		/**
		 * 	@brief erase
		 * 
		 * 	@param first An iterator.
		 * 	@param last An iterator.
		 * 
		 * 	Removes the nodes in range @p first - @p last.
		*/
		void			erase(iterator first, iterator last)
		{
			return (tree.erase(first, last));
		}

		/**
		 * 	@brief swap
		 * 
		 * 	@param other A %map with the same type of @c *this.
		*/
		void			swap(const map& other)
		{
			tree.swap(other.tree);
		}

		/**
		 * 	@brief clear
		 * 
		 * 	Empty the %map.
		*/
		void			clear() const
		{
			tree.clear();
		}

		/**
		 * 	@brief key comp
		 * 
		 * 	@return The comparison key object holded by @c *this.
		*/
		key_compare		key_comp() const
		{
			return (tree.key_comp());
		}

		/**
		 * 	@brief value_comp
		 * 
		 * 	@return The value comparison object.
		*/
		value_compare	value_comp() const
		{
			return (value_compare(tree.key_comp()));
		}

		/**
		 * 	@brief find
		 * 
		 * 	@param k The key of the pair to find.
		 * 
		 * 	@return An iterator pointing to the pair maching with @p k key.
		*/
		iterator		find(const key_type& k)
		{
			return (tree.find(k));
		}

		/**
		 * 	@brief lower_bound
		 * 
		 * 	@param k A key.
		 * 
		 * 	@return An iterator pointing to the first element of the subsequece
		 * 	maching with the @p k key.
		*/
		iterator		lower_bound(const key_type& k)
		{
			return (tree.lower_bound(k));
		}

		/**
		 * 	@brief lower_bound
		 * 
		 * 	@param k A key.
		 * 
		 * 	@return A const iterator pointing to the first element of the subsequece
		 * 	maching with the @p k key.
		*/
		const_iterator	lower_bound(const key_type& k)
		{
			return (tree.lower_bound(k));
		}

		/**
		 * 	@brief upper_bound
		 * 
		 * 	@param k A key.
		 * 
		 * 	@return An iterator pointing to the last element of the subsequece
		 * 	maching with the @p k key.
		*/
		iterator		upper_bound(const key_type& k)
		{
			return (tree.upper_bound(k));
		}

		/**
		 * 	@brief upper_bound
		 * 
		 * 	@param k A key.
		 * 
		 * 	@return A const iterator pointing to the last element of the subsequece
		 * 	maching with the @p k key.
		*/
		const_iterator		upper_bound(const key_type& k)
		{
			return (tree.upper_bound(k));
		}

		/**
		 * 	@brief equal_range
		 * 
		 * 	@param k A key.
		 * 
		 * 	@return A pair of iterators pointing to the maching @p k value.
		*/
		std::pair<iterator, iterator>	equal_range(const key_type& k)
		{
			return (tree.equal_range(k));
		}

		template <typename K1, typename T1, typename C1, typename A1>
		friend bool	operator==(const map<K1, T1, C1, A1>& lhs, const map>K1, T1, C1, A1>& rhs);

		template <typename K1, typename T1, typename C1, typename A1>
		friend bool	operator<(const map<K1, T1, C1, A1>& lhs, const map>K1, T1, C1, A1>& rhs);
	};

	//@{
	/**
	 * 	@brief Boolean comparison
	 * 
	 * 	@param lhs A %map
	 * 	@param rhs A %map of the same type of @p lhs.
	 * 	@return The boolean result of the requiested operation.
	*/
	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool	operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (lhs.tree == rhs.tree);
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool	operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (lhs.tree < rhs.tree);
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool	operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (lhs.tree != rhs.tree);
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool	operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (lhs.tree > rhs.tree);
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool	operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (lhs.tree <= rhs.tree);
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool	operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (lhs.tree >= rhs.tree);
	}
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
	void		swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
};
