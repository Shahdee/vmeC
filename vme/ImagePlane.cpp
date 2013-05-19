#include "StdAfx.h"
#include "ImagePlane.h"
#include <iostream>

using namespace std;


CImagePlane::CImagePlane(QWidget *parent) : QTabWidget(parent){

	m_p2d = new QWidget();
	m_p3d = new QWidget();

	m_p2d->setObjectName(QString::fromUtf8("2d"));

	m_p3d->setObjectName(QString::fromUtf8("3d"));

	this->addTab(m_p2d, QString());
	this->addTab(m_p3d, QString()); 

}


CImagePlane::~CImagePlane(void){

}



void CImagePlane::paintEvent(QPaintEvent *){

	QTabWidget::paintEvent(NULL);
	
	
}
