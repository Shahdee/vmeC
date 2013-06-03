#include "StdAfx.h"
#include "Plane.h"


CPlane::CPlane(QWidget *parent) : QGLWidget(parent){

    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
}


CPlane::~CPlane(void){
}


void CPlane::initializeGL(){

	qglClearColor(Qt::black);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void CPlane::resizeGL(int w, int h){
	
	glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void CPlane::paintGL(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

