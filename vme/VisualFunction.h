#include "stdafx.h"
#include <QtGui\qgraphicsview.h>
#include <QtGui\qgraphicsscene.h>

class CVisualFunction : public QGraphicsView{
	
	Q_OBJECT

	public:
		CVisualFunction(QWidget * parent = 0);
		~CVisualFunction(void);

		void InitScene(std::vector<unsigned short>* pBuffer);
		void ShowFunction();


	private:

		QGraphicsScene *m_pScene;

		std::vector<unsigned short>* m_pBuffer;

		void CalcHistogramm();
};

