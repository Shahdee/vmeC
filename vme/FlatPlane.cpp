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

CFlatPlane::~CFlatPlane(void){}

void CFlatPlane::setXRotation(const int & angel){}

void CFlatPlane::setYRotation(const int & angel){}

void CFlatPlane::setZRotation(const int & angel){}

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
	
	QBrush background = QBrush(QColor(255, 0, 0));
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
	qglClearColor(Qt::lightGray);
	// Qt auto turn on z-buffer in constructor of QGLWidget
}

void  CFlatPlane::resizeGL(int width, int height){
	 glMatrixMode(GL_PROJECTION); 
	 glLoadIdentity(); 
	 //glOrtho(-1.0, 1.0, -1.0, 1.0, -10.0, 1.0);  
	 glOrtho(0.0f, 512.0f, 512.0f, 0.0f, -1.0, 1.0);  
	 glViewport(0, 0, (GLint)width, (GLint)height); 
}

/*
ћатрица моделировани€ отвечает за наблюдение сцены; а матрица проекции за проецирование сцены, которое может быть либо ортогональным, либо перспективным.
*/

void CFlatPlane::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Axis();
}

void CFlatPlane::Axis(){
   
   glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
   glPointSize(3.0f);

    glBegin(GL_POINTS);
		for(GLint i=0; i<510; i++)
			for(GLint j=0; j<510; j++)
					glVertex2i(i, j);
	glEnd();
}
