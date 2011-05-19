
#include <QApplication>
#include "ComplexeCubique.h"
#include "Viewer.h"
#include "Parser.h"

int main(int argc, char** argv)
{
	ComplexeCubique<DIM_C,DIM_P,TYPE> complexe;

	if (argc < 2)
	{
		std::cout << "Usage:\n\t" << argv[0] << " " << "fichier-complexe [--gui]" << std::endl;
		exit(EXIT_FAILURE);
	}

	Parser parseur(complexe, argv[1]);

	if (argc == 3 && strcmp("--gui", argv[2]) == 0)
	{
		glutInit(&argc, argv);
		QApplication app(argc, argv);
		app.setApplicationName("Cubical");

		Viewer<3,3,int> viewer(&complexe);
		viewer.show();
		app.exec();
	}
	else
	{
		std::cout << "Avant simplification :\n" << complexe << std::endl;
		while(complexe.simplifier());
		std::cout << "Après simplification :\n" << complexe << std::endl;
	}

	complexe.~ComplexeCubique();

	return EXIT_SUCCESS;
}
