#pragma once
#include <QtOpenGL/QGLWidget>


class CFlatPlane: public QGLWidget
{
	Q_OBJECT

public:
	CFlatPlane(QWidget *parent = 0);
	~CFlatPlane(void);

	 int xRotation() const { return m_xRot; }
     int yRotation() const { return m_yRot; }
     int zRotation() const { return m_zRot; }

protected:

	//void paintEvent(QPaintEvent *event);

	void showEvent(QShowEvent *event);

	//reimplemented from QGLWidget
    void initializeGL(); 
    void resizeGL(int width, int height);
    void paintGL();

private:
	void setupViewport(const int & width, const int & height);
	void drawSurface(QPainter* painter, QPaintEvent* event);

	int m_xRot;
	int m_yRot;
	int m_zRot;

public slots:
	 void setXRotation(const int & angle);
     void setYRotation(const int & angle);
     void setZRotation(const int & angle);

};

