#include "StdAfx.h"
#include "VolumePlane.h"
#include <qimage.h>

CVolumePlane::CVolumePlane(QWidget *parent) : QGLWidget(parent){
	m_label = new QLabel;
}


CVolumePlane::~CVolumePlane(void){
	delete m_label;
}

void CVolumePlane::paintEvent(QPaintEvent* event){
	QGLWidget::paintEvent(NULL);
}

void CVolumePlane::SetImageSize(unsigned short width, unsigned short height){
	m_pmWidth = width;
	m_pmHeight = height;
}

//template<class T>
void CVolumePlane::FillPixelMap(/*std::vector<T>*/){
		
	QImage image(m_pmWidth, m_pmHeight, QImage::Format_ARGB32);
	for(unsigned short i=0; i<m_pmWidth; i++)
		for(unsigned short j=0; j<m_pmHeight; j++)
		{
			QRgb value = qRgb(255, 0, 0);		
			image.setPixel(i,j, value);
		}
		m_label->setPixmap(QPixmap::fromImage(image));
		m_label->show();
}