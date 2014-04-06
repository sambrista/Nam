#include <QPaintEvent>
#include <QPainter>
#include "tablero.h"
#include <QTimer>
#include <cstdlib>
#include <ctime>
#include "comida.h"
#include "muneco.h"
#include "constantes.h"

Tablero::Tablero (QWidget *parent) : QWidget(parent) {
	
	comida = NULL;
	muneco = new Muneco;
	velocidadComida = 3;
	primeraVez = true;
	on = false;
	tiempo = new QTimer(this);
	tempEstado = new QTimer(this);
	tempEstado->setSingleShot(true);
	tempCrecimiento = new QTimer(this);
	estadoCrecer = QUIETO;
	setFixedSize(ANCHURA,ALTURA);
	setPalette(QPalette(QColor(220, 220, 255)));
	setAutoFillBackground(true);
	srand(time(NULL));
	connect(tiempo, SIGNAL(timeout()), this, SLOT(moverComida()));
	connect(tempEstado, SIGNAL(timeout()), this, SLOT(finEstado()));
	connect(tempCrecimiento, SIGNAL(timeout()), this, SLOT(crecer()));
}

void Tablero::iniciar() {
	on = true;
	if (primeraVez) {
		primeraVez = false;
	}
	muneco->setVelocidad(5);
	muneco->setTamano(TAMANOBASE);
	muneco->centrar(ANCHURA);
	nuevaComida();
}

void Tablero::finalizar() {
	tiempo->stop();
	tempEstado->stop();
	tempCrecimiento->stop();
	muneco->setEstado(NORMAL);
	delete comida;
	comida = NULL;
	on = false;
	estadoCrecer = QUIETO;
	update();
}

void Tablero::nuevaComida() {
	delete comida;
	comida = NULL;
	int tmp = rand() % 9;
	switch(tmp) {
		case 0:
		comida = new Comida(QUESITO);
		break;
		case 1:
		comida = new Comida(FROSKITOS);
		break;
		case 2:
		comida = new Comida(LENTEJAS);
		break;
		default:
		comida = new Comida(CARAMELO);
		comida->setColor(QColor(rand()%226+ 30,rand()%226 + 30,rand()%226 + 30));
	}
	comida->setVelocidad(velocidadComida);
	comida->setPunto(QPoint(rand() % (ANCHURA - comida->anchura()), -comida->altura()));
	tiempo->start(5);
	update();
}

void Tablero::moverComida() {
	int x, y;
	x = comida->punto().x() + rand() % (comida->dispersion() * 2 + 1) - comida->dispersion();
	y = comida->punto().y() + rand() % comida->velocidad() + 1;
	if (x < comida->anchura() / 2) {
		x = comida->anchura() / 2;
	}
	if (x > ANCHURA - comida->anchura() / 2 - 2) {
		x = ANCHURA - comida->anchura() / 2 - 2;
	}
	comida->setPunto(QPoint(x,y));
	if (comida->rectDibujo().intersects(muneco->rectCabeza())) {
		tiempo->stop();
		switch(comida->tipo()) {
			case (CARAMELO):
				emit(acierto());
				muneco->setEstado(FELIZ);
				tempEstado->start(500);
				nuevaComida();
				break;
			case (QUESITO):
				muneco->setEstado(ENFERMO);
				tempEstado->start(500);
				nuevaComida();
				emit(fallo());
				break;
			case (FROSKITOS):
				muneco->setEstado(FELIZ);
				tempEstado->start(500);
				estadoCrecer = CRECIENDO;
				tempCrecimiento->start(5);
				nuevaComida();
				break;
			case (LENTEJAS):
				muneco->setEstado(ENFERMO);
				tempEstado->start(500);
				estadoCrecer = DECRECIENDO;
				tempCrecimiento->start(5);
				nuevaComida();
				break;
		}
	} else if (comida->rectDibujo().intersects(QRect(0,ALTURA-1,ANCHURA,1))) {
		tiempo->stop();
		switch(comida->tipo()) {
			case (CARAMELO):
				nuevaComida();
				emit(fallo());
				break;
			default:
				nuevaComida();
				break;
		}

	} else {
		update(comida->rectUpdate());
	}
}

void Tablero::moverIzquierda() {
	if (muneco->posicion() != 0) {
		muneco->moverIzquierda();
		emit(cambioPosicion(muneco->posicion()));
		update(muneco->rectUpdate());
	}
}

void Tablero::moverDerecha() {
	if (muneco->posicion() != ANCHURA - muneco->anchura() - 1) {
		if (muneco->posicion() + muneco->velocidad() > ANCHURA - muneco->anchura() - 1) {
			muneco->setPosicion(ANCHURA - muneco->anchura() - 1);
		} else {
			muneco->moverDerecha();
		}
		emit(cambioPosicion(muneco->posicion()));
		update(muneco->rectUpdate());
	}
}

void Tablero::setTamanoMuneco (int tam) {
	if (tam != muneco->tamano()) {
		if (tam < TAMANOMIN) {
			tam = TAMANOMIN;
		}
		if (tam > TAMANOMAX) {
			tam = TAMANOMAX;
		}
		if (tam < muneco->tamano()) {
			QRect tmp = muneco->rectUpdate();
			muneco->setTamano(tam);
			update(tmp);
		} else {
			muneco->setTamano(tam);
			if (muneco->posicion() + muneco->anchura() > ANCHURA - 1) {
				muneco->setPosicion(ANCHURA-muneco->anchura()-1);
				emit(cambioPosicion(ANCHURA-muneco->anchura()-1));
			}
			update(muneco->rectUpdate());
		}
		emit(cambioTamanoMuneco(tam));
	}
}

void Tablero::setPosicion (int pos) {
	if (pos != muneco->posicion()) {
		if (pos < 0) {
			pos = 0;
		}
		if (pos > (ANCHURA - muneco->anchura() - 1)) {
			pos = ANCHURA - muneco->anchura() - 1;
		}
	muneco->setPosicion(pos);
	emit(cambioPosicion(pos));
	update(muneco->rectUpdate());
	}
}

void Tablero::pintaComida (QPainter &painter) {
	if (comida != NULL) {
		comida->pintar(painter);
	}
}

void Tablero::pintaTexto (QPainter &painter) {
	if (!on) {
		painter.setPen(Qt::black);
		if (primeraVez) {
			painter.drawText(rect(), Qt::AlignCenter, QString::fromUtf8("¡¡Bienvenido a ÑAM!!\n\nAyuda a Ñam a comer\ntodos los caramelos que\npuedas sin que se te\ncaigan al suelo.\n\nÑam adora los Froskitos...\n¡pero odia las lentejas!\n\n¡Y ten mucho cuidado con\nlos quesitos Bambeidel!\n\nPulsa iniciar para empezar."));
		} else {
			painter.setFont(QFont("Sans",36,QFont::Bold));
			painter.drawText(rect(),Qt::AlignCenter,tr("Game\nOver"));
		}
	}
}

void Tablero::pintaPaisaje (QPainter &painter) {
	if (on) {
		//Pintamos el Sol con sus rayos
		painter.setBrush(Qt::yellow);
		painter.setPen(Qt::yellow);
		painter.drawLine(QLineF(0,0,0,110));
		painter.drawLine(QLineF(0,0,110,0));
		painter.drawLine(QLineF(0,0,100,30));
		painter.drawLine(QLineF(0,0,30,100));
		painter.drawLine(QLineF(0,0,65,65));
		painter.drawLine(QLineF(0,0,15,105));
		painter.drawLine(QLineF(0,0,105,15));
		painter.drawLine(QLineF(0,0,45,85));
		painter.drawLine(QLineF(0,0,85,45));
		painter.drawPie(QRect(-50,-50,100,100),271*16,89*16);
		//Pintamos las nubes
		painter.setBrush(Qt::white);
		painter.setPen(Qt::NoPen);
		painter.drawEllipse(QRect(ANCHURA/4, ALTURA/3 - 20, ANCHURA/2,20));
		painter.drawEllipse(QRect(ANCHURA/2, 2 * ALTURA/3 - 10, ANCHURA/4,10));
		//Pintamos el tronco del arbol
		painter.setPen(Qt::black);
		painter.setBrush(QColor(200,180,130));
		painter.drawRect(QRect(11, ALTURA-25,4,25));
		//Las hojas del arbol
		painter.setBrush(Qt::darkGreen);
		painter.drawEllipse(QRect(6,ALTURA-55,15,30));
		//Pintamos la pared de la casa.
		painter.setBrush(Qt::white);
		painter.setPen(Qt::black);
		painter.drawRect(QRect(ANCHURA-60,ALTURA-60,59,60));
		//Pintamos la puerta
		painter.setBrush(QColor(200,180,130));
		painter.drawRect(QRect(ANCHURA-45, ALTURA-40,12,40));
		//Pintamos la ventana
		painter.setBrush(QColor(100,100,255));
		painter.drawRect(QRect(ANCHURA-20,ALTURA-38,10,10));
		//Definimos los puntos del tejado
		QPointF tejado[3] = {
			QPointF(ANCHURA-60,ALTURA-60),
			QPointF(ANCHURA-1,ALTURA-60),
			QPointF(ANCHURA-30,ALTURA-80)
		};
		//Pintamos el tejado
		painter.setBrush(Qt::red);
		painter.drawConvexPolygon(tejado,3);
		//Pintamos el suelo
		painter.setPen(Qt::darkGreen);
		painter.drawLine(QLineF(0,ALTURA-1,ANCHURA,ALTURA-1));
	}
}

void Tablero::pintaMuneco(QPainter &painter) {
	if (on) {
		muneco->pintar(painter);
	}
}

void Tablero::paintEvent (QPaintEvent * /* event */) {
	QPainter painter(this);
	pintaPaisaje(painter);
	pintaMuneco(painter);
	pintaComida(painter);
	pintaTexto(painter);
}

void Tablero::finEstado() {
	muneco->setEstado(NORMAL);
	update(muneco->rectUpdate());
}

void Tablero::setVelocidadComida(int vel) {
	if (comida != NULL) {
		if (vel != velocidadComida) {
			if (vel < 1) {
				vel = 1;
			}
			velocidadComida = vel;
			comida->setVelocidad(vel);
			emit(cambioVelocidadComida(vel));
		}
	}
}

void Tablero::setVelocidad(int vel) {
	if (vel != muneco->velocidad()) {
		if (vel < 1) {
			vel = 1;
		}
		muneco->setVelocidad(vel);
		emit(cambioVelocidad(muneco->velocidad()));
	}
}

void Tablero::crecer() {
	switch (estadoCrecer) {
		case CRECIENDO:
			setTamanoMuneco(muneco->tamano()+1);
			switch (muneco->tamano()) {
				case TAMANOMAX:
				estadoCrecer = QUIETO;
				tempCrecimiento->stop();
				tempCrecimiento->start(5000);
				setVelocidad(7);
				break;
				case TAMANOBASE:
				estadoCrecer = QUIETO;
				tempCrecimiento->stop();
				setVelocidad(5);
				break;
			}
		break;
		case DECRECIENDO:
			setTamanoMuneco(muneco->tamano()-1);
			switch (muneco->tamano()) {
				case TAMANOMIN:
				estadoCrecer = QUIETO;
				tempCrecimiento->stop();
				tempCrecimiento->start(5000);
				setVelocidad(3);
				break;
				case TAMANOBASE:
				estadoCrecer = QUIETO;
				tempCrecimiento->stop();
				setVelocidad(5);
				break;
			}
		break;
		case QUIETO:
			if (muneco->tamano() == TAMANOMAX) {
				estadoCrecer = DECRECIENDO;
			} else {
				estadoCrecer = CRECIENDO;
			}
			tempCrecimiento->start(5);
		break;
	}
}


