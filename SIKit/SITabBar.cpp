//
//  SITabBarView.cpp
//  SITabBarView
//
//  Copyright 2010 Silicon Illusions. All rights reserved.
//

#include "SITabBar.h"
#include "SITabBarItem.h"
#include "SINavigationController.h"

#include <QPainter>
#include <iostream>

SITabBar::SITabBar(QWidget *parent)
    :SIView(parent)
{
    setObjectName(QString("tabBar"));
    setGeometry(QRect(0, 0, QApplication::desktop()->width(), QApplication::desktop()->height())); // Tab Bar is full screen by nature as it containts its Views

    qDebug("SITabBar constructor");

    //m_background = 0;
    //setSelectedIndex(0);
    setUserInteractionEnabled(true);

    // Internal Layout
    m_internalLayout = new QVBoxLayout(this);
    m_internalLayout->setObjectName(QString("tabBarInternalLayoutQVBoxLayout"));
    m_internalLayout->setSpacing(0);
    m_internalLayout->setContentsMargins(0, 0, 0, 0);

    // Navigation Controller Container
    m_navigationControllerContainer = new QStackedWidget(this);
    m_navigationControllerContainer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

    // Tab Bar Container
    m_tabBarContainer = new QWidget(this);
    m_tabBarContainer->setObjectName(QString().sprintf("tabBarContainer%p", &m_tabBarContainer));
    m_tabBarContainer->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    m_tabBarContainer->setMaximumWidth(QApplication::desktop()->width());

    // Tab Bar Layout
    m_layout = new QHBoxLayout(m_tabBarContainer);
    m_layout->setObjectName(QString("tabBarQHBoxLayout"));

    // Configure Layout
    setLayout(m_internalLayout);
    m_internalLayout->addWidget(m_navigationControllerContainer);
    m_internalLayout->addWidget(m_tabBarContainer);

}

SITabBar::~SITabBar()
{
    m_tabBarButtons.clear();
    m_defaultHeaderImage.clear();

}

void SITabBar::setBackgroundImage(const QString &fileName)
{
    QPixmap pixmap(fileName);
    m_tabBarContainer->setStyleSheet(QString("QWidget#%1 { background-image: url(%2); }").arg(m_tabBarContainer->objectName()).arg(fileName));
    m_tabBarContainer->setMinimumHeight(pixmap.height());
    m_tabBarContainer->resize(QApplication::desktop()->width(), pixmap.height());

}

SITabBarItem &SITabBar::addTabBarButton(const bool hidden)
{
    //qDebug("SITabBar addTabBarButton");

    // Create
    SITabBarItem *newButton = new SITabBarItem(m_tabBarButtons.count(), this);
    SINavigationController *newController = new SINavigationController(this);

    // Store
    m_tabBarButtons.append(newButton);
    m_tabBarViews.append(newController);

    // Setup the button
    if( !hidden )
    {
        newButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        newButton->setMaximumSize(barItemSize());
    }
    newButton->setAssociatedNavigationController(newController);
    // Setup the Navigation controller
    newController->resize(QApplication::desktop()->width(), QApplication::desktop()->height() - m_tabBarContainer->height());
    newController->setTabBar(this);
    if( !m_defaultHeaderImage.isEmpty() )
        newController->navigationBar().setBackground(m_defaultHeaderImage);

    // Setup nav controller
    m_navigationControllerContainer->addWidget(newController);

    // Connect
    if( !hidden )
        QObject::connect(newButton, SIGNAL(buttonPressed(int)), this, SLOT(tabBarButtonPressed(int)));

    // Layout
    if( !hidden )
        m_layout->addWidget(newButton);

    if( m_tabBarButtons.count() == 1 ) // By this, we assume this is the first Button we add, and thus, we select it
        setSelectedIndex(0);

    //qDebug("SITabBar addTabBarButton - Done");

    return *newButton;

}

void SITabBar::tabBarButtonPressed(int index)
{
    if( !userInteractionEnabled() )
        return;

    setSelectedIndex(index);

}

void SITabBar::setSelectedIndex(int index)
{
    if( !userInteractionEnabled() )
        return;

    qDebug("SITabBar::setSelectedIndex(%d)", index);

    m_selectedIndex = index;

    for( int i = 0; i < m_tabBarButtons.count(); ++i )
        m_tabBarButtons[i]->setSelected(index == i);

    // Show selected tab
    m_navigationControllerContainer->setCurrentIndex(index);

    emit selectionChanged(index);

    repaint();

}

QPointer<SINavigationController> const &SITabBar::navigationControllerAtTab(int index) const
{
    return m_tabBarButtons[index]->associatedNavigationController();
}
