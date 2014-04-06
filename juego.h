#ifndef __JUEGO__
#define __JUEGO__

#include <QWidget>
#include <QLCDNumber>
#include <QPushButton>
#include "tablero.h"

class QLCDNumber;
class QPushButton;

class Juego : public QWidget {
	Q_OBJECT
	public:
		Juego(QWidget *parent = 0);
	private:
		bool on;
		QLCDNumber *lcdAciertos;
		QLCDNumber *lcdFallos;
		QLCDNumber *lcdMaximo;
		Tablero *tablero;
		QPushButton *btnIniciar;
	private slots:
		void incAciertos();
		void incFallos();
		void botonPresionado();
		void iniciar();
		void finalizar();
};

#endif
