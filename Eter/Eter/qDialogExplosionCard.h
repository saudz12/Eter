#pragma once
#include "qdialog.h"
#include "qpointer.h"
#include "qlabel.h"
#include "qimage.h"
#include "qpushbutton.h"
#include "qpixmap.h"
#include "qdir.h"
#include "qboxlayout.h"
#include "qpainter.h"

#include <memory>

#include "ExplosionCard.h"

class qDialogExplosionCard : public QDialog
{
	Q_OBJECT
public:
	explicit qDialogExplosionCard(QWidget* parent, std::shared_ptr<ExplosionCard>& explCard, int boardSize);
signals:
	void acceptExplCard(ExplosionCard card);
	void rejectExlpCard(ExplosionCard card);
private:
	///functions
	void updateImage();
	void setupDialog();
	void showImage();
	///members
	std::shared_ptr<ExplosionCard> m_explCard;


	QPointer<QVBoxLayout> m_layoutLabel;
	QPointer<QHBoxLayout> m_layoutButtons;
	QPointer<QLabel> m_labelCard;
	QImage* m_imageCard;
	QPointer<QPushButton> m_buttonPlayCard;
	QPointer<QPushButton> m_buttonCancelCard;
	QPointer<QPushButton> m_buttonRotateCard;

	QPixmap m_pixmapEmptyExplosion;
	QPixmap m_pixmapRemove;
	QPixmap m_pixmapReturn;
	QPixmap m_pixmapHole;
	QPixmap m_nothingLabel;

	const int m_WIDTH = 240, m_HEIGTH = 240;
	const int m_size;
	const int m_CELL_WIDTH;
	const int m_CELL_HEIGTH;
public slots:
	void rotateCard();
	void acceptCard();
	void rejectCard();
};

