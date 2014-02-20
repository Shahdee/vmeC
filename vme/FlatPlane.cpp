#include "stdafx.h"
#include <QtGui>
#include "FlatPlane.h"
#include <ctime>

 #ifndef GL_MULTISAMPLE
 #define GL_MULTISAMPLE  0x809D
 #endif

CFlatPlane::CFlatPlane(QWidget *parent) :  QGLWidget(QGLFormat(QGL::SampleBuffers), parent){
	m_bShowImage = false;
	m_dWinMin = 0.0;
	m_dWinMax = 0.0;
}

CFlatPlane::~CFlatPlane(void){}


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
		if(pvertexArray != NULL && pcolorArray != NULL){
			glVertexPointer (2, GL_FLOAT, 0, pvertexArray);
			glColorPointer(3, GL_FLOAT, 0, pcolorArray);
			glDrawArrays(GL_POINTS, 0, m_iWidth*m_iHeight);
		}
	}
}

void CFlatPlane::SetImagePrm(const int width, const int height, const double center, const double range ){
	m_iWidth = width;
	m_iHeight = height;
	m_dWinCenter = center;
	m_dWinWidth = range;

	m_dWinMax = m_dWinCenter + 0.5*m_dWinWidth;
	m_dWinMin = m_dWinMax - m_dWinWidth;

	ComputeChangeVals();
}

void CFlatPlane::SendImageBuffer(std::vector<unsigned short>* pBuffer){
	m_pImageBuffer = pBuffer;
}

void CFlatPlane::ComputeChangeVals(){

    if (m_dWinWidth < 5000){
        m_iChangeWidth = 2;
        m_iChangeCenter = 2;
    }
    else 
		if (m_dWinWidth > 40000){
			m_iChangeWidth = 50;
			m_iChangeCenter = 50;
		}
		else{
			m_iChangeWidth = 25;
			m_iChangeCenter = 25;
		}
}

void CFlatPlane::ComputeLookUpTable(){

	float factor = 255.0/(m_dWinMax - m_dWinMin);
	lut = new std::vector<float>;
	for(unsigned int i=0; i< 65535; i++){
		 if (i <= m_dWinMin)
			lut->push_back(0);
         else
			 if (i >= m_dWinMax)
				lut->push_back(1.0);
             else
				lut->push_back(((i - m_dWinMin)*factor)/255.0f);
	}
}

void CFlatPlane::CreateVertexColorArr(){

	//DWORD tick1 = GetTickCount();

	if(pvertexArray == NULL){
		pvertexArray = new float[m_iWidth * m_iHeight * 2];
	}

	int j=0;
	int k=0;
	for(int i=0; i<m_iWidth*m_iHeight*2; i+=2){
		if(j==512){
			k++;
			j=0;
		}
		pvertexArray[i]=k;
		pvertexArray[i+1]=j;
		j++;
	}	

	if(pcolorArray == NULL){
		pcolorArray = new float[m_iWidth*m_iHeight*3];
	}

	//DWORD t1 = GetTickCount();

	k=0;
	j=0;
	for(int i=0; i<m_iWidth*m_iHeight*3; i+=3){
		if(j==512){
			k++;
			j=0;
		}
		pcolorArray[i]=lut->at(m_pImageBuffer->at(k*m_iHeight+j)); //R
		pcolorArray[i+1]= pcolorArray[i]; //G
		pcolorArray[i+2]= pcolorArray[i]; //B
		//pcolorArray[i+3]=1.0f; //A
		j++;
	}

	//DWORD t2 = GetTickCount() - t1;

	m_bShowImage = true;
	//system("pause");
}


void CFlatPlane::FlushBuffers(bool bTF){

	if (pvertexArray != NULL){
		delete[] pvertexArray;
		pvertexArray = NULL;
	}

	if (pcolorArray != NULL){
		delete[] pcolorArray;
		pcolorArray = NULL;
	}

	if (lut != NULL){
		delete lut;
		lut = NULL;
	}

	if (m_pImageBuffer != NULL  && !bTF){
		delete m_pImageBuffer;
		m_pImageBuffer = NULL;
	}
}

void CFlatPlane::ResetImageBufferPtr(){
	
	m_pImageBuffer = NULL;
}

void CFlatPlane::mousePressEvent(QMouseEvent* ev){
	if(!m_bShowImage) return;

	if(ev->button() == Qt::RightButton){
		m_lastPress = ev->pos();
		m_bRightBtnPressed = true;
	}

}

void CFlatPlane::mouseReleaseEvent(QMouseEvent* ev){
	if(!m_bShowImage) return;

	if(ev->button() == Qt::RightButton){

		if(m_bRightBtnPressed)
		{
			m_bRightBtnPressed = false;
		}
	}
}


void CFlatPlane::mouseMoveEvent(QMouseEvent * ev){
	
	if(m_bRightBtnPressed){

		if(m_lastPress.y() > ev->pos().y()){
			
			m_dWinWidth +=50;
			m_dWinMax = m_dWinCenter + 0.5*m_dWinWidth;
			m_dWinMin = m_dWinMax - m_dWinWidth;
		}

		if(m_lastPress.y() < ev->pos().y()){

			m_dWinWidth -=50;
			m_dWinMax = m_dWinCenter + 0.5*m_dWinWidth;
			m_dWinMin = m_dWinMax - m_dWinWidth;
		}

		if(m_lastPress.x() > ev->pos().x()){
			m_dWinCenter -=50;
			m_dWinMax = m_dWinCenter + 0.5*m_dWinWidth;
			m_dWinMin = m_dWinMax - m_dWinWidth;
		}

		if(m_lastPress.x() < ev->pos().x()){
			m_dWinCenter +=50;
			m_dWinMax = m_dWinCenter + 0.5*m_dWinWidth;
			m_dWinMin = m_dWinMax - m_dWinWidth;
		}

		ComputeLookUpTable();
		CreateVertexColorArr();
		updateGL();
	}
}


std::vector<unsigned short>* CFlatPlane::m_pImageBuffer;
std::vector<float>* CFlatPlane::lut;
float* CFlatPlane::pvertexArray;
float* CFlatPlane::pcolorArray;