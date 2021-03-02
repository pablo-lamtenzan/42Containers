
/** @file ft_rbtree.hpp
 * 
 * 	This file cointain the implementation of a Red-Black-Tree
 * 	used to implement @c map , @c multimap , @c set and @c multiset containers.
 * 
 * 	Documentation: https://catherine-leung.gitbook.io/data-strutures-and-algorithms/red-black-trees
 * 	Deeper explenation in wikipedia.
 */

/*
TO DO:
 IMPORTANT:
 - aux_insert_and_rebalance(bool left_insertion, Node_Ptr target, Node_Ptr parent, RBT_Base<T>& header) throw();
 - aux_rebalance_for_erase(Const_Node_Ptr target, RBT_Base<T>& header) throw();

 ALL IS DONE EXECT REBALANCING
*/

#pragma once

# include <ft_iterator.hpp>
# include <ft_allocator.hpp>

# include <utility> // std::pair

namespace FT_NAMESPACE
{
	////////////////////
	// Red Black enum //
	////////////////////

	/**
	 * 	@brief Color enum.
	 * 
	 * 	Used to define the color of a branch.
	*/
	enum RBT_Color
	{
		RBT_Red = false,
		RBT_Black = true
	};

	/////////////////////////
	// Red Black tree node //
	/////////////////////////

	/**
	 * 	@brief Node
	 * 
	 * 	@tparam Val The type of the value holded by the node.
	 * 
	 * 	Class used to manage the RBT nodes.
	*/
	template <typename Val>
	struct RBT_Node
	{
		/* Member types */

		typedef Val						value_type;
		typedef value_type*				pointer;
		typedef const pointer			const_pointer;
		typedef RBT_Node*				Node_Ptr;
		typedef const RBT_Node*			Const_Node_Ptr;
		typedef RBT_Node<value_type>*	Link_type;

		/*
		 * CORE:
		 * 
		 * - Color: represent the color of the node.
		 * - Parent: pointer to the previous node.
		 * - Left: pointer to the left child node.
		 * - Right: pointer to the right child node.
		 * - Value: the value holded by the node.
		*/
		RBT_Color	color;
		Node_Ptr	parent;
		Node_Ptr	left;
		Node_Ptr	right;
		Val			value;

		/* Member fucntions */

		inline pointer			Node_get_value_ptr() throw();
		inline const_pointer	Node_get_value_ptr() const throw();
	};

	//@{
	/**
	 * 	@brief Node_get_value_ptr
	 * 
	 * 	@return A pointer to the value holded by the node.
	*/
	template <typename Val>
	typename RBT_Node<Val>::pointer
	RBT_Node<Val>::Node_get_value_ptr()
	throw()
	{ return (std::addressof(value)); }

	template <typename Val>
	typename RBT_Node<Val>::const_pointer
	RBT_Node<Val>::Node_get_value_ptr() const
	throw()
	{ return (std::addressof(value)); }
	//@}

	///////////////////////////
	// Red Black tree header //
	///////////////////////////

	/**
	 * 	@brief RBT_Header
	 * 
	 * 	Helper class to default initialisation of header and count.
	*/
	template <typename T>
	struct RBT_Header
	{
		/* Member types */

		typedef std::size_t			size_type;

		/* Core */

		RBT_Node<T>	header;
		size_type	tree_count;

		/* Member functions */

		RBT_Header();
		inline void Node_reset() throw();
	};

	/**
	 * @brief Constrctor
	*/
	template <typename T>
	RBT_Header<T>::RBT_Header()
	{
		header.color = RBT_Red;
		Node_reset();
	}

	/**
	 * @brief reset
	 * 
	 * Set @c *this to it empty state.
	*/
	template <typename T>
	void
	RBT_Header<T>::Node_reset() throw()
	{
		parent = NULL;
		left = &this;
		right = &this;
		count = 0ul;
	}

	//@{
	/**
	 * 	@brief Maximum, Miminum
	 * 
	 * 	@return The maximun (bottom right) or minimum (bottom left) nodes.
	*/
	template <typename T>
	inline static typename RBT_Header<T>::Node_Ptr
	Node_maximum(typename RBT_Header<T>::Node_Ptr x)
	throw()
	{
		while (x->right)
			x = x->right;
		return (x);
	}

	template <typename T>
	inline static typename RBT_Header<T>::Const_Node_Ptr
	Node_maximum(typename RBT_Header<T>::Const_Node_Ptr x)
	throw()
	{
		while (x->right)
			x = x->right;
		return (x);
	}

	template <typename T>
	inline static typename RBT_Header<T>::Node_Ptr
	Node_minimum(typename RBT_Header<T>::Node_Ptr x)
	throw()
	{
		while (x->left)
			x = x->left;
		return (x);
	}

	template <typename T>
	inline static typename RBT_Header<T>::Const_Node_Ptr
	Node_minimum(typename RBT_Header<T>::Const_Node_Ptr x)
	throw()
	{
		while (x->left)
			x = x->left;
		return (x);
	}
	//@}

	/////////////////
	// Key Compare //
	/////////////////

	/**
	 * 	@brief Key_Compare
	 * 
	 * 	@tparam Key_Comp A condition used to compare.
	 * 
	 * 	Helper class to support comparisions, garantee initialisation of
	 * 	@p Key_Comp
	*/
	template <class Key_Comp>
	struct RBT_Key_Compare
	{
		/* Core */

		Key_Comp	key_compare;

		/* Member functions */

		RBT_Key_Compare();
		RBT_Key_Compare(const Key_Comp& cmp);
	};

	/**
	 * 	@brief Constructor
	*/
	template <class Key_Comp>
	RBT_Key_Compare<Key_Comp>::RBT_Key_Compare()
	: key_compare()
	{ }

	/**
	 * 	@brief Copy constructor
	*/
	template <class Key_Comp>
	RBT_Key_Compare<Key_Comp>::RBT_Key_Compare(const Key_Comp& cmp)
	: key_compare(cmp)
	{ }

	///////////////////////////
	// Increment / Decrement //
	///////////////////////////

	/**
	 * 	@brief increment
	 * 
	 * 	@param x A red black tree node.
	 * 
	 * 	Increments @p x by 1 step.
	*/
	template <typename Val>
	static RBT_Node<Val>*
	aux_increment(RBT_Node<Val>* x)
	throw()
	{
		/* If x in the bottom of the tree */
		if (x->right == 0)
		{
			/* While x is the right child, go up in the tree */
			RBT_Node<Val>* y = x->parent;
			while (x == y->right)
			{
				x = y;
				y = y->parent;
			}
			if (x->right != y)
				x = y;
		}
		else
		{
			/* Go to the bottom of the next branch */
			x = x->right;
			while (x->left)
				x = x->left;
		}
		return (x);
	}

	//@{
	/**
	 * 	@brief Mutable/Const increment signature
	*/
	template <typename Val>
	inline static RBT_Node<Val>*
	RBT_increment(RBT_Node<Val>* x)
	throw()
	{ return (aux_increment(x)); }

	template <typename Val>
	inline static const RBT_Node<Val>*
	RBT_increment(RBT_Node<Val>* x)
	throw()
	{ return (aux_increment(static_cast<RBT_Node<Val>*>(x))); }
	//@}

	/**
	 * 	@brief decrement
	 * 
	 * 	@param x A red black tree node.
	 * 
	 * 	Decrement @p x by 1 step.
	*/
	template <typename Val>
	static RBT_Node<Val>*
	aux_decrement(RBT_Node<Val>* x)
	throw()
	{
		/* If the grandparent is equal to x, the prev is it right child */
		if (x->color == RBT_Red && x->parent->parent == x)
			x = x->right;
		/* If x is on the bottom of the tree */
		else if (x->left == 0)
		{
			/* Go up until x is the left node */
			RBT_Node<Val>* y = x->parent;
			while (x == y->left)
			{
				x = y;
				y = y->parent;
			}
			x = y;
		}
		/* Is not on the bottom */
		else
		{
			/* Go to the bottom of the previous branch */
			RBT_Node<Val>* y = x->left;
			while (y->right)
				y = y->right;
			x = y;
		}
		return (x);
	}

	//@{
	/**
	 * 	@brief Mutable/Const decrement signature
	*/
	template <typename Val>
	inline RBT_Node<Val>*
	RBT_decrement(RBT_Node<Val>* x)
	throw()
	{ return (aux_decrement(x)); }

	template <typename Val>
	inline const RBT_Node<Val>*
	RBT_decrement(RBT_Node<Val>* x)
	throw()
	{ return (aux_decrement(static_cast<RBT_Node<Val>*>(x))); }
	//@}

	/////////////////////////////
	// Red Black tree iterator //
	/////////////////////////////

	/**
	 * 	@brief RBT Iterator
	 * 
	 * 	@tparam T The type of the value holded by the node.
	 * 	@tparam T_Ref A reference to T.
	 * 	@tparam T_Ptr A pointer to T.
	 * 
	 * 	NOTE: Using T_ref as const and T_ptr this class can be define a const iterator.
	*/
	template <class T, class T_Ref, class T_Ptr>
	struct RBT_iterator
	{
		/* Member types */

		typedef T					value_type;
		typedef T_Ref				reference;
		typedef const value_type&	const_reference;
		typedef T_Ptr				pointer;
		typedef const value_type*	const_pointer;

		typedef bidirectional_iterator_tag	iterator_tag;
		typedef std::ptrdiff_t				difference_type;

		typedef RBT_iterator<value_type, reference, pointer>			Self;
		typedef const RBT_iterator<T, const_reference, const_pointer>	Const_Self;

		typedef typename RBT_Node<T>::Node_Ptr					Node_Ptr;
		typedef typename RBT_Node<T>::Link_type					Link_type;

		/* Core */

		Node_Ptr		node;
		// TO DO: Node must Const_Node_Ptr for Const_Self (for the moment only fucntional of mutable instances)
		// I Must typedef the type of the node depending of the iterator instance.

		/* Member functions */

		RBT_iterator();
		RBT_iterator(Node_Ptr x);
		RBT_iterator(Const_Self& it);

		/* Requires read/write iterators */
		inline reference		operator*() const;
		inline pointer			operator->() const;

		/* Require forward iterators */
		inline Self&			operator++();
		inline Const_Self&		operator++() const;
		inline Self				operator++(int);
		inline Const_Self		operator++(int) const;

		/* Require bidirectional iterators */
		inline Self&			operator--();
		inline Const_Self&		operator--() const;
		inline Self				operator--(int);
		inline Const_Self		operator--(int) const;

		/* Non members */
		friend bool	operator==(const Self&, const Self&);
		friend bool	operator!=(const Self&, const Self&);
		friend bool	operator==(const Const_Self&, const Const_Self&);
		friend bool	operator!=(const Const_Self&, const Const_Self&);
	};

	/**
	 * 	@brief Default constructor
	*/
	template <class T, class T_Ref, class T_Ptr>
	RBT_iterator<T, T_Ref, T_Ptr>::RBT_iterator()
	: node()
	{ }

	/**
	 * 	@brief Constructor
	*/
	template <class T, class T_Ref, class T_Ptr>
	RBT_iterator<T, T_Ref, T_Ptr>::RBT_iterator(Node_Ptr x)
	: node(x)
	{ }

	/**
	 * 	@brief Convert const constructor
	*/
	template <class T, class T_Ref, class T_Ptr>
	RBT_iterator<T, T_Ref, T_Ptr>::RBT_iterator(Const_Self& it)
	: node(it.node)
	{ }

	///////////////////////////////////
	// Requires read/write iterators //
	///////////////////////////////////

	template <class T, class T_Ref, class T_Ptr>
	typename RBT_iterator<T, T_Ref, T_Ptr>::reference
	RBT_iterator<T, T_Ref, T_Ptr>::operator*() const
	{ return (*static_cast<Link_type>(node)->Node_get_value_ptr()); }

	template <class T, class T_Ref, class T_Ptr>
	typename RBT_iterator<T, T_Ref, T_Ptr>::pointer
	RBT_iterator<T, T_Ref, T_Ptr>::operator->() const
	{ return (static_cast<Link_type>(node)->Node_get_value_ptr()); }

	////////////////////////////////
	// Requires forward iterators //
	////////////////////////////////

	template <class T, class T_Ref, class T_Ptr>
	typename RBT_iterator<T, T_Ref, T_Ptr>::Self&
	RBT_iterator<T, T_Ref, T_Ptr>::operator++()
	{
		node = RBT_increment(node);
		return (*this);
	}

	template <class T, class T_Ref, class T_Ptr>
	typename RBT_iterator<T, T_Ref, T_Ptr>::Const_Self&
	RBT_iterator<T, T_Ref, T_Ptr>::operator++() const
	{
		node = RBT_increment(node);
		return (*this);
	}

	template <class T, class T_Ref, class T_Ptr>
	typename RBT_iterator<T, T_Ref, T_Ptr>::Self
	RBT_iterator<T, T_Ref, T_Ptr>::operator++(int)
	{
		Self tmp = *this;
		operator++();
		return (tmp);
	}

	template <class T, class T_Ref, class T_Ptr>
	typename RBT_iterator<T, T_Ref, T_Ptr>::Const_Self
	RBT_iterator<T, T_Ref, T_Ptr>::operator++(int) const
	{
		Self tmp = *this;
		operator++();
		return (tmp);
	}

	//////////////////////////////////////
	// Requires bidirectional iterators //
	//////////////////////////////////////

	template <class T, class T_Ref, class T_Ptr>
	typename RBT_iterator<T, T_Ref, T_Ptr>::Self&
	RBT_iterator<T, T_Ref, T_Ptr>::operator--()
	{
		node = RBT_decrement(node);
		return (*this);
	}

	template <class T, class T_Ref, class T_Ptr>
	typename RBT_iterator<T, T_Ref, T_Ptr>::Const_Self&
	RBT_iterator<T, T_Ref, T_Ptr>::operator--() const
	{
		node = RBT_decrement(node);
		return (*this);
	}

	template <class T, class T_Ref, class T_Ptr>
	typename RBT_iterator<T, T_Ref, T_Ptr>::Self
	RBT_iterator<T, T_Ref, T_Ptr>::operator--(int)
	{
		Self tmp = *this;
		operator--();
		return (tmp);
	}

	template <class T, class T_Ref, class T_Ptr>
	typename RBT_iterator<T, T_Ref, T_Ptr>::Const_Self
	RBT_iterator<T, T_Ref, T_Ptr>::operator--(int) const
	{
		Self tmp = *this;
		operator--();
		return (tmp);
	}

	/////////////////
	// Non members //
	/////////////////

	template <class T, class T_Ref, class T_Ptr>
	inline bool
	operator==(const typename RBT_iterator<T, T_Ref, T_Ptr>::Self& lhs,
	const typename RBT_iterator<T, T_Ref, T_Ptr>::Self& rhs)
	{ return (lhs.node == rhs.node); }

	template <class T, class T_Ref, class T_Ptr>
	inline bool
	operator!=(const typename RBT_iterator<T, T_Ref, T_Ptr>::Self& lhs,
	const typename RBT_iterator<T, T_Ref, T_Ptr>::Self& rhs)
	{ return (lhs.node != rhs.node); }

	template <class T, class T_Ref, class T_Ptr>
	inline bool
	operator==(const typename RBT_iterator<T, T_Ref, T_Ptr>::Const_Self& lhs,
	const typename RBT_iterator<T, T_Ref, T_Ptr>::Const_Self& rhs)
	{ return (lhs.node == rhs.node); }

	template <class T, class T_Ref, class T_Ptr>
	inline bool
	operator!=(const typename RBT_iterator<T, T_Ref, T_Ptr>::Const_Self& lhs,
	const typename RBT_iterator<T, T_Ref, T_Ptr>::Const_Self& rhs)
	{ return (lhs.node != rhs.node); }

	/////////////////////////
	// Red Black tree base //
	/////////////////////////

	/**
	 * 	@brief RBT_Base
	 * 
	 * 	The base class of RedBlackTree class. Fast type for initialiation.
	*/
	template <typename Val, typename Key_Compare, typename Alloc>
	struct RBT_Base
	: public RBT_Key_Compare<Key_Compare>, public RBT_Header<Val>, public RBT_Node<Val>
	{
		/* Member types */

		typedef RBT_Key_Compare<Key_Compare>	Base_Key_Compare;
		typedef RBT_Header<Val>					RBT_Header;
		typedef RBT_Node<Val>					RBT_Node;
		typedef Alloc							allocator_type;

		/* Imported members */

		using RBT_Header::header;
		using RBT_Header::tree_count;
		using Base_Key_Compare::key_compare;

		/* Core */

		allocator_type			memory;

		/* Member functions */

		RBT_Base();
		RBT_Base(const Key_Compare& cmp, const RBT_Node& x);
		RBT_Base(const RBT_Base& other);
	};

	/**
	 * 	@brief Default Constructor
	*/
	template <typename Val, typename Key_Compare, typename Alloc>
	RBT_Base<Val, Key_Compare, Alloc>::RBT_Base()
	: RBT_Node(), memory()
	{ }

	/**
	 * 	@brief Constructor
	*/
	template <typename Val, typename Key_Compare, typename Alloc>
	RBT_Base<Val, Key_Compare, Alloc>::RBT_Base(const Key_Compare& cmp, const RBT_Node& x)
	: Base_Key_Compare(cmp), RBT_Node(x), memory()
	{ }

	/**
	 * 	@brief Copy Constructor
	*/
	template <typename Val, typename Key_Compare, typename Alloc>
	RBT_Base<Val, Key_Compare, Alloc>::RBT_Base(const RBT_Base& other)
	: Base_Key_Compare(other.key_compare), RBT_Node(other), memory(other.memory)
	{ }

	////////////////////
	// Red Black tree //
	////////////////////

	/**
	 * 	@brief RedBlackTree
	 * 
	 * 	@tparam Key
	 * 	@tparam Val
	 * 	@tparam Key_Val
	 * 	@tparam Compare
	 * 	@tparam Alloc
	 * 
	 * 	A red-black tree is a kind of Abstract Search Tree specilised using
	 * 	Nodes defined by a color: Red or Black.
	 * 	Using this feature and some rules, RBT is the fasthest Search Tree algorithm.
	 * 
	 * 	Rules:
	 * 	1) Every Node must have color red or black.
	 * 	2) The root Node must be black.
	 * 	3) If a node is red it children and it parent must be black.
	 * 	4) Every path from the root to a NullNode (end of a brach in the bottom)
	 * 		must contain the same amount of black nodes.
	 * 
	 * 	That means, for every insertion and deletion the rules must be checked and the
	 * 	RBT architecture must be corrected if necesary. This is the complexity.
	 * 	
	*/
	template <typename Key, typename Val, typename Key_Val, typename Compare, typename Alloc = allocator<Val>>
	class RedBlackTree : public RBT_Base<Val, Compare, Alloc> // check for second param template Base
	{
		/* Engine types */

		protected:

		typedef typename RBT_Node<Val>::Node_Ptr		Node_Ptr;
		typedef typename RBT_Node<Val>::Const_Node_Ptr	Const_Node_Ptr;
		typedef typename RBT_Node<Val>::Link_type		Link_type;
		typedef const RBT_Node<Val>*					Const_Link_type;

		// TO DO: Function to recicle a pool of nodes
		// TO DO: Alloc Node
		// (perhabs to do, perhabs not) // DO IT !

		/* Members types */

		public:

		typedef Key					key_type;
		typedef Val					value_type;
		typedef value_type*			pointer;
		typedef const pointer		const_pointer;
		typedef value_type&			reference;
		typedef const reference		const_reference;
		typedef std::size_t			size_type;
		typedef std::ptrdiff_t		difference_size;
		typedef Alloc				allocator_type;

		typedef RBT_iterator<value_type, reference, pointer>				iterator;
		typedef RBT_iterator<value_type, const_reference, const_pointer>	const_iterator;

		typedef reverse_iterator<iterator>		reverse_iterator;
		typedef reference<const_iterator>		const_reverse_iterator;

		/* Auxiliar functions*/

		protected:

		/* Fast type / readable basic operations */
		inline Node_Ptr&				get_root() throw();
		inline Const_Node_Ptr&			get_root() const throw();
		inline Node_Ptr&				get_leftmost() throw();
		inline Const_Node_Ptr&			get_leftmost() const throw();
		inline Node_Ptr&				get_rightmost() throw();
		inline Const_Node_Ptr&			get_rightmost() const throw();
		inline Link_type				get_begin() throw();
		inline Const_Link_type			get_begin() const throw();
		inline Node_ptr&				get_end() throw();
		inline Const_Node_Ptr&			get_end() const throw();

		/* Memory handlers */
		inline Link_type				get_node() throw(std::bad_alloc);
		inline void						put_node(Link_type p) throw();
		void							construct_node(Link_type target,
										const_reference value) throw(std::bad_alloc);
		inline Link_type				create_node(const_reference value) throw(std::bad_alloc):
		inline void						destroy_node(Link_type p) throw();
		inline void						drop_node(Link_type p) throw();
		template <typename NodeGen>
		Link_type						clone_node(Const_Link_type src, NodeGen& node_gen) throw();

		/* Copy handlers */
		template <typename NodeGen>
		Link_type						aux_copy(Const_Link_type target, Node_Ptr parent,
										NodeGen&) throw(std::bad_alloc);
		template <typename NodeGen>
		Link_type						aux_copy(const RedBlackTree& src, NodeGen& gen) throw(std::bad_alloc);
		inline Link_type				aux_copy(const RedBlackTree& src) throw(std::bad_alloc);

		/* Rebalancing handlers */
		void 							aux_insert_and_rebalance(bool insert_left, Node_Ptr target,
										Node_Ptr parent, RBT_Node<Val>& header) throw();
		Node_Ptr 						aux_rebalance_for_erase(Node_Ptr const target,
										RBT_Node<Val>& header) throw();

		/* Inserters */
		std::pair<Node_Ptr, Node_Ptr>	aux_insert_unique_pos(const key_type& k) throw();
		std::pair<Node_Ptr, Node_Ptr>	aux_insert_equal_pos(const key_type& k) throw();
		std::pair<Node_Ptr, Node_Ptr>	aux_insert_hint_unique_pos(const key_type& k) throw();
		std::pair<Node_Ptr, Node_Ptr>	aux_insert_hint_equal_pos(const key_type& k) throw();
		std::pair<iterator, bool>		aux_insert_unique(const_reference value) throw(std::bad_alloc);
		iterator						aux_insert_equal(const_reference value) throw(std::bad_alloc);
		template <typename NodeGen>
		iterator						aux_insert_unique(const_iterator pos, const_reference value,
										NodeGen&) throw(std::bad_alloc);
		inline iterator					aux_insert_unique(const_iterator pos, const_reference value)
										throw(std::bad_alloc);
		template <typename NodeGen>
		iterator						aux_insert_equal(const_iterator pos, const_reference value,
										NodeGen&) throw(std::bad_alloc);
		inline iterator					aux_insert_equal(const_iterator pos, const_reference value)
										throw(std::bad_alloc);
		template <typename InputIt>
		void							aux_insert_range_unique(InputIt first, InputIt last) throw(std::bad_alloc);
		template <typename InputIt>
		void							aux_insert_range_equal(InputIt first, InputIt last) throw(std::bad_alloc);
		template <typename NodeGen>
		iterator						aux_insert(Node_Ptr first, Node_Ptr last,
										const_reference value, NodeGen&) throw(std::bad_alloc):
		iterator						aux_insert_lower(Node_Ptr target, const_reference value) throw(std::bad_alloc);
		iterator						aux_insert_equal_lower(const_reference value) throw(std::bad_alloc);

		/* Erasers */
		void							aux_erase(Link_type target) throw();
		void 							aux_erase(const_iterator pos) throw();
		void							aux_erase(const_iterator first, const_iterator last) throw();

		/* Lookup handlers */
		iterator						aux_lower_bound(Link_type x, Node_Ptr y, const key_type& k) throw();
		const_iterator					aux_lower_bound(Const_Link_type x, Const_Node_Ptr y, const key_type& k) const throw();
		iterator						aux_upper_bound(Link_type x, Node_Ptr y, const key_type& k) throw();
		const_iterator					aux_upper_bound(Const_Link_type x, Const_Node_Ptr y, const key_type& k) const throw();

		/* Node allocation classes */

		class Node_Alloc
		{
			/* Core */

			RedBlackTree& rbtree;

			/* Member functions */

			public:

			Node_Alloc(RedBlackTree& t);
			template <typename Arg>
			Link_type	operator()(const Arg arg) throw(std::bad_alloc);
		};

		/* Member functions */

		public:

		RedBlackTree();
		RedBlackTree(const Compare& cmp, const allocator_type& alloc = allocator_type());
		RedBlackTree(const RedBlackTree& other);
		~RedBlackTree();
		// TO DO: operator=
		RedBlackTree&					operator=(const RedBlackTree& other);

		/* Iterators */
		inline iterator					begin();
		inline const_iterator			begin() const;
		inline iterator					end();
		inline const_iterator			end() const;
		inline reverse_iterator			rbegin();
		inline const_reverse_iterator	rbegin() const;
		inline reverse_iterator			rend();
		inline const_reverse_iterator	rend() const;

		/* Capacity */
		inline bool						empty() const;
		inline size_type				size() const;
		inline size_type				max_size() const;

		/* Modifiers */
		// TO DO Insert ?!?!?!!? (how did i forgot this ? lmao)
		inline void						clear();
		inline void						erase(iterator pos);
		inline void						erase(const_iterator pos);
		size_type						erase(const key_type& k);
		inline void						erase(iterator first, iterator last);
		inline void						erase(const_iterator first, const_iterator last);
		void							swap(RedBlackTree& other);

		/* Lookup*/
		size_type						count(const key_type& k) const;
		iterator						find(const key_type& k);
		const_iterator					find(const key_type& k) const;
		std::pair<iterator, iterator>				equal_range(const key_type& k);
		std::pair<const_iterator, const_iterator>	equal_range(const key_type& k) const;
		inline iterator					lower_bound(const key_type& k);
		inline const_iterator			lower_bound(const key_type& k) const;
		inline iterator					upper_bound(const key_type& k);
		inline const_iterator			upper_bound(const key_type& k) const;

		/* Observers */
		inline Compare					key_comp() const;
		// TO DO: value_comp

		/* Non members */
		friend bool	operator==(const RedBlackTree&, const RedBlackTree&);
		friend bool	operator<(const RedBlackTree&, const RedBlackTree&);
	};

	///////////////////////////////////////////
	// Fast type / readable basic operations //
	///////////////////////////////////////////

	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::Node_Ptr&
	RedBlackTree<K, V, KV, C, A>::get_root()
	throw()
	{ return (header.parent); }
		
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::Const_Node_Ptr&
	RedBlackTree<K, V, KV, C, A>::get_root() const
	throw()
	{ return (header.parent); }

	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::Node_Ptr&
	RedBlackTree<K, V, KV, C, A>::get_leftmost()
	throw()
	{ return (header.left); }

	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::Const_Node_Ptr&
	RedBlackTree<K, V, KV, C, A>::get_leftmost() const
	throw()
	{ return (header.left); }

	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::Node_Ptr&
	RedBlackTree<K, V, KV, C, A>::get_rightmost()
	throw()
	{ return (header.right); }

	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::Const_Node_Ptr&
	RedBlackTree<K, V, KV, C, A>::get_rightmost() const
	throw()
	{ return (header.right); }

	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::Link_type
	RedBlackTree<K, V, KV, C, A>::get_begin()
	throw()
	{ return (static_cast<Link_type>(header.parent)); }

	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::Const_Link_type
	RedBlackTree<K, V, KV, C, A>::get_begin() const
	throw()
	{ return (static_cast<Const_Link_type>(header.parent)); }

	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::Node_ptr&
	RedBlackTree<K, V, KV, C, A>::get_end()
	throw()
	{ return (&header); }

	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::Const_Node_Ptr&
	RedBlackTree<K, V, KV, C, A>::get_end() const
	throw()
	{ return (&header); }

	template <class K, class V, class KV, class C, class A>
	inline static const typename RedBlackTree<K, V, KV, C, A>::key_type&
	sget_key(typename RedBlackTree<K, V, KV, C, A>::Const_Link_type target)
	throw()
	{ return (Key_Val()(*target->Node_get_value_ptr())); }

	template <class K, class V, class KV, class C, class A>
	inline static const typename RedBlackTree<K, V, KV, C, A>::key_type&
	sget_key(typename RedBlackTree<K, V, KV, C, A>::Const_Node_Ptr target)
	throw()
	{ return (sget_key(static_cast<typename RedBlackTree<K, V, KV, C, A>::Const_Link_type>(target))); }

	template <class K, class V, class KV, class C, class A>
	inline static typename RedBlackTree<K, V, KV, C, A>::Link_type
	sget_left(typename RedBlackTree<K, V, KV, C, A>::Node_Ptr target)
	throw()
	{ return (static_cast<Link_type>(target->left)); }

	template <class K, class V, class KV, class C, class A>
	inline static typename RedBlackTree<K, V, KV, C, A>::Const_Link_type
	sget_left(typename RedBlackTree<K, V, KV, C, A>::Const_Node_Ptr target)
	throw()
	{ return (static_cast<Const_Link_type>(target->left)); }

	template <class K, class V, class KV, class C, class A>
	inline static typename RedBlackTree<K, V, KV, C, A>::Link_type
	sget_right(typename RedBlackTree<K, V, KV, C, A>::Node_Ptr target)
	{ return (static_cast<typename RedBlackTree<K, V, KV, C, A>::Link_type>(target->right)); }

	template <class K, class V, class KV, class C, class A>
	inline static typename RedBlackTree<K, V, KV, C, A>::Const_Link_type
	sget_right(typename RedBlackTree<K, V, KV, C, A>::Const_Node_Ptr target)
	throw()
	{ return (static_cast<typename RedBlackTree<K, V, KV, C, A>::Const_Link_type>(target->right)); }

	template <class K, class V, class KV, class C, class A>
	inline static typename RedBlackTree<K, V, KV, C, A>::Node_Ptr
	sget_maximum(typename RedBlackTree<K, V, KV, C, A>::Node_Ptr target)
	throw()
	{ return (Node_maximum(target)); }

	template <class K, class V, class KV, class C, class A>
	inline static typename RedBlackTree<K, V, KV, C, A>::Const_Node_Ptr
	sget_maximum(typename RedBlackTree<K, V, KV, C, A>::Const_Node_Ptr target)
	throw()
	{ return (Node_maximum(target)); }

	template <class K, class V, class KV, class C, class A>
	inline static typename RedBlackTree<K, V, KV, C, A>::Node_Ptr
	sget_minimum(typename RedBlackTree<K, V, KV, C, A>::Node_Ptr target)
	throw()
	{ return (Node_minimum(target)); }

	template <class K, class V, class KV, class C, class A>
	inline static typename RedBlackTree<K, V, KV, C, A>::Const_Node_Ptr
	sget_minimum(typename RedBlackTree<K, V, KV, C, A>::Const_Node_Ptr target)
	throw()
	{ return (Node_minimum(target)); }

	/////////////////////
	// Memory handlers //
	/////////////////////

	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::Link_type
	RedBlackTree<K, V, KV, C, A>::get_node()
	throw(::std::bad_alloc)
	{ return (memory.allocate(1ul)); }


	template <class K, class V, class KV, class C, class A>
	void
	RedBlackTree<K, V, KV, C, A>::put_node(Link_type p)
	throw()
	{ memory.deallocate(p); }

	/**
	 * 	@brief construct node
	 * 
	 * 	@param target A pointer to the node to construct.
	 * 	@param value The data instance to construct.
	 * 	@throw std::bad_alloc
	 * 
	 * 	Fast type + exeption tryer node constructor.
	*/
	template <class K, class V, class KV, class C, class A>
	void
	RedBlackTree<K, V, KV, C, A>::construct_node(Link_type target, const_reference value)
	throw(::std::bad_alloc)
	{
		try {
			memory.construct(target->Node_get_value_ptr(), value);
		} catch (std::bad_alloc&) {
			put_node(target);
			throw;
		}
	}

	/**
	 * 	@brief create node
	 * 
	 * 	@param value The data instance to construct.
	 * 	@throw std::bad_alloc
	 * 
	 *	@return A pointer to a node holding an constructed instance of @p value.
	*/
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::Link_type
	RedBlackTree<K, V, KV, C, A>::create_node(const_reference value)
	throw(::std::bad_alloc)
	{
		Link_type	new_node = get_node();
		construct_node(new_node, value_type);
		return (new_node);
	}

	/**
	 * 	@brief destroy node
	 * 
	 * 	@param p A pointer to the node where is the data to destroy.
	*/
	template <class K, class V, class KV, class C, class A>
	void
	RedBlackTree<K, V, KV, C, A>::destroy_node(Link_type p)
	throw()
	{ memory.destroy(p->Node_get_value_ptr()); }

	/**
	 * 	@brief drop node
	 * 
	 * 	@param p A pointer to the node.
	 * 
	 * 	Destroys the data holded and deallocate the node.
	*/
	template <class K, class V, class KV, class C, class A>
	void
	RedBlackTree<K, V, KV, C, A>::drop_node(Link_type p)
	throw()
	{
		destroy_node(p);
		put_node(p);
	}

	/**
	 * 	@brief clone node
	 * 
	 * 	@tparam NodeGen A function to create nodes.
	 * 	@param src A node instance to clone
	 * 	@param node_gen a NodeGen function.
	 * 	
	 * 	@return A pointer to the cloned node.
	*/
	template <class K, class V, class KV, class C, class A>
	template <typename NodeGen>
	typename RedBlackTree<K, V, KV, C, A>::Link_type
	RedBlackTree<K, V, KV, C, A>::clone_node(Const_Link_type src, NodeGen& node_gen)
	throw()
	{
		Link_type	cln = node_gen(*src->Node_get_value_ptr());
		cln->color = src->color;
		cln->left = NULL;
		cln->right = NULL;
		return (cln);
	}

	///////////////////
	// Copy handlers //
	///////////////////

	/**
	 * 	@brief copy
	 * 
	 * 	@tparam NodeGen A allocator object.
	 * 	@param target The top node of the copy.
	 * 	@param parent The parent node of @p target.
	 * 	
	 * 	Perform a recursive structural copy starting to @p target.
	 *
	 * 	NOTE: @p target and @p parent must be non-null.
	*/
	template <class K, class V, class KV, class C, class A>
	template <typename NodeGen>
	typename RedBlackTree<K, V, KV, C, A>::Link_type
	RedBlackTree<K, V, KV, C, A>::aux_copy(Const_Link_type target, Node_Ptr parent, NodeGen& node_gen)
	throw(::std::bad_alloc)
	{
		/* Copy the highter node and link to parent */
		Link_type top = clone_node(target, node_gen);
		top->parent = parent;

		try {

			/* Copy the right branches */
			if (sget_right(target))
				sget_right(top) = aux_copy(sget_right(target), top, node_gen);

			/* Link parent - child */
			parent = top;
			target = sget_left(target);

			/* Copy the left branches */
			while (target)
			{
				/* Copy the left branch node */
				Link_type i = clone_node(target, node_gen);
				sget_left(parent) = i;
				i->parent = parent;
		
				/* For each left branch copy the right branch */
				if (sget_right(target))
					sget_right(i) = aux_copy(sget_right(target), i, node_gen);

				/* Link parent - child */
				parent = i;
				target = sget_left(target);
			}

		} catch (std::bad_alloc&) {
			aux_erase(top);
			throw;
		}
		return (top);
	}		

	/**
	 * 	@brief copy
	 * 
	 * 	@tparam NodeGen a node creator function.
	 *
	 * 	Copies @p src and return the root to the copy.
	 * 	NOTE: update local members.
	*/
	template <class K, class V, class KV, class C, class A>
	template <typename NodeGen>
	typename RedBlackTree<K, V, KV, C, A>::Link_type
	RedBlackTree<K, V, KV, C, A>::aux_copy(const RedBlackTree& src, NodeGen& gen)
	throw(::std::bad_alloc)
	{
		Link_type root = aux_copy(src.get_begin(), get_end(), gen);
		get_leftmost() = sget_minimum(root);
		get_rightmost() = sget_maximum(root);
		count = src.count;
		return (root);
	}

	template <class K, class V, class KV, class C, class A>
	RedBlackTree<K, V, KV, C, A>::Link_type
	RedBlackTree<K, V, KV, C, A>::aux_copy(const RedBlackTree& src)
	throw(::std::bad_alloc)
	{
		Node_Alloc nd(*this);
		return (aux_copy(src, nd));
	}

	/////////////////////////
	// Rebalancig handlers //
	/////////////////////////

	/// Rotates the tree to the left
	template <class K, class V, class KV, class C, class A>
	static void
	aux_rotate_left(typename RedBlackTree<K, V, KV, C, A>::Node_Ptr const target,
	typename RedBlackTree<K, V, KV, C, A>::Node_Ptr&root)
	throw()
	{
		typedef typename RedBlackTree<K, V, KV, C, A>::Node_Ptr Node_Ptr;

		Node_Ptr const tmp = sget_right(target);

		/* Target right child = left child of target right child,
			if this left child exist target begins the parent */
		if ((target->right = tmp->left))
			tmp->left->parent = target;

		/* tmp takes as parent it grand-parent */
		tmp->parent = x->parent;

		/* Change the root if the root is the target */
		if (target == root)
			root = tmp;
			/* If target is left node */
		else if (target == target->parent->left)
			target->parent->left = tmp;
		else
			target->parent->right = tmp;

		tmp->left = target;
		target->parent = tmp;
	}

	/// Rotates the tree to the right
	template <class K, class V, class KV, class C, class A>
	static void
	aux_rotate_right(typename RedBlackTree<K, V, KV, C, A>::Node_Ptr const target,
	typename RedBlackTree<K, V, KV, C, A>::Node_Ptr& root)
	throw()
	{
		typedef typename RedBlackTree<K, V, KV, C, A>::Node_Ptr Node_Ptr;

		Node_Ptr const tmp = sget_left(target);

		if ((target->left = tamp->right))
			tmp->right = target;
		tmp->parent = target->parent;
		if (target == root)
			root = tmp;
		else if (target == target->parent->right)
			target->parent->right = tmp;
		else
			target->parent->left = tmp;
		tmp->right = target;
		target->parent = target;
	}

	template <class K, class V, class KV, class C, class A>
	static void
	aux_rebalance_tree(typename RedBlackTree<K, V, KV, C, A>::Node_Ptr& const target,
	typename RedBlackTree<K, V, KV, C, A>::Node_Ptr const parent_child,
	typename RedBlackTree<K, V, KV, C, A>::Node_Ptr const grand_parent_child,
	void (&rot1)(typename RedBlackTree<K, V, KV, C, A>::Node_Ptr const, typename RedBlackTree<K, V, KV, C, A>::Node_Ptr&),
	void (&rot2)(typename RedBlackTree<K, V, KV, C, A>::Node_Ptr const, typename RedBlackTree<K, V, KV, C, A>::Node_Ptr&),
	RBT_Node<V>& header)
	throw()
	{
		typedef typename RedBlackTree<K, V, KV, C, A>::Node_Ptr Node_Ptr;

		Node_Ptr const grand_parent = target->parent->parent;
		Node_Ptr& root = header.parent;

		if (grand_parent_child && grand_parent_child->color == RBT_Red)
		{
			target->parent->color = RBT_Black;
			grand_parent_child->color = RBT_Black;
			grand_parent->color = RBT_Red;
			target = grand_parent;
		}
		else
		{
			if (target == parent_child)
			{
				target = target->parent;
				rot1(target, root);
			}
			target->parent->color = RBT_Black;
			grand_parent->color = RBT_Red;
			rot2(grand_parent, root);
		}
	}

	template <class K, class V, class KV, class C, class A>
	void
	RedBlackTree<K, V, KV, C, A>::aux_insert_and_rebalance(bool insert_left,
	Node_Ptr target, Node_Ptr parent, RBT_Node<V>& header)
	throw()
	{
		typedef typename RedBlackTree<K, V, KV, C, A>::Node_Ptr Node_Ptr;

		/* Init the new node to insert */
		target->parent = parent;
		target->left = 0;
		target->right = 0;
		target->color = RBT_Red;

		/* 	First, proceed to insert, the new node will be child of the parent.
			Root's leftmost and rightmost nodes are maintained.
			NOTE: First node is always inserted left. */
		if (insert_left)
		{
			parent->left = target;

			if (parent == &header)
			{
				/* Make it leftmost */
				header.parent = target;
				header.right = target;
			}
			else if (parent == header.left) /* Maintain leftmost pointing to min node */
				header.left = target;
		}
		else
		{
			parent->right = target;

			if (parent == header.right) /* Maintain rightmost pointing to max node */
				header.right = target;
		}

		/* Then, rebalance the tree */
		while (target != get_root() && target->parent->color == RBT_Red)
		{
			Node_Ptr const grand_parent = target->parent->parent;
		
			if (target->parent == grand_parent->left)
				aux_rebalance_tree(target, target->parent->right, grand_parent->right,
				aux_rotate_left, aux_rotate_right, header);
			else
				aux_rebalance_tree(target, target->parent->left, grand_parent->left,
				aux_rotate_right, aux_rotate_left, header);
		}
		get_root()->color = RBT_Black;
	}

	template <class K, class V, class KV, class C, class A>
	static bool
	aux_erase_rebalance(typename RedBlackTree<K, V, KV, C, A>::Node_Ptr& tmp,
	typename RedBlackTree<K, V, KV, C, A>::Node_Ptr& parent_tmp, bool is_right)
	throw()
	{
		typedef typename RedBlackTree<K, V, KV, C, A>::Node_Ptr Node_Ptr;

		Node_Ptr brother =
		is_right ? parent_tmp->left : parent_tmp->right;
	
		static void (*const rot[])(Node_Ptr const, Node_Ptr&) {
			&aux_rotate_left,
			&aux_rotate_right
		};

		if (brother->color == RBT_Red)
		{
			brother->color = RBT_Black;
			parent_tmp->color = RBT_Red;
			rot[is_right](parent_tmp, get_root());
			brother = is_right ? parent_tmp->right : parent_tmp->left;
		}

		if ((!is_right && (brother->left == 0 || brother->left->color == RBT_Black)
			&& (brother->right == 0 || brother->right->color == RBT_Black))
			|| ((is_right && (brother->right == 0 || brother->right->color == RBT_Black)
			&& (brother->left == 0 || brother->right->color == RBT_Black)))
		{
			brother->color = RBT_Red;
			tmp = parent_tmp;
			parent_tmp = parent_tmp->parent;
		}
		else
		{
			if (brother->right == 0 || brother->right->color == RBT_Black)
			{
				brother->left->color = RBT_Black;
				brother->color = RBT_Red;
				rot[!is_right](brother, get_root());
				brother = parent_tmp->right;
			}
			brother->color = parent_tmp->color;
			parent_tmp->color = RBT_Black;
			if ((is_right && brother->left) || (!is_right && brother->right))
				!is_right ? brother->right->color : brother->left->color = RBT_Black;
			rot[is_right](parent_tmp, get_root());
			return (true);
		}
		return (false);
	}

	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::Node_Ptr
	RedBlackTree<K, V, KV, C, A>::aux_rebalance_for_erase(Node_Ptr const target, RBT_Node<V>& header)
	throw()
	{
		Node_Ptr successor = target;
		Node_Ptr tmp = 0;
		Node_Ptr tmp_parent = 0;

		/* If target has at most one non null child */
		if (target->left == 0)
			tmp = target->right;
		else
		{
			/* If target has exactly 1 non null child */
			if (target->right == 0)
				tmp = target->left;
	
			/* If target has 2 non null children */
			else
			{
				successor = target->right;
				while (successor->left)
					successor = successor->left;
				tmp = successor->right;
			}
		}

		/* target has no null children */
		if (successor != target)
		{
			/* Relink successor */

			target->left->parent = successor;
			successor->left = target->left;

			if (successor != target->right)
			{
				tmp_parent = successor->parent;
				if (tmp)
					tmp->parent = successor->parent;
				successor->parent->left = tmp;
				successor->right = target->right;
				target->right->parent = successor;
			}
			else
				tmp_parent = successor;
				
			if (get_root() == target)
				get_root() = successor;
			else if (target->parent->left == target)
				target->parent->left = successor;
			else
				target->parent->right = successor;
			std::swap(successor->color, target->color);
			successor = target; // NOTE: successor point to the node to be deleted now
		}
		/* target has at least 1 null child */
		else
		{
			tmp_parent = successor->parent;

			if (tmp)
				tmp->parent = successor->parent;
	
			if (get_root() == target)
				get_root() = tmp;
			else
			{
				if (target->parent->left == target)
					target->parent->left = tmp;
				else
					arget->parent->right = tmp;
			}

			// TO DO: Is it worth to make a function for this condition ?
			if (get_leftmost() == target)
			{
				if (target->right == 0)
					get_leftmost() = target->parent;
				else
					get_leftmost() = sget_minimum(tmp);
			}
			if (get_rightmost() == target)
			{
				if (target->left == 0)
					get_rightmost() = target->parent;
				else
					get_rightmost() = sget_maximum(tmp);
			}
		}

		/* Rebalance */
		if (successor->color == RBT_Black)
		{
			while (tmp != get_root() && (!tmp || tmp->color == RBT_Black))
			{
				if (tmp == tmp_parent->left && aux_erase_rebalance(tmp, tmp_parent, false))
					break ;
				else if (aux_erase_rebalance(tmp, tmp_parent, true))
					break ;

				if (tmp)
					tmp->color = RBT_Black;
			}
		}
		return (successor);
	}

	///////////////
	// Inserters //
	///////////////

	/**
	 * 	@brief aux insert unique pos.
	 * 
	 * 	@return A pair of Node_ptr pointing to the maching subsequence
	 * 	 with @p k, a key.
	*/
	template <class K, class V, class KV, class C, class A>
	::std::pair<typename RedBlackTree<K, V, KV, C, A>::Node_Ptr, typename RedBlackTree<K, V, KV, C, A>::Node_Ptr>
	RedBlackTree<K, V, KV, C, A>::aux_insert_unique_pos(const key_type& k)
	throw()
	{
		Link_type x = get_begin();
		Node_Ptr y = get_end();
		bool cmp = true;

		/* Search for the lower maching node and store it on y */
		while (x)
		{
			y = x;
			if ((cmp = key_compare(k, sget_key(x))))
				x = sget_left(x);
			else
				x = sget_right(x);
		}
		iterator i(y);

		/* If no match */
		if (cmp)
		{
			/* If is the first one return else decrement */
			if (i == begin())
				return (std::pair<Node_Ptr, Node_Ptr>(0, y));
			else
				i--;
		}

		/* If reverse conparison no match return */
		if (key_compare(sget_right(i.node), k))
			return (std::pair<Node_Ptr, Node_Ptr>(0, y));

		/* If macthes */
		return (std::pair<Node_Ptr, Node_Ptr>(i.node, 0));
	}

	/**
	 * 	@brief aux insert equal pos.
	 * 
	 * 	@return A pair of Node_ptr pointing to the maching subsequence
	 * 	 with @p k, a key.
	*/
	template <class K, class V, class KV, class C, class A>
	::std::pair<typename RedBlackTree<K, V, KV, C, A>::Node_Ptr, typename RedBlackTree<K, V, KV, C, A>::Node_Ptr>
	RedBlackTree<K, V, KV, C, A>::aux_insert_equal_pos(const key_type& k)
	throw()
	{
		Link_type x = get_begin();
		Node_Ptr y = get_end();

		/* Search for the lower maching node and store it on y */
		while (x)
		{
			y = x;
			if ((cmp = key_compare(k, sget_key(x))))
				x = sget_left(x);
			else
				x = sget_right(x);
		}
		return (std::pair<Node_Ptr, Node_Ptr>(0, y));
	}

	/**
	 * 	@brief aux insert hint unique pos
	 * 
	 * 	@return A pair of Node_Ptr pointnig to position to insert.
	 * 	NOTE: Uses @p pos and @p k to find the index to the insertion.
	*/
	template <class K, class V, class KV, class C, class A>
	::std::pair<typename RedBlackTree<K, V, KV, C, A>::Node_Ptr, typename RedBlackTree<K, V, KV, C, A>::Node_Ptr>
	RedBlackTree<K, V, KV, C, A>::aux_insert_hint_unique_pos(const_iterator position, const key_type& k)
	throw()
	{
		iterator pos = position; // TO DO: const cast method in iterator

		/* If the requested position is the last node. */
		if (pos == end())
		{
			/* If no matches with the right child */
			if (size() > 0 && key_compare(sget_key(get_rightmost()), k))
				return (std::pair<Node_Ptr, Node_Ptr>(0, get_rightmost()));
			
			/* Else get the position form the left brach */
			return (aux_insert_unique_pos(k));
		}

		/* If is not the last and the comparison is false try before*/
		else if (key_compare(k, sget_key(pos.node)))
		{
			iterator before = pos;

			/* If pos is the begin */
			if (pos.node == get_leftmost())
				return (std::pair<Node_Ptr, Node_Ptr>(get_leftmost(), get_leftmost()));

			/* Else try comparison with the predecend node (if false) */
			else if (key_compare(sget_key(--before.node), k))
				return (sget_right(before.node) ? std::pair<Node_Ptr, Node_Ptr>(0, before.node)
					: std::pair<Node_Ptr, Node_Ptr>(0, before.node));

			/* Else try inverse comparison */
			return (aux_insert_unique_pos(k));
		}

		/* Else if the inverse comparison is false try after */
		else i f(key_compare(sget_key(pos.node), k))
		{
			iterator after = pos;

				/* If pos is the begin */
			if (pos.node == get_rightmost())
				return (std::pair<Node_Ptr, Node_Ptr>(0, get_rightmost()));

			/* Else try comparison with the next node (if false) */
			else if (key_compare(k, sget_key(++after.node)))
				return (sget_right(after.node) ? std::pair<Node_Ptr, Node_Ptr>(0, before.node)
					: std::pair<Node_Ptr, Node_Ptr>(0, after.node));

			/* Else try inverse comparison */
			return (aux_insert_unique_pos(k));
		}

		/* If the key k matches with the pair at the given position */
		return (std::pair<Node_Ptr, Node_Ptr>(pos.node, 0));
	}

	/**
	 * 	@brief aux insert hint equal pos
	 * 
	 * 	@return A pair of Node_Ptr pointnig to position to insert.
	 * 	NOTE: Uses @p pos and @p k to find the index to the insertion.
	*/
	template <class K, class V, class KV, class C, class A>
	::std::pair<typename RedBlackTree<K, V, KV, C, A>::Node_Ptr, typename RedBlackTree<K, V, KV, C, A>::Node_Ptr>
	RedBlackTree<K, V, KV, C, A>::aux_insert_hint_equal_pos(const_iterator position, const key_type& k)
	throw()
	{
		iterator pos = position; // TO DO: const cast method in iterator

		/* If the requested position is the last node. */
		if (pos == end())
		{
			/* If no matches with the right child */
			if (size() > 0 && key_compare(k, sget_key(get_rightmost())))
				return (std::pair<Node_Ptr, Node_Ptr>(0, get_rightmost()));
				
			/* Else get the position form the left brach */
			return (aux_insert_equal_pos(k));
		}
			
		/* If is not the last and the comparison is false try before*/
		else if (key_compare(k, sget_key(pos.node)))
		{
			iterator before = pos;

			/* If pos is the begin */
			if (pos.node == get_leftmost())
				return (std::pair<Node_Ptr, Node_Ptr>(get_leftmost(), get_leftmost()));

			/* Else try comparison with the predecend node (if false) */
			else if (key_compare(sget_key(--before.node), k))
				return (sget_right(before.node) ? std::pair<Node_Ptr, Node_Ptr>(0, before.node)
					: std::pair<Node_Ptr, Node_Ptr>(0, before.node));

			/* Else try inverse comparison */
			return (aux_insert_equal_pos(k));
		}

		/* Else if the inverse comparison is false try after */
		else i f(key_compare(sget_key(pos.node), k))
		{
			iterator after = pos;

			/* If pos is the begin */
			if (pos.node == get_rightmost())
				return (std::pair<Node_Ptr, Node_Ptr>(0, get_rightmost()));

			/* Else try comparison with the next node (if false) */
			else if (key_compare(k, sget_key(++after.node)))
				return (sget_right(after.node) ? std::pair<Node_Ptr, Node_Ptr>(0, before.node)
					: std::pair<Node_Ptr, Node_Ptr>(0, after.node));

			/* Else try inverse comparison */
			return (aux_insert_equal_pos(k));
		}

		/* If the key k matches with the pair at the given position */
		return (std::pair<Node_Ptr, Node_Ptr>(0, 0));
	}

	/**
	 * 	@brief insert unique
	 * 
	 * 	@param value The value to insert.
	 *
	 * 	Perfom an insertion of @p value on the %RBT.
	 * 	NOTE: @p value is unique in the %RBT else the insertion
	 * 	is not performed. 
	*/
	template <class K, class V, class KV, class C, class A>
	::std::pair<typename RedBlackTree<K, V, KV, C, A>::iterator, bool>
	RedBlackTree<K, V, KV, C, A>::aux_insert_unique(const_reference value)
	throw(::std::bad_alloc)
	{
		/* Get the position to insert */
		std::pair<Node_Ptr, Node_Ptr> pos = aux_insert_unique_pos(Key_Val()(value));

		/* If pos has a second member == no match */
		if (pos.second)
		{
			/* Insert the data */
			Node_Alloc nd(*this);
			return (std::pair<iterator, bool>(aux_insert(pos.first, pos.second, value, nd), true));
		}

		/* Else if value already exist */
		return (std::pair<iterator, bool>(iterator(pos.first), false));
	}

	/**
	 * 	@brief insert unique
	 * 
	 * 	@param value The value to insert.
	 *
	 * 	Perfom an insertion of @p value on the %RBT. 
	*/
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::iterator
	RedBlackTree<K, V, KV, C, A>::aux_insert_equal(const_reference value)
	throw(::std::bad_alloc)
	{
		/* Get the position to insert */
		std::pair<Node_Ptr, Node_Ptr> pos = aux_insert_equal_pos(Key_Val()(value));

		/* Insert the data */
		Node_Alloc nd(*this);
		return (aux_insert(pos.first, pos.second, value, nd));
	}

	/**
	 * 	@brief aux insert unique
	 * 
	 * 	@tparam NodeGen a node allocator object.
	 * 	@param pos The index of the requested insertion.
	 * 	@param value The data to insert.
	 * 	@param node_gen A NodeGen.
	 * 
	 * 	Performs an insertion if @p value at @p pos using @p @node_gen.
	*/
	template <class K, class V, class KV, class C, class A>
	template <typename NodeGen>
	typename RedBlackTree<K, V, KV, C, A>::iterator
	RedBlackTree<K, V, KV, C, A>::aux_insert_unique(const_iterator pos, const_reference value, NodeGen& node_gen)
	throw(::std::bad_alloc)
	{
		/* Get the index of the insertion */
		std::pair<Node_Ptr, Node_Ptr> pos = aux_insert_hint_unique_pos(pos, Key_Val()(value));

		/* If the value is unique proceed to the insertion */
		if (pos.second)
			return (aux_insert(pos.first, pos.second, value, node_gen));

		/* Else if the value already exist */
		return (iterator(pos.first));
	}

	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::iterator
	RedBlackTree<K, V, KV, C, A>::aux_insert_unique(const_iterator pos, const_reference value)
	throw(::std::bad_alloc)
	{
		Node_Alloc	nd(*this);
		return (aux_insert_unique(pos, value, nd));
	}

	template <class K, class V, class KV, class C, class A>
	template <typename NodeGen>
	typename RedBlackTree<K, V, KV, C, A>::iterator
	RedBlackTree<K, V, KV, C, A>::aux_insert_equal(const_iterator pos, const_reference value, NodeGen& node_gen)
	throw(::std::bad_alloc)
	{
		/* Get the index of the insertion */
		std::pair<Node_Ptr, Node_Ptr> pos = aux_insert_hint_equal_pos(pos, Key_Val()(value));

		/* Check for no match and then proced to insert */
		if (pos.second)
			return (aux_insert(pos.first, pos.second, value, node_gen));

		/* If match */
		return (aux_insert_equal_lower(value));
	}

	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::iterator
	RedBlackTree<K, V, KV, C, A>::aux_insert_equal(const_iterator pos, const_reference value)
	throw(::std::bad_alloc)
	{
		Node_Alloc	nd(*this);
		return (aux_insert_equal(pos, value, nd));
	}

	template <class K, class V, class KV, class C, class A>
	template <typename InputIt>
	void
	RedBlackTree<K, V, KV, C, A>::aux_insert_range_unique(InputIt first, InputIt last)
	throw(::std::bad_alloc)
	{
		Node_Alloc nd(*this);
		for (; first != last ; first++)
			aux_insert_unique(end(), *first, nd);
	}

	template <class K, class V, class KV, class C, class A>
	template <typename InputIt>
	void
	RedBlackTree<K, V, KV, C, A>::aux_insert_range_equal(InputIt first, InputIt last)
	throw(::std::bad_alloc)
	{
		Node_Alloc nd(*this);
		for (; first != last ; first++)
			aux_insert_equal(end(), *first, nd);
	}

	/**
	 * 	@brief aux insert
	 * 
	 * 	@tparam NodeGen A Node allocator function.
	 * 	@param first A pointer to some node.
	 * 	@param last A pointer to some node.
	 * 	@param value The value to be inserted.
	 * 
	 * 	@return An iterator to the inserted data.
	 * 	
	 * Insert copies of @p value in range @p first - @p last,
	 * 	using NodeGen as function to allocates nodes.
	*/
	// TO DO: Naming first and last seems incorrect
	// last could be parent
	template <class K, class V, class KV, class C, class A>
	template <typename NodeGen>
	typename RedBlackTree<K, V, KV, C, A>::iterator
	RedBlackTree<K, V, KV, C, A>::aux_insert(Node_Ptr first, Node_Ptr last, const_reference value, NodeGen& node_gen)
	throw(::std::bad_alloc)
	{
		/* Check if is a left insertion */
		bool is_left_insertion = first || last = get_end() || key_compare(Key_Val()(value, sget_key(last)));

		/* Allocate a new node */
		Link_type nd = node_gen(value);

		/* Insert the value and rebalance the branches if necesary */
		aux_insert_and_rebalance(is_left_insertion, nd, last, header);

		/* Increment the size counter */
		tree_count++;

		return (iterator(nd));
	}

	/**
	 * 	@brief  aux insert lower
	 * 
	 * 	TO DO target coukd be parent
	*/
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::iterator
	RedBlackTree<K, V, KV, C, A>::aux_insert_lower(Node_Ptr target, const_reference value)
	throw(::std::bad_alloc)
	{
		/* Check if is a left insertion */
		bool is_left_insertion = target == get_end() || !key_compare(sget_key(target), Key_Val()(value));

		/* Allocate a new node */
		Link_type nd = create_node(value);

		/* Insert the value and rebalance the branches if necesary */
		aux_insert_and_rebalance(is_left_insertion, nd, target, header);

		/* Increment the size counter */
		tree_count++;

		return (iterator(nd));
	}

	/**
	 * 	@brief Insert equal lower
	 * 
	 * 	TO DO
	*/
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::iterator
	RedBlackTree<K, V, KV, C, A>::aux_insert_equal_lower(const_reference value)
	throw(::std::bad_alloc)
	{
		/* Iterate from the root until a null node to find the
			equal lower node target */

		Link_type i = get_begin();
		Node_Ptr target = get_end();

		while (i)
		{
			target = i;
			/* Search the lower equal node */
			if (!key_compare(sget_key(i), Key_Val(value)))
				sget_left(i);
			else
				sget_right(i);
		}
		return (aux_insert_lower(target, value));
	}

	/////////////
	// Erasers //
	/////////////

	/**
	 * 	@brief aux erase
	 * 
	 * 	Starting from @p target erases all the lower and equal nodes.
	 * 	NOTE: Does not rebalance the tree.
	*/
	template <class K, class V, class KV, class C, class A>
	void
	RedBlackTree<K, V, KV, C, A>::aux_erase(Link_type target)
	throw()
	{
		while (target)
		{
			aux_erase(sget_right(target));
			Link_type tmp = target;
			target = sget_left(target);
			drop_node(tmp);
		}
	}

	/**
	 * 	@brief aux erase
	 * 
	 * 	Erase the data at @p pos and rebalance the tree.
	*/
	template <class K, class V, class KV, class C, class A>
	void
	RedBlackTree<K, V, KV, C, A>::aux_erase(const_iterator pos)
	throw()
	{
		/* Unlink and rebalance */
		Link_type target =
		static_cast<Link_type>(aux_rebalance_for_erase(
			const_cast<Node_Ptr>(pos.node), header));
			
		/* Remove the node */
		drop_node(target);
		tree_count--;
	}

	/**
	 * 	@brief aux erase
	 * 
	 * 	Erase the data in range @p first - @p past.
	*/
	template <class K, class V, class KV, class C, class A>
	void
	RedBlackTree<K, V, KV, C, A>::aux_erase(const_iterator first, const_iterator last)
	throw()
	{
		/* Check if no rebalance is needed */
		if (first == begin() && last == end())
			clear();
		/* Erase in range and rebalance durring the process */
		else
			while (first != last)
				aux_erase(first++);
	}

	/////////////////////
	// Lookup handlers //
	/////////////////////

	/**
	 * 	@brief aux lower bound
	 * 
	 * 	@param x
	 * 	@param y
	 * 	@param k A key.
	 * 
	 * 	@return An iterator of the last element of the maching subsequence
	 * 	 with @p k.
	*/
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::iterator
	RedBlackTree<K, V, KV, C, A>::aux_lower_bound(Link_type x, Node_Ptr y, const key_type& k)
	throw()
	{
		while (x)
		{
			/* For each comparision update y */
			if (!key_compare(sget_key(x), k))
			{
				y = x;
				x = sget_left(x);
			}
			else
				x = sget_right(x);
		}
		/* Return an iterator to the last maching comparision */
		return (iterator(y));
	}

	/**
	 * 	@brief aux lower bound
	 * 
	 * 	@param x
	 * 	@param y
	 * 	@param k A key.
	 * 
	 * 	@return A const iterator of the last element of the maching subsequence
	 * 	 with @p k.
	*/
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::const_iterator
	RedBlackTree<K, V, KV, C, A>::aux_lower_bound(Const_Link_type x, Const_Node_Ptr y, const key_type& k) const
	throw()
	{
		while (x)
		{
			/* For each comparision update y */
			if (!key_compare(sget_key(x), k))
			{
				y = x;
				x = sget_left(x);
			}
			else
				x = sget_right(x);
		}
		/* Return a const iterator to the last maching comparision */
		return (const_iterator(y));
	}

	/**
	 * 	@brief aux upper bound
	 * 
	 * 	@param x
	 * 	@param y
	 * 	@param k A key.
	 * 
	 * 	@return An iterator of the first element of the maching subsequence
	 * 	 with @p k.
	*/
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::iterator
	RedBlackTree<K, V, KV, C, A>::aux_upper_bound(Link_type x, Node_Ptr y, const key_type& k)
	throw()
	{
		while (x)
		{
			/* For each false comparision update y */
			if (key_compare(k, sget_key(x)))
			{
				y = x;
				x = sget_left(x);
			}
			else
				x = sget_right(x);
		}
		/* Return a iterator to the first maching comparision */
		return (iterator(y));
	}

	/**
	 * 	@brief aux upper bound
	 * 
	 * 	@param x
	 * 	@param y
	 * 	@param k A key.
	 * 
	 * 	@return A const iterator of the first element of the maching subsequence
	 * 	 with @p k.
	*/
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::const_iterator
	RedBlackTree<K, V, KV, C, A>::aux_upper_bound(Const_Link_type x, Const_Node_Ptr y, const key_type& k) const
	throw()
	{
		while (x)
		{
			/* For each false comparision update y */
			if (key_compare(k, sget_key(x)))
			{
				y = x;
				x = sget_left(x);
			}
			else
				x = sget_right(x);
		}
		/* Return a const iterator to the first maching comparision */
		return (const_iterator(y));
	}

	////////////////////
	// Node allocator //
	////////////////////

	/**
	 * 	@brief Constructor
	 * 
	 * 	Init a Red Black tree.
	*/
	template <class K, class V, class KV, class C, class A>
	RedBlackTree<K, V, KV, C, A>::Node_Alloc::Node_Alloc(RedBlackTree& t)
	: rbtree(t)
	{ }

	/**
	 * 	@brief operator()
	 * 
	 * 	Allocates a new node in the constructed tree
	*/
	template <class K, class V, class KV, class C, class A>
	template <typename Arg>
	typename RedBlackTree<K, V, KV, C, A>::Link_type
	RedBlackTree<K, V, KV, C, A>::Node_Alloc::operator()(const Arg arg)
	throw (std::bad_alloc)
	{ return (rbtree.create_node(arg)); }


	//////////////////////
	// Member functions //
	//////////////////////

	/**
	 * 	@brief Default Constructor
	*/
	template <class K, class V, class KV, class C, class A>
	RedBlackTree() { }

	/**
	 * 	@brief Constructor
	 * 
	 * 	@param cmp A compare function
	 * 	@param alloc An allocator.
	*/
	template <class K, class V, class KV, class C, class A>
	RedBlackTree<K, V, KV, C, A>::RedBlackTree(const Compare& cmp, const allocator_type& alloc)
	: RBT_Base(cmp, Node_Ptr(alloc))
	{ }

	/**
	 * 	@brief Copy Contructor
	 * 
	 * 	@param other A RedBlackTree with the same type of @c *this.
	*/
	template <class K, class V, class KV, class C, class A>
	RedBlackTree<K, V, KV, C, A>::RedBlackTree(const RedBlackTree& other)
	: Node_Ptr(other.header) // TO DO: Header is possible wrong here, i think i need a constructor for count and header
	{
		if (other.get_root())
			get_root() = aux_copy(other);
	}

	/**
	 * 	@brief Destructor
	*/
	template <class K, class V, class KV, class C, class A>
	RedBlackTree<K, V, KV, C, A>::~RedBlackTree()
	{ aux_erase(get_begin()); }

	///////////////
	// Iterators //
	///////////////

	/**
	 * 	@brief begin
	 * 
	 * 	@return An iterator to the first position.
	*/
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::iterator
	RedBlackTree<K, V, KV, C, A>::begin()
	{ return (iterator(get_leftmost())); }

	/**
	 * 	@brief begin
	 * 
	 * 	@return A const iterator to the first position.
	*/
	template <class K, class V, class KV, class C, class A>
	RedBlackTree<K, V, KV, C, A>::const_iterator
	begin() const
	{ return (const_iterator(get_leftmost())); }

	/**
	 * 	@brief end
	 * 
	 * 	@return An iterator to the last position.
	*/
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::iterator
	RedBlackTree<K, V, KV, C, A>::end()
	{ return (iterator(&header)); }

	/**
	 * 	@brief begin
	 * 
	 * 	@return A const iterator to the last position.
	*/
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::const_iterator
	RedBlackTree<K, V, KV, C, A>::end() const
	{ return (const_iterator(&header)); }

	/**
	 * 	@brief rbegin
	 * 
	 * 	@return A reverse iterator to the last position.
	*/
	template <class K, class V, class KV, class C, class A>
	reverse_iterator	rbegin()
	{
		return (reverse_iterator(end()));
	}

	/**
	 * 	@brief rbegin
	 * 
	 * 	@return A const reverse iterator to the last position.
	*/
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::const_reverse_iterator
	RedBlackTree<K, V, KV, C, A>::rbegin() const
	{ return (const_reverse_iterator(end())); }

	/**
	 * 	@brief rend
	 * 
	 * 	@return A reverse iterator to the first position.
	*/
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::reverse_iterator
	RedBlackTree<K, V, KV, C, A>::rend()
	{ return (reverse_iterator(begin())); }

	/**
	 * 	@brief rbegin
	 * 
	 * 	@return A const reverse iterator to the first position.
	*/
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::const_reverse_iterator
	RedBlackTree<K, V, KV, C, A>::rend() const
	{ return (const_reverse_iterator(begin())); }

	//////////////
	// Capacity //
	//////////////

	/**
	 * 	@brief empty
	 * 
	 * 	@return True if the %RedBlackTree is empty.
	*/
	template <class K, class V, class KV, class C, class A>
	bool
	RedBlackTree<K, V, KV, C, A>::empty() const
	{ return (count == 0); }

	/**
	 * 	@brief size
	 * 
	 * 	@return The number of nodes holded by the %RBT.
	*/
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::size_type
	RedBlackTree<K, V, KV, C, A>::size() const
	{ return (count); }

	/**
	 * 	@brief max_size
	 * 
	 * 	@return The maximun number of elemens that %RBT can hold.
	*/
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::size_type
	RedBlackTree<K, V, KV, C, A>::max_size() const
	{ return (size_type(std::numeric_limits<size_type>::max() / sizeof(value_type))); }

	///////////////
	// Modifiers //
	///////////////

	/**
	 * 	@brief clear
	 * 
	 * 	Empty the %RBT.
	*/
	template <class K, class V, class KV, class C, class A>
	void
	RedBlackTree<K, V, KV, C, A>::clear()
	{
		aux_erase(begin());
		header.Node_reset(); // Not 100% sure about this.
	}

	/**
	 * 	@brief Erase
	 * 
	 * 	@param pos An iterator.
	 * 
	 * 	Removes the values holded at @p pos.
	*/
	template <class K, class V, class KV, class C, class A>
	void
	RedBlackTree<K, V, KV, C, A>::erase(iterator pos)
	{ aux_erase(pos); }

	/**
	 * 	@brief Erase
	 * 
	 * 	@param pos A const iterator.
	 * 
	 * 	Removes the values holded at @p pos.
	*/
	template <class K, class V, class KV, class C, class A>
	void
	RedBlackTree<K, V, KV, C, A>::erase(const_iterator pos)
	{ aux_erase(pos); }

	/**
	 * 	@brief Erase
	 * 
	 * 	@param k A key.
	 * 
	 * 	Removes the values maching with the key @p k.
	*/
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::size_type
	RedBlackTree<K, V, KV, C, A>::erase(const key_type& k)
	{
		const size_type old_size = size();
		std::pair<iterator, iterator> pos = equal_range(k);

		aux_erase(pos.first, pos.second);
		return (old_size - size());
	}

	/**
	 * 	@brief Erase
	 * 
	 * 	@param first An iterator.
	 * 	@param last An iterator.
	 * 
	 * 	Removes the values in range @p first - @p last.
	*/
	template <class K, class V, class KV, class C, class A>
	void
	RedBlackTree<K, V, KV, C, A>::erase(iterator first, iterator last)
	{ aux_erase(first, last); }

	/**
	 * 	@brief Erase
	 * 
	 * 	@param first A const iterator.
	 * 	@param last A const iterator.
	 * 
	 * 	Removes the values in range @p first - @p last.
	*/
	template <class K, class V, class KV, class C, class A>
	void
	RedBlackTree<K, V, KV, C, A>::erase(const_iterator first, const_iterator last)
	{ aux_erase(first, last); }


	/**	
	 * 	@brief swap
	 * 
	 * 	Swap @c *this with @p other.
	*/
	template <class K, class V, class KV, class C, class A>
	void
	RedBlackTree<K, V, KV, C, A>::swap(RedBlackTree& other)
	{
		// TO DO: Implement move data
	}

	////////////
	// Lookup //
	////////////

	/**
	 * 	@brief count
	 * 
	 * 	@return The number of matches with the key @p k.
	*/
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::size_type
	RedBlackTree<K, V, KV, C, A>::count(const key_type& k) const
	{
		std::pair<const_iterator, const_iterator> match = equal_range(k);
		return (size_type(distance(match.first, match.second)));
	}

	/**
	 * 	@brief find
	 * 
	 * 	@param k A key.
	 * 
	 * 	Search for a pair unsing the given @p k key and return an
	 * 	iterator pointing to the matching node.
	*/
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::iterator
	RedBlackTree<K, V, KV, C, A>::find(const key_type& k)
	{
		/* Get the last match in a subsequence that matchs with the key k. */
		iterator match = aux_lower_bound(get_begin(), get_end(), k);

		/* Check for the end or return the lower match */
		if (match == end() || key_compare(k, sget_key(match.node)))
			return (end());
		else
			return (match);
	}

	/**
	 * 	@brief find
	 * 
	 * 	@param k A key.
	 * 
	 * 	Search for a pair unsing the given @p k key and return an
	 * 	iterator pointing to the matching node.
	*/
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::const_iterator
	RedBlackTree<K, V, KV, C, A>::find(const key_type& k) const
	{
		/* Get the last match in a subsequence that matchs with the key k. */
		const_iterator match = aux_lower_bound(get_begin(), get_end(), k);

		/* Check for the end or return the lower match */
		if (match == end() || key_compare(k, sget_key(match.node)))
			return (end());
		else
			return (match);
	}

	/**
	 * 	@brief Equal range
	 * 
	 * 	@param key A key.
	 * 
	 * 	@return Return a pair of iterators pointing the maching
	 * 	 @p k key.
	*/
	template <class K, class V, class KV, class C, class A>
	::std::pair<typename RedBlackTree<K, V, KV, C, A>::iterator, typename RedBlackTree<K, V, KV, C, A>::iterator>
	RedBlackTree<K, V, KV, C, A>::equal_range(const key_type& k)
	{
		/* Update y, iterate with x */
		Link_type x = get_begin();
		Link_type y = get_end();

		while (x)
		{
			/* Key check is false go right */
			if (key_compare(sget_key(x), k))
				x = sget_right(x);

			/* Inverse key check false go left */
			else if (key_compare(k, sget_key(x))
			{
				/* Store last left node */
				y = x;
				x = sget_left(x);
			}

			/* Match */
			else
			{
				/* Calc the range of the matches and return them */
				Link_type x_right = sget_right(x);
				y = x;
				x = sget_left(x);
				return (std::pair<iterator, iterator>(aux_lower_bound(x, y, k),
					 aux_upper_bound(x_right, y, k)));
			}
		}
			
		/* No match */
		return (std::pair<iterator, iterator>(iterator(y), iterator(y)));
	}

	/**
	 * 	@brief Equal range
	 * 
	 * 	@param key A key.
	 * 
	 * 	@return Return a pair of const iterators pointing the maching
	 * 	 @p k key.
	*/
	template <class K, class V, class KV, class C, class A>
	std::pair<typename RedBlackTree<K, V, KV, C, A>::const_iterator, typename RedBlackTree<K, V, KV, C, A>::const_iterator>
	RedBlackTree<K, V, KV, C, A>::equal_range(const key_type& k) const
	{
		/* Update y, iterate with x */
		Const_Link_type x = get_begin();
		Const_Link_type y = get_end();

		while (x)
		{
			/* Key check is false go right */
			if (key_compare(sget_key(x), k))
				x = sget_right(x);

			/* Inverse key check false go left */
			else if (key_compare(k, sget_key(x))
			{
				/* Store last left node */
				y = x;
				x = sget_left(x);
			}

			/* Match */
			else
			{
				/* Calc the range of the matches and return them */
				Const_Link_type x_right = sget_right(x);
				y = x;
				x = sget_left(x);
				return (std::pair<const_iterator, const_iterator>(aux_lower_bound(x, y, k),
					 aux_upper_bound(x_right, y, k)));
			}
		}
			
		/* No match */
		return (std::pair<const_iterator, const_iterator>(iterator(y), iterator(y)));
	}

	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::iterator
	RedBlackTree<K, V, KV, C, A>::lower_bound(const key_type& k)
	{ return (aux_lower_bound(get_begin(), get_end(), k)); }

	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::const_iterator
	RedBlackTree<K, V, KV, C, A>::lower_bound(const key_type& k) const
	{ return (aux_lower_bound(get_begin(), get_end(), k)); }

	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::iterator
	upper_bound(const key_type& k)
	{ return (aux_upper_bound(get_begin(), get_end(), k)); }

	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::const_iterator
	RedBlackTree<K, V, KV, C, A>::upper_bound(const key_type& k) const
	{ return (aux_upper_bound(get_begin(), get_end(), k)); }

	///////////////
	// Observers //
	///////////////

	/**
	 * 	@brief key_comp
	 * 
	 * 	@return The %RedBlackTree key compare.
	*/
	template <class K, class V, class KV, class C, class A>
	typename RedBlackTree<K, V, KV, C, A>::Compare
	RedBlackTree<K, V, KV, C, A>::key_comp() const
	{ return (key_compare); }

	/////////////////
	// Non members //
	/////////////////

	//@{
	/**
	 * 	@brief Boolean comparison
	 * 
	 * 	@param lhs A %RBT
	 * 	@param rhs A %RBT with the same type of @p lhs.
	 * 
	 * 	@return The boolean result of the requested operation.
	*/
	template <class K, class V, class KV, class C, class A>
	inline bool
	operator==(const RedBlackTree<K, V, KV, C, A>& lhs, const RedBlackTree<K, V, KV, C, A>& rhs)
	{ return (lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

	template <class K, class V, class KV, class C, class A>
	inline bool
	operator<(const RedBlackTree<K, V, KV, C, A>& lhs, const RedBlackTree<K, V, KV, C, A>& rhs)
	{ return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), ehs.end())); }

	template <class K, class V, class KV, class C, class A>
	inline bool
	operator!=(const RedBlackTree<K, V, KV, C, A>& lhs, const RedBlackTree<K, V, KV, C, A>& rhs)
	{ return (!(lhs == rhs)); }

	template <class K, class V, class KV, class C, class A>
	inline bool
	operator>(const RedBlackTree<K, V, KV, C, A>& lhs, const RedBlackTree<K, V, KV, C, A>& rhs)
	{ return (rhs < lhs); }

	template <class K, class V, class KV, class C, class A>
	inline bool
	operator<=(const RedBlackTree<K, V, KV, C, A>& lhs, const RedBlackTree<K, V, KV, C, A>& rhs)
	{ return (!(lhs > rhs)); }

	template <class K, class V, class KV, class C, class A>
	inline bool
	operator>=(const RedBlackTree<K, V, KV, C, A>& lhs, const RedBlackTree<K, V, KV, C, A>& rhs)
	{ return (!(lhs < rhs)); }
	//@}

	/**
	 * 	@brief swap
	 * 
	 * 	Specialised swap made to swap %RBT.
	*/
	template <typename Key, typename T, typename Key_Val, typename Compare, typename Alloc>
	inline void
	swap(const RedBlackTree<Key, T, Key_Val, Compare, Alloc>& lhs, const RedBlackTree<Key, T, Key_Val, Compare, Alloc>& rhs)
	{ lhs.swap(rhs); }

	// TO DO: l 1764 operator= NOT IMPL HERE 
};