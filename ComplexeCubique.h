#ifndef COMPLEXECUBIQUE_H
#define COMPLEXECUBIQUE_H

#include <vector>
#include <map>
#include "Cellule.h"

template<int n, int k, typename T>
class ComplexeCubique
{
     public:
          ComplexeCubique();
          ~ComplexeCubique();
          bool estValide();
          void creerCellule(Point<k,T>* point);
          template<int dimension> void creerCellule(const std::vector<int>& indicesCellules);
          void supprimerCellule(CelluleVirtuelle* cellule);
          std::vector<CelluleVirtuelle*>::iterator touverCellule(CelluleVirtuelle* cellule);
          std::vector<CelluleVirtuelle*>::iterator trouverIPlus1Cellule(CelluleVirtuelle* cellule);
          bool reduction(CelluleVirtuelle* c1, CelluleVirtuelle* c2);
          void simplification();
          std::vector<CelluleVirtuelle*>* getCellules(int dimension);
          CelluleVirtuelle* getCellule(int dimension, int position);
          template<int _n, int _k, typename _T> friend std::ostream& operator<<(std::ostream& sortie, const ComplexeCubique<_n,_k,_T>& complexe);

     private:
          std::map<int, std::vector<CelluleVirtuelle*>*> ensemblesCellules;

};

template<int n, int k, typename T>
ComplexeCubique<n,k,T>::ComplexeCubique()
{
     for (int i=0; i<=n; i++)
          ensemblesCellules.insert(std::pair<int, std::vector<CelluleVirtuelle*>*>(i, new std::vector<CelluleVirtuelle*>()));
}

template<int n, int k, typename T>
ComplexeCubique<n,k,T>::~ComplexeCubique()
{
     std::map<int, std::vector<CelluleVirtuelle*>*>::iterator itMap;
     std::vector<CelluleVirtuelle*>::iterator itVec;

     for (itMap = ensemblesCellules.begin(); itMap != ensemblesCellules.end(); ++itMap)
     {
          std::vector<CelluleVirtuelle*>* vVirtICell = itMap->second;
          for (itVec = vVirtICell->begin(); itVec != vVirtICell->end(); ++itVec)
          {
               delete *itVec;
          }
          vVirtICell->clear();
          delete itMap->second;
     }
     ensemblesCellules.clear();
}

template<int n, int k, typename T>
bool ComplexeCubique<n,k,T>::estValide()
{
     std::map<int, std::vector<CelluleVirtuelle*>*>::iterator itMap;
     for (itMap = ensemblesCellules.begin(); itMap != ensemblesCellules.end(); ++itMap)
     {
          std::vector<CelluleVirtuelle*> vVirtICell = *(itMap->second);
          std::vector<CelluleVirtuelle*>::iterator itVect;
          for (itVect = vVirtICell.begin(); itVect != vVirtICell.end(); ++itVect)
          {
               const std::vector<CelluleVirtuelle*>* picBorderCells = (*itVect)->getBords();
               if (picBorderCells != NULL)
               {
                    for (int i = 0; i < picBorderCells->size(); i++)
                    {
                         if (picBorderCells->at(i) == NULL)
                              return false;
                    }
               }
          }
     }
     return true;
}

template<int n, int k, typename T>
void ComplexeCubique<n,k,T>::creerCellule(Point<k,T>* point)
{
    Cellule<0>* cellule = new Cellule<0>(*point);
    ensemblesCellules.find(0)->second->push_back(cellule);
}

template<int n, int k, typename T>
template<int dimension>
void ComplexeCubique<n,k,T>::creerCellule(const std::vector<int>& indicesCellules)
{
    Cellule<dimension-1>* temp;
    std::vector<Cellule<dimension-1>*>* cellulesBord = new std::vector<Cellule<dimension-1>*>();
    for (unsigned int i = 0; i < indicesCellules.size(); ++i)
    {
        temp = static_cast<Cellule<dimension-1>*>(ensemblesCellules[dimension-1]->at(indicesCellules[i]));
        cellulesBord->push_back(temp);
    }
    Cellule<dimension>* cellule = new Cellule<dimension>(cellulesBord);
    ensemblesCellules[dimension]->push_back(cellule);
}

template<int n, int k, typename T>
void ComplexeCubique<n,k,T>::supprimerCellule(CelluleVirtuelle* cellule)
{
    if (cellule == NULL)
        return;

    int dimension = cellule->getDimension();
    if (dimension < n)
    {
        assert(trouverIPlus1Cellule(cellule) == ensemblesCellules[0]->end());
    }

    std::vector<CelluleVirtuelle*>::iterator it = touverCellule(cellule);
    ensemblesCellules[dimension]->erase(it);
}

template<int n, int k, typename T>
std::vector<CelluleVirtuelle*>::iterator ComplexeCubique<n,k,T>::touverCellule(CelluleVirtuelle* cellule)
{
    if (cellule == NULL)
        return ensemblesCellules[0]->end();
    int dimension = cellule->getDimension();
    return find(ensemblesCellules[dimension]->begin(), ensemblesCellules[dimension]->end(), cellule);
}

template<int n, int k, typename T>
std::vector<CelluleVirtuelle*>::iterator ComplexeCubique<n,k,T>::trouverIPlus1Cellule(CelluleVirtuelle* cellule)
{
    if (cellule == NULL || cellule->getDimension() == n)
        return ensemblesCellules[0]->end();

    int dimension = cellule->getDimension();
    std::vector<CelluleVirtuelle*>::iterator it;
    for (it = ensemblesCellules[dimension+1]->begin(); it != ensemblesCellules[dimension+1]->end(); ++it)
    {
      if ((*it)->hasIMoins1Cellule(cellule))
           return it;
    }
    return ensemblesCellules[0]->end();
}

template<int n, int k, typename T>
bool ComplexeCubique<n,k,T>::reduction(CelluleVirtuelle* c1, CelluleVirtuelle* c2)
{
    if ((c1 == NULL || c2 == NULL) && (c1->getDimension() == c2->getDimension() - 1))
        return false;

    //C1 est dans le bord de C2
    if (!c2->hasIMoins1Cellule(c1))
            return false;

    //Il n’existe pas de (i + 1)-cellule (à part c2) ayant c1 dans son bord
    std::vector<CelluleVirtuelle*>::iterator it;
    int dimension = c1->getDimension() + 1;
    for (ensemblesCellules[dimension]->begin(); it != ensemblesCellules[dimension]->end(); ++it)
    {
        if ((*it)->hasIMoins1Cellule(c1) && *it != c2)
            return false;
    }

    //Il n’existe pas de (i + 2)-cellule ayant c2 dans son bord
    dimension = c1->getDimension() + 2;
    if (n <= c1->getDimension() + 2)
    {
        for (ensemblesCellules[dimension]->begin(); it != ensemblesCellules[dimension]->end(); ++it)
        {
            if ((*it)->hasIMoins1Cellule(c2))
                return false;
        }
    }

    //Suppression des deux cellules
    supprimerCellule(c1);
    supprimerCellule(c2);

    return true;
}

template<int n, int k, typename T>
void ComplexeCubique<n,k,T>::simplification()
{
    bool Reductible = false;

    std::vector<CelluleVirtuelle*>::iterator itCellule, itCelluleBord;
    std::vector<CelluleVirtuelle*>* vect;

    for (int i = n; i > 0; --i)
    {
        vect = ensemblesCellules.find(i)->second;

        for (itCellule = vect->begin(); itCellule != vect->end(); ++itCellule)
        {
            if (Reductible)
            {
                itCellule = vect->begin();
                Reductible = false;
            }

            for (itCelluleBord = (*itCellule)->getBords()->begin();
                 itCelluleBord != (*itCellule)->getBords()->end();
                 ++itCelluleBord)
            {
                Reductible = reduction(*itCelluleBord, *itCellule);
                if (Reductible)
                    break;
            }
        }

    }
}

template<int n, int k, typename T>
std::vector<CelluleVirtuelle*>* ComplexeCubique<n,k,T>::getCellules(int dimension)
{
    return ensemblesCellules.find(dimension)->second;
}

template<int n, int k, typename T>
CelluleVirtuelle* ComplexeCubique<n,k,T>::getCellule(int dimension, int position)
{
    assert(dimension >= 0 && dimension <= n);
    assert(position >= 0 && (unsigned) position < ensemblesCellules[dimension]->size());
    return ensemblesCellules[dimension]->at(position);
}

template<int n, int k, typename T>
std::ostream& operator<<(std::ostream& sortie, const ComplexeCubique<n,k,T>& complexe)
{
    sortie << n << " " << k << std::endl;
    for (int i=0; i<=n; i++)
        sortie << complexe.ensemblesCellules.find(i)->second->size() << " ";
    sortie << std::endl << std::endl;

    for (unsigned int i=0; i<complexe.ensemblesCellules.find(0)->second->size(); i++)
        sortie << ((Cellule<0>*) complexe.ensemblesCellules.find(0)->second->at(i))->getSommet() << std::endl;

    sortie << std::endl;

    for (int j=1; j<=n; j++)
    {
        for (unsigned int i=0; i<complexe.ensemblesCellules.find(j)->second->size(); i++)
        {
            std::vector<CelluleVirtuelle*>* vectIMoins1 = complexe.ensemblesCellules.find(j-1)->second;

            CelluleVirtuelle* cellule = complexe.ensemblesCellules.find(j)->second->at(i);
            std::vector<CelluleVirtuelle*>::iterator it;
            for (it = cellule->getBords()->begin(); it != cellule->getBords()->end(); ++it)
            {
                int indice = std::find(vectIMoins1->begin(), vectIMoins1->end(), *it) - vectIMoins1->begin();
                sortie << indice << " ";
            }
            sortie << std::endl;
        }
        sortie << std::endl;
    }
    return sortie;
}

#endif
