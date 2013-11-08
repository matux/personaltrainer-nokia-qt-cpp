//
//  SITabBarItem.cpp
//  SITabBarItem
//
//  Copyright 2010 Silicon Illusions. All rights reserved.
//

#include "sitabbaritem.h"

#include <iostream>
#include <QtGui>

SITabBarItem::SITabBarItem(int index, QWidget *parent)
    :SIView(parent)
{
    m_icon = 0;
    m_iconSelected = 0;
    m_isSelected = false;
    m_index = index;

}

SITabBarItem::~SITabBarItem()
{

}

void SITabBarItem::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);
    if( isSelected() )
    {
        if( m_iconSelected.isNull() )
            painter.drawPixmap(rect().center() - m_icon.rect().center(), m_icon);
        else if( !m_icon.isNull() )
            painter.drawPixmap(rect().center() - m_icon.rect().center(), m_iconSelected);
    }
    else if( !m_icon.isNull() )
        painter.drawPixmap(rect().center() - m_icon.rect().center(), m_icon);

}

void SITabBarItem::mousePressEvent(QMouseEvent *mouseEvent)
{
    qDebug("SITabBarItemView::mousePressEvent - index: %d", m_index);

    // Send button pressed signal
    emit buttonPressed(m_index);

    QWidget::mousePressEvent(mouseEvent);

}
