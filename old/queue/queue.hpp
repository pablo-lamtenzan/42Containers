# pragma once

# include <exception>
# include "../lexicographical_compare.hpp"
/*
** Documentation: https://en.cppreference.com/w/cpp/container/queue
*/

// TO DO: Container is equal to deque by default

namespace ft 
{

	template <class T, class Container>
	class queue
	{
		
		/* Member types */

		public:

		typedef typename container_type		Container;
		typedef typename value_type			Container::value_type;
		typedef typename size_type			Container::size_type;
		typedef typename reference			Container::reference;
		typedef typename const_reference	Container::const_reference;

		/* Object member */

		private:

		struct Node
		{
			/* Object members */

			container_type	c;
			struct Node* 	prev;
			struct Node* 	next;

			/* Constructors */

			Node() { }

			Node(container_type cont)
			{
				try {
					this = new Node;
				}
				catch (std::bad_alloc& e) { std::cerr << e.what() << std::endl; throw ; }
				c = cont;
				prev = NULL;
				next = NULL;
			}

			/* Destructor */

			~Node()
			{
				c->~container_type();
				delete this;
			}
		};
		
		Node*								ebp;
		Node*								eqp;

		/*
		** Adds target before eqp and update eqp to target
		*/
		void								push_front(Node* target)
		{
			if (empty())
				ebp = eqp = target;
			else
			{
				eqp->prev = target;
				target->next = eqp;
				eqp = target;
			}
		}

		/*
		** Clears all the queue and set ebp = eqp = NULL
		*/
		void								clear()
		{
			while (eqp != NULL)
			{
				eqp->~Node();
				eqp = eqp->next;
			}
			ebp = eqp;
		}

		/* Constructors */

		public:

		explicit queue() : ebp(NULL), eqp(NULL) { }
		explicit queue(const Container& cont = Container()) : ebp(Node(cont)), eqp(ebp) { }
		queue(const stack& other) : ebp(Node(other.c)), eqp(ebp) { }

		/* Destructor */
		~queue() { clear(); }

		queue&				operator=(const stack& other)
		{
			if (this != &other)
			{
				clear();
				try {
					for (Node* i = other.ebp ; i != NULL ; i = i->prev)
						push_front(Node(i.c));
				} catch(std::bad_alloc& e)
				{
					if (!empty())
						clear();
					throw ;
				}
			}
			return (*this);
		}

		/* Element access */

		// TO DO: What to do if ebp or eqp are NULL ? (for the moment it segfualt, but have it to segfault ?) 

		reference			front()
		{
			return (eqp->c);
		}

		const_reference		front() const
		{
			return (eqp->c);
		}

		reference			back()
		{
			return (ebp->c);
		}

		const_reference		back() const
		{
			return (ebp->c);
		}

		/* Capacity */

		bool				empty() const { return (eqp == NULL && ebp == NULL); }

		size_type			size() const
		{
			size_type		s = 0;

			if (empty())
				return (s);
			for (Node* i = ebp ; i != NULL ; i = i->prev)
				s++;
			return (s);
		}

		/* Modifiers */

		void				push(const value_type& value)
		{
			try {
				push_front(Node(value));
			} catch(std::bad_alloc& e)
			{
				if (!empty())
					clear();
				throw ;
			}
		}

		void				pop()
		{
			if (!empty())
			{
				eqp->~Node();
				eqp = eqp->next;
				if (eqp)
					eqp->prev = NULL;
			}
		}

		void				swap(const stack& other)
		{
			std::swap(ebp, other.ebp);
			std::swap(qsp, other.eqp);
		}
	};

	/* Non-member functions */

	// TO DO: All overload operators must be friends

	template <class T, class Container>
	bool					operator==(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{
		Node* i = lhs.ebp, y = rhs.ebp;
		for ( ; i != NULL && y != NULL ; i = i->prev, y = y->prev)
			if (i->c != y->c)
				return (false);
		return ((!i && y) || (i && !y));
	}

	template <class T, class Container>
	bool					operator!=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{
		return (!operator==(lhs, rhs));
	}

	template <class T, class Container>
	bool					operator<(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{
		// This is imcomplete (doesn't work for the moment), i've just cp-paste from stack and vector
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())));
	}

	template <class T, class Container>
	bool					operator<=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{
		return (operator==(lhs, rhs) || operator<(lhs, rhs));
	}

	template <class T, class Container>
	bool					operator>(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{
		return (!operator<=(lhs, rhs));
	}

	template <class T, class Container>
	bool					operator>=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{
		return (!operator<(lhs, rhs));
	}

	template <class T, class Container>
	void					swap(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{
		lhs.swap(rhs);
	}
};