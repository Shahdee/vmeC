#include "stdafx.h"
#include "vme.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	vme w;
	w.showMaximized();
	return a.exec();
}
