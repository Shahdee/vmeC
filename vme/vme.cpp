#include "stdafx.h"
#include "vme.h"
#include <QtGui>


vme::vme(QWidget *parent, Qt::WFlags flags) : QMainWindow(parent, flags)
{
	m_ui.setupUi(this);
	QObject::connect(m_ui.m_tbarOpeStudyButton, SIGNAL(triggered()), this, SLOT(GetPathAndReadSeveralFiles()));
	QObject::connect(m_ui.m_tbarOpenImageButton, SIGNAL(triggered()), this, SLOT(GetPathAndReadFile()));
	QObject::connect(m_ui.m_tbarExitButton, SIGNAL(triggered()), this , SLOT(close()));
	QObject::connect(m_ui.m_vis3D
}

void vme::GetPathAndReadSeveralFiles(){

	QStringList afilePaths = QFileDialog::getOpenFileNames(this, tr("Selected Dicom files"), "");

	if(afilePaths.size() > 0){
		QStringList::iterator it = afilePaths.begin();
		
		m_dicomDecoder.ClearData();

		if(vme::m_v3dBuffer.size() > 0)
		{
			for(int i=0; i< vme::m_v3dBuffer.size(); i++){
				delete (vme::m_v3dBuffer[i]);
			}
			m_ui.m_2dStackTab->ResetBufferPtr();
		}
		//DWORD tick1 = GetTickCount();

		while(it != afilePaths.end()) {

			if(m_dicomDecoder.ReadFile((*it))){
				
				vme::m_v3dBuffer.push_back(m_dicomDecoder.buffer);
			
				if( it != (afilePaths.end()-1))
					m_dicomDecoder.ClearData();
				else{
					m_ui.m_2dStackTab->FlushBuffers();
					m_ui.m_2dStackTab->SetImagePrm(m_dicomDecoder.m_width, m_dicomDecoder.m_height, m_dicomDecoder.m_windowCentre, m_dicomDecoder.m_windowWidth);
					m_ui.m_2dStackTab->SendBuffer(m_dicomDecoder.buffer);
					m_ui.m_2dStackTab->ComputeLookUpTable();
					m_ui.m_2dStackTab->CreateVertexColorArr();

					m_ui.m_2dStackTab->updateGL();
				}
			}
			++it;
		}
		//DWORD tick2 = GetTickCount() - tick1;
	}
}

void vme::GetPathAndReadFile()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open Dicom image"), "", tr("Files (*.*)"));
	
	if(path.size()>0)
	{
		m_dicomDecoder.ClearData();

		if(m_dicomDecoder.ReadFile(path))
		{
			if(vme::m_v3dBuffer.size() > 0)
			{
				for(int i=0; i< vme::m_v3dBuffer.size(); i++){

					delete (vme::m_v3dBuffer.at(i));
					vme::m_v3dBuffer.at(i) = NULL;
				}
				vme::m_v3dBuffer.erase(vme::m_v3dBuffer.begin(), vme::m_v3dBuffer.end());
				m_ui.m_2dStackTab->ResetBufferPtr();
			}
			m_ui.m_2dStackTab->FlushBuffers();
			m_ui.m_2dStackTab->SetImagePrm(m_dicomDecoder.m_width, m_dicomDecoder.m_height, m_dicomDecoder.m_windowCentre, m_dicomDecoder.m_windowWidth);
			m_ui.m_2dStackTab->SendBuffer(m_dicomDecoder.buffer);
			m_ui.m_2dStackTab->ComputeLookUpTable();
			m_ui.m_2dStackTab->CreateVertexColorArr();

			m_ui.m_2dStackTab->updateGL();
		}
	}
}

vme::~vme(){}

std::vector<std::vector<unsigned short>*> vme::m_v3dBuffer;

