
# pragma once

# include <exception>
# include "../lexicographical_compare.hpp"
/*
** Documentation: https://en.cppreference.com/w/cpp/container/stack
*/

// TO DO: Container is equal to deque by default

namespace ft 
{

	template <class T, class Container>
	class stack
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
		Node*								esp;

		/*
		** Adds target after esp and update esp to target
		*/
		void								push_front(Node* target)
		{
			if (empty())
				ebp = esp = target;
			else
			{
				esp->next = target;
				target->prev = esp;
				esp = target;
			}
		}

		/*
		** Clears all the stack and set ebp = esp = NULL
		*/
		void								clear()
		{
			while (esp != NULL)
			{
				esp->~Node();
				esp = esp->prev;
			}
			ebp = esp;
		}

		/* Constructors */

		public:

		explicit stack() : ebp(NULL), esp(NULL) { }
		explicit stack(const Container& cont = Container()) : ebp(Node(cont)), esp(ebp) { }
		stack(const stack& other) : ebp(Node(other.c)), esp(ebp) { }

		/* Destructor */
		~stack() { clear(); }

		stack&				operator=(const stack& other)
		{
			if (this != &other)
			{
				clear();
				try {
					for (Node* i = other.ebp ; i != NULL ; i = i->next)
						push_back(Node(i.c));
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

		reference			top() { return (esp.c); }

		const_reference		top() const { return (esp.c); }

		/* Capacity */

		bool				empty() const { return (esp == NULL && ebp == NULL); }

		size_type			size() const
		{
			size_type		s = 0;

			if (empty())
				return (s);
			for (Node* i = ebp ; i != NULL ; i = i->next)
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
				esp->~Node();
				esp = esp->prev;
				if (esp)
					esp->next = NULL;
			}
		}

		void				swap(const stack& other)
		{
			std::swap(ebp, other.ebp);
			std::swap(esp, other.esp);
		}
	};

	/* Non-member functions */

	// TO DO: All overload operators must be friends

	template <class T, class Container>
	bool					operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		Node* i = lhs.ebp, y = rhs.ebp;
		for ( ; i != NULL && y != NULL ; i = i->next, y = y->next)
			if (i->c != y->c)
				return (false);
		return ((!i && y) || (i && !y));
	}

	template <class T, class Container>
	bool					operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (!operator==(lhs, rhs));
	}

	template <class T, class Container>
	bool					operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		// This is imcomplete (doesn't work for the moment), i've just cp-paste from vector
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())));
	}

	template <class T, class Container>
	bool					operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (operator==(lhs, rhs) || operator<(lhs, rhs));
	}

	template <class T, class Container>
	bool					operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (!operator<=(lhs, rhs));
	}

	template <class T, class Container>
	bool					operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (!operator<(lhs, rhs));
	}

	template <class T, class Container>
	void					swap(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		lhs.swap(rhs);
	}
};