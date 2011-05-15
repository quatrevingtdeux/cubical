#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <vector>
#include <assert.h>

// ============================================================
// Classe Point
// ============================================================

template <int k, typename T>
class Point
{
        public:
                Point(); // Le constructeur n'initialise pas le tableau de coordonnées (impossible car T varie)
                Point(const std::vector<T> coord);
                ~Point() {} // Le destructeur ne détruit rien (car T peut être un int, par exemple)
                int getDimension() const;
                T& operator[](int i);
                template<int _k, typename _T> friend std::ostream& operator<<(std::ostream& sortie, const Point<_k,_T>& point);
		
	private:
                T coordonnees[k];
};

// ============================================================
// Implémentation des méthodes
// ============================================================

template <int k, typename T>
Point<k,T>::Point()
{
    assert(k > 0);
}

template <int k, typename T>
Point<k,T>::Point(const std::vector<T> coord)
{
        assert(k > 0 && coord.size() == k);
        for(int i = 0; i < k; i++)
        {
            coordonnees[i] = coord[i];
        }
}

template <int k, typename T>
int Point<k,T>::getDimension() const
{
	return k;
}

template <int k, typename T>
T& Point<k,T>::operator[](int i)
{
	assert(i >= 0 && i < k);
	return coordonnees[i];
}

template <int k, typename T>
std::ostream& operator<<(std::ostream& sortie, const Point<k,T>& point)
{
    sortie << "Point :" << std::endl;
    sortie << "\tDimension = " << point.getDimension() << std::endl;
    sortie << "\tAdresse = " << &point << std::endl;
    for(int i=0; i<k; i++)
        sortie << "\tcoordonnees[" << i << "] = " << point.coordonnees[i] << std::endl;
    return sortie;
}

#endif
