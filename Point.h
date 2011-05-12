#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <assert.h>

template <int k, typename T>
class Point
{
	public:
		Point();
		Point(T coord[k]);
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
Point<k,T>::Point(T coord[k])
{
	assert(k > 0);
	for(int i = 0; i < k; i++)
		coordonnees[i] = coord[i]; 
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
