#pragma once

#include <QtOpenGL/QGLWidget>


class CVolumePlane: public QGLWidget
{
public:
	CVolumePlane(QWidget *parent = 0);
	~CVolumePlane(void);

	void SetImageSize(unsigned short width, unsigned short height);

	//template<class T>
	void FillPixelMap(/*std::vector<T>**/);

protected:
	 void paintEvent(QPaintEvent *event);


private:
	QLabel* m_label;
	int m_pmWidth;
	int m_pmHeight;
};

