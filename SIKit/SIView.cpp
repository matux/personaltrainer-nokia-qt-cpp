//
//  SIView.cpp
//  SIView
//
//  Copyright 2010 Silicon Illusions. All rights reserved.
//

#include "siview.h"

#include <QPainter>
#include <iostream>

SIView::SIView(QWidget *parent)
    :QWidget(parent),
    m_tabBar(NULL),
    m_navigationController(NULL)
{
    setObjectName(QString().sprintf("SIView%p", this));

    m_centralWidget = new QWidget(this);
    m_centralWidget->setObjectName(QString().sprintf("%p", m_centralWidget));

}

SIView::~SIView()
{

}

void SIView::setBackgroundImage(const QString &filename)
{
    QPixmap pm(filename);
    resize(pm.width(), pm.height());
    m_centralWidget->setStyleSheet(QString("QWidget#%1 { background-image: url(%2); }").arg(m_centralWidget->objectName()).arg(filename));
    m_centralWidget->resize(pm.width(), pm.height());
    //m_centralWidget->setMinimumWidth(pm.height());
    //m_centralWidget->setMinimumHeight(pm.height());

}

void SIView::showEvent(QShowEvent *showEvent)
{
    emit viewWillAppear();
}

void SIView::hideEvent(QHideEvent *hideEvent)
{
    emit viewWillDisappear();
}
