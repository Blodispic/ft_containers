#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <memory>
#include "vector.hpp"
#include "iterator.hpp"

namespace ft {
	template<class T, class Container = ft::vector<T> >
		class stack
		{
			public :
				typedef T			value_type;
				typedef Container	container_type;
				typedef size_t		size_type;
				
				explicit stack(const container_type& cont = container_type()): c(cont) {}
				explicit stack( const stack& other): c(other) {}
				~stack(){}

				value_type& top()
				{
					return (c.back());
				};
				
				const value_type& top() const
				{
					return (c.back());
				};

				bool empty() const
				{
					return (c.empty());
				};

				size_type size() const
				{
					return (c.size());
				};

				void push(const value_type& value)
				{
					c.push_back(value);
				};

				void pop()
				{
					c.pop_back();
				};
			protected :
				Container c;
			
			template< class T1, class Container1>
			friend bool operator==(const stack<T1,Container1>& lhs, const stack<T1,Container1>& rhs);

			template< class T1, class Container1>
			friend bool operator<(const stack<T1,Container1>& lhs, const stack<T1,Container1>& rhs);


		};
		template< class T, class Container >
		bool operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs)
		{
			return (lhs.c == rhs.c);
		};

		template< class T, class Container >
		bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
		{
			return (!(lhs == rhs));
		};

		template< class T, class Container >
		bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
		{
			return (lhs.c < rhs.c);
		};

		template< class T, class Container >
		bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
		{
			return (lhs < rhs || lhs == rhs);
		};

		template< class T, class Container >
		bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
		{
			return (!(lhs <= rhs));
		};

		template< class T, class Container >
		bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
		{
			return (!(lhs < rhs));
		};
}

#endif
