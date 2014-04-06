
#include "ventana.h"
#include "juego.h"
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include "constantes.h"

Ventana::Ventana() {
	QWidget *juego = new Juego;
	actSalir = new QAction(tr("&Salir"),this);
	actSalir->setShortcut(tr("Ctrl+S"));
	actSalir->setStatusTip(tr("Pulse aqui para salir"));
	actAcercaNam = new QAction(QString::fromUtf8("Acerca de Ñam"),this);
	actAcercaNam->setShortcut(tr("CTRL+N"));
	actAcercaNam->setStatusTip(tr("Información sobre el juego y su creador"));
	actAcercaQT = new QAction(tr("Acerca de QT"),this);
	actAcercaQT->setShortcut(tr("CTRL+Q"));
	actAcercaQT->setStatusTip(tr("Acerca de las librerias graficas QT"));
	
	menJuego = menuBar()->addMenu(tr("Juego"));
	menJuego->addAction(actSalir);
	menuBar()->addSeparator();
	menAcercaDe = menuBar()->addMenu(tr("Acerca de"));
	menAcercaDe->addAction(actAcercaNam);
	menAcercaDe->addAction(actAcercaQT);
	
	connect(actSalir, SIGNAL(triggered()),this, SLOT(close()));
	connect(actAcercaNam,SIGNAL(triggered()), this, SLOT(acercaDe()));
	connect(actAcercaQT, SIGNAL(triggered()), this, SLOT(acercaDeQT()));
	
	setCentralWidget(juego);
	setFixedSize(ANCHURA + 150, ALTURA + 70);
	setWindowTitle(QString::fromUtf8("ÑAM"));
}

void Ventana::acercaDe() {
	QMessageBox::about(this,QString::fromUtf8("Acerca de ÑAM"),tr("<center><h1>&Ntilde;AM</h1><p>Versi&oacute;n 2.0</p><p><em>Creado por Alfonso Jim&eacute;nez V&iacute;lchez y licenciado bajo GNU GPLv2</em></p></center>"));
}

void Ventana::acercaDeQT() {
	QMessageBox::aboutQt(this, tr("Acerca de QT"));
}
