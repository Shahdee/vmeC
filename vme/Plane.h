#pragma once

#include <QtOpenGL>

class CPlane: public QGLWidget
{
	Q_OBJECT

public:
	CPlane(QWidget* parent);
	~CPlane(void);

private:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();
};

