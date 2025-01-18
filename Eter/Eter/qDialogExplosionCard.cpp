#include "qDialogExplosionCard.h"

qDialogExplosionCard::qDialogExplosionCard(QWidget* parent, std::shared_ptr<ExplosionCard>& explCard, int boardSize) :
    QDialog(parent), m_explCard{ explCard },
    m_pixmapEmptyExplosion{ QDir::currentPath() + QString("/textures/explosion_blank.jpg") },
    m_size{ boardSize },
    m_pixmapRemove{ QDir::currentPath() + QString("/textures/explosionSprite_0.png") },
    m_pixmapReturn{ QDir::currentPath() + QString("/textures/explosionSprite_1.png") },
    m_pixmapHole{ QDir::currentPath() + QString("/textures/hole_sprite.png") },
    m_CELL_WIDTH{ m_WIDTH / m_size },
    m_CELL_HEIGTH{ m_HEIGTH / m_size }
{
    setFixedSize(m_WIDTH , m_HEIGTH+60);
    setupDialog();
    updateImage();
}

void qDialogExplosionCard::setupDialog()
{
    setWindowTitle("Explosion Card");
    setModal(true);

    m_labelCard = new QLabel(this);
    m_labelCard->setScaledContents(true);
    m_labelCard->setFixedSize(m_WIDTH, m_HEIGTH);

    m_layoutLabel = new QVBoxLayout();
    m_layoutLabel->addWidget(m_labelCard);

    m_buttonCancelCard = new QPushButton("Cancel", this);
    m_buttonPlayCard = new QPushButton("Play", this);
    m_buttonRotateCard = new QPushButton("Rotate", this);

    m_layoutButtons = new QHBoxLayout();
    m_layoutButtons->addWidget(m_buttonCancelCard);
    m_layoutButtons->addWidget(m_buttonPlayCard);
    m_layoutButtons->addWidget(m_buttonRotateCard);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(m_layoutLabel);
    mainLayout->addLayout(m_layoutButtons);
    setLayout(mainLayout);

    connect(m_buttonRotateCard, &QPushButton::clicked, this, &qDialogExplosionCard::rotateCard);
    connect(m_buttonCancelCard, &QPushButton::clicked, this, &qDialogExplosionCard::rejectCard);
    connect(m_buttonPlayCard, &QPushButton::clicked, this, &qDialogExplosionCard::acceptCard);
}

void qDialogExplosionCard::acceptCard()
{
    emit acceptExplCard(*m_explCard);
    accept();
}

void qDialogExplosionCard::rejectCard()
{
    emit rejectExlpCard(*m_explCard);
    reject();
}

void qDialogExplosionCard::updateImage()
{
    QImage matrixImage(m_size * m_CELL_WIDTH, m_size * m_CELL_HEIGTH, QImage::Format_ARGB32);
    matrixImage.fill(Qt::transparent);

    QPainter painter(&matrixImage);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setPen(Qt::black);

    QPixmap scaledBackground = m_pixmapEmptyExplosion.scaled(m_size * m_CELL_WIDTH, m_size * m_CELL_HEIGTH, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, scaledBackground);

    const explMap& mapExpl = m_explCard->GetExplosionMap();

    for (const auto& card : mapExpl)
    {
        auto& [position, type] = card;
        auto& [row, col] = position;
        QRect cellRect(col * m_CELL_WIDTH, row * m_CELL_HEIGTH, m_CELL_WIDTH, m_CELL_HEIGTH);

        QPixmap scaledPixmap;
        switch (type)
        {
        case ReturnRemoveOrHoleCard::RemoveCard:
            scaledPixmap = m_pixmapRemove.scaled(m_CELL_WIDTH, m_CELL_HEIGTH, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            painter.drawPixmap(cellRect, scaledPixmap);
            break;
        case ReturnRemoveOrHoleCard::ReturnCard:
            scaledPixmap = m_pixmapReturn.scaled(m_CELL_WIDTH, m_CELL_HEIGTH, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            painter.drawPixmap(cellRect, scaledPixmap);
            break;
        case ReturnRemoveOrHoleCard::HoleCard:
            scaledPixmap = m_pixmapHole.scaled(m_CELL_WIDTH, m_CELL_HEIGTH, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            painter.drawPixmap(cellRect, scaledPixmap);
            break;
        default:
            painter.setBrush(Qt::white);
            painter.setPen(Qt::black);
            painter.drawRect(cellRect);
            break;
        }
    }

    painter.end();

    m_labelCard->setPixmap(QPixmap::fromImage(matrixImage));
}

void qDialogExplosionCard::rotateCard()
{
    m_explCard->RotateToRight(m_size);
    updateImage();
}
