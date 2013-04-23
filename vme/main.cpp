#include "stdafx.h"
#include "vme.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	vme w;
	w.show();
	return a.exec();
}
