#include "comida.h"
#include <QWidget>
#include <QPainter>

Comida::Comida() {
	_tipo = CARAMELO;
	_velocidad = 3;
	_dispersion = 5;
	_altura = 8;
	_anchura = 16;
	_punto = QPoint(0,0);
	_color = QColor(255,0,0);
}

Comida::Comida(tipoComida newTip) {
	_tipo = newTip;
	switch(newTip) {
		case (CARAMELO):
			_velocidad = 3;
			_dispersion = 5;
			_altura = 8;
			_anchura = 16;
			_punto = QPoint(0,0);
			break;
		case (QUESITO):
			_velocidad = 3;
			_dispersion = 8;
			_altura = _anchura = 14;
			_punto = QPoint(0,0);
			break;
		case (FROSKITOS):
			_velocidad = 6;
			_dispersion = 2;
			_altura = _anchura = 30;
			_punto = QPoint(0,0);
			break;
		case (LENTEJAS):
			_velocidad = 8;
			_dispersion = 2;
			_altura = _anchura = 60;
			_punto = QPoint(0,0);
			break;
	}
}

int Comida::anchura() {
	return(_anchura);
}

int Comida::altura() {
	return(_altura);
}

int Comida::velocidad() {
	return(_velocidad);
}

int Comida::dispersion() {
	return(_dispersion);
}

QRect Comida::rectDibujo() {
	QRect rectangulo(0, 0, _anchura, _altura);
	rectangulo.moveCenter(_punto);
	return(rectangulo);
}

QRect Comida::rectUpdate() {
	QRect rectangulo(0,0,_anchura + _dispersion * 2 + 2, _altura + _velocidad * 2 + 2);
	rectangulo.moveCenter(_punto);
	return(rectangulo);
}

QPoint Comida::punto() {
	return(_punto);
}

tipoComida Comida::tipo() {
	return(_tipo);
}

void Comida::setAltura(int newAlt)  {
	if (newAlt > 0) {
		_altura = newAlt;
	}
}
void Comida::setAnchura(int newAnc)  {
	if (newAnc > 0) {
		_anchura = newAnc;
	}
}
void Comida::setVelocidad (int newVel) {
	if (newVel > 0) {
		_velocidad = newVel;
	}
}

void Comida::setDispersion (int newDis) {
	if (newDis > 0) {
		_dispersion = newDis;
	}
}

void Comida::setPunto (QPoint newPun) {
	_punto = newPun;
}

void Comida::setTipo (tipoComida newTip) {
	_tipo = newTip;
}


void Comida::pintar (QPainter &painter) {
	QPointF triangulo[3];
	int x, y, despx, despy;
	switch(_tipo) {
		case (CARAMELO):
			//Extraemos x, y y los desplazamientos del rectangulo.
			rectDibujo().getRect(&x,&y,&despx,&despy);
			painter.setPen(Qt::black);
			painter.setBrush(_color);
			//Pintamos el triángulo de la izquierda.
			triangulo[0] = QPointF(x,y);
			triangulo[1] = QPointF(x,y + despy);
			triangulo[2] = QPointF(x + (despx / 4), y + (despy / 2));
			painter.drawConvexPolygon(triangulo,3);
			//Pintamos el triángulo de la derecha.
			triangulo[0] = QPointF(x + despx,y);
			triangulo[1] = QPointF(x + despx,y + despy);
			triangulo[2] = QPointF(x + ((3 * despx) / 4), y + (despy / 2));
			painter.drawConvexPolygon(triangulo,3);
			//Pintamos el centro del caramelo.
			painter.drawEllipse(QRect(x + (despx / 4), y, despx / 2, despy));
			break;
		case (QUESITO):
			painter.setBrush(Qt::red);
			painter.setPen(Qt::black);
			//Pintamos el envoltorio.
			painter.drawEllipse(rectDibujo());
			painter.setBrush(Qt::white);
			//Pintamos el triangulito de quesito que asoma.
			painter.drawPie(rectDibujo(),67*16,46*16);
			break;
		case (FROSKITOS):
			painter.setBrush(QColor(160,130,80));
			painter.setPen(Qt::black);
			//Pintamos el Froskitos.
			painter.drawEllipse(rectDibujo());
			painter.setPen(QColor(100,80,30));
			rectDibujo().getRect(&x,&y,&despx,&despy);
			//Pintamos dos circunferencias concéntricas.
			painter.drawEllipse(QRect(x + despx / 6, y + despy/6, 4 * despx/6, 4 * despy/6));
			painter.drawEllipse(QRect(x + despx / 3, y + despy/3, despx/3, despy/3));
			break;
		case (LENTEJAS):
			painter.setBrush(Qt::white);
			painter.setPen(Qt::black);
			//Pintamos el plato.
			painter.drawEllipse(rectDibujo());
			painter.setBrush(QColor(160,130,80));
			rectDibujo().getRect(&x,&y,&despx,&despy);
			//Pintamos las lentejas.
			painter.drawEllipse(QRect(x + despx / 6, y + despy/6, 4 * despx/6, 4 * despy/6));
			break;
	}
}

QColor Comida::color() {
	return(_color);
}

void Comida::setColor(QColor newCol) {
	_color = newCol;
}

