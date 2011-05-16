#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "ComplexeCubique.h"

//#include "testPoint.cpp"

#define DIMENSION_COMPLEXE 3
#define DIMENSION_POINTS 3
#define NOMBRE_0_CELLULES 10
#define NOMBRE_1_CELLULES 10
#define NOMBRE_2_CELLULES 1

#include "testPoint.cpp"

using namespace std;

int main(int argc, char** argv)
{
        if(argc != 2)
	{
		cout << "Usage: " << argv[0] << " " << "descripteur" << endl;
		exit(EXIT_FAILURE);
	}
	
	ifstream fichier(argv[1]);
	
	testPoint();

	if(fichier)
        {
		string input;
                getline(fichier,input);
                istringstream ligne(input);

                int bidon;
                ligne >> bidon;
                if(bidon != DIMENSION_COMPLEXE)
                {
                    cout << "Dimensions du complexe non concordantes : " << bidon << " != " << DIMENSION_COMPLEXE << endl;
                    exit(EXIT_FAILURE);
                }

                ligne >> bidon;
                if(bidon != DIMENSION_POINTS)
                {
                    cout << "Dimensions des points non concordantes : " << bidon << " != " << DIMENSION_POINTS << endl;
                    exit(EXIT_FAILURE);
                }

                getline(fichier, input);
                istringstream ligne2(input);

                ligne2 >> bidon;
                if(bidon != NOMBRE_0_CELLULES)
                {
                    cout << "Nombres de 0-cellules non concordants : " << bidon << " != " << NOMBRE_0_CELLULES << endl;
                    exit(EXIT_FAILURE);
                }

                ligne2 >> bidon;
                if(bidon != NOMBRE_1_CELLULES)
                {
                    cout << "Nombres de 1-cellules non concordants : " << bidon << " != " << NOMBRE_1_CELLULES << endl;
                    exit(EXIT_FAILURE);
                }

                ligne2 >> bidon;
                if(bidon != NOMBRE_2_CELLULES)
                {
                    cout << "Nombres de 2-cellules non concordants : " << bidon << " != " << NOMBRE_2_CELLULES << endl;
                    exit(EXIT_FAILURE);
                }

                //Créer le complexe
                ComplexeCubique<DIMENSION_COMPLEXE,DIMENSION_POINTS,int> complexe;

                for(int i = 0; i < NOMBRE_0_CELLULES; i++)
                {
                    //Lire et créer point
                    Point<DIMENSION_POINTS,int>* point = new Point<DIMENSION_POINTS,int>();
                    getline(fichier, input);
                    istringstream ligne3(input);
                    for(int j = 0; j < DIMENSION_POINTS; j++)
                    {
                        int coordonnee;
                        ligne3 >> coordonnee;
                        (*point)[j] = coordonnee;
                    }
                    //Ajouter 0-cellule au complexe
                    complexe.creerCellule(point);
                }

                for(int i = 0; i < NOMBRE_1_CELLULES; i++)
                {
                    //Lire et récupérer 0-cellules
                    //Ajouter 1-cellule au complexe attachée à son bord
                }

                for(int i = 0; i < NOMBRE_2_CELLULES; i++)
                {
                    //Lire et récupérer 1-cellules
                    //Ajouter 2-cellule au complexe attachée à son bord
                }

                complexe.~ComplexeCubique();
                fichier.~ifstream();


        }

	exit(EXIT_SUCCESS);
}
