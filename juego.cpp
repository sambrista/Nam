#include "tablero.h"
#include "juego.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLCDNumber>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QGridLayout>
#include <QShortcut>
#include "constantes.h"
#include <QSlider>

Juego::Juego (QWidget *parent) : QWidget(parent) {
	btnIniciar = new QPushButton(tr("&Iniciar"));
	on = false;
	tablero = new Tablero;
	QLabel *lblAciertos = new QLabel(tr("Puntos"));
	QLabel *lblFallos = new QLabel(tr("Vidas"));
	QLabel *lblMaximo = new QLabel(tr("Record"));
	lcdAciertos = new QLCDNumber(2);
	lcdFallos = new QLCDNumber(2);
	lcdMaximo = new QLCDNumber(2);
	QVBoxLayout *cajatablero = new QVBoxLayout;
	QGridLayout *tabla = new QGridLayout;
	QVBoxLayout *cajaV = new QVBoxLayout;
	QHBoxLayout *cajaH = new QHBoxLayout;
	QFrame *marco = new QFrame;
	btnIniciar->setEnabled(true);
	lcdAciertos->setSegmentStyle(QLCDNumber::Filled);
	lcdFallos->setSegmentStyle(QLCDNumber::Filled);
	lcdMaximo->setSegmentStyle(QLCDNumber::Filled);
	lcdAciertos->display(0);
	lcdFallos->display(VIDAS);
	lcdMaximo->display(0);
	marco->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	tabla->addWidget(lblMaximo,0,0);
	tabla->addWidget(lcdMaximo,0,1);
	tabla->setRowMinimumHeight(1,20);
	tabla->addWidget(lblAciertos,2,0);
	tabla->addWidget(lcdAciertos,2,1);
	tabla->addWidget(lblFallos,3,0);
	tabla->addWidget(lcdFallos,3,1);
	cajaV->addLayout(tabla);
	cajaV->addSpacing(10);
	cajaV->addWidget(btnIniciar);
	cajaV->addStretch();
	cajatablero->addWidget(tablero);
	marco->setLayout(cajatablero);
	cajaH->addWidget(marco);
	cajaH->addLayout(cajaV);
	setLayout(cajaH);
	(void) new QShortcut(Qt::Key_Right, tablero, SLOT(moverDerecha()));
	(void) new QShortcut(Qt::Key_Left, tablero, SLOT(moverIzquierda()));
	connect(btnIniciar, SIGNAL(clicked()), this, SLOT(botonPresionado()));
	connect(tablero, SIGNAL(acierto()), this, SLOT(incAciertos()));
	connect(tablero, SIGNAL(fallo()), this, SLOT(incFallos()));
}

void Juego::incFallos() {
	if (lcdFallos->intValue() == 0) {
		finalizar();
	} else {
		lcdFallos->display(lcdFallos->intValue() - 1);
	}
}

void Juego::incAciertos() {
	lcdAciertos->display(lcdAciertos->intValue() + 1);
	if (lcdAciertos->intValue() + 1 > lcdMaximo->intValue()) {
		lcdMaximo->display(lcdAciertos->intValue());
	}
}

void Juego::finalizar() {
	on = false;
		btnIniciar->setText(tr("&Iniciar"));
	tablero->finalizar();
}

void Juego::iniciar() {
	on = true;
	btnIniciar->setText(tr("&Finalizar"));
	tablero->setTamanoMuneco(40);
	lcdAciertos->display(0);
	lcdFallos->display(10);
	tablero->iniciar();
}

void Juego::botonPresionado() {
	if (on) {
		finalizar();
	} else {
		iniciar();
	}
}
