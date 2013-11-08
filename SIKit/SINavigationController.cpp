//
//  SINavigationController.h
//  SINavigationController
//
//  Copyright 2010 Silicon Illusions. All rights reserved.
//

#include "SINavigationController.h"
#include "SINavigationBar.h"
#include "SIView.h"

#include <iostream>

SINavigationController::SINavigationController(QWidget *parent)
    :QWidget(parent),
     m_tabBar(NULL)
{
    setObjectName(QString().sprintf("SINavigationController%p", this));
    setGeometry(0, 0, QApplication::desktop()->width(), QApplication::desktop()->height());

    // Layout components
    m_navigationBar = new SINavigationBar(this);
    m_stackedWidget = new QStackedWidget(this);

    // Layout
    m_verticalLayout = new QVBoxLayout(this);
    m_verticalLayout->setSpacing(0);
    m_verticalLayout->setContentsMargins(0, 0, 0, 0);
    m_verticalLayout->addWidget(m_navigationBar);
    m_verticalLayout->addWidget(m_stackedWidget);

    qDebug("SINavigationController::SINavigationController (%s) Created.", objectName().toAscii().constData());

}

SINavigationController::~SINavigationController()
{

}

int SINavigationController::addView(SIView *view)
{
    // First, set up the View because adding the Widget
    // unleashes a series of events that the View may
    // catch, thus it's better if at that point the
    // View is already set up.
    view->setNavigationController(this);
    view->setTabBar(tabBar());

    // Then we add it
    int index = m_stackedWidget->addWidget(view);

    return index;
}

void SINavigationController::removeViewAt(int index)
{
    QWidget *w = m_stackedWidget->widget(index);
    if( !w ) return;
    m_stackedWidget->removeWidget(w);
    w->setParent(NULL);
    delete w;

}

void SINavigationController::removeViewsInCascadeFrom(int index)
{
    if( index >= m_stackedWidget->count() )
        return;

    for( int j = m_stackedWidget->count() - 1; j >= index; --j )
        removeViewAt(j);
}

void SINavigationController::pushView(SIView *view)
{
    showViewAtIndex(addView(view));
}

QWidget *SINavigationController::popView()
{
    if( m_stackedWidget->indexOf(m_stackedWidget->currentWidget()) == 0 )
        return NULL;

    QWidget *w = m_stackedWidget->currentWidget();
    m_stackedWidget->removeWidget(w);
    w->setParent(NULL);
    delete w;
    //if( m_stackedWidget->currentIndex() > 0 )
    //    m_stackedWidget->setCurrentIndex(m_stackedWidget->currentIndex() - 1);

    return m_stackedWidget->currentWidget();

}

QWidget *SINavigationController::popToRootView()
{
    QWidget *rootView = NULL;
    while( (rootView = popView()) != NULL )
        continue;
    return rootView;
}
