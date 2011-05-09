#ifndef POINT_H
#define POINT_H

template <int k, class T>
class Point
{
	public:
		Point();
		setCoordonnees();
		
	private:
		std::vector<T> coordonnees; //TODO taille k
};

#endif
