#ifndef __VENTANA_H__
#define __VENTANA_H__

#include <QMainWindow>
#include <QAction>
#include <QMenu>

class QMenu;
class QAction;

class Ventana : public QMainWindow {
	Q_OBJECT

	public:
		Ventana();
	private:
		QMenu *menJuego;
		QMenu *menAcercaDe;
		QAction *actSalir;
		QAction *actAcercaNam;
		QAction *actAcercaQT;
	private slots:
		void acercaDe();
		void acercaDeQT();
};

#endif
