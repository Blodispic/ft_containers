#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>		//Pour std::allocator
#include "iterator.hpp"
#include "utils.hpp"

namespace ft {
	template<class T, class Allocator = std::allocator<T> >
		class vector
		{
			public:
				typedef T			    												value_type;
				typedef Allocator	    												allocator_type;
				typedef size_t		    												size_type;
				typedef ptrdiff_t														difference_type;
				typedef value_type&     												reference;
				typedef value_type&														const_reference;
				typedef typename Allocator::pointer										pointer;
				typedef typename Allocator::const_pointer								const_pointer;
				typedef	ft::vector_iterator<pointer>									iterator;
				typedef ft::vector_iterator<const_pointer>								const_iterator;
				typedef	ft::reverse_iterator<iterator>									reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;

				explicit vector (const allocator_type& alloc = allocator_type() ): _allocator(alloc), _allocator_ptr(NULL), _capacity(0), _size(0) {}
				explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()): _allocator(alloc), _allocator_ptr(NULL), _capacity(count), _size(count) 
				{
					if (count > 0)
					{
						_allocator_ptr = _allocator.allocate(count);
						for (size_type i = 0; i < count; i++)
							_allocator.construct(_allocator_ptr + i, value);
					}
				}
				template<class InputIt>
					vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(), typename ft::enable_if<!std::is_integral<InputIt>::value>::type * = NULL): _allocator(alloc), _allocator_ptr(NULL), _capacity(0), _size(0)
					{
						InputIt	tmp = first;
						size_type size;

						for (size = 0; tmp != last; size++)
							tmp++;
						if (size > 0)
						{
							this->_capacity = size;
							this->_allocator_ptr = _allocator.allocate(size);
							for ( ; first != last; first++)
								this->push_back(*first);
						}

					}

				vector(const vector& other) 
				{
					this->_allocator = other._allocator;
					this->_capacity = other._size;
					this->_size = other._size;
					if (this->_capacity > 0)
					{
						this->_allocator_ptr = this->_allocator.allocate(this->_capacity);
						for (size_type i = 0; i < other._size; i++)
							this->_allocator.construct(this->_allocator_ptr + i, other[i]);
					}
				}

				~vector()
				{
					if (this->_size > 0)
						for (size_type i = 0; i < this->_size; i++)
							this->_allocator.destroy(this->_allocator_ptr + i);
					if (this->_capacity > 0)
						this->_allocator.deallocate(this->_allocator_ptr, this->_capacity);
					this->_capacity = 0;
					this->_size = 0;
				}

				vector& operator=(const vector& other)
				{
					this->assign(other.begin(), other.end());
					return (*this);
				}

				void assign(size_type count, const T& value)
				{
					this->clear();
					reserve(count);
					if (count > 0)
						for (size_type i = 0; i < count; i++)
							this->push_back(value);
				}

				template< class InputIt >
					void assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type * = NULL)
					{
						InputIt	tmp = first;
						size_type size;

						this->clear();
						for (size = 0; tmp != last; size++)
							tmp++;
						reserve(size);
						if (size > 0)
							for ( ; first != last; first++)
								this->push_back(*first);
					}

				allocator_type get_allocator() const
				{
					return (this->_allocator);
				}

				reference operator[](size_type pos)
				{
					return (this->_allocator_ptr[pos]);
				}

				const_reference operator[](size_type pos) const
				{
					return (this->_allocator_ptr[pos]);
				}

				reference at(size_type pos)
				{
					if (pos >= size())
						throw (std::out_of_range("vector"));
					return (this->_allocator_ptr[pos]);
				}

				const_reference at(size_type pos) const
				{
					if (pos >= size())
						throw (std::out_of_range("vector"));
					return (this->_allocator_ptr[pos]);
				}

				reference front()
				{
					return (this->_allocator_ptr[0]);
				}

				const_reference front() const{
					return (this->_allocator_ptr[0]);
				}

				reference back()
				{
					return (this->_allocator_ptr[size() - 1]);
				}

				const_reference back() const
				{
					return (this->_allocator_ptr[size() - 1]);
				}

				T* data()
				{
					if (size() == 0)
						return (this->_allocator_ptr);
					return (this->_allocator_ptr);
				}

				const T* data() const
				{
					if (size() == 0)
						return (this->_allocator_ptr);
					return (this->_allocator_ptr);	
				}

				iterator begin()
				{
					return (iterator(_allocator_ptr));
				}

				const_iterator begin() const
				{
					return (const_iterator(_allocator_ptr));
				}

				iterator end()
				{
					return (iterator(_allocator_ptr + _size));
				}

				const_iterator end() const
				{
					return (const_iterator(_allocator_ptr + _size));
				}

				reverse_iterator rbegin()
				{
					return (reverse_iterator(this->end()));
				}

				const_reverse_iterator rbegin() const
				{
					return (const_reverse_iterator(this->end()));
				}

				reverse_iterator rend()
				{
					return (reverse_iterator(this->begin()));
				}

				const_reverse_iterator rend() const
				{
					return (const_reverse_iterator(this->begin()));
				}

				bool empty() const
				{
					if (begin() == end())
						return (true);
					return (false);
				}

				size_type size() const
				{
					return (this->_size);
				}

				size_type max_size() const
				{
					return (_allocator.max_size());
				}

				void reserve(size_type new_cap)
				{
					if (new_cap > max_size())
						throw (std::length_error("vector"));
					if (new_cap > this->_capacity)
					{
						T *new_ptr;
						size_type new_nb = this->_size;

						new_ptr = this->_allocator.allocate(new_cap);
						for (size_type i = 0; i < this->_size; i++)
							this->_allocator.construct(new_ptr + i, this->_allocator_ptr[i]);
						if (this->_size > 0)
						{
							for (size_type i = 0; i < this->_size; i++)
								this->_allocator.destroy(this->_allocator_ptr + i);
						}
						if (this->_capacity > 0)
							this->_allocator.deallocate(this->_allocator_ptr, this->_capacity);
						this->_allocator_ptr = new_ptr;
						this->_capacity = new_cap;
						this->_size = new_nb;
					}
				}

				size_type capacity() const
				{
					return (_capacity);
				}

				void clear()
				{
					if (_size > 0)
					{
						for(size_t i = 0; i < _size; i++)
						{
							this->_allocator.destroy(this->_allocator_ptr + _size);
						}
					}
					this->_size = 0;
				}

				iterator insert(iterator pos, const T& value)
				{
					difference_type id = pos - begin();

					if (this->_size + 1 > this->_capacity)
					{
						if (this->_size + 1 <= this->_capacity * 2)
							reserve(this->_capacity * 2);
						else	
							reserve(this->_size + 1);
					}
					else
						reserve(this->_capacity);
					pos = begin() + id;
					_allocator.construct(this->_allocator_ptr + this->_size, this->_allocator_ptr[this->_size - 1]);
					for (difference_type j = this->_size - 1; j > id ; j--)
						this->_allocator_ptr[j] = this->_allocator_ptr[j - 1];
					this->_size++;
					if (size_type(id) == _size)
						_allocator.construct( _allocator_ptr + id, value );
					else
						_allocator_ptr[id] = value;
					return (iterator(this->_allocator_ptr + id));
				}

				iterator insert(iterator pos, size_type count, const T& value)
				{
					difference_type id = pos - begin();
					if (count == 0)
						return (pos);
					if (this->_size + count > this->_capacity)
					{
						if (this->_size + count <= this->_capacity * 2)
							reserve(this->_capacity * 2);
						else	
							reserve(this->_size + count);
					}
					else
						reserve(this->_capacity);
					pos = begin() + id;
					for (size_type i = 0; i < count; i++)
					{
						_allocator.construct(this->_allocator_ptr + this->_size, this->_allocator_ptr[this->_size - 1]);
						for (difference_type j = this->_size - 1; j > id ; j--)
							this->_allocator_ptr[j] = this->_allocator_ptr[j - 1];
						this->_size++;
					}
					for (size_type i = 0; i < count; i++)
						this->at(id + i) = value;
					return (iterator(this->_allocator_ptr + id));
				}

				template< class InputIt >
				iterator insert(iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type * = NULL)
				{
					size_type count;
					InputIt	tmp = first;

					for (count = 0; tmp != last; count++)
						tmp++;
					difference_type id = pos - begin();
					if (first == last)
						return (pos);
					if (this->_size + count > this->_capacity)
					{
						if (this->_size + count <= this->_capacity * 2)
							reserve(this->_capacity * 2);
						else	
							reserve(this->_size + count);
					}
					else
						reserve(this->_capacity);
					for (size_type i = 0; i < count; i++)
					{
						_allocator.construct(this->_allocator_ptr + this->_size, this->_allocator_ptr[this->_size - 1]);
						for (difference_type j = this->_size - 1; j > id ; j--)
							this->_allocator_ptr[j] = this->_allocator_ptr[j - 1];
						this->_size++;
					}
					difference_type i = 0;
					for (InputIt it(first); it != last; it++, i++)
						this->at(id + i) = *it;
					return (pos);
				}

				iterator erase( iterator pos )
				{
					size_type id = pos - begin();
					if (this->_size == id)
						return (this->end());
					for ( size_type i = id; i < _size - 1; i++ ) 
        		        _allocator_ptr[i] = _allocator_ptr[i + 1];
					this->pop_back();
					return (pos);
				}

        	iterator erase (iterator first, iterator last)
			{
        	    for (difference_type id = last - first; id > 0; id--)
        	        this->erase(first);
        	    return (first);
        	}

			void push_back( const T& value )
			{
				reserve(1);
				insert(this->end(), value);
				return ;
			}

			void pop_back()
			{
				this->_allocator.destroy(this->_allocator_ptr + this->_size - 1);
				this->_size--;
			}

			void resize( size_type count, T value = T() )
			{
				if (count > max_size())
					throw (std::length_error("vector"));
				if (count > this->_capacity)
				{
					if (count <= this->_capacity * 2)
						reserve(this->_capacity * 2);
					else
						reserve(count);
				}
				else
					reserve(this->_capacity);
				if (count > this->_size)
					while (count > this->_size)
						push_back(value);
				else if (count < this->_size)
					while (count < this->_size)
						pop_back();
			}

			void swap( vector& other )
			{
				std::swap(this->_allocator, other._allocator);
				std::swap(this->_allocator_ptr, other._allocator_ptr);
				std::swap(this->_capacity, other._capacity);
				std::swap(this->_size, other._size);
			}

			protected:
				Allocator		_allocator;
				pointer			_allocator_ptr;
				size_type		_capacity;
				size_type		_size;

				template< class T1, class Alloc1 >
				friend bool operator==(const ft::vector<T1,Alloc1>& lhs, const ft::vector<T1,Alloc1>& rhs);

				template< class T1, class Alloc1 >
				friend bool operator<( const ft::vector<T1,Alloc1>& lhs,const ft::vector<T1,Alloc1>& rhs );
		};

	template< class T, class Alloc >
		bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			for (size_t i = 0; i < lhs.size(); i++)
			{
				if (lhs._allocator_ptr[i] != rhs._allocator_ptr[i])
					return (false);
			}
			return (true);
		};

	template< class T, class Alloc >
		bool operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			return (!(lhs == rhs));
		};

	template< class T, class Alloc >
		bool operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		};

	template< class T, class Alloc >
		bool operator<=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			return (!(lhs > rhs));
		};

	template< class T, class Alloc >
		bool operator>(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			return (rhs < lhs);
		};

	template< class T, class Alloc >
		bool operator>=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			return (!(lhs < rhs));
		};

	template< class T, class Alloc >
		void swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs )
		{
				lhs.swap(rhs);
		};


}

#endif