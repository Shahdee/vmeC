#include "StdAfx.h"
#include "VolumePlane.h"


CVolumePlane::CVolumePlane(QWidget *parent) : QGLWidget(parent){


}


CVolumePlane::~CVolumePlane(void){

}

void CVolumePlane::paintEvent(QPaintEvent* event){
	
	QGLWidget::paintEvent(NULL);
}
