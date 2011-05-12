#include <QApplication>
#include <fstream>
#include "viewer.h"
//------------------------------------------------------------------------------
//-------------------------------------main-------------------------------------
//------------------------------------------------------------------------------
int main(int argc, char**argv)
{
  if (argc!=2)
    {
      std::cout<<"Usage: a.out file\n"
	       <<" avec filename le nom d'un fichier texte décrivant un complexe cubique 3 3\n";
      return EXIT_FAILURE;
    }

  // 1) créer un complexe, en le lisant dans le fichier argv[1].

  int c; // modifier
  /* ... TODO */
  
  // 2) Lancer l'ihm.
  glutInit(&argc, argv);
  QApplication app(argc, argv);  
  app.setApplicationName("Cubical complex");

  Viewer<3,3,double> v(c); // A changer si besoin pour les template arguments.

  v.show();
  return app.exec();
}
