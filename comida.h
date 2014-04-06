#ifndef __COMIDAH__
#define __COMIDAH__

#include <QWidget>
#include <QPainter>

enum tipoComida {CARAMELO,QUESITO, FROSKITOS, LENTEJAS};

class Comida {
	public:
		Comida();
		Comida(tipoComida newTip);
		int anchura();
		int altura();
		int velocidad();
		int dispersion();
		QRect rectDibujo();
		QRect rectUpdate();
		QPoint punto();
		tipoComida tipo();
		QColor color();
		void setAltura(int newAlt);
		void setAnchura(int newAnc);
		void setVelocidad (int newVel);
		void setDispersion (int newDis);
		void setPunto (QPoint newPun);
		void setTipo (tipoComida newTip);
		void pintar (QPainter &painter);
		void setColor(QColor newCol);
	private:
		QColor _color;
		int _anchura;
		int _altura;
		QPoint _punto;
		int _velocidad;
		int _dispersion;
		tipoComida _tipo;
};

#endif
