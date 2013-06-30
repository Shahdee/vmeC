#include "StdAfx.h"
#include <QtGui>
#include "FlatPlane.h"

 #ifndef GL_MULTISAMPLE
 #define GL_MULTISAMPLE  0x809D
 #endif


CFlatPlane::CFlatPlane(QWidget *parent) :  QGLWidget(QGLFormat(QGL::SampleBuffers), parent){
	m_bShowImage = false;
	m_winMin = 0.0;
	m_winMax = 0.0;
}

CFlatPlane::~CFlatPlane(void){

}


/*
void CFlatPlane::paintEvent(QPaintEvent* event){
	
	
	makeCurrent(); // Makes this widget the current widget for OpenGL operations, i.e. makes the widget's rendering context the current OpenGL rendering context.

	QPainter *painter = new QPainter();
	painter->begin(this);
	
	drawSurface(painter, event);
	
	painter->end();
	
}*/

void CFlatPlane::showEvent(QShowEvent* event){}


void CFlatPlane::initializeGL(){
	qglClearColor(QColor(0.5, 0, 0.5, 255));
}

void  CFlatPlane::resizeGL(int width, int height){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

#ifdef QT_OPENGL_ES_1
	glOrtho(0.0f, GLfloat(width), GLfloat(height), 0.0f, -1.0f, 10.0f);
#else
	glOrtho(0.0, GLfloat(width), GLfloat(height), 0.0, -1.0, 10.0);
#endif
	glViewport(0, 0, (GLint)width, (GLint)height);
}

void CFlatPlane::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	if(m_bShowImage){
		SetImage();
	}
}


void CFlatPlane::Axis(){
	glLineWidth(3.0f);
	glColor3f(1.0f, 0.5f, 0.5f);
	glBegin(GL_LINES);
		glVertex2f(-1.0f, 0.0f);
		glVertex2f(1.0, 0.0f);
	glEnd();
}

void CFlatPlane::SetImagePrm(const int width, const int height, const double center, const double range ){
	m_pmWidth = width;
	m_pmHeight = height;
	m_winMax = center + 0.5*range;
	m_winMin = m_winMax - range;
}

void CFlatPlane::SendBuffer(std::vector<unsigned short>* pBuffer){
	m_bShowImage = true;
	buffer = pBuffer;
}



void CFlatPlane::ComputeLookUpTable(){
	float factor = 255.0/(m_winMax - m_winMin);
	lut = new std::vector<unsigned char>;
	for(unsigned int i=0; i< 65535; i++){
		 if (i <= m_winMin)
			lut->push_back(0);
         else
			 if (i >= m_winMax)
				lut->push_back(255);
             else
				lut->push_back((i - m_winMin)*factor);
	}
}

void CFlatPlane::SetImage(){
	glPointSize(1.0f);
	
	glBegin(GL_POINTS);

	for(int i=0; i<m_pmWidth; i++){
		for(int j=0; j<m_pmWidth; j++){
			unsigned short index = buffer->at(i*m_pmWidth+j);
			unsigned char c = lut->at(index); 
			QColor current(c,c,c);
			qglColor(current);
			glVertex2i(i,j);
		}
	}
	glEnd();
}

std::vector<unsigned short>* CFlatPlane::buffer;
std::vector<unsigned char>* CFlatPlane::lut;