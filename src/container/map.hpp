#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <cstdlib>
#include "utils.hpp"
#include "iterator.hpp"

namespace ft {
	template < class Node >
	class	map_iterator;

	template < class Node >
	class	const_map_iterator;

	template <class Iter>
    class reverse_iterator;

	template <typename Pair>
	struct Node
	{
		Pair value;
		Node* left;
		Node* right;
		Node* parent;
		int height;
		bool end;

		Node() : value(NULL), left(NULL), right(NULL), parent(NULL), height(0), end(false){}
		
		Node(const Pair &other) : value(other), left(NULL), right(NULL), parent(NULL), height(0), end(false){}

		Node(const Node &other)
		{
			*this = other;
		}
		
		~Node(){}

		Node &operator=(const Node &rhs)
		{
			if (this != &rhs)
			{
				this->value = rhs.value;
				this->left = rhs.left;
				this->right = rhs.right;
				this->parent = rhs.parent;
				this->height = rhs.height;
				this->end = rhs.end;
			}
			return (*this);
		}
	}; 

	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key                     														key_type;
		typedef T   																			mapped_type;
		typedef ft::pair<const key_type, mapped_type> 											value_type;
		typedef typename std::size_t    														size_type;
		typedef typename std::ptrdiff_t															difference_type;
		typedef Compare																			key_compare;
		typedef Allocator																		allocator_type;
		typedef typename Allocator::template rebind<Node<value_type> >::other					node_allocator;
		typedef typename Allocator::reference&													reference;
		typedef const typename Allocator::reference&											const_reference;	
		typedef typename Allocator::pointer														pointer;	 
		typedef typename Allocator::const_pointer												const_pointer;
		typedef typename ft::map_iterator<pointer>												iterator;
		typedef typename ft::map_iterator<const_pointer>										const_iterator;
		typedef typename ft::reverse_iterator<iterator>											reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>									const_reverse_iterator;

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			protected:
				key_compare comp;
			public:
				value_compare(Compare c) : comp(c) {}
				bool operator()(const value_type &lhs, const value_type &rhs) const
				{
					return comp(lhs.first, rhs.first);
				}
		};

		explicit map(const Compare &comp = key_compare(), const Allocator &alloc = Allocator()): _allocator(alloc), _first_element(NULL), _last_element(NULL), _root(NULL), _size(0), _comp(comp){}
		
		template <class InputIt>
		map(InputIt first, InputIt last, const Compare &comp = Compare(), const Allocator &alloc = Allocator()): _allocator(alloc), _first_element(NULL), _last_element(NULL), _root(NULL), _size(0), _comp(comp)
		{
			insert(first, last);
		};

		map(const map &other) : _allocator(other._allocator), _first_element(NULL), _last_element(NULL), _root(NULL), _comp(other._comp)
		{
			insert(other.begin(), other.end());
		}

		~map()
		{
			clear();
		}

		map &operator=(const map &other)
		{
			clear();
			insert(other.begin(), other.end());
			return(*this);
		}

		allocator_type get_allocator() const
		{
			return (this->_allocator);
		}

		mapped_type &at(const Key &key)
		{
			for(iterator it(this->begin()); it != this->end(); it++)
			{
				if ( it.base()->value.first == key)
					return (it->second);
			}
			throw (std::out_of_range("map"));
		}
		const mapped_type &at(const Key &key) const
		{
			for(iterator it(this->begin()); it != this->end(); it++)
			{
				if ( it.base()->value.first == key)
					return (it->second);
			}
			throw (std::out_of_range("map"));
		}

		mapped_type &operator[](const Key &key)
		{
			return (*((this->insert(ft::make_pair(key, mapped_type()))).first)).second;
		}

		iterator begin()
		{
			return (iterator(_first_element));
		}
		const_iterator begin() const
		{
			return (const_iterator(_first_element));
		}

		iterator end()
		{
			return (iterator(_last_element));
		}
		const_iterator end() const
		{
			return (const_iterator(_last_element));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(_last_element));
		}
		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(_last_element));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(_first_element));
		}
		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(_first_element));
		}

		bool empty() const
		{
			return (_size == 0);
		}

		size_type size() const
		{
			return (_size);
		}

		size_type max_size() const
		{
			return (_allocator.max_size());
		}

		void clear()
		{
			recursive_clear(_root);
			_root = NULL;
			_first_element = NULL;
			_last_element = NULL;
			_size = 0;
		}

		ft::pair<iterator, bool> insert(const value_type &value){
			if (count(value.first) == 1)
				return (ft::make_pair(find(value.first), false));

			Node<value_type>* node_ptr;
			if (!_root)
			{
				Node<value_type>* node_end;
	
				node_ptr = _allocator.allocate(1);
				_allocator.construct(node_ptr, value);
				node_end = _allocator.allocate(1);
				node_end->end = true;
				node_end->left = NULL;
				node_end->right = NULL;
				node_end->parent = node_ptr;
				node_end->height = 0;
				_size = 1;
				_root = node_ptr;
				_root->right = node_end;
				_root->height = 1;
				this->_first_element = _root;
				this->_last_element = _root->right;
				return (ft::make_pair(find(_root->value.first), true));
			}
			else
			{
				if (_comp(value.first, _root->value.first) == false)
				{
					if (!_root->right || _root->right == _last_element)
					{
						node_ptr = _allocator.allocate(1);
						_allocator.construct(node_ptr, value);
						_size++;
						if (_root->right == _last_element)
						{
							node_ptr->right = _last_element; 
							_last_element->parent = node_ptr;
						}
						_root->right = node_ptr;
						_root->right->parent = _root;
						rebalance(_root->right);
						return (ft::make_pair(_root->right, true));
					}
					else
						return (ft::make_pair(rinsert(_root->right, value), true));

				}
				else
				{
					if (!_root->left)
					{
						node_ptr = _allocator.allocate(1);
						_allocator.construct(node_ptr, value);
						_size++;		
						_root->left = node_ptr;
						_root->left->parent = _root;
						if (_root == _first_element)
							_first_element = _root->left; 
						rebalance(_root->left);
						return (ft::make_pair(find(_root->left->value.first), true));
					}
					else
						return (ft::make_pair(rinsert(_root->left, value), true));
				}
			}
			ft::pair<iterator, bool> ret;
			ret.first = node_ptr;
			ret.second = true;
			return (ret);
			
		}

		iterator insert(iterator pos, const value_type &value)
		{
			if (count(value.first) == 1)
				return (find(value.first));

			Node<value_type>* node_ptr;
			pos = this->upper_bound(value.first);
			if (!_root)
			{
				Node<value_type>* node_end;
				node_ptr = _allocator.allocate(1);
				_allocator.construct(node_ptr, value);
				node_end = _allocator.allocate(1);
				node_end->end = true;
				node_end->left = NULL;
				node_end->right = NULL;
				node_end->parent = node_ptr;
				node_end->height = 0;
				_size = 1;
				_root = node_ptr;
				_root->right = node_end;
				_root->height = 1;
				this->_first_element = _root;
				this->_last_element = _root->right;
				return (find(value.first));
			}
			else
			{
				if (_comp(value.first, pos->first) == false)
				{
					if (pos.base()->right && pos.base()->right->end == false)
						return (rinsert(find(pos.base()->right->value.first), value));
					else if (pos.base() == _last_element)
					{
						_size++;
						node_ptr = _allocator.allocate(1);
						_allocator.construct(node_ptr, value);
						node_ptr->right = pos.base();
						node_ptr->parent = pos.base()->parent;
						node_ptr->parent->right = node_ptr;
						pos.base()->parent = node_ptr;
						return (rebalance(node_ptr));						
					}
					else
					{
						_size++;
						node_ptr = _allocator.allocate(1);
						_allocator.construct(node_ptr, value);
						if (pos.base()->right == _last_element)
						{
							node_ptr->right = _last_element; 
							_last_element->parent = node_ptr;
						}
						pos.base()->right = node_ptr;
						pos.base()->right->parent = pos.base();
						return (rebalance(pos.base()->right));
					}
				}
				else
				{
					if (pos.base()->left)
						return (rinsert(pos.base()->left, value));
					else
					{
						node_ptr = _allocator.allocate(1);
						_allocator.construct(node_ptr, value);
						_size++;
						pos.base()->left = node_ptr;
						pos.base()->left->parent = pos.base();
						if (pos.base() == _first_element)
							_first_element = pos.base()->left; 
						return (rebalance(pos.base()->left));
					}	
				}
			}
			return (find(value.first));
		}

		template <class InputIt>
		void insert(InputIt first, InputIt last)
		{
			while (first != last)
			{
				insert(*first);
				first++;
			}
		}

		void erase(iterator pos)
		{
			if (pos.base() && pos.base()->end == true)
				return ;
			Node<value_type>* to_delete = pos.base();
			iterator balance;

			if (!to_delete)
				return;
			if (pos.base() == _root && !pos.base()->left && pos.base()->right == _last_element)
			{
				_allocator.destroy(_last_element);
				_allocator.deallocate(_last_element, 1);
				_allocator.destroy(pos.base());
				_allocator.deallocate(pos.base(), 1);
				_root = NULL;
				_first_element = NULL;
				_last_element = NULL;
				_size--;
				return;
			}
			if (pos.base()->parent)
			{
				if (pos.base()->left)
				{
					iterator it(pos.base()->left);

					while (it.base()->right)
						it = it.base()->right;
					if (it.base()->parent == pos.base())
						balance = it.base();
					else
						balance = it.base()->parent;
					if (it.base()->left && it.base()->parent->right == it.base())
					{
						it.base()->parent->right = it.base()->left;
						it.base()->left->parent = it.base()->parent;
					}
					else if (!it.base()->left && it.base()->parent->right == it.base())
						it.base()->parent->right = NULL;
					else if (it.base()->left && it.base()->parent->left == it.base())
					{
						it.base()->parent->left = it.base()->left;
						it.base()->left->parent = it.base()->parent;
					}
					else if (!it.base()->left && it.base()->parent->left == it.base())
						it.base()->parent->left = NULL;
					if (pos.base()->right)
					{
						it.base()->right = pos.base()->right;
						pos.base()->right->parent = it.base();
					}
					else
						it.base()->right = NULL;
					if (pos.base()->parent->left == pos.base())
						pos.base()->parent->left = it.base();
					else
						pos.base()->parent->right = it.base();
					if (pos.base()->left)
					{
						pos.base()->left->parent = it.base();
						it.base()->left = pos.base()->left;
					}
					it.base()->parent = pos.base()->parent;
				}
				else if (pos.base()->right)
				{
					iterator it(pos.base()->right);

					if (it.base()->parent == pos.base())
						balance = it.base();
					else
						balance = it.base()->parent;
					it.base()->parent = pos.base()->parent;
					if (pos.base()->parent->left == pos.base())
						pos.base()->parent->left = it.base();
					else
						pos.base()->parent->right = it.base();
				}
				else
				{
					if (pos.base() == pos.base()->parent->left)
						pos.base()->parent->left = NULL;
					else
						pos.base()->parent->right = NULL;
					balance = pos.base()->parent;
				}
			}
			else
			{
				if (pos.base()->left)
				{
					iterator it(pos.base()->left);

					while (it.base()->right)
						it = it.base()->right;
					if (it.base()->parent == pos.base())
						balance = it.base();
					else
						balance = it.base()->parent;	
					if (it.base()->left && it.base()->parent->right == it.base())
					{
						it.base()->parent->right = it.base()->left;
						it.base()->left->parent = it.base()->parent;
					}
					else if (!it.base()->left && it.base()->parent->right == it.base())
						it.base()->parent->right = NULL;
					else if (it.base()->left && it.base()->parent->left == it.base())
					{
						it.base()->parent->left = it.base()->left;
						it.base()->left->parent = it.base()->parent;
					}
					else if (!it.base()->left && it.base()->parent->left == it.base())
						it.base()->parent->left = NULL;
					if (pos.base()->right)
					{
						it.base()->right = pos.base()->right;
						pos.base()->right->parent = it.base();
					}
					else
						it.base()->right = NULL;
					if (pos.base()->left)
					{
						it.base()->left = pos.base()->left;
						pos.base()->left->parent = it.base();
					}
					else
						it.base()->left = NULL;
					if (pos.base()->left)
					{
						pos.base()->left->parent = it.base();
						it.base()->left = pos.base()->left;
					}
					_root = it.base();
					it.base()->parent = NULL;
				}
				else if (pos.base()->right)
				{
					iterator it(pos.base()->right);
					if (it.base()->parent == pos.base())
						balance = it.base();
					else
						balance = it.base()->parent;
					it.base()->parent = NULL;
					if ((it.base()->right && it.base()->right->end == true) && !it.base()->left)
					{
						_root = it.base();
						_first_element = it.base();
					}
				}
			}
			_allocator.destroy(to_delete);
			_allocator.deallocate(to_delete, 1);
			set_begin_end();
			set_height(balance);
			rebalance(balance);
			_size--;
		}

		void erase(iterator first, iterator last)
		{
			iterator	next;

			next = first;
			while (first != last) 
			{
				next++;
				erase(first);
				first = next;
			}
		}

		size_type erase(const Key &key)
		{
			iterator	toErase = this->find(key);
			
			if (toErase == end())
				return ( 0 );
			erase(toErase);
			return ( 1 );
		}
 
		void swap(map &other)
		{
			std::swap(_allocator, other._allocator);
			std::swap(_first_element, other._first_element);
			std::swap(_last_element, other._last_element);
			std::swap(_size, other._size);
			std::swap(_comp, other._comp);
		}
 
		size_type count(const Key &key) const
		{
			if (_size == 0)
				return(0);
			for (const_iterator it(this->begin()); it != this->end(); it++)
				if (it.base()->value.first == key)
					return (1);
			return (0);
		}
 
		iterator find(const Key &key)
		{
			iterator it;

			for (it = this->begin(); it != this->end(); it++)
				if (it.base()->value.first == key)
					return (it);
			return (_last_element);
		}

		const_iterator find(const Key &key) const{
			const_iterator it;
			for (it = this->begin(); it != this->end(); it++)
				if (it.base()->value.first == key)
					return (it);
			return (_last_element);
		}
 
		ft::pair<iterator, iterator> equal_range(const Key &key)
		{
			return (ft::make_pair(lower_bound(key), upper_bound(key)));
		}
		
		ft::pair<const_iterator, const_iterator> equal_range(const Key &key) const
		{
			return (ft::make_pair(lower_bound(key), upper_bound(key)));
		}

		iterator lower_bound(const Key &key)
		{
				Node<value_type>*	node_ptr = _root;
				Node<value_type>*	old = NULL ;
				iterator 			ret;
				
				if (_root == NULL )
					return (end());
				while ( node_ptr != NULL ) 
				{
					old = node_ptr;
					if (node_ptr->value.first == key)
						return (node_ptr) ;
					if (key_comp()(node_ptr->value.first, key) == false) 
						node_ptr = node_ptr->left;
					else
						node_ptr = node_ptr->right;
				}
				if ( old == _last_element && old->value.first != key)
					return (end());
				if (old != NULL &&  key_comp()(old->value.first, key) == true) 
				{
					ret = old;
					return (++ret);
				}
				return (old);
		}

		const_iterator lower_bound(const Key &key) const
		{
				Node<value_type>*	node_ptr = _root;
				Node<value_type>*	old = NULL ;
				const_iterator 			ret;
				
				if (_root == NULL )
					return (end());
				while ( node_ptr != NULL ) 
				{
					old = node_ptr;
					if (node_ptr->value.first == key)
						return (node_ptr) ;
					if (key_comp()(node_ptr->value.first, key) == false) 
						node_ptr = node_ptr->left;
					else
						node_ptr = node_ptr->right;
				}
				if ( old == _last_element && old->value.first != key)
					return (end());
				if (old != NULL &&  key_comp()(old->value.first, key) == true) 
				{
					ret = old;
					return (++ret);
				}
				return (old);
		}
 
		iterator upper_bound(const Key &key)
		{
			iterator it = lower_bound(key);
			if (it == end())
				return (it);
			if (key == it.base()->value.first && it != end())
				return (++it);
			else
				return (it);
		}
		
		const_iterator upper_bound(const Key &key) const
		{
			iterator it = lower_bound(key);
			if (it == end())
				return (it);
			if (key == it.base()->value.first && it != end())
				return (++it);
			else
				return (it);
		}

		key_compare key_comp() const
		{
			return (this->_comp);
		}

		value_compare value_comp() const
		{
			return (value_compare(key_comp()));
		}

	private:
		/*	Node est un noeud, la map aura Plusieurs noeud
			Chaque noeud aura accès a son fils gauche et droit ainsi que son parent
			Si le noeud n'a pas de parent, on defini le noeud à 0
			Pour définir le dernier élément, on check si *Node = _last_element
			La définition du premier élément est important, ça sera la base du tri left-right

		*/

		node_allocator _allocator;
		Node<value_type>* _first_element;
		Node<value_type>* _last_element;
		Node<value_type>* _root;
		size_type _size;
		key_compare _comp;
		size_t max;

		void	set_height(iterator pos)
		{
			iterator it(pos);
			if (!pos.base()->left && (!pos.base()->right || (pos.base()->right && pos.base()->right->end == true)))
			{
				pos.base()->height = 0;
				if (pos.base()->parent && pos.base()->parent->left && pos.base()->parent->right)
					pos.base()->parent->height = std::max(pos.base()->parent->left->height , pos.base()->parent->right->height) + 1;
				if (it.base()->parent)
					it = it.base()->parent;
			}
			while (it.base() != NULL)
			{	
				if (it.base()->left && it.base()->right && it.base()->right->end == false)
					it.base()->height = std::max(it.base()->left->height , it.base()->right->height) + 1;
				else if (it.base()->left)
					it.base()->height = it.base()->left->height + 1;
				else if (it.base()->right && it.base()->right->end == false)
					it.base()->height = it.base()->right->height + 1;
				it = it.base()->parent;
				
			}
		}

		void	set_left_right(int *left, int *right, iterator it)
		{
			if (it.base()->left)
				*left = it.base()->left->height + 1;
			else
				*left = 0;
			if (it.base()->right && it.base()->right->end == false)
				*right = it.base()->right->height + 1;
			else
				*right = 0;

		}

		void	set_begin_end()
		{
			Node<value_type>* tmp = _root;
			if (tmp->left)
				while (tmp->left)
					tmp = tmp->left;
			else
				tmp = _root;
			this->_first_element = tmp;
			tmp = _root;
			while (tmp->right)
				tmp = tmp->right;
			this->_last_element = tmp;
		}

		void	rotate(iterator it, int nb)
		{
			switch (nb)
			{
			case 1:
			{
				//LL Rotate Right

				Node<value_type>* Left = it.base()->left;
				if (it.base() == _root)
					_root = Left;
				if (it.base()->parent)
				{
					Left->parent = it.base()->parent;
					if (it.base()->parent->left == it.base())
						it.base()->parent->left = Left;
					else
						it.base()->parent->right = Left;
				}
				else
					Left->parent = NULL;
				if (Left->right)
				{
					it.base()->left = Left->right;
					Left->right->parent = it.base();
				}
				else
					it.base()->left = NULL;
				it.base()->parent = Left; 
				Left->right = it.base();
				return;
			}
			case 2:
			{
				//LR LEFT RIGHT
				rotate(it.base()->left, 3);
				rotate(it, 1);
				return;
			}
			case 3:
			{
				//RR Rotate left
				Node<value_type>* Right = it.base()->right;
				if (it.base() == _root)
					_root = Right;
				if (it.base()->parent)
				{
					Right->parent = it.base()->parent;
					if (it.base()->parent->right == it.base())
						it.base()->parent->right = Right;
					else
						it.base()->parent->left = Right;
				}
				else
					Right->parent = NULL;
				if (Right->left)
				{
					it.base()->right = Right->left;
					Right->left->parent = it.base();
				}
				else
					it.base()->right = NULL;
				it.base()->parent = Right; 
				Right->left = it.base();
				return;
			}
			case 4:
			{
				//RL RIGHT LEFT
				rotate(it.base()->right, 1);
				rotate(it, 3);
				return;
			}
			default:
				return;
			}
		}

		void	check_Node(iterator it)
		{
			int left = 0;
			int right = 0;

			set_height(it.base());
			set_left_right(&left, &right, it);
			if (left - right > 1)
			{
				set_left_right(&left, &right, it.base()->left);
				if (left >= right)
					rotate(it, 1);
				else if (left < right)
					rotate(it, 2);
			}
			else if (left - right < -1)
			{
				set_left_right(&left, &right, it.base()->right);
				set_height(it.base()->right);
				if (left > right)
					rotate(it, 4);
				else if (left <= right)
					rotate(it, 3);
			}
			set_height(it);
		}

		iterator rinsert(iterator pos, const value_type &value){
			Node<value_type>* node_ptr;
			
			if (!_root)
			{
				Node<value_type>* node_end;
				node_ptr = _allocator.allocate(1);
				_allocator.construct(node_ptr, value);

				node_end = _allocator.allocate(1);
				node_end->end = true;
				node_end->left = NULL;
				node_end->right = NULL;
				node_end->parent = node_ptr;
				node_end->height = 0;

				_size = 1;
				_root = node_ptr;
				_root->right = node_end;
				_root->height = 1;
				this->_first_element = _root;
				this->_last_element = _root->right;
				return (find(value.first));
			}
			else
			{
				if (_comp(value.first, pos->first) == false)
				{
					if (pos.base()->right && pos.base()->right->end == false)
						return (rinsert(pos.base()->right, value));
					else if (pos.base() == _last_element)
					{
						_size++;
						node_ptr = _allocator.allocate(1);
						_allocator.construct(node_ptr, value);
						node_ptr->right = pos.base();
						node_ptr->parent = pos.base()->parent;
						node_ptr->parent->right = node_ptr;
						pos.base()->parent = node_ptr;
						return (rebalance(node_ptr));						
					}
					else
					{
						_size++;
						node_ptr = _allocator.allocate(1);
						_allocator.construct(node_ptr, value);
						if (pos.base()->right == _last_element)
						{
							node_ptr->right = _last_element; 
							_last_element->parent = node_ptr;
						}
						pos.base()->right = node_ptr;
						pos.base()->right->parent = pos.base();
						return (rebalance(pos.base()->right));
					}
				}
				else
				{
					if (pos.base()->left)
						return (rinsert(pos.base()->left, value));
					else
					{
						node_ptr = _allocator.allocate(1);
						_allocator.construct(node_ptr, value);
						_size++;
						pos.base()->left = node_ptr;
						pos.base()->left->parent = pos.base();
						if (pos.base() == _first_element)
							_first_element = pos.base()->left; 
						return (rebalance(pos.base()->left));
					}	
				}
			}
			return (find(value.first));
		}

		iterator	rebalance(iterator pos)
		{
			iterator it(pos);
			set_height(pos);
			while (it.base()->parent != NULL)
			{	
				check_Node(it);
				it = it.base()->parent;
			}
			check_Node(it);
			return (pos);
		}

		void	recursive_clear(Node<value_type>* ptr)
		{
			if (ptr)
			{
				recursive_clear(ptr->right);
				recursive_clear(ptr->left);
				_allocator.destroy(ptr);
				_allocator.deallocate(ptr, 1);
			}			
		}
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key, T, Compare, Alloc> &lhs,
					const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return ( false );
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::map<Key, T, Compare, Alloc> &lhs,
					const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const ft::map<Key, T, Compare, Alloc> &lhs,
				   const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	};	

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key, T, Compare, Alloc> &lhs,
					const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs > rhs));
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const ft::map<Key, T, Compare, Alloc> &lhs,
				   const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return (rhs < lhs);
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::map<Key, T, Compare, Alloc> &lhs,
					const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	};

	template <class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key, T, Compare, Alloc> &lhs,
			  ft::map<Key, T, Compare, Alloc> &rhs)
	{
		lhs.swap(rhs);
	};

}

#endif
