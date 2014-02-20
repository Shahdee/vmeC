#include "StdAfx.h"
#include "VisualFunction.h"

CVisualFunction::CVisualFunction(QWidget * parent):QGraphicsView(parent){
	
	m_pScene = new QGraphicsScene(this->rect(), this); 

}

CVisualFunction::~CVisualFunction(void){}

void CVisualFunction::InitScene(std::vector<unsigned short>* pBuffer){

	m_pScene->clear();
	m_pBuffer = pBuffer;

	CalcHistogramm();
}

void CVisualFunction::CalcHistogramm(){
	
}


void CVisualFunction::ShowFunction(){
	
}
