
/**	@file deque.hpp
 * 
 *	This file contains the deque container implementation.
*/

# pragma once

# include <ft_containers.hpp>

# define FT_MAX(x, y) x > y ? x : y

/**
 * 	@brief Deque node size MACROS
 * 
 * 	@param x Use to be size_of(T).
 * 
 * 	Used to define the max size of a node (node: see later).
 * 	The size is @b 512 and is overwritable if needed, but the idea
 * 	is to keep constant node sizes to optimize the allocation
 * 	functions using always small sizes.
*/
#ifndef FT_DEQUE_BUFF_SIZE
# define FT_DEQUE_BUFF_SIZE 0x200
#endif

# define FT_DEQUE_GET_BUFF_SIZE(x) x < FT_DEQUE_BUFF_SIZE ? std::size_t(FT_DEQUE_BUFF_SIZE / size) : std::size_t(0x1)

namespace FT_NAMESPACE
{
	/**
	 * 	@brief Deque iterator
	 * 
	 * 	@tparam T The type holded by the deque container.
	 * 	@tparam Ref_T A mtable or const reference to T
	 * 	@tparam Ptr_T A mutable or const pointer to T
	 * 
	 * 	Implementation of deque iterator class, this class as also used
	 * 	to deque management. In fact is part of the core algorithm of deque.
	 * 	Deque class holds 2 @c deque_iterator that defines the front and the back
	 * 	of the deque.
	*/
	template <class T, typename Ref_T, typename Ptr_T>
	struct deque_iterator
	{
		// 	Note: Node and Map concept haven't nothing in common to map container or linked-list nodes.

		/* Member types */

		public:

		typedef T				value_type;
		typedef	Ptr_T			pointer;
		typedef Ref_T			reference;
		typedef std::size_t		size_type;
		typedef std::ptrdiff_t	difference_type;
		typedef deque_iterator	Self;

		/* Note: Typedefs {const_reference} and {const_pointer} aren't the
			same as typedefs const {reference} and const {pointer} when
			the deque_iterator is a {const_iterator} */
		typedef const value_type&									const_reference;
		typedef const value_type*									const_pointer;
		typedef Self<value_type, value_type&, value_type*>			iterator;
		typedef Self<value_type, const_reference, const_pointer>	const_iterator;

		/* Core types (see: explenation in deque class) */
		typedef	value_type*		Node_ptr;
		typedef Node_ptr*		Map_ptr;

		/**
		 * 	@brief get_node_size
		 * 
		 * 	Fast-use of the MACROS.
		*/
		size_type				get_node_size() { return (FT_DEQUE_BUFF_SIZE(sizeof(value_type)); }

		/* Core:
		* (see: futher explenation in deque class)
		* - curr -> points to the current element in the node.
		* - head -> points to the first element in the node.
		* - tail -> points to the last element in the node.
		* - node -> points to the current node.
		*/
		Node_ptr		curr;
		Node_ptr		head;
		Node_ptr		tail;
		Map_ptr			node;

		/**
		 * 	@brief Default Constructor
		*/
		deque_iterator() : curr(), head(), tail(), node() { }

		/**
		 * 	@brief Constructor
		 * 
		 * 	@param pos The index in the deque.
		 * 	@param map The index node in the map.
		*/
		deque_iterator(Node_ptr pos, Map_ptr map)
		: curr(pos), head(*map), tail(Node_ptr(*map + difference_type(get_node_size()))), node(map) { }

		/**
		 * 	@brief Conversion iterator to const_iterator Constructor.
		*/
		deque_iterator(const_iterator& other)
		: curr(other.curr), head(other.head), tail(other.tail), node(other.node) { }

		/**
		 * 	@brief Change node
		 *
		 * 	@param new_node The new host node.
		 *
		 * 	Migrates all the control data core to @a new_node
		 * 	execpt @c curr.
		*/
		void		it_change_node(Map_ptr new_node)
		{
			node = new_node;
			head = *node;
			tail = Node_ptr(head + difference_type(get_node_size()));
		}

		public:

		//@{
		/**
		 * 	@brief deque_iterator overload operators
		*/
		reference		operator*() const
		{
			return (*curr);
		}

		pointer			operator->()
		{
			return (curr);
		}

		Self&			operator++()
		{
			if (++curr == tail)
			{
				it_change_node(node + 1);
				curr = head;
			}
			return (*this);
		}

		Self			operator++(int)
		{
			Self tmp = *this;
			++(*this);
			return (tmp);
		}

		Self&			operator--()
		{
			if (--curr == tail)
			{
				it_change_node(node - 1);
				curr = head;
			}
			return (*this);
		}

		Self			operator--(int)
		{
			Self tmp = *this;
			--(*this);
			return (tmp);
		}

		Self&			operator+=(difference_type n)
		{
			const difference_type amount = n + (curr - head);

			/* Smaller than the remening space in the curr node */
			if (amount >= 0 && amount < difference_type(get_node_size()))
				curr += amount;
			/* Or need to change fill more node(s) */
			else 
			{
				// Handle addition or substraction
				const difference_type map_index = amount > 0
					? amount / difference_type(get_node_size())
					: -difference_type(amount - 1);
				it_change_node(node + map_index);
				/* Update the current index */
				curr = head + (amount - map_index * difference_type(get_node_size()));
			}
		}

		Self&			operator-=(difference_type n)
		{
			return (*this -= -n );
		}

		reference		operator[](difference_type n) const
		{
			return (*(this + n));
		}

		/**
		 * 	@brief Boolean operators
		 * 
		 * 	@param lhs A %deque_iterator.
		 * 	@param rhs A %deque_iterator with the same type of @p lhs.
		 * 	@return The result of the requested operation.
		*/
		friend bool		operator==(const_reference lhs, const_reference rhs)
		{
			return (lhs.curr == rhs.curr);
		}

		friend bool		operator!=(const_reference lhs, const_reference rhs)
		{
			return (lhs.curr != rhs.curr);
		}

		friend bool		operator<(const_reference lhs, const_reference rhs)
		{
			return (lhs.curr < rhs.curr);
		}

		friend bool		operator<=(const_reference lhs, const_reference rhs)
		{
			return (lhs.curr <= rhs.curr);
		}

		friend bool		operator>(const_reference lhs, const_reference rhs)
		{
			return (lhs.curr > rhs.curr);
		}

		friend bool		operator>=(const_reference lhs, const_reference rhs)
		{
			return (lhs.curr >= rhs.curr);
		}

		/**
		 * 	@brief Boolean operators
		 * 
		 * 	@tparam _T_Ref a reference to T that could be const or mutable.
		 * 	@tparam _T_Ptr a pointer to T that could be const or mutable.
		 * 	@param lhs A %deque_iterator.
		 * 	@param rhs A %deque_iterator.
		 * 	@return The result of the requested operation.
		 * 
		 * 	Note: One of both is a const_iterator.
		*/
		template <typename _T_Ref, typename _T_Ptr>
		friend bool		operator==(const_reference lhs, const deque_iterator<T, _T_Ref, _T_Ptr>&  rhs)
		{
			return (lhs.curr == rhs.curr);
		}

		template <typename _T_Ref, typename _T_Ptr>
		friend bool		operator!=(const_reference lhs, const deque_iterator<T, _T_Ref, _T_Ptr>& rhs)
		{
			return (lhs.curr != rhs.curr);
		}

		template <typename _T_Ref, typename _T_Ptr>
		friend bool		operator<(const_reference lhs, const deque_iterator<T, _T_Ref, _T_Ptr>& rhs)
		{
			return (lhs.curr < rhs.curr);
		}

		template <typename _T_Ref, typename _T_Ptr>
		friend bool		operator<=(const_reference lhs, const deque_iterator<T, _T_Ref, _T_Ptr>& rhs)
		{
			return (lhs.curr <= rhs.curr);
		}

		template <typename _T_Ref, typename _T_Ptr>
		friend bool		operator>(const_reference lhs, const deque_iterator<T, _T_Ref, _T_Ptr>& rhs)
		{
			return (lhs.curr > rhs.curr);
		}

		template <typename _T_Ref, typename _T_Ptr>
		friend bool		operator>=(const_reference lhs, const deque_iterator<T, _T_Ref, _T_Ptr>& rhs)
		{
			return (lhs.curr >= rhs.curr);
		}

		/**
		 * 	@brief operator-+
		 * 
		 * 	@return The arithmetic operation between @p lhs and @p rhs.
		*/
		template <typename _T_Ref, typename _T_Ptr>
		friend difference_type	operator-(const_reference lhs, deque_iterator<T, _T_Ref, _T_Ptr>& rhs)
		{
			return (difference_type(difference_type(get_node_size()) * difference_type(lhs.node - rhs.node - 1) + difference_type(lhs.curr - lhs.head) + difference_type(rhs.tail - rhs.curr)));
		}

		friend Self				operator-(const_reference lhs, difference_type n)
		{
			Self tmp = lhs;
			tmp -= n;
			return (tmp);
		}

		friend Self				operator+(const_reference x, difference_type n)
		{
			Self tmp = x;
			tmp += n;
			return (tmp);
		}

		friend Self				operator+(difference_type n, const_reference x)
		{
			return (x + n);
		}
	};

	/**
	 * 	@brief deque_algorithm
	 * 
	 * 	This class is the base class of @c deque it allocates and destroy but dont
	 * 	initialise the data
	*/
	template <class T, class Allocator>
	class deque_algorithm
	{
		/* Member types */

		protected:

		typedef T				value_type;
		typedef value_type*		pointer;
		typedef const pointer	const_pointer;
		typedef value_type&		reference;
		typedef const reference	const_reference;
		typedef Allocator		allocator_type;

		typedef deque_iterator<T, reference, pointer>				iterator;
		typedef deque_iterator<T, const_reference, const_pointer>	const_iterator;

		typedef typename iterator::difference_type	difference_type;
		typedef typename iterator::Node_ptr			Node_ptr;
		typedef typename iterator::Map_ptr			Map_ptr;
		typedef typename iterator::size_type		size_type;

		/* Core:
		 * 
		 * head -> A %deque_iterator at the front of the deque.
		 * tail -> A %deque_iterator at the back of the deque.
		 * map -> An array of pointer to arrays of T.
		 * map_size -> The size of the map. */
		iterator		head;
		iterator		tail;
		Map_ptr			map;
		size_type		map_size;

		allocator_type	memory;
		enum { map_initial_size = 8 };

		/* Constructor */

		/**
		 * 	@brief Default Constructor
		*/
		deque_algorithm() : head(), tail(), map(), map_size() { }

		deque_algorithm(const allocator_type& alloc) : memory(alloc) { }

		using iterator::get_node_size;

		/**
		 * 	@brief Allocate node
		 * 
		 * 	Fast use of allocator.
		*/
		pointer		alg_allocate_node()
		{
			return (memory.allocate(get_node_size()))
		}

		/**
		 * 	@brief Deallocate node
		 * 
		 * 	Fast use deallocator
		*/
		void		alg_deallocate_node(pointer p)
		{
			memory.deallocate(p, get_node_size());
		}

		/**
		 * 	@brief Allocate map
		 * 
		 * 	Fast use of allocator.
		*/
		pointer		alg_allocate_map(size_type n)
		{
			return (memory.allocate(n));
		}

		/**
		 * 	@brief Deallocate map
		 * 
		 * 	Fast use deallocator
		*/
		void		alg_deallocate_map(pointer p, size_type n)
		{
			memory.deallocate(p, n);
		}

		/**
		 * 	@brief Destroy nodes
		 * 
		 * 	@param first A Map_ptr.
		 * 	@param last A Map_ptr.
		 * 
		 * 	Deallocates the nodes in range @p first - @p last.
		*/
		void		alg_destroy_nodes(Map_ptr first, Map_ptr last)
		{
			for (Map_ptr i = first ; i < last ; i++)
				alg_deallocate_node(*i);
		}

		/**
		 * 	@brief Create nodes
		 * 
		 * 	@param first A Map_ptr.
		 * 	@param last A Map_ptr.
		 * 	
		 * 	Allocates nodes in range @p first - @p last.
		 * 
		 * 	@throw std::bad_alloc.
		*/
		void		alg_create_node(Map_ptr first, Map_ptr last)
		{
			Map_ptr	curr;

			try {
				for (curr = first ; curr < last ; curr++)
					curr = alg_allocate_node();
			} catch(std::bad_alloc& e) {
				alg_destroy_nodes(first, curr);
				throw;
			}
		}

		/**
		 * 	@brief Itatialise map
		 * 
		 * 	@param n The len of the map.
		 * 
		 * 	@throw std::bad_alloc.
		*/
		void		alg_init_map(size_type n)
		{
			const size_type		num_nodes = (n / get_node_size()) + 1;

			map_size = size_type(FT_MAX(map_initial_size, num_nodes + 2));
			map = alg_allocate_map(map_size);

			Map_ptr		map_first = (map  + map_size - num_nodes) / 2;
			Map_ptr		map_last = map_first + num_nodes;

			try {
				alg_create_nodes(map_first, map_last);
			}
			catch (std::bad_alloc& e) { 
				alg_deallocate_map(map, map_size);
				throw;
			}

			head.it_change_node(map_first);
			tail.it_change_node(map_last - 1);
			head.curr = head.head;
			tail.curr = tail.head + num_nodes % get_node_size();
		}
	};

	// to do deque description tomorrow + deque implementation
};