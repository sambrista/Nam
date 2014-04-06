#ifndef __MUNECOH__
#define __MUNECOH__

#include <QWidget>
#include <QPainter>
enum estadoMuneco {NORMAL,FELIZ,ENFERMO};

class Muneco {
	public:
		Muneco();
		int posicion();
		int tamano();
		int velocidad();
		QRect rectCabeza();
		QRect rectUpdate();
		estadoMuneco estado();
		int anchura();
		void setTamano(int newTam);
		void setVelocidad(int newVel);
		void setPosicion(int newPos);
		void setEstado(estadoMuneco newEst);
		void centrar(int longitud);
		void moverDerecha();
		void moverIzquierda();
		void pintar(QPainter &painter);
	private:
		estadoMuneco _estado;
		int _tamano;
		int _velocidad;
		int _diametroCabeza;
		int _posicion;
};

#endif
