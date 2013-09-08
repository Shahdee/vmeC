#ifndef VME_H
#define VME_H

#include <QtGui/QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsview>
#include "ui_vme.h"

#include "DicomDecoder.h"

class vme : public QMainWindow
{
	Q_OBJECT

public:
	vme(QWidget *parent = 0, Qt::WFlags flags = 0);

	~vme();

	CDicomDecoder m_dicomDecoder;

private:
	Ui::vmeClass ui;

private slots:

	void GetPathAndReadSeveralFiles();

	void GetPathAndReadFile();

public:

};

#endif // VME_H
