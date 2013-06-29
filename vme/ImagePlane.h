#pragma once


class CImagePlane : public QTabWidget
{
	Q_OBJECT

public:
	CImagePlane(QWidget *parent = 0);
	~CImagePlane(void);

 protected:
     void paintEvent(QPaintEvent *event);


 private:


	
};

