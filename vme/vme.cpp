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
	if(obj.ReadFile(path))
	{

	}
}

vme::~vme(){}

