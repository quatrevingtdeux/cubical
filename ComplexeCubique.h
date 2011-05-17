#ifndef ComplexeCubique_H
#define ComplexeCubique_H

#include <vector>
#include <map>
#include "Cellule.h"

#define DIM_C 3
#define DIM_P 3
#define TYPE int

template<int n, int k, typename T>
class ComplexeCubique
{
     public:
          ComplexeCubique();
          ~ComplexeCubique();

          bool estValide();
          void ajouterCellule(CelluleVirtuelle* cellule);
          void supprimerCellule(CelluleVirtuelle* cellule);
          std::vector<CelluleVirtuelle*>::iterator touverCellule(CelluleVirtuelle* cellule);
          std::vector<CelluleVirtuelle*>::iterator trouverIPlus1Cellule(CelluleVirtuelle* cellule);
          bool reduction(CelluleVirtuelle* c1, CelluleVirtuelle* c2);
          template<int _n, int _k, typename _T> friend std::ostream& operator<<(std::ostream& sortie, const ComplexeCubique<_n,_k,_T>& complexe);

     private:
          std::map<int, std::vector<CelluleVirtuelle*>*> ensemblesCellules;

};

template<int n, int k, typename T>
ComplexeCubique<n, k, T>::ComplexeCubique()
{
     for(int i=0; i<=n; i++)
          ensemblesCellules.insert(std::pair<int, std::vector<CelluleVirtuelle*>*>(i, new std::vector<CelluleVirtuelle*>()));
}

template<int n, int k, typename T>
ComplexeCubique<n, k, T>::~ComplexeCubique()
{
     std::map<int, std::vector<CelluleVirtuelle*>*>::iterator itMap;
     std::vector<CelluleVirtuelle*>::iterator itVec;

     for(itMap = ensemblesCellules.begin(); itMap != ensemblesCellules.end(); ++itMap)
     {
          std::vector<CelluleVirtuelle*> vVirtICell = *(itMap->second);
          for(itVec = vVirtICell.begin(); itVec != vVirtICell.end(); )
          {
               delete *itVec;
               itVec = vVirtICell.erase(itVec);
          }
          delete itMap->second;
     }
     ensemblesCellules.clear();
}

template<int n, int k, typename T>
bool ComplexeCubique<n, k, T>::estValide()
{
     std::map<int, std::vector<CelluleVirtuelle*>*>::iterator itMap;
     for(itMap = ensemblesCellules.begin(); itMap != ensemblesCellules.end(); ++itMap)
     {
          std::vector<CelluleVirtuelle*> vVirtICell = *(itMap->second);
          std::vector<CelluleVirtuelle*>::iterator itVect;
          for(itVect = vVirtICell.begin(); itVect != vVirtICell.end(); ++itVect)
          {
               const std::vector<CelluleVirtuelle*>* picBorderCells = (*itVect)->getBords();
               if(picBorderCells != NULL)
               {
                    for(int i = 0; i < picBorderCells->size(); i++)
                    {
                         if(picBorderCells->at(i) == NULL)
                              return false;
                    }
               }
          }
     }
     return true;
}

template<int n, int k, typename T>
void ComplexeCubique<n, k, T>::ajouterCellule(CelluleVirtuelle* cellule)
{
    assert(cellule->getDimension() <= n);
    ensemblesCellules[cellule->getDimension()]->push_back(cellule);
}

template<int n, int k, typename T>
void ComplexeCubique<n, k, T>::supprimerCellule(CelluleVirtuelle* cellule)
{
    if(cellule == NULL)
        return;

    int dimension = cellule->getDimension();
    if(dimension < n)
    {
        assert(trouverIPlus1Cellule(cellule) == ensemblesCellules[0]->end());
    }

    std::vector<CelluleVirtuelle*>::iterator it = touverCellule(cellule);
    delete cellule;
    ensemblesCellules[dimension]->erase(it);
}

template<int n, int k, typename T>
std::vector<CelluleVirtuelle*>::iterator ComplexeCubique<n, k, T>::touverCellule(CelluleVirtuelle* cellule)
{
    if(cellule == NULL)
        return ensemblesCellules[0]->end();
    int dimension = cellule->getDimension();
    return find(ensemblesCellules[dimension]->begin(), ensemblesCellules[dimension]->end(), cellule);
}

template<int n, int k, typename T>
std::vector<CelluleVirtuelle*>::iterator ComplexeCubique<n, k, T>::trouverIPlus1Cellule(CelluleVirtuelle* cellule)
{
    if(cellule == NULL || cellule->getDimension() == n)
        return ensemblesCellules[0]->end();

    int dimension = cellule->getDimension();
    std::vector<CelluleVirtuelle*>::iterator it;
    for(it = ensemblesCellules[dimension+1]->begin(); it != ensemblesCellules[dimension+1]->end(); ++it)
    {
      if((*it)->hasIMoins1Cellule(cellule))
           return it;
    }
    return ensemblesCellules[0]->end();
}

template<int n, int k, typename T>
bool ComplexeCubique<n, k, T>::reduction(CelluleVirtuelle* c1, CelluleVirtuelle* c2)
{
    if((c1 == NULL || c2 == NULL) && (c1->getDimension() == c2->getDimension() - 1))
        return false;

    //C1 est dans le bord de C2
    if(!c2->hasIMoins1Cellule(c1))
            return false;

    //Il n’existe pas de (i + 1)-cellule (à part c2) ayant c1 dans son bord
    std::vector<CelluleVirtuelle*>::iterator it;
    int dimension = c1->getDimension() + 1;
    for(ensemblesCellules[dimension]->begin(); it != ensemblesCellules[dimension]->end(); ++it)
    {
        if((*it)->hasIMoins1Cellule(c1) && *it != c2)
            return false;
    }

    //Il n’existe pas de (i + 2)-cellule ayant c2 dans son bord
    dimension = c1->getDimension() + 2;
    if(n <= c1->getDimension() + 2)
    {
        for(ensemblesCellules[dimension]->begin(); it != ensemblesCellules[dimension]->end(); ++it)
        {
            if((*it)->hasIMoins1Cellule(c2))
                return false;
        }
    }

    //Suppression des deux cellules
    supprimerCellule(c1);
    supprimerCellule(c2);

    return true;
}

template<int n, int k, typename T>
std::ostream& operator<<(std::ostream& sortie, const ComplexeCubique<n,k,T>& complexe)
{
    sortie << n << " " << k << std::endl;
    for(int i=0; i<=n; i++)
        sortie << complexe.ensemblesCellules.find(i)->second->size() << " ";
    sortie << std::endl;

    for(int i=0; i<complexe.ensemblesCellules.find(0)->second->size(); i++)
        sortie << ((Cellule<0>*) complexe.ensemblesCellules.find(0)->second->at(i))->getSommet() << std::endl;

    for(int j=1; j<=n; j++)
    {
        for(int i=1; i<complexe.ensemblesCellules.find(j)->second->size(); i++)
        {
            CelluleVirtuelle* cellule = complexe.ensemblesCellules.find(j)->second->at(i);
            for(std::vector<CelluleVirtuelle*>::iterator it = cellule->getBords()->begin(); it != cellule->getBords()->end(); ++it)
                sortie << std::find(cellule->getBords()->begin(), cellule->getBords()->end(), cellule) - cellule->getBords()->begin() << " ";
        }
        sortie << std::endl;
    }
    return sortie;
}

#endif
