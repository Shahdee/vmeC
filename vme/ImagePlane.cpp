#include "StdAfx.h"
#include "ImagePlane.h"
#include <iostream>

using namespace std;


CImagePlane::CImagePlane(QWidget *parent) : QTabWidget(parent){


}


CImagePlane::~CImagePlane(void){

}



void CImagePlane::paintEvent(QPaintEvent *){

	QTabWidget::paintEvent(NULL);
	
	
}
