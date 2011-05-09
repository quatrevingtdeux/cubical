#ifndef POINT_H
#define POINT_H

template <int k, class T>
class Point
{
	public:
		Point<k,T>();
		void setCoordonnees();
		int getDimension();
		
	private:
		T coordonnees[k];
		//std::valarray<T> coordonnees;
};

#endif