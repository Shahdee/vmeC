#include "stdafx.h"
#include "vme.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QRect screenSize = a.desktop()->screenGeometry();
	vme w;
	w.show();
	return a.exec();
}
