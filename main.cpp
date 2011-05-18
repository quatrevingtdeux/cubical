
#include <QApplication>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include "ComplexeCubique.h"
#include "Cellule.h"
#include "Viewer.h"

#include "Parser.h"

using namespace std;

int main(int argc, char** argv)
{
	ComplexeCubique<DIM_C,DIM_P,TYPE> complexe;
	if (argc == 2)
	{
		Parser parseCeFichier(complexe, argv[1]);

		std::cout << complexe << std::endl;
	}

	glutInit(&argc, argv);
	QApplication app(argc, argv);
	app.setApplicationName("Cubical complex");

	Viewer<3,3,int> viewer(&complexe);

	viewer.show();
	return app.exec();

	//comp.~ComplexeCubique();
	return EXIT_SUCCESS;
}
