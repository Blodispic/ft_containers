#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include "map.hpp"

namespace ft {

	template <typename Pair>
	struct Node;
	
	struct input_iterator_tag { };
	struct output_iterator_tag { };	
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template <class Iter>
	struct iterator_traits{
		typedef std::ptrdiff_t difference_type;
		typedef Iter value_type;
		typedef Iter* pointer;
		typedef Iter& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class T>
	struct iterator_traits<T *>{
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class T>
	struct iterator_traits<const T *>{
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T *, class Reference = T &>
	struct iterator{
			typedef Category iterator_category;
			typedef T value_type;
			typedef Distance difference_type;
			typedef Pointer pointer;
			typedef Reference reference;
	};

	template <class T>
	class vector_iterator : ft::iterator<typename ft::iterator_traits<T>::iterator_category,
										typename  ft::iterator_traits<T>::value_type,
										typename  ft::iterator_traits<T>::difference_type,
										typename  ft::iterator_traits<T>::pointer,
										typename  ft::iterator_traits<T>::reference>
	{
	public:

		typedef typename ft::iterator_traits<T>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<T>::value_type value_type;
		typedef typename ft::iterator_traits<T>::difference_type difference_type;
		typedef typename ft::iterator_traits<T>::pointer pointer;
		typedef typename ft::iterator_traits<T>::reference reference;

		vector_iterator() : _current(){}
		vector_iterator(T x) : _current(x){}
		template <class U>
		vector_iterator(const vector_iterator<U> &other) : _current(other.base()){};
	
	~vector_iterator() {};

		template <class U>
		vector_iterator &operator=(const vector_iterator<U> &other)
		{
			_current = other.base();
			return (*this);
		};

		T base() const
		{
			return (_current);
		}

		reference operator*() const
		{
			return (*_current);
		}

		pointer operator->() const
		{
			return (_current);
		}

		reference operator[]( const difference_type n) const
		{
			return (_current[n]);
		}

		vector_iterator &operator++(void)
		{
			++_current;
			return (*this);
		}

		vector_iterator &operator--(void)
		{
			--_current;
			return (*this);
		}

		vector_iterator operator++(int)
		{
			vector_iterator tmp = *this;
			_current++;
			return (tmp);
		}

		vector_iterator operator--(int)
		{
			vector_iterator tmp = *this;
			_current--;
			return (tmp);
		}

		vector_iterator operator+(const difference_type n) const
		{
			return (vector_iterator(_current + n));
		}

		vector_iterator operator-(const difference_type& n) const
		{
			return (vector_iterator(_current - n));
		}

		vector_iterator &operator+=(const difference_type n)
		{
			_current += n;
			return (*this);
		}

		vector_iterator &operator-=(const difference_type n)
		{
			_current -= n;
			return (*this);
		}

	protected:
		T _current;
	};

	template <class Iterator1, class Iterator2>
	bool operator==(const vector_iterator<Iterator1> &lhs, const vector_iterator<Iterator2> &rhs)
	{
		return (lhs.base() == rhs.base());
	};

	template <class Iterator1, class Iterator2>
	bool operator!=(const vector_iterator<Iterator1> &lhs, const vector_iterator<Iterator2> &rhs)
	{
		return (lhs.base() != rhs.base());
	};

	template <class Iterator1, class Iterator2>
	bool operator<(const vector_iterator<Iterator1> &lhs, const vector_iterator<Iterator2> &rhs)
	{
		return (lhs.base() < rhs.base());
	};
	template <class Iterator1, class Iterator2>
	bool operator<=(const vector_iterator<Iterator1> &lhs, const vector_iterator<Iterator2> &rhs)
	{
		return (lhs.base() <= rhs.base());
	};
	template <class Iterator1, class Iterator2>
	bool operator>(const vector_iterator<Iterator1> &lhs, const vector_iterator<Iterator2> &rhs)
	{
		return (lhs.base() > rhs.base());
	};
	template <class Iterator1, class Iterator2>
	bool operator>=(const vector_iterator<Iterator1> &lhs, const vector_iterator<Iterator2> &rhs)
	{
		return (lhs.base() >= rhs.base());
	};

	template <class T>
	vector_iterator<T> operator+(typename vector_iterator<T>::difference_type n, const vector_iterator<T> &it)
	{
		return (vector_iterator<T>(it.base() + n));
	};

	template <class T, class T2>
	typename vector_iterator<T>::difference_type operator-(const vector_iterator<T> &lhs, const vector_iterator<T2> &rhs)
	{
		return (lhs.base() - rhs.base());
	};


	template <class Map_Node>
	class map_iterator {
		public :
		typedef          ft::bidirectional_iterator_tag	 			iterator_category;
		typedef typename ft::iterator_traits<Map_Node>::value_type 		value_type;
		typedef typename ft::iterator_traits<Map_Node>::difference_type difference_type;
		typedef const typename ft::iterator_traits<Map_Node>::pointer 		pointer;
		typedef const typename ft::iterator_traits<Map_Node>::reference 		reference;
		private :

			Node<value_type>* _current;

		public :
			// typename value_type::first_type first;
			// typename value_type::second_type second;

			map_iterator() : _current() {};
			map_iterator(Node<value_type>* current) : _current(current){};
			template <class T>
			map_iterator(const map_iterator<T> &other) : _current(other.base()) {};
			~map_iterator() {};

			map_iterator &operator=(const map_iterator& other) {
				_current = other.base();
				return (*this);
			};

			Node<value_type>* base() const {
				return (_current); 
			};

			reference operator *() const {
				return (_current->value); 
			};

			pointer operator->() const { 
				return (&(operator*())); 
			};		

			map_iterator &operator++(void) {
				if (_current->end == true)
				{
					return (*this);
				}
				if (_current->right) {
					_current = _current->right;
					while (_current->left){
						_current = _current->left;
					}
				}
				else {
					while (_current->parent != NULL && _current->parent->right == _current)
						_current = _current->parent;
					_current = _current->parent;
				}
				return (*this);
			}

			map_iterator &operator--(void) {
				if (!_current)
					return (*this);
				if (_current->left) {
					_current = _current->left;
					while (_current->right)
						_current = _current->right;
				}
				else {
					while (_current->parent != NULL && _current == _current->parent->left)
						_current = _current->parent;
					_current = _current->parent;
				}
				return (*this);
			}

			map_iterator operator++(int) {
				map_iterator tmp = *this;
				++*this;
				return (tmp);
			}

			map_iterator operator--(int) {
				map_iterator tmp = *this;
				--*this;
				return (tmp);
			}

			bool	operator==( const map_iterator& rhs ) const {
			return ( this->_current == rhs._current );
			}

			bool	operator!=( const map_iterator& rhs ) const {
				return ( this->_current != rhs._current );
			}

	};

	template <class Map_Node>
	class const_map_iterator {
		public :
		typedef          ft::bidirectional_iterator_tag	 			iterator_category;
		typedef typename ft::iterator_traits<Map_Node>::value_type 		value_type;
		typedef typename ft::iterator_traits<Map_Node>::difference_type difference_type;
		typedef const typename ft::iterator_traits<Map_Node>::pointer 		pointer;
		typedef const typename ft::iterator_traits<Map_Node>::reference 		reference;
		private :

			Node<value_type>* _current;

		public :
			// typename value_type::first_type first;
			// typename value_type::second_type second;

			const_map_iterator() : _current() {};
			const_map_iterator(Node<value_type>* current) : _current(current){};
			template <class T>
			const_map_iterator(const const_map_iterator<T> &other) : _current(other.base()) {};
			~const_map_iterator() {};

			const_map_iterator &operator=(const const_map_iterator& other) {
				_current = other.base();
				return (*this);
			};

			Node<value_type>* base() const {
				return (_current); 
			};

			reference operator *() const {
				return (_current->value); 
			};

			pointer operator->() const { 
				return (&(operator*())); 
			};		

			const_map_iterator &operator++(void) {
				if (_current->end == true)
				{
					return (*this);
				}
				if (_current->right) {
					_current = _current->right;
					while (_current->left){
						_current = _current->left;
					}
				}
				else {
					while (_current->parent != NULL && _current->parent->right == _current)
						_current = _current->parent;
					_current = _current->parent;
				}
				return (*this);
			}

			const_map_iterator &operator--(void) {
				if (!_current)
					return (*this);
				if (_current->left) {
					_current = _current->left;
					while (_current->right)
						_current = _current->right;
				}
				else {
					while (_current->parent != NULL && _current == _current->parent->left)
						_current = _current->parent;
					_current = _current->parent;
				}
				return (*this);
			}

			const_map_iterator operator++(int) {
				const_map_iterator tmp = *this;
				++*this;
				return (tmp);
			}

			const_map_iterator operator--(int) {
				const_map_iterator tmp = *this;
				--*this;
				return (tmp);
			}

			bool	operator==( const const_map_iterator& rhs ) const {
			return ( this->_current == rhs._current );
			}

			bool	operator!=( const const_map_iterator& rhs ) const {
				return ( this->_current != rhs._current );
			}

	};

	template <class Iter>
	class reverse_iterator : ft::iterator<typename ft::iterator_traits<Iter>::iterator_category,
										  typename  ft::iterator_traits<Iter>::value_type,
										  typename  ft::iterator_traits<Iter>::difference_type,
										  typename  ft::iterator_traits<Iter>::pointer,
										  typename  ft::iterator_traits<Iter>::reference>
	{
		public:
			typedef Iter iterator_type;
			typedef typename Iter::iterator_category iterator_category;
			typedef typename Iter::value_type value_type;
			typedef typename Iter::difference_type difference_type;
			typedef typename Iter::pointer pointer;
			typedef typename Iter::reference reference;

			reverse_iterator(): _current() {}
			explicit reverse_iterator(iterator_type x) : _current(x){}
			template <class U>
			reverse_iterator(const reverse_iterator<U> &other) : _current(other.base()){};

			template <class U>
			reverse_iterator &operator=(const reverse_iterator<U> &other)
			{
				_current = other.base();
				return (*this);
			};

			iterator_type base() const 
			{ 
				return (_current);
			}

			reference operator*() const
			{
				iterator_type tmp = _current;
				return (*(--tmp));
			}

			pointer operator->() const 
			{
				return (std::addressof(operator * ()));
			}

			reference operator[](difference_type n) const
			{
				return (base()[-n - 1]);
			}

			reverse_iterator &operator++(void)
			{
				--_current;
				return (*this);
			}

			reverse_iterator &operator--(void)
			{
				++_current;
				return (*this);
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				_current--;
				return (tmp);
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				_current++;
				return (tmp);
			}

			reverse_iterator operator+(difference_type n) 
			{ 
				return (reverse_iterator(_current - n)); 
			}

			reverse_iterator operator-(difference_type n) const
			{ 
				return (reverse_iterator(_current + n)); 
			}

			reverse_iterator &operator+=(difference_type n)
			{
				_current -= n;
				return (*this);
			}

			reverse_iterator &operator-=(difference_type n)
			{
				_current += n;
				return (*this);
			}

		protected:
			iterator_type _current;
	};

	template <class Iterator1, class Iterator2>
	bool operator==(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs) 
	{ 
		return (lhs.base() == rhs.base()); 
	};

	template <class Iterator1, class Iterator2>
	bool operator!=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{ 
		return (lhs.base() != rhs.base()); 
	};

	template <class Iterator1, class Iterator2>
	bool operator<(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() > rhs.base());
	};
	template <class Iterator1, class Iterator2>
	bool operator<=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() >= rhs.base());
	};
	template <class Iterator1, class Iterator2>
	bool operator>(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() < rhs.base());
	};
	template <class Iterator1, class Iterator2>
	bool operator>=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() <= rhs.base());
	};

	template <class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter> &it)
	{
		return (reverse_iterator<Iter>(it.base() - n));
	};

	template <class Iter, class Iter2>
	typename reverse_iterator<Iter>::difference_type operator-(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter2> &rhs)
	{
		return (rhs.base() - lhs.base());
	};

}



#endif
