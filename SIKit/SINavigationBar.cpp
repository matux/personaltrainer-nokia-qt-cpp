//
//  SINavigationBar.cpp
//  SINavigationBar
//
//  Copyright 2010 Silicon Illusions. All rights reserved.
//

#include "SINavigationBar.h"

SINavigationBar::SINavigationBar(QWidget *parent)
    :QWidget(parent)
{
    setObjectName(QString().sprintf("SINavigationBar%p", parent));

    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString().sprintf("%p", centralWidget));

}
/*
SINavigationBar::~SINavigationBar()
{

}
*/
void SINavigationBar::setBackground(const QString &fileName)
{
    QPixmap pixmap(fileName);

    resize(QApplication::desktop()->width(), pixmap.height());
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setMinimumWidth(QApplication::desktop()->width());
    setMinimumHeight(pixmap.height());

    centralWidget->setStyleSheet(QString("QWidget#%1 { background-image: url(%2); }").arg(centralWidget->objectName()).arg(fileName));
    centralWidget->resize(size());
    centralWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    centralWidget->setMinimumWidth(QApplication::desktop()->width());
    centralWidget->setMinimumHeight(pixmap.height());

}

void SINavigationBar::addSubview(QWidget *subview)
{
    subview->setParent(centralWidget);
}
