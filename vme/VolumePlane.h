#pragma once

#include <QtOpenGL/QGLWidget>


class CVolumePlane: public QGLWidget
{
public:
	CVolumePlane(QWidget *parent = 0);
	~CVolumePlane(void);

protected:
	 void paintEvent(QPaintEvent *event);
};

