#include "StdAfx.h"
#include <QtGui>
#include "FlatPlane.h"
#include <ctime>

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
	qglClearColor(QColor(128, 0, 128, 255));
	glEnableClientState( GL_VERTEX_ARRAY);	 
	glEnableClientState (GL_COLOR_ARRAY);
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

void CFlatPlane::SetImagePrm(const int width, const int height, const double center, const double range ){
	m_pmWidth = width;
	m_pmHeight = height;
	m_winMax = center + 0.5*range;
	m_winMin = m_winMax - range;

	m_bShowImage = true;
}

void CFlatPlane::SendBuffer(std::vector<unsigned short>* pBuffer){
	buffer = pBuffer;
}



void CFlatPlane::ComputeLookUpTable(){
	float factor = 255.0/(m_winMax - m_winMin);
	lut = new std::vector<float>;
	for(unsigned int i=0; i< 65535; i++){
		 if (i <= m_winMin)
			lut->push_back(0);
         else
			 if (i >= m_winMax)
				lut->push_back(1.0);
             else
				lut->push_back(((i - m_winMin)*factor)/255.0f);
	}
}

void CFlatPlane::CreateVertexColorArr(){

	//DWORD tick1 =  GetTickCount();

	if(!pvertexArray){
		pvertexArray = new float[m_pmWidth*m_pmHeight*2];
	}

	int j=0;
	int k=0;
	for(int i=0; i<m_pmHeight*m_pmWidth*2; i+=2){
		if(j==512){
			k++;
			j=0;
		}
		pvertexArray[i]=k;
		pvertexArray[i+1]=j;
		j++;
	}	

	if(!pcolorArray){
		pcolorArray = new float[m_pmWidth*m_pmHeight*4];
	}

	k=0;
	j=0;
	for(int i=0; i<m_pmHeight*m_pmWidth*4; i+=4){
		if(j==512){
			k++;
			j=0;
		}
		pcolorArray[i]=lut->at(buffer->at(k*m_pmHeight+j));
		pcolorArray[i+1]=lut->at(buffer->at(k*m_pmHeight+j));
		pcolorArray[i+2]=lut->at(buffer->at(k*m_pmHeight+j));
		pcolorArray[i+3]=1.0f;
		j++;
	}

	//DWORD tick2 = GetTickCount() - tick1;
}

void CFlatPlane::SetImage(){
	 
	 DWORD tick1 =  GetTickCount();

	 glVertexPointer (2, GL_FLOAT, 0, pvertexArray);
	 glColorPointer(4, GL_FLOAT, 0, pcolorArray);
	 glDrawArrays(GL_POINTS, 0, m_pmWidth*m_pmHeight);

	 DWORD tick2 = GetTickCount() - tick1;

	 //system("pause");
}

std::vector<unsigned short>* CFlatPlane::buffer;
std::vector<float>* CFlatPlane::lut;
float* CFlatPlane::pvertexArray;
float* CFlatPlane::pcolorArray;