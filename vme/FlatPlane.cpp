#include "StdAfx.h"
#include <QtGui>
#include "FlatPlane.h"

 #ifndef GL_MULTISAMPLE
 #define GL_MULTISAMPLE  0x809D
 #endif


CFlatPlane::CFlatPlane(QWidget *parent) :  QGLWidget(QGLFormat(QGL::SampleBuffers), parent){

	m_xRot = 0;
    m_yRot = 0;
    m_zRot = 0;

}

CFlatPlane::~CFlatPlane(void){

}

void CFlatPlane::setXRotation(const int & angel){
	
}

void CFlatPlane::setYRotation(const int & angel){
	
}

void CFlatPlane::setZRotation(const int & angel){
	
}

void CFlatPlane::setupViewport(const int & width, const int & height){
	
	int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	#ifdef QT_OPENGL_ES
		glOrthof(-0.5, +0.5, -0.5, 0.5, 4.0, 15.0);
	#else
		glOrtho(-0.5, +0.5, -0.5, 0.5, 4.0, 15.0);
	#endif
    glMatrixMode(GL_MODELVIEW);
}

void CFlatPlane::drawSurface(QPainter* painter, QPaintEvent* event){
	
	QBrush background = QBrush(QColor(64, 32, 64));
	painter->fillRect(event->rect(), background);
}

/*
void CFlatPlane::paintEvent(QPaintEvent* event){
	
	
	makeCurrent(); // Makes this widget the current widget for OpenGL operations, i.e. makes the widget's rendering context the current OpenGL rendering context.

	QPainter *painter = new QPainter();
	painter->begin(this);
	
	drawSurface(painter, event);
	
	painter->end();
	
}*/

void CFlatPlane::showEvent(QShowEvent* event){
	
}


void CFlatPlane::initializeGL(){
	 
	qglClearColor(QColor(255, 0, 0));

	glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    static GLfloat lightPosition[4] =  { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void  CFlatPlane::resizeGL(int width, int height){

	int side = qMin(width, height);
	glViewport((width - side) / 2, (height - side) / 2, side, side);
 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#else
    glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void CFlatPlane::paintGL(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(m_xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(m_yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(m_zRot / 16.0, 0.0, 0.0, 1.0);
}
