#include "stdafx.h"
#include "vme.h"
#include <QtGui>


vme::vme(QWidget *parent, Qt::WFlags flags) : QMainWindow(parent, flags)
{
	ui.setupUi(this);
	QObject::connect(ui.m_tbarOpeStudyButton, SIGNAL(triggered()), this, SLOT(GetPathAndReadSeveralFiles());
	QObject::connect(ui.m_tbarOpenImageButton, SIGNAL(triggered()), this, SLOT(GetPathAndReadFile()));
	QObject::connect(ui.m_tbarExitButton, SIGNAL(triggered()), this , SLOT(close()));
}

void vme::GetPathAndReadSeveralFiles(){

	QString path = QFileDialog::getExistingDirectory(this, tr("Open Dicom folder"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	m_dicomDecoder.ClearData();


}

void vme::GetPathAndReadFile()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open Dicom image"), "", tr("Files (*.*)"));
	
	m_dicomDecoder.ClearData();

	if(m_dicomDecoder.ReadFile(path))
	{
		ui.m_2dStackTab->FlushBuffers();
		ui.m_2dStackTab->SetImagePrm(m_dicomDecoder.m_width, m_dicomDecoder.m_height, m_dicomDecoder.m_windowCentre, m_dicomDecoder.m_windowWidth);
		ui.m_2dStackTab->SendBuffer(m_dicomDecoder.buffer);
		ui.m_2dStackTab->ComputeLookUpTable();
		ui.m_2dStackTab->CreateVertexColorArr();
	}
}

vme::~vme(){}

