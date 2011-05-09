#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <assert.h>

template <int k, typename T>
class Point
{
	public:
		Point();
		~Point() {}
		int getDimension();
		T& operator[](int i);
		
	private:
		T coordonnees[k];
};

template <int k, typename T>
Point<k,T>::Point()
{
	assert(k > 0);
}

template <int k, typename T>
int Point<k,T>::getDimension()
{
	return k;
}

template <int k, typename T>
T& Point<k,T>::operator[](int i)
{
	assert(i >= 0 && i < k);
	return coordonnees[i];
}

#endif

int PointTest()
{
	Point<5,int> p;
	std::cout << "Dimension=" << p.getDimension() << std::endl;
	p[0] = 28;
	std::cout << "p[0]=" << p[0] << std::endl;
	return 0;
}
