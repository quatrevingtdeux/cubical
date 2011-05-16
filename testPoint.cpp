
#include <iostream>
#include <vector>
#include "Point.h"

bool testPoint()
{
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	// test class Point<k, T>
	std::cout << "=== Test de la class Point<k,T> ===" << std::endl;
	
	// Point()
	std::cout << "Test de Point() et ~Point()..." << std::endl;
	Point<3, int> test0;
	Point<2, double>* test = new Point<2, double>();
	Point<3, int>* test2 = new Point<3, int>();
	test2->~Point();
	std::cout << "...OK" << std::endl;
	
	//Point(const std::vector<T> coord)
	std::cout << "Test de Point(vector)..." << std::endl;
	std::vector<int> coord;
	for (int i = 0; i < 3; ++i)
		coord.push_back(i+1);
	Point<3, int> test3(coord);
	Point<3, int>* test4 = new Point<3, int>(coord);
	test4->~Point();
	std::cout << "...OK" << std::endl;
	
	//~Point()
	// previsouly tested
	
	//int getDimension() const;
	std::cout << "Test de getDimension()..." << std::endl;
	if (test0.getDimension() != 3)
		return false;
	if (test->getDimension() != 2)
		return false;
	test0.~Point();
	test->~Point();
	std::cout << "...OK" << std::endl;
	
	//T& operator[](int i);
	std::cout << "Test de operator[]()..." << std::endl;
	if (test3[2] != 3)
		return false;	
	std::cout << "...OK" << std::endl;
	
	//template<int _k, typename _T> friend std::ostream& operator<<(std::ostream& sortie, const Point<_k,_T>& point);
	std::cout << "Test de operator<<()..." << std::endl;
	std::cout << test3 << std::endl;
	test3.~Point();
	std::cout << "...OK" << std::endl;
	
	std::cout << "=== All tests succeeded ===" << std::endl;
	return true;
}


