#include "stdafx.h"
#include "vme.h"
#include <QtGui>


vme::vme(QWidget *parent, Qt::WFlags flags) : QMainWindow(parent, flags)
{
	ui.setupUi(this);
	QObject::connect(ui.m_tbarOpenImageButton, SIGNAL(triggered()), this, SLOT(GetFilePath()));
	QObject::connect(ui.m_tbarExitButton, SIGNAL(triggered()), this , SLOT(close()));
}


void vme::GetFilePath()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)"));
	
	if(m_dicomDecoder.ReadFile(path))
	{
		ui.m_2dTab->SetImagePrm(m_dicomDecoder.m_width, m_dicomDecoder.m_height, m_dicomDecoder.m_windowCentre, m_dicomDecoder.m_windowWidth);
		ui.m_2dTab->SendBuffer(m_dicomDecoder.buffer);
		
		DWORD tick1 = GetTickCount();
			ui.m_2dTab->ComputeLookUpTable();
			ui.m_2dTab->CreateVertexColorArr();
		DWORD tick2 = GetTickCount() - tick1;
		//system("pause");
	}
}

vme::~vme(){}

