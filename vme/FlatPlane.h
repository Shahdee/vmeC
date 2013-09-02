#pragma once
#include <QtOpenGL/QGLWidget>


class CFlatPlane: public QGLWidget
{
	Q_OBJECT

public:
	CFlatPlane(QWidget *parent = 0);
	~CFlatPlane(void);

	void Axis();
	void SetImage();
	void SetImagePrm(const int w, const int h, const double center, const double width);
	void SendBuffer(std::vector<unsigned short>*);
	void ComputeLookUpTable(); 
	void CreateVertexColorArr();
	void FlushBuffers();

protected:
	void showEvent(QShowEvent *event);

	//reimplemented from QGLWidget
    void initializeGL(); 
    void resizeGL(int width, int height);
    void paintGL();

private:
	int m_pmWidth;
	int m_pmHeight;
	double m_winMin;
	double m_winMax;
	bool m_bShowImage;

	static float* pvertexArray;
	static float* pcolorArray;
	static std::vector<unsigned short>* buffer;
	static std::vector<float>* lut;
};

