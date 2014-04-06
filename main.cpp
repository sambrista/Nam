#include <QApplication>
#include "ventana.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	Ventana *juego = new Ventana;
	juego->show();
	return(app.exec());
}
