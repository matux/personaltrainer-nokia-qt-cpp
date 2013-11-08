#include "headerview.h"

#include <iostream>

HeaderView::HeaderView(QWidget *parent)
    :SIView(parent)
{
    initUi();
}

HeaderView::HeaderView(const QString &titleImageFilename, QWidget *parent)
    :SIView(parent)
{
    initUi();
    m_titlePixmap = new QPixmap(titleImageFilename);
}

HeaderView::~HeaderView()
{
    delete m_titlePixmap;
}

void HeaderView::initUi()
{
    setObjectName(QString("headerView"));
    setGeometry(QRect(0, 0, 360, 130));

    m_userInteraction = true;

    m_backButton = new SIButton(this);
    m_backButton->setObjectName(QString::fromUtf8("backButton"));
    m_backButton->setGeometry(QRect(13, 8, 96, 96));
    m_backButton->setNormalStatePix(":/images/res/header_boton_volver.png");
    m_backButton->setPressedStatePix(":/images/res/header_boton_volver_on.png");
    QObject::connect(m_backButton, SIGNAL(clicked()), this, SLOT(backPressedSlot()));

    m_homeButton = new SIButton(this);
    m_homeButton->setObjectName(QString::fromUtf8("backButton"));
    m_homeButton->setGeometry(QRect(278, 8, 96, 96));
    m_homeButton->setAlignment(Qt::AlignTop|Qt::AlignRight);
    m_homeButton->setNormalStatePix(":/images/res/header_boton_home.png");
    m_homeButton->setPressedStatePix(":/images/res/header_boton_home_on.png");
    QObject::connect(m_homeButton, SIGNAL(clicked()), this, SLOT(homePressedSlot()));

    m_titlePixmap = NULL;

}

void HeaderView::paintEvent(QPaintEvent *paintEvent)
{
    // Draw us
    QPainter painter(this);
    if( m_titlePixmap && !m_titlePixmap->isNull() )
        painter.drawPixmap(0, 56, *m_titlePixmap);

}

void HeaderView::homePressedSlot()
{
    if( !m_userInteraction )
        return;

    emit homePressed();

    repaint();
}

void HeaderView::backPressedSlot()
{
    if( !m_userInteraction )
        return;

    if( !navigationController()->popView() )
        homePressedSlot();

    repaint();
}

void HeaderView::setTitleImageFilename(const QString &fileName)
{
    if( m_titlePixmap )
        delete m_titlePixmap;

    m_titlePixmap = new QPixmap(fileName);

}
