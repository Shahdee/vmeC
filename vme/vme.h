#ifndef VME_H
#define VME_H

#include <QtGui/QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsview>
#include "ui_vme.h"
#include <QtGui>

#include "DicomDecoder.h"

class vme : public QMainWindow
{
	Q_OBJECT

public:
	vme(QWidget *parent = 0, Qt::WFlags flags = 0);

	~vme();

	CDicomDecoder m_dicomDecoder;

	static std::vector<std::vector<unsigned short>*> m_v3dBuffer;

private:
	Ui::vmeClass m_ui;

	QString m_sfilePath[];
	
private slots:

	void GetPathAndReadSeveralFiles();

	void GetPathAndReadFile();

public:

};

#endif // VME_H
