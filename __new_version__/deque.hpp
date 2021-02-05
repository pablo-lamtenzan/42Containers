
/**	@file deque.hpp
 * 
 *	This file contains the deque container implementation.
*/

# pragma once

# include <ft_iterator.hpp>
# include <ft_allocator.hpp>

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
		void		alg_create_nodes(Map_ptr first, Map_ptr last)
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
		 * 	@param n The len of the %deque.
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

	/**
	 * 	@brief Deque
	 * 
	 * 	@tparam T the type holded by a deque elemement.
	 * 	@tparam Allocator An allocator type.
	 * 
	 * 	Front/Back insertion optimised %vector. A deque contains 4 members:
	 *
	 * 	- T**			map
	 * 	- std::size_t	map_size;
	 * 	- iterator		head, tail
	 * 	
	 * 	%map_size is at least 8, %map is an array of pointers to arrays of T type,
	 * 	%head and %tail are the front and the back of the deque. Each pointer to array
	 * 	in %map is called a "node". Each node contains a max size of T elems that is the max
	 * 	fast alloction size. The greather will be the size of T less elements a node will hold.
	 * 
	 * 	The first node starts at position (%map + %map_size) / 2, more nodes can be appended or
	 * 	prepended. %head point to the first element in the first node and %tail points to the last
	 * 	element in the last node. If the %deque contains more elements than %map_size, %map is
	 * 	reallocated with a greather size.
	 * 
	 * 	This algorithm is faster than %vector algorithm. Each time a %vector need to increase it capacity,
	 * 	all its elements must be copied in the new %vector. In a %deque only the pointers to the nodes will
	 * 	be copied when an incrementation of the capacity is needed. This optimisations are the same of insertion
	 * 	and deletion of elements.
	*/
	template <class T, class Allocator = allocator<T>>
	class deque : protected deque_algorithm<T, Allocator>
	{
		/* Member types */

		typedef deque_algorithm<T, Allocator>	Base;
		typedef typename Base::Node_ptr			Node_ptr;
		typedef typename Base::Map_ptr			Map_ptr;

		public:

		typedef typename Base::value_type		value_type;
		typedef typename Base::size_type		size_type;
		typedef typename Base::difference_type	difference_type;
		typedef typename Base::allocator_type	allocator_type;
		typedef value_type&						reference;
		typedef typename Base::const_reference	const_reference;
		typedef value_type*						pointer;
		typedef typename Base::const_pointer	const_pointer;
		typedef typename Base::iterator			iterator;
		typedef typename Base::const_iterator	const_iterator;
		typedef reverse_iterator<iterator>			reverse_iterator;
		typedef reverse_iterator<const_iterator>	const_reverse_iterator;

		using iterator::get_node_size;
		using Base::alg_allocate_node;
		using Base::alg_deallocate_node;
		using Base::alg_allocate_map;
		using Base::alg_deallocate_map;
		using Base::alg_destroy_nodes;
		using Base::alg_create_nodes;
		using Base::alg_init_map;

		using Base::head;
		using Base::tail;
		using Base::map;
		using Base::map_size;
		using Base::memory;

		/* Auxliar functions */

		private:

		/**
		 * 	@brief destruct node in range
		 * 
		 * 	@param first A pointer to T.
		 * 	@param last A pointer to T.
		 * 
		 * 	Destructs elements in a node range @p first - @p last.
		*/
		static void		dq_destroy_node_in_range(Node_ptr first, Node_ptr last)
		{
			for (Node_ptr i = first ; i < last ; i++)
				memory.destroy(i);
		}

		/**
		 * 	@brief destruct and deallocate a node
		 * 
		 * 	@param target The node that each element will be destroyed.
		*/
		static void		dq_destroy_node(Node_ptr target)
		{
			dq_destroy_node_in_range(target, Node_ptr(target + get_node_size()));
			alg_deallocate_node(target);
		}

		/**
		 * 	@brief destroy in range
		 * 
		 * 	@param firts An %iterator.
		 * 	@param last An %interator.
		 * 
		 * 	Destroys whatever is between @p first and @p last.
		*/
		static void		dq_destroy_in_range(iterator first, iterator last)
		{
			/* Destroy all nodes except the edges */
			for (Map_ptr i = first.node + 1 ; i < last.node ; i++)
				dq_destroy_node(*i);
			/* Destroy the remaining ranges in the edges:
				- first.curr - firts.tail
				- last.head - last.curr */
			if (first.node != last.node)
			{
				dq_destroy_node_in_range(first.curr, first.tail);
				alg_deallocate_node(first);
				dq_destroy_node_in_range(last.head, last.curr);
				alg_deallocate_node(last);
			}
			else
			{
				dq_destroy_node_in_range(first.curr, last.curr);
				alg_deallocate_node(first);
			}
		}

		public:
		/**
		 * 	@brief Default Constructor
		*/
		deque() { }

		/**
		 * 	@brief Constructor
		 * 
		 * 	@param n The number of elements holded by the %deque.
		 * 	@param value The default value of each element.
		 * 	@param alloc An allocator type.
		*/
		explicit deque(size_type n, const_reference value = value_type(), const allocator_type& alloc = allocator_type())
		: Base(alloc)
		{
			alg_init_map(n);
			assign(head, tail, value); // TO DO: Use it if it definition of assign exist
		}

		/**
		 * 	@brief Copy Constructor
		 *
		 * @param other A %deque with same T of @c *this.
		*/
		deque(const deque& other) : base(other.memory)
		{
			alg_init_map(other.size()); // Or capacity ?
			assign(other.begin(), other.end());
		}

		/**
		 * 	@brief Range Constructor
		 * 
		 * 	@tparam InputIt An input iterator.
		 * 	@param first An InputIt.
		 * 	@param end An InputIt
		 * 	@param Alloc An allocator type.
		 * 
		 * 	Init a deque with the values holded in range @p first - @p last.
		*/
		template <typename InputIt>
		deque(InputIt first, InputIt last, const allocator_type) : Base(alloc)
		{
			assign(first, last);
		}

		/**
		 * @brief Destructor
		*/
		deque()
		{
			dq_destroy_in_range(begin(), end());
		}

		/**
		 * 	@brief operator=
		 * 
		 * 	@param other A deque.
		 * 	@return @c *this.
		*/
		deque& 			operator=(const deque& other)
		{
			dq_destroy_in_range(begin(), end());
			// copy form copy constructor
			alg_init_map(other.size()); // Or capacity ?
			assign(other.begin(), other.end());
		}

		/**
		 * 	@brief assign
		 * 
		 * 	@tparam InputIt An input iterator.
		 * 	@param first An InputIt.
		 * 	@param last An InputIt.
		 * 
		 * 	Fills the copy with elements in range @p first - @p last.
		*/
		template <typename InputIt>
		void				assign(InputIt first, InputIt last)
		{
			// TO DO:

			/*
			 1) Need the number of nodes between first and last

			 const size_type s = last - first // need it ?
			 
			 2 ) for (node = first ; node < last ; node ++) // Map_ptr
			 		{
						for (__node = *node ; __node < get_node_size() ; __node++) // Node_ptr
							memory.construct(__node, node)
					}
			
			Notes: - Do it using function no scracth code
					- First and Last node are spetial remember (do like dq_destroy_in_range)
			*/
		}

		/**
		 * 	@brief begin
		 * 
		 * 	@return An iterator to the first element in the %deque.
		*/
		iterator		begin()
		{
			return (head);
		}

		/**
		 * 	@brief begin
		 * 
		 * 	@return A const iterator to the first element in the %deque.
		*/
		const_iterator	begin() const
		{
			return (head);
		}

		/**
		 * 	@brief end
		 * 
		 * 	@return An iterator to the last element in the %deque.
		*/
		iterator		end()
		{
			return (tail);
		}

		/**
		 * 	@brief end
		 * 
		 * 	@return A const iterator to the last element in the %deque.
		*/
		const_iterator			end() const
		{
			return (tail);
		}

		/**
		 * 	@brief rbegin
		 * 
		 * 	@return A reverse iterator to the first element in the %deque.
		*/
		reverse_iterator		rbegin()
		{
			return (reverse_iterator(end() - 1));
		}

		/**
		 * 	@brief rbegin
		 * 
		 * 	@return A const reverse iterator to the first element in the %deque.
		*/
		const_reverse_iterator	rbegin() const
		{
			return (const_reverse_iterator(end() - 1));
		}

		/**
		 * 	@brief rend
		 * 
		 * 	@return A reverse iterator to the last element in the %deque.
		*/
		reverse_iterator		rend()
		{
			return (reverse_iterator(begin()));
		}

		/**
		 * 	@brief rend
		 * 
		 * 	@return A const reverse iterator to the last element in the %deque.
		*/
		const_reverse_iterator	rend() const
		{
			return (const_reverse_iterator(begin()));
		}

		/**
		 * 	@brief size
		 * 
		 * 	@return The current number of element holded by the %deque.
		*/
		size_type		size() const
		{
			return (size_type(tail - head));
		}

		/**
		 * 	@brief max size
		 * 
		 * 	@return The maximun amount of element that the %deque can hold.
		*/
		size_type		max_size() const
		{
			return (size_type(std::numeric_limits<size_type>::max() / sizeof(value_type)));
		}

		/**
		 * 	@brief resize
		 * 
		 * 	@param new_size The new size.
		 * 
		 * 	Change the size of the %deque.
		 * 	Note: if @p new_size > @c this->size() the new elements are unitialised.
		*/
		void			resize(size_type new_size)
		{
			// TO DO:

			/*
				if (new cap > size())
					append unititilised elems
				else
					remove_elems
			*/
		}

		/**
		 * 	@brief resize
		 * 
		 * 	@param new_size The new size.
		 * 	@param value A T type value.
		 * 
		 * 	Change the size of the %deque.
		 * 	Note: if @p new_size > @c this->size() the new elements are itialised with @a value.
		*/
		void			resize(size_type new_size, const_reference value = value_type())
		{
			// TO DO:

			/*
				if (new cap > size())
					append value elems
				else
					remove_elems
			*/
		}

		/**
		 * 	@brief empty
		 * 
		 * 	@return True if the @c *this is empty.
		*/
		bool			empty() const
		{
			return (begin() == end());
		}

		/**
		 * 	@brief operator[]
		 * 
		 * 	@param n An index
		 * 
		 * 	@return A reference to the value indexed at @p n.
		*/
		reference		operator[](size_type n)
		{
			return (head[difference_type(n)]);
		}

		/**
		 * 	@brief operator[]
		 * 
		 * 	@param n An index
		 * 
		 * 	@return A const reference to the value indexed at @p n.
		*/
		const_reference		operator[](size_type n)
		{
			return (head[difference_type(n)]);
		}

		/**
		 * 	@brief at
		 * 
		 * 	@param n An index
		 * 
		 * 	@return A reference to the value indexed at @p n.
		 * 	@throw std::out_of_range if @p n > @c this->size().
		*/
		reference		at(size_type n)
		{
			if (n > size())
				throw std::out_of_range(std::string("deque::_M_range_check: __n "
				       "(which is %zu)>= this->size() "
				       "(which is %zu)"), n, size()); // TO DO: Need a printf
			return (head[difference_type(n)]);
		}

		/**
		 * 	@brief at
		 * 
		 * 	@param n An index
		 * 
		 * 	@return A const reference to the value indexed at @p n.
		 * 	@throw std::out_of_range if @p n > @c this->size().
		*/
		const_reference		at(size_type n)
		{
			if (n > size())
				throw std::out_of_range(std::string("deque::_M_range_check: __n "
				       "(which is %zu)>= this->size() "
				       "(which is %zu)"), n, size()); // TO DO: Need a printf
			return (head[difference_type(n)]);
		}

		/**
		 * 	@brief front
		 * 
		 * 	@return A reference to the first element in the %deque.
		*/
		reference			front()
		{
			return (reference(*begin()));
		}

		/**
		 * 	@brief front
		 * 
		 * 	@return A const reference to the first element in the %deque.
		*/
		const_reference		front() const
		{
			return (const_reference(*begin()));
		}

		/**
		 * 	@brief back
		 * 
		 * 	@return A reference to the last element in the %deque.
		*/
		reference			back()
		{
			return (reference(*--end()));
		}

		/**
		 * 	@brief back
		 * 
		 * 	@return A const reference to the last element in the %deque.
		*/
		const_reference		back() const
		{
			return (const_reference(*--end()));
		}

		/**
		 * 	@brief push front
		 * 
		 *	@param x A T element.
		 *
		 * 	Prepend @p x.
		*/
		void				push_front(const_reference x)
		{
			if (head.curr == head.head)
			{
				// TO DO: Resize front ?
				// To check
			}
			else
				memory.construct(head.curr - 1, x);
			head.curr--;
		}

		/**
		 * 	@brief push back
		 * 
		 *	@param x A T element.
		 *
		 * 	Append @p x.
		*/
		void				push_back(const_reference x)
		{
			if (tail.curr == tail.tail - 1)
				resize(size_type(size() * 2)); // DO TO: The amount of bytes each time i resize
			memory.construct(tail.curr++, x);
		}

		/**
		 * 	@brief pop front
		 * 
		 * 	@removes the first element.
		*/
		void				pop_front()
		{
			if (!empty())
			{
				if (head.curr == head.tail - 1)
				{
					// Check this tail - 1 is the first element ?
				}
				else
					memory.destroy(head.curr++);
			}
		}

		/**
		 * 	@brief pop back
		 * 
		 * 	@removes the first element.
		*/
		void				pop_back()
		{
			if (!empty())
			{
				/* Check if is the begining of a node */
				if (tail.curr == tail.head)
				{
					// TO DO: Change node --> tail = tail - 1
					// TO DO: Update curr = head.tail - 1
					// Check if more operations are needed
				}
				else
					memory.destroy(head.curr--);
			}
		}

		// Insert dependecy
		void				insert(const_iterator pos, value_type amount, const_reference value);

		/**
		 * 	@brief insert
		 * 
		 * 	@param index A const interator into %deque.
		 * 	@param value The iserted value.
		 * 	@return An iterator to the inserted data.
		 * 
		 * 	Insert @c value at @c index (before the current element that is holds at @c index before the call).
		*/
		iterator			insert(const_iterator pos, const_reference value)
		{
			insert(pos, size_type(1), value);
			return (iterator((*this)[pos]));
		}

		void				insert(const_iterator pos, value_type amount, const_reference value)
		{
			// TO DO: Today i m so fcking tired
		}

		template <typename InputIt>
		iterator			insert(const_iterator pos, InputIt first, Inputit last)
		{
			// TO DO: Today i m so fcking tired
		}


		// Erase dependecy
		iterator			erase(iterator first, iterator last)

		/**
		 * 	@brief erase
		 * 
		 * 	@param pos The target iterator.
		 * 	@return An iterator pointing to the next element.
		 * 
		 * 	Remove an element at the index @a pos.
		*/
		iterator			erase(iterator pos)
		{
			return (erase(pos, pos + 1));
		}

		iterator			erase(iterator first, iterator last)
		{
			// TO DO: Today i m so fcking tired
		}

		/**
		 * 	@brief swap
		 * 
		 *	@param other A %vector.
		 *
		 * 	Swap the underlying work data of @c *this and @a other.
		*/
		void			swap(const vector& other)
		{
			alg_swap_data(other); // TO DO Implement this fct lke i did in vector
		}
	};

	//@{
	/** @brief Boolean operators
	 * 
	 * 	@param lhs A %deque.
	 * 	@param rhs A %deque of the same type of @a lhs.
	 * 
	 * 	@return A boolean that is the result of the requested boolean operation.
	*/
	template <class T, class Allocator>
	inline bool			operator==(const deque<T, Allocator>& lhs, const deque<T, Allocator>& rhs)
	{
		// TO DO: Is it worth it to implement std::equal ? 
		return (lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Allocator>
	inline bool			operator<(const deque<T, Allocator>& lhs, const deque<T, Allocator>& rhs)
	{
		return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())));
	}

	template <class T, class Allocator>
	inline bool			operator!=(const deque<T, Allocator>& lhs, const deque<T, Allocator>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Allocator>
	inline bool			operator>(const deque<T, Allocator>& lhs, const deque<T, Allocator>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Allocator>
	inline bool			operator>=(const deque<T, Allocator>& lhs, const deque<T, Allocator>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Allocator>
	inline bool			operator<=(const deque<T, Allocator>& lhs, const deque<T, Allocator>& rhs)
	{
		return (!(last > rhs));
	}

	template <class T, class Allocator>
	void				swap(const deque<T, Allocator>& lhs, const deque<T, Allocator>& rhs)
	{
		lhs.swap(rhs);
	}
};