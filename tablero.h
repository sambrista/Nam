#ifndef __TABLEROH__
#define __TABLEROH__

#include <QWidget>
#include <QTimer>
#include "comida.h"
#include "muneco.h"

class QTimer;

enum estadoCrecimiento {QUIETO,CRECIENDO,DECRECIENDO};

class Tablero : public QWidget {
	Q_OBJECT
	public:
		Tablero(QWidget *parent = 0);
	private:
		int velocidadComida;
		void pintaMuneco(QPainter &painter);
		void pintaComida(QPainter &painter);
		void pintaPaisaje(QPainter &painter);
		void pintaTexto(QPainter &painter);
		QTimer *tiempo;
		QTimer *tempEstado;
		QTimer *tempCrecimiento;
		bool on;
		bool primeraVez;
		estadoCrecimiento estadoCrecer;
		Comida *comida;
		Muneco *muneco;
	protected:
		void paintEvent(QPaintEvent *event);
	public slots:
		void setPosicion(int pos);
		void nuevaComida();
		void iniciar();
		void finalizar();
		void moverDerecha();
		void moverIzquierda();
		void setVelocidadComida(int vel);
		void setVelocidad(int vel);
		void setTamanoMuneco(int tam);
	private slots:
		void moverComida();
		void finEstado();
		void crecer();
	signals:
		void cambioTamanoMuneco(int tam);
		void cambioVelocidad(int vel);
		void cambioVelocidadComida(int vel);
		void cambioPosicion(int pos);
		void acierto();
		void fallo();
};

#endif
