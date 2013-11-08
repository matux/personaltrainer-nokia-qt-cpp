#include "SISwitchButton.h"

SISwitchButton::SISwitchButton(QWidget *parent)
    :SIButton(parent),
    m_state(SISwitchButton::OFF)
{

}

SISwitchButton::~SISwitchButton()
{

}

void SISwitchButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // Get the correct Pixmap
    const QPixmap &buttonPixMap = m_state == SISwitchButton::ON ? pressedStatePix() : normalStatePix();

    // Setup the position
    QPoint pos;
    if( alignment() & Qt::AlignLeft )
        pos.setX(0);
    else
        pos.setX((geometry().width() >> 1) - (buttonPixMap.width() >> 1));

    if( alignment() & Qt::AlignTop )
        pos.setY(0);
    else
        pos.setY((geometry().height() >> 1) - (buttonPixMap.height() >> 1));

    // Draw
    painter.drawPixmap(pos, buttonPixMap);

}

void SISwitchButton::mousePressEvent(QMouseEvent *e)
{
     switchState();
     SIButton::mousePressEvent(e);
}

void SISwitchButton::switchState()
{
    m_state = (m_state == SISwitchButton::ON) ? SISwitchButton::OFF : SISwitchButton::ON;
    emit stateSwitched();
}
