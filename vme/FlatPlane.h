#pragma once
#include <QtOpenGL/QGLWidget>


class CFlatPlane: public QGLWidget
{
	Q_OBJECT

public:
	CFlatPlane(QWidget *parent = 0);
	~CFlatPlane(void);

	void Axis();
	void SetImagePrm(const int w, const int h, const double center, const double width);
	void SendImageBuffer(std::vector<unsigned short>*);
	void ComputeLookUpTable(); 
	void CreateVertexColorArr();
	void FlushBuffers(bool bTF = false);
	void ResetImageBufferPtr();

protected:
	void showEvent(QShowEvent *event);

	//reimplemented from QGLWidget
    void initializeGL(); 
    void resizeGL(int width, int height);
    void paintGL();

private:
	int m_iWidth;
	int m_iHeight;
	double m_dWinMin;
	double m_dWinMax;
	double m_dWinCenter;
	double m_dWinWidth;

	int m_iChangeWidth;
	int	m_iChangeCenter;

	bool m_bShowImage;

	static float* pvertexArray;
	static float* pcolorArray;
	static std::vector<unsigned short>* m_pImageBuffer;
	static std::vector<float>* lut;

	QPoint m_lastPress;
	bool m_bRightBtnPressed;

	void ComputeChangeVals();

	void mousePressEvent(QMouseEvent * ev);
	void mouseReleaseEvent(QMouseEvent * ev);
	void mouseMoveEvent(QMouseEvent * ev);
};

