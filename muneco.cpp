#include <QWidget>
#include "muneco.h"
#include <QPainter>
#include "comida.h"
#include "constantes.h"
#include <cmath>
#include <iostream>

Muneco::Muneco() {
	_tamano = TAMANOBASE;
	_velocidad = 3;
	_diametroCabeza = 2 * TAMANOBASE / 3;
	_estado = NORMAL;
	_posicion = 0;
}

int Muneco::posicion() {
	return(_posicion);
}

int Muneco::tamano() {
	return(_tamano);
}

int Muneco::velocidad() {
	return(_velocidad);
}

QRect Muneco::rectCabeza() {
	return(QRect(_posicion, ALTURA - (_diametroCabeza * 3 / 2), _diametroCabeza,_diametroCabeza));
}

QRect Muneco::rectUpdate() {
	return(QRect(_posicion-_velocidad-1, ALTURA - _tamano, 2 * _velocidad + _diametroCabeza + 2, _tamano));
}

estadoMuneco Muneco::estado() {
	return(_estado);
}

void Muneco::setTamano(int newTam) {
	if (newTam < TAMANOMIN) {
		newTam = TAMANOMIN;
	}
	_tamano = newTam;
	_diametroCabeza = 2 * _tamano / 3;
}

void Muneco::setVelocidad(int newVel) {
	if (newVel < 1) {
		newVel = 1;
	}
	if (newVel % 2 == 0) {
		newVel++;
	}
	_velocidad = newVel;
}

void Muneco::setPosicion(int newPos) {
	if (newPos < 0) {
		newPos = 0;
	}
	_posicion = newPos;
}

void Muneco::setEstado(estadoMuneco newEst) {
	_estado = newEst;
}

void Muneco::centrar(int longitud) {
	setPosicion((longitud - _diametroCabeza) / 2);
}

void Muneco::moverDerecha() {
	setPosicion(_posicion + _velocidad);
}

void Muneco::moverIzquierda() {
	setPosicion(_posicion - _velocidad);
}

int Muneco::anchura() {
	return(_diametroCabeza);
}

void Muneco::pintar (QPainter &painter) {
	//Pintamos el cuerpo
	painter.setPen(Qt::black);
	painter.drawLine(QLineF(_posicion+_diametroCabeza / 2,ALTURA - _diametroCabeza / 2 , _posicion+_diametroCabeza / 2, ALTURA- 3 * _diametroCabeza  / 10));
	//Dependiendo si la posicion es par o impar, pintamos el muñeco de una forma u otra para dar sensación de movimiento.
	if (_posicion % 2 == 0)	{
		//Pintamos la mano izquierda
		painter.drawLine(QLineF(_posicion+_diametroCabeza/6,ALTURA- 9 * _diametroCabeza/20, _posicion+_diametroCabeza/3, ALTURA-3 * _diametroCabeza / 10));
		painter.drawLine(QLineF(_posicion+_diametroCabeza/3,ALTURA-3 * _diametroCabeza / 10, _posicion+_diametroCabeza/2, ALTURA- 9 * _diametroCabeza/20));
		//Pintamos la mano derecha
		painter.drawLine(QLineF(_posicion+5 * _diametroCabeza/6,ALTURA- 9 * _diametroCabeza/20, _posicion+2 * _diametroCabeza / 3, ALTURA-3 * _diametroCabeza / 10));
		painter.drawLine(QLineF(_posicion+2 * _diametroCabeza / 3,ALTURA-3 * _diametroCabeza / 10, _posicion+_diametroCabeza/2, ALTURA- 9 * _diametroCabeza/20));
		//Pintamos las piernas
		painter.drawLine(QLineF(_posicion+_diametroCabeza/3, ALTURA-2, _posicion+_diametroCabeza/2, ALTURA-3 * _diametroCabeza  / 10));
		painter.drawLine(QLineF(_posicion+2 * _diametroCabeza / 3, ALTURA-2, _posicion+_diametroCabeza/2, ALTURA-3 * _diametroCabeza  / 10));
	} else {
		//Pintamos la mano izquierda
		painter.drawLine(QLineF(_posicion+_diametroCabeza/8,ALTURA-_diametroCabeza/2, _posicion+_diametroCabeza/3, ALTURA-3 * _diametroCabeza/8));
		painter.drawLine(QLineF(_posicion+_diametroCabeza/3,ALTURA-3 * _diametroCabeza/8, _posicion+_diametroCabeza/2, ALTURA- 9 * _diametroCabeza/20));
		//Pintamos la mano derecha
		painter.drawLine(QLineF(_posicion+7 * _diametroCabeza/8,ALTURA-_diametroCabeza/2, _posicion+2 * _diametroCabeza / 3, ALTURA-3 * _diametroCabeza/8));
		painter.drawLine(QLineF(_posicion+2 * _diametroCabeza / 3,ALTURA-3 * _diametroCabeza/8, _posicion+_diametroCabeza/2,  ALTURA- 9 * _diametroCabeza/20));
		//Pintamos las piernas
		painter.drawLine(QLineF(_posicion+2*_diametroCabeza/5, ALTURA-2, _posicion + _diametroCabeza/2, ALTURA-3 * _diametroCabeza  / 10));
		painter.drawLine(QLineF(_posicion+3*_diametroCabeza / 5, ALTURA-2, _posicion + _diametroCabeza/2, ALTURA-3 * _diametroCabeza  / 10));
	}
	//Pintamos la lengua
	painter.setBrush(Qt::red);
	painter.setPen(Qt::NoPen);
	painter.drawEllipse(QRect(_posicion+7 *_diametroCabeza/16, ALTURA-9 * _diametroCabeza / 8,3 * _diametroCabeza/16,_diametroCabeza/3));
	//Dependiendo del estado pintamos la cabeza de una forma u otra.
	switch(_estado) {
		case FELIZ:
		//Pintamos la cabeza
			painter.setPen(Qt::black);
			if (_tamano > TAMANOBASE) {
			painter.setBrush(QColor(255,(255 / (TAMANOBASE - TAMANOMAX)) * _tamano - ((255 / (TAMANOBASE - TAMANOMAX))* TAMANOMAX),0));
			} else {
			painter.setBrush(Qt::yellow);
			}
			painter.drawPie(rectCabeza(),90* 16,360* 16);
			//Pintamos el ojo
			painter.drawLine(QLineF(_posicion + 7 * _diametroCabeza / 10, ALTURA - 6 * _diametroCabeza / 5, _posicion + 9 * _diametroCabeza / 10, ALTURA - 11 * _diametroCabeza / 10));
			painter.drawLine(QLineF(_posicion + 9 * _diametroCabeza / 10,ALTURA - 11 * _diametroCabeza / 10 , _posicion + 7 * _diametroCabeza / 10, ALTURA - _diametroCabeza));
			break;
		case ENFERMO:
			//Pintamos la cabeza
			painter.setPen(Qt::black);
			painter.setBrush(Qt::green);
			painter.drawPie(rectCabeza(),90* 16,360* 16);
			//Pintamos el ojo
			painter.drawLine(QLineF(_posicion + 7 * _diametroCabeza / 10, ALTURA - _diametroCabeza, _posicion + 9 * _diametroCabeza / 10, ALTURA - 6 * _diametroCabeza / 5));
			painter.drawLine(QLineF(_posicion + 9 * _diametroCabeza / 10, ALTURA - _diametroCabeza, _posicion + 7 * _diametroCabeza / 10, ALTURA - 6 * _diametroCabeza / 5));
			break;
		case NORMAL:
			//Pintamos la cabeza.
			painter.setPen(Qt::black);
			if (_tamano > TAMANOBASE) {
			painter.setBrush(QColor(255,(255 / (TAMANOBASE - TAMANOMAX)) * _tamano - ((255 / (TAMANOBASE - TAMANOMAX))* TAMANOMAX),0));
			} else {
			painter.setBrush(Qt::yellow);
			}
			painter.drawPie(rectCabeza(),(180-45) * 16,270 * 16);
			//Pintamos el ojo
			painter.setBrush(Qt::white);
			if (_tamano > TAMANOBASE) {
			painter.drawPie(QRect(_posicion + 7 * _diametroCabeza / 10,ALTURA - 6 * _diametroCabeza / 5, _diametroCabeza/5,_diametroCabeza/5),115*16,180*16);
			} else {
			painter.drawEllipse(QRect(_posicion + 7 * _diametroCabeza / 10,ALTURA - 6 * _diametroCabeza / 5, _diametroCabeza/5,_diametroCabeza/5));
			painter.setBrush(Qt::black);
			painter.drawEllipse(QRect(_posicion + 37 * _diametroCabeza / 50,ALTURA - 6 * _diametroCabeza / 5, 3 * _diametroCabeza/25, 3 * _diametroCabeza/25));
			}
			break;
	}
}

