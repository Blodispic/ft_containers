#include "../container/stack.hpp"
#include "../container/vector.hpp"
#include "../container/map.hpp"
#include <vector>
#include <stack>
#include <map>
#include <list>

#define ok std::cout << "\033[1;32m [OK] \033[0m" ;
#define last_ok std::cout << "\033[1;32m [OK] \033[0m\n\n" ;
#define no std::cout << "\033[1;31m [NO] \033[0m" ;
#define last_no std::cout << "\033[1;31m [NO] \033[0m\n\n" ;

	template<class T>
void	check(T a, T b, const int end = 0)
{
	if (a == b) {
		if (end == 0) {
			ok;
		}
		else
			last_ok;
	}
	else {
		if (end == 0) {
			no;
		}
		else
			last_no;
	}
}
//void	check_all (std::vector<int> a, ft::vector<int> b)
//{
//	if ( a.capacity() == b.capacity() )
//	{
//		if ( a.size() == b.size() )
//		{
//			for (size_t i = 0; i < a.size(); i++)
//			{
////				std::cout << a[i] << "  " << b[i] << std::endl;
//				if (a[i] != b[i])
//					std::cout << "in the vector at["<< i << "]:    real = " << a[i]<< "my = " << b[i] << std::endl;
//			}
//		}
//		else
//			std::cout << "size :    real = " << a.size()<< "my = " << b.size() << std::endl;
//	}
//	else
//		std::cout << "capacity :    real = " << a.capacity()<< "my = " << b.capacity() << std::endl;
//	no;
//}
void	check_all (std::vector<int> *a, ft::vector<int> *b)
{
	if ( a->capacity() == b->capacity() )
	{
		if ( a->size() == b->size() )
		{
			for (size_t i = 0; i < a->size(); i++)
			{
	//			std::cout << a->at(i) << "  " << b->at(i) << std::endl;
				if (a->at(i) != b->at(i))
				{
					std::cout << "in the vector at["<< i << "]:    real = " << a->at(i) << "my = " << b->at(i) << std::endl;
					no;
					return ;
				}
			}
			ok;
			return ;

		}
		else
			std::cout << "size :    real = " << a->size()<< "my = " << b->size() << std::endl;
	}
	else
		std::cout << "capacity :    real = " << a->capacity()<< "my = " << b->capacity() << std::endl;
	no;
}

	template<class T>
void c( T a, T b )
{
	std::cout << a << " !=  " <<  b << std::endl;
}

int main (int ac, char **av)
{

	(void)ac;
	(void)av;

	if (ac <= 1 || strcmp(av[1], "stack") == 0)
	{

		std::cout << "\033[1;34m STACK : \033[0m" << std::endl ;

		ft::stack<int> mystack;
		std::stack<int, std::vector<int> > stack;

		check( mystack.empty(), stack.empty() );

		mystack.push(12);
		stack.push(12);
		mystack.push(42);
		stack.push(42);

		check( mystack.top(), stack.top() ) ;
		check( mystack.size(), stack.size() );
		check( mystack.empty(), stack.empty() );

		mystack.pop();
		stack.pop();
		check( mystack.top(), stack.top() );
		check( mystack.size(), stack.size() );
		check( mystack.empty(), stack.empty() );

		ft::stack<int> mystack_test;
		mystack_test.push(1);
		mystack_test.push(2);
		mystack_test.push(3);

		mystack = mystack_test;
		//check( mystack, mystack_test);
		check( mystack.size(), mystack_test.size() );
		check( mystack.empty(), mystack_test.empty() );

		mystack.pop();
		mystack.pop();
		mystack_test.pop();
		mystack_test.pop();

		check( mystack.top(), mystack_test.top() );
		check( mystack.size(), mystack_test.size() );
		check( mystack.empty(), mystack_test.empty(), 1 );
	}
	if (ac <= 1 || strcmp(av[1], "vector") == 0)
	{
		std::cout << "\033[1;34m VECTOR : \033[0m" << std::endl ;
		std::cout << "\033[1;30m constructor : \033[0m" << std::endl ;

		{
			std::vector<int> real( 4, 100 );
			ft::vector<int> my( 4, 100 );

			check( my.size() , real.size() );
			check( my[0] , real[0] );
			check( my[3] , real[3]);

			ft::vector<int> v( 10, 22 );
			std::vector<int> r( 10, 22 );
			v.reserve(20);
			r.reserve(20);
			ft::vector<int> v2( v );
			std::vector<int> r2( r );
			check_all( &r2, &v2 );


			/*
			   std::vector<int> real2( real.begin(), real.end() );
			   ft::vector<int> my2( my.begin(), my.end() );

			   check( my2.size() , real2.size() );
			   check( my2[0] , real2[0] );
			   check( my2[3] , real2[3] );
			   */

			std::cout << "\n\033[1;30m elements access : \033[0m" << std::endl ;
			try {
				my.at( my.size() + 1 );
			}
			catch ( std::out_of_range& e ) {
				ok;
			}
			check( my.at(3), real.at(3) );

			my.at(0) = 78;
			my[3] = 16;
			my[2] = 3;
			// now front equals 78, and back 16
			my.front() -= my.back();
			check ( my.front(), 62 );
			check ( my.back(), 16 );

			ft::vector<int>::pointer c1_ptr;
			ft::vector<int>::const_pointer c1_cPtr;
			c1_cPtr = my.data();
			for (size_t n = 0; n < my.size(); ++n, c1_cPtr++)
				check (*c1_cPtr, my[n] );
			c1_ptr = my.data();
			*c1_ptr = 20;
			for (size_t n = 0; n < my.size(); ++n, c1_ptr++)
				check (*c1_ptr, my[n] );

		}
		{
			std::cout << "\n\033[1;30m capacity : \033[0m" << std::endl ;

			std::vector<int> real;
			ft::vector<int> my;

			check( my.size() , real.size() );
		}
		{
			std::vector<int> real( 4, 100 );
			ft::vector<int> my( 4, 100 );

			check( my.size(), real.size() );
			check( my.capacity(), real.capacity() );
			real.push_back( 4 );
			my.push_back( 4 );
			check( my.capacity(), real.capacity() );
			check( my.size(), real.size() );
			real.push_back( 5 );
			my.push_back( 5 );
			check( my.capacity(), real.capacity() );
			check( my.size(), real.size() );
			my.reserve( 30 );
			real.reserve( 30 );
			check( my.capacity(), real.capacity() );
			check( my.size(), real.size() );
			check ( my.back(), real.back() );
		}
		{
			std::vector<int> real;
			ft::vector<int> my;

			check( real.capacity(), my.capacity() );
			my.reserve( 30 );
			real.reserve( 30 );
			check( real.capacity(), my.capacity() );
			my.reserve( 0 );
			real.reserve( 0 );
			check( real.capacity(), my.capacity() );


			for (int i = 1000; i < 1300; ++i)
				my.push_back(i);
			for (int i = 1000; i < 1300; ++i)
				real.push_back(i);
			check( my.capacity(), real.capacity() );
			check( my.size(), real.size() );
			check ( my.back(), real.back() );
			check_all( &real, &my);


			std::vector<int> real_cpy;
			ft::vector<int> my_cpy;

			real_cpy = real;
			my_cpy = my;

			check_all( &real_cpy, &my_cpy);


		}
		{
			std::cout << "\n\033[1;30m modifier : \033[0m" << std::endl ;

			ft::vector<int> my( 1 );
			std::vector<int> real( 1 );

			real.resize( 6, 'a' );
			my.resize( 6, 'a' );
			check_all( &real, &my);

			real.resize( 2, 'c' );
			my.resize( 2, 'c' );
			check_all( &real, &my);

			real.resize( 30 );
			my.resize( 30 );
			check_all( &real, &my);

		}
		{

			ft::vector<int> my;
			std::vector<int> real;

			my.push_back(42);
			real.push_back(42);
			my.push_back( 1 );
			real.push_back( 1 );
			my.push_back( 1 );
			real.push_back( 1 );
			my.push_back( 2 );
			real.push_back( 2 );
			check_all(&real, &my);

			my.assign(2, 100);
			real.assign(2, 100);
			check_all( &real, &my );
			my.assign(8, 8);
			real.assign(8, 8);
			check_all( &real, &my );

			for ( int i = 1; i < 8; i++) {
				my.pop_back() ;
				real.pop_back() ;
			}
			check_all( &real, &my );

			/*
			 * LES ITERATO TESTER 			
			 std::cout << "\n\033[1;30m iterator : \033[0m" << std::endl ;
			 std::cout << std::endl;
			 for (std::vector<int>::reverse_iterator it = real.rbegin() ; it != real.rend(); ++it)
			 std::cout << ' ' << *it ;

			 std::cout << std::endl;
			 for (ft::vector<int>::reverse_iterator it = my.rbegin() ; it != my.rend(); ++it)
			 std::cout << ' ' << *it ;
			 std::cout << std::endl;
			 for (std::vector<int>::iterator it = real.begin() ; it != real.end(); ++it)
			 std::cout << ' ' << *it ;
			 std::cout << std::endl;
			 for (ft::vector<int>::iterator it = my.begin() ; it != my.end(); ++it)
			 std::cout << ' ' << *it ;
			 std::cout << std::endl;

			 ok;
			 */

		}
		{
			ft::vector<int> foo (3,100);   // three ints with a value of 100
			ft::vector<int> bar (5,200);   // five ints with a value of 200
			std::vector<int> foo2 (3,100);   // three ints with a value of 100
			std::vector<int> bar2 (5,200);   // five ints with a value of 200

			foo.swap(bar);
			foo2.swap(bar2);

			check_all( &foo2, &foo);
			check_all( &bar2, &bar);

			foo2.clear();
			foo.clear();
			check_all( &foo2, &foo);


		}
		{

			ft::vector<int> my(10, 1);
			std::vector<int> real;


			for (size_t i = 0; i < my.size() - 1 ; i++)
				std::cout << my[i] << "-" ;
			std::cout << std::endl;

			std::cout << my.capacity() << std::endl;
			ft::vector<int>::iterator it = my.begin();
			ft::vector<int>::const_iterator ite = my.begin();
			my.insert ( it , 2 );
			for (size_t i = 0; i < my.size() - 1 ; i++)
				std::cout << my[i] << "-" ;
			std::cout << std::endl;

			it = my.begin();
			my.insert ( it , 3 );
			it = my.begin();
			my.insert ( it , 4 );
			it = my.begin();
			for (size_t i = 0; i < my.size() - 1 ; i++)
				std::cout << my[i] << "-" ;
			std::cout << std::endl;
			my.insert ( it , 5 );
			it = my.begin();
			my.insert ( it , 6 );
			it = my.begin();
			std::cout << my.size() << " -  "  << my.capacity() << std::endl;
			my.insert ( it , 7 );
			it = my.begin();
			my.insert ( it , 8 );
			std::cout << my.size() << "  - "  << my.capacity() << std::endl;
			it = my.begin();
			my.insert ( it , 9 );
			std::cout << my.size() << "-   "  << my.capacity() << std::endl;
			my.insert ( it , 9 );
			std::cout << my.size() << " -  "  << my.capacity() << std::endl;
			my.insert ( it , 9 );
			std::cout << my.size() << "  - "  << my.capacity() << std::endl;
			my.insert ( it , 9 );
			my.insert ( it , 9 );
			my.insert ( it , 9 );
			my.insert ( it , 9 );
			my.insert ( it , 9 );
			my.insert ( it , 9 );
			my.insert ( it , 9 );
			my.insert ( it , 9 );
			std::cout << my.size() << " -  "  << my.capacity() << std::endl;
			int array2[33] = {7, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33};
			my.insert(my.end(), array2, array2 + 33);

			for (size_t i = 0; i < my.size() - 1 ; i++)
				std::cout << my[i] << "-" ;
			std::cout << std::endl;

			std::cout << "(const_ite - it): " << (ite - it) << std::endl;

			ft::vector<int> vct(my.begin(), my.end());
			for (size_t i = 0; i < my.size() - 1 ; i++)
				std::cout << vct[i] << "-" ;
			std::list<int> lst;
			std::list<int>::iterator lst_it;
			for (int i = 1; i < 5; ++i)
				lst.push_back(i * 3);

			ft::vector<int> vctt(lst.begin(), lst.end());
			vct.assign(lst.begin(), lst.end());
			vct.insert(vct.end(), lst.rbegin(), lst.rend());


			ft::map<int, char> mymap;
			ft::map<int, int > map;
			std::cout << std::endl;
			mymap.insert(ft::make_pair(8, 'a'));
			mymap.insert(ft::make_pair(3, 'c'));
			mymap.insert(ft::make_pair(1, 'd'));
			mymap.insert(ft::make_pair(6, 'e'));
			mymap.insert(ft::make_pair(4, 'f'));
			mymap.insert(ft::make_pair(7, 'g'));
			mymap.insert(ft::make_pair(13, 'i'));
			mymap.insert(ft::make_pair(10, 'b'));
			mymap.insert(ft::make_pair(14, 'h'));
			std::cout << "lower 0 = " << mymap.lower_bound(0)->first << std::endl;
			std::cout << "upper 0 = " << mymap.upper_bound(0)->first << std::endl;
			std::cout << "lower 4 = " << mymap.lower_bound(4)->first << std::endl;
			std::cout << "upper 4 = " << mymap.upper_bound(4)->first << std::endl;
			std::cout << "lower 5 = " << mymap.lower_bound(5)->first << std::endl;
			std::cout << "upper 5 = " << mymap.upper_bound(5)->first << std::endl;
			// std::cout << mymap.insert(ft::make_pair(20, 20)).second << std::endl;
			// std::cout << mymap.insert(ft::make_pair(20, 20)).second << std::endl;
			// std::cout << "1size = " << mymap.size() << std::endl;
			// std::cout << mymap.insert(ft::make_pair(10, 10)).second << std::endl;
			// std::cout << "2size = " << mymap.size() << std::endl;
			// std::cout << mymap.insert(mymap.end(), ft::make_pair(29, 29))->first<< std::endl;
			// std::cout << "3size = " << mymap.size() << std::endl;
			// std::cout << mymap.insert(mymap.end(), ft::make_pair(24, 24))->first<< std::endl;
			// std::cout << "4size = " << mymap.size() << std::endl;
			// std::cout << mymap.insert(ft::make_pair(30, 30)).second << std::endl;
			// std::cout << "5size = " << mymap.size() << std::endl;
			// std::cout << mymap.insert(ft::make_pair(26, 26)).second << std::endl;
			// std::cout << "5size = " << mymap.size() << std::endl;
			// std::cout << mymap.insert(ft::make_pair(15, 15)).second << std::endl;
			// std::cout << "5size = " << mymap.size() << std::endl;
			// std::cout << mymap.insert(ft::make_pair(18, 18)).second << std::endl;
			// std::cout << "5size = " << mymap.size() << std::endl;
			// std::cout << mymap.insert(ft::make_pair(17, 17)).second << std::endl;
			// std::cout << "5size = " << mymap.size() << std::endl;
			// std::cout << mymap.insert(ft::make_pair(2, 2)).second << std::endl;
			// std::cout << "5size = " << mymap.size() << std::endl;
			// std::cout << mymap.insert(ft::make_pair(13, 13)).second << std::endl;
			// std::cout << "5size = " << mymap.size() << std::endl;
			// std::cout << mymap.insert(ft::make_pair(56, 56)).second << std::endl;
			// std::cout << "5size = " << mymap.size() << std::endl;
			// std::cout << mymap.insert(ft::make_pair(33, 33)).second << std::endl;
			// std::cout << "5size = " << mymap.size() << std::endl;
			// std::cout << mymap.insert(ft::make_pair(100, 100)).second << std::endl;
			std::cout << "5size = " << mymap.size() << std::endl;
// 
			// std::cout << "---------------------------------------------- Begin erase = " << mymap.begin().base()->value.second << " | End = " << mymap.end().base()->parent->value.second << std::endl;
			// mymap.erase(mymap.find(2));
			// mymap.erase(mymap.find(10));
			// mymap.erase(mymap.find(13));
			// mymap.erase(mymap.find(15));
			// mymap.erase(mymap.find(17));
			// mymap.erase(mymap.find(18));
			// mymap.erase(mymap.find(20));
			// mymap.erase(mymap.find(24));
			// mymap.erase(mymap.find(26));
			// mymap.erase(mymap.find(28));
			// mymap.erase(mymap.find(29));
			// mymap.erase(mymap.find(33));
			// mymap.erase(mymap.find(56));
			
			// mymap.erase(mymap.end().base()->parent->parent);
			// std::cout << " ---------------------------------------------- Begin erase = " << mymap.begin().base()->value.second << " | End = " << mymap.end().base()->parent->value.second << std::endl;
// 
			// std::cout << std::endl << mymap._first_element->value.second << std::endl;
			// for (ft::map<int ,int>::iterator ito(mymap.begin()); ito != mymap.end(); ito++)
			// {
				// std::cout << "height = " << ito.base()->height << " - " << ito->first << std::endl;
				// if (ito.base()->left)
				// {
					// std::cout << "Left height = " << ito.base()->left->height << " - " << ito.base()->left->value.second << std::endl;
				// }
				// if (ito.base()->right)
				// {
					// std::cout << "right height = " << ito.base()->right->height << " - " << ito.base()->right->value.second << std::endl;
				// }
				// if (ito.base()->parent)
				// {
					// std::cout << "parent height = " << ito.base()->parent->height << " - " << ito.base()->parent->value.second << std::endl;
				// }
				// std::cout << std::endl;
				// mymap.erase(ito);
			// }
// 
			// ft::map<int, int> m(mymap);
			// std::cout << "is empty ? : " << m.empty() << std::endl;
			// std::cout << "is size ? : " << m.size() << std::endl;
			// mymap.erase(mymap.find(100));

        	// std::cout << &it << "  " << ito.base()  << "  " << ito.base()->parent << std::endl;
			// std::cout << "Begin = " << mymap.begin().base()->value.second << " End parent = " << mymap.end().base()->parent->value.second << std::endl;
// 
// 
        	// ft::pair<int, int > test;
        	// ft::pair<int, int > test2(3, 5);
// 
        	// test = ft::pair<int, int >(8,2);
        	// std::cout << "test" << std::endl;
			

			// my.
        	// my.insert( test );
        	// std::cout << my._root << " " << my._root->godfather << " " << my._root->left << " " << my._root->right << " " << my._root->pair.first << " " << my._root->pair.second << std::endl;
        	// test = test2;
        	// my.insert ( test );;
        	// std::cout << my._root << " " << my._root->godfather << " " << my._root->left << " " << my._root->right << " " << my._root->pair.first << " " << my._root->pair.second << std::endl;
        	// my._root = my._root->left;
        	// std::cout << my._root << " " << my._root->godfather << " " << my._root->left << " " << my._root->right << " " << my._root->pair.first << " " << my._root->pair.second << std::endl;
//        first.insert ( ft::pair<int ,int>( 7 ,50) );;
//        first.insert ( ft::pair<int ,int>( 6 ,150) );;
//        std::cout << "mymap contains:\n";
//        for (size_t i = 0; i < my.size(); i++)
//            std::cout << my[i].first << " == " << my[i].second << std::endl;
//        for (ft::map<int ,int>::iterator it = first.begin(); it != first.end(); ++it)
//            std::cout << it->pair.first << " => " << it->pair.second << '\n';
//			check_all( &real, &my );

//			real.insert ( real.begin() + 1 , 5 , 300 );
//			my.insert ( my.begin() + 1 , 5 , 300 );
//			check_all( &real, &my );
//			
//			real.insert ( real.begin() + 5 , 2 );
//			my.insert( my.begin() + 5 , 2 );
//			check_all( &real, &my );
		}
		//check a faire sur assigm avec iterator  




		//BIZARREE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//			check_all( real, my);
		//			c(real.capacity(), my.capacity() ) ;



	}
}