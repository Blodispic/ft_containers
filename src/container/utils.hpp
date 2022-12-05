#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>

namespace ft {

    template<bool B, class T = void>
    struct enable_if {};
    
    template<class T>
    struct enable_if<true, T> { typedef T type; };

    template< class T > struct remove_const {
        typedef T type;
    };
    template< class T > struct remove_const<const T> {
        typedef T type;
    };

    template <class T, T v>
    struct integral_constant {
        const static T                    value = v;
        typedef T                        value_type;
        typedef    integral_constant<T, v>    type;
        operator value_type() const {
            return value;
        }
        value_type operator()() const {
            return value;
        }
    };

    typedef integral_constant<bool,true>    true_type;
    typedef integral_constant<bool,false>    false_type;

    template < class T > struct is_integral_base : public false_type {};
    template <> struct          is_integral_base<bool> : public true_type {};
    template <> struct          is_integral_base<char> : public true_type {};
    template <> struct          is_integral_base<wchar_t> : public true_type {};
    template <> struct          is_integral_base<signed char> : public true_type {};
    template <> struct          is_integral_base<short> : public true_type {};
    template <> struct          is_integral_base<int> : public true_type {};
    template <> struct          is_integral_base<long> : public true_type {};
    template <> struct          is_integral_base<long long> : public true_type {};
    template <> struct          is_integral_base<unsigned char> : public true_type {};
    template <> struct          is_integral_base<unsigned short> : public true_type {};
    template <> struct          is_integral_base<unsigned int> : public true_type {};
    template <> struct          is_integral_base<unsigned long> : public true_type {};
    template <> struct          is_integral_base<unsigned long long> : public true_type {};

    template < class T > struct    is_integral : public is_integral_base<typename remove_const<T>::type> {};

    template < class InputIterator1, class InputIterator2, class Compare >
	bool	lexicographical_compare( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp ) {
		for ( ; ( first1 != last1 ) && ( first2 != last2 ); first1++, first2++ ) {
			if ( comp( *first1, *first2 ) )
				return ( true );
			if ( comp( *first2, *first1 ) )
				return ( false );
		}
		return ( ( first1 == last1 ) && ( first2 != last2 ) );
	};

    template<class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                 InputIt2 first2, InputIt2 last2)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
        {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }
    
        return (first1 == last1) && (first2 != last2);
    };

	template <class InputIterator1, class InputIterator2>
	bool	equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 ) {
		while ( first1 != last1 ) {
			if ( !( *first1 == *first2 ) )
			return ( false );
			++first1;
			++first2;
		}
		return ( true );
	};

    template <class T1, class T2>
    struct pair
    {
        typedef T1  first_type;
        typedef T2  second_type;

        first_type  first;
        second_type second;

        pair(){}
        pair(const T1 &x, const T2 &y): first(x), second(y){}
        template <class U1, class U2>
        pair(const pair<U1, U2> &p): first(p.first), second(p.second) {};
        
        
        pair& operator=(const pair& other){
            this->first = other.first;
            this->second = other.second;
            return (*this);
        }
    };

    template <class T1, class T2>
    ft::pair<T1, T2> make_pair(T1 t, T2 u){
        return (ft::pair<T1, T2>(t, u));
    };

    template <class T1, class T2>
    bool operator==(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs){
        return ((lhs.first == rhs.first) && (lhs.second == rhs.second));
    };
    template <class T1, class T2>
    bool operator!=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs){
        return (!(lhs == rhs));
    };
    template <class T1, class T2>
    bool operator<(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs){
        if (lhs.first < rhs.first)
            return (true);
        else if (rhs.first < lhs.first)
            return (false);
        else if (lhs.second < rhs.second)
            return (true);
        else
            return (false);
    };
    template <class T1, class T2>
    bool operator<=(const std::pair<T1, T2> &lhs, const std::pair<T1, T2> &rhs){
        return (!(rhs < lhs));
    };
    template <class T1, class T2>
    bool operator>(const std::pair<T1, T2> &lhs, const std::pair<T1, T2> &rhs){
        return (rhs < lhs);
    };
    template <class T1, class T2>
    bool operator>=(const std::pair<T1, T2> &lhs, const std::pair<T1, T2> &rhs){
        return (!(lhs < rhs));
    };
}

#endif
